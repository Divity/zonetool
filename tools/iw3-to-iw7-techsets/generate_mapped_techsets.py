#!/usr/bin/env python3
"""Generate the IW3/IW5 -> IW7 techset mapping from shipped data.

The table in src/IW5/Dumper/IW7/Assets/Material.cpp used to be written by hand, one row at a
time, and the cost showed: 34 rows against 810 structured IW3 techsets, and several rows
degraded further than they needed to, so every blend material in a converted map lost its
normal and specular maps.

The safety rule that motivated the hand table is real. A technique binds its arguments by
scanning the material's texture table for each hash with no bounds check, so pointing a
material at a technique whose slot set does not match is a crash rather than a glitch. But
that rule is checkable rather than a matter of judgement: every IW7 techset's required slot
set can be read straight off the materials that ship on it.

  IW7 techsets referenced by stock materials : 7398
     with exactly ONE slot signature         : 7319  (98.9%)
     stock materials covered                 : 54708

So a candidate is accepted only when its slot signature, taken from stock, is exactly the set
our converter would emit for that IW3 techset. That makes the property structural.

Inputs, all read-only:
  --iw3     CoD4 install, for raw/techsets/*.techset      (the 2549 real IW3 names)
  --iw7     IW7 install, for zonetool_paths/*/materials   (stock slot signatures)

Output is the C++ initialiser body for `mapped_techsets`, on stdout.
"""

import argparse
import collections
import glob
import json
import os
import re

SLOT_COLOUR = (2, 2695565377)
SLOT_NORMAL = (5, 1507003663)
SLOT_SPEC = (8, 887934131)

SLOT_DETAIL = (3, 3948059469)

PACKED_COLOUR = (14, 2695565377)
PACKED_NORMAL = (15, 1507003663)

PACKED_ALPHA = (16, 2771134132)

BLEND = {
    "r0": "replace",
    "b0": "ndw_blend",
    "t0": "atest",
}

FEATURE_SLOT = {
    "c0": SLOT_COLOUR,
    "n0": SLOT_NORMAL,
    "s0": SLOT_SPEC,
    "d0": SLOT_DETAIL,
}

IW3_NAME = re.compile(r"^(mc|wc)_(.*?)([rbt]0)((?:[a-z]\d)*)$")
FEATURE_TOKEN = re.compile(r"[a-z]\d")


def iw7_slot_signatures(iw7_root):
    """techset -> (dominant slot signature, signature count, stock usage count)."""
    sigs = collections.defaultdict(collections.Counter)
    pattern = os.path.join(iw7_root, "zonetool_paths", "*", "materials", "**", "*.json")
    for path in glob.glob(pattern, recursive=True):
        try:
            with open(path, "r", encoding="utf-8", errors="replace") as handle:
                material = json.load(handle)
        except Exception:
            continue
        techset = material.get("techniqueSet->name")
        if not techset:
            continue
        table = material.get("textureTable") or []
        signature = frozenset(
            (entry.get("semantic"), entry.get("typeHash"))
            for entry in table
            if isinstance(entry, dict)
        )
        sigs[techset][signature] += 1

    out = {}
    for techset, counter in sigs.items():
        dominant, _ = counter.most_common(1)[0]
        out[techset] = (dominant, len(counter), sum(counter.values()))
    return out


DEAD_MIDDLES = ("hsm",)


def decode_iw3(name):
    """(prefix, blend letter, ordered feature tokens) or None if it is not a structured name."""
    match = IW3_NAME.match(name)
    if not match:
        return None
    prefix, middle, blend, features = match.groups()
    if blend not in BLEND:
        return None
    if any(("_%s_" % dead) in ("_%s" % middle) for dead in DEAD_MIDDLES):
        return None
    return prefix, blend, FEATURE_TOKEN.findall(features)


def wanted_signature(tokens):
    """The slot set our converter emits for a material carrying these IW3 features."""
    return frozenset(FEATURE_SLOT[t] for t in tokens if t in FEATURE_SLOT)


FILLABLE = {
    SLOT_COLOUR: "slot_colour",
    SLOT_NORMAL: "slot_normal",
    SLOT_SPEC: "slot_spec",
    SLOT_DETAIL: "slot_detail",
    (9, 2771134132): "slot_occl",
    (2, 3054311504): "slot_layer1",
}


def canonical(prefix, blend, kept):
    family = "mo" if prefix == "mc" else "wc"
    ordered = [t for t in ("c0", "s0", "n0", "d0") if t in kept]
    return "%s_l_sm_%s_i0%s" % (family, BLEND[blend], "".join(ordered))


def choose(prefix, blend, tokens, sigs):
    """Pick the IW7 technique that binds the most of this material's real textures.

    The rule is not "the slot sets are equal". A technique binds a fixed set of hashes, and the
    converter already fills any it has no texture for with a default ($identitynormalmap, $white
    ...), so a candidate is safe whenever every slot it binds is one we can fill. What we are
    choosing between is how much of the source survives.

    So: compose the canonical name and take the FIRST reachable one, degrading features only when
    the fuller spelling does not exist. Scoring candidates instead looked more principled and was
    worse - `mo_l_sm_replace_i0c0s0` also binds a normal slot (filled with $identitynormalmap), so
    it scored level with `mo_l_sm_replace_i0c0s0n0` and won on stock usage, quietly dropping the
    real normal map. Least degradation is the whole ranking. That keeps `mc_l_sm_b0c0n0s0` on
    `mo_l_sm_ndw_blend_i0c0s0n0` (all three) instead of `mo_l_sm_ndw_blend_i0c0` (colour only),
    which is what the hand table did and why converted blend materials lost their normal and
    specular maps.

    Composing rather than searching every signature-compatible name is deliberate: ranking by
    stock usage picked `mo_l_sm_ndw_blend_i0c0s0n0_svp_scred_vm` over the plain name, and an
    unlit technique for a lit material. Both are slot-compatible and both are wrong.
    """
    have = [t for t in ("c0", "s0", "n0", "d0") if t in tokens]
    for drop in range(len(have) + 1):
        kept = have[: len(have) - drop] if drop else have
        candidate = canonical(prefix, blend, kept)
        entry = sigs.get(candidate)
        if entry is None:
            continue
        stock_sig, sig_count, _usage = entry
        if any(slot not in FILLABLE for slot in stock_sig):
            continue
        return candidate, stock_sig, sig_count
    return None, None, 0


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--iw3", required=True, help="CoD4 install root")
    parser.add_argument("--iw7", required=True, help="IW7 install root")
    parser.add_argument("--seed", help="also take IW3 techset names from this source file's "
                                       "existing table (IW5-only names have no .techset on disk)")
    parser.add_argument("--report", action="store_true", help="write a summary to stderr")
    args = parser.parse_args()

    sigs = iw7_slot_signatures(args.iw7)

    names = set(
        os.path.basename(p)[: -len(".techset")]
        for p in glob.glob(os.path.join(args.iw3, "raw", "techsets", "*.techset"))
    )

    if args.seed:
        with open(args.seed, "r", encoding="utf-8", errors="replace") as handle:
            body = handle.read()
        start = body.find("mapped_techsets =")
        end = body.find("mapped_techsets_effect_vertlit")
        if start >= 0:
            segment = body[start:end if end > start else None]
            for key in re.findall(r'\{"([^"]+)",\s*(?:\{"|make_techset_map\(|\w+\})', segment):
                names.add(key)

    names = sorted(names)

    rows = []
    required = {}
    stats = collections.Counter()
    for name in names:
        decoded = decode_iw3(name)
        if not decoded:
            stats["unstructured"] += 1
            continue
        prefix, blend, tokens = decoded
        signature = wanted_signature(tokens)
        if not signature:
            stats["no slots"] += 1
            continue

        regular, stock_sig, sig_count = choose(prefix, blend, tokens, sigs)
        if not regular:
            stats["unreachable"] += 1
            continue
        if sig_count > 1:
            stats["ambiguous signature"] += 1
        required[regular] = stock_sig

        packed = ""
        packed_alpha = ""
        if BLEND[blend] == "replace":
            packed = regular + "p0"
            packed_sig = sigs.get(packed)
            want = {PACKED_COLOUR, PACKED_NORMAL}
            if "d0" in regular:
                want.add(SLOT_DETAIL)
            if packed_sig is None or packed_sig[0] != frozenset(want):
                packed = ""
        else:
            packed_alpha = regular + "pa0"
            pa_sig = sigs.get(packed_alpha)
            want = {PACKED_COLOUR, PACKED_NORMAL, PACKED_ALPHA}
            if "d0" in regular:
                want.add(SLOT_DETAIL)
            if pa_sig is None or pa_sig[0] != frozenset(want):
                packed_alpha = ""

        rows.append((name, regular, packed, packed_alpha))
        stats["mapped"] += 1
        if packed:
            stats["with packed"] += 1
        if packed_alpha:
            stats["with packed alpha"] += 1

    width = max((len(r[0]) for r in rows), default=0) + 3
    for name, regular, packed, packed_alpha in rows:
        target = '{"%s"' % regular
        if packed_alpha:
            target += ', "", "", "%s"' % packed_alpha
        elif packed:
            target += ', "", "%s"' % packed
        target += "}"
        print('\t\t\t{"%s",%s%s},' % (name, " " * (width - len(name)), target))

    print()
    print("				// generated: the slots each target binds, read off the stock materials that")
    print("				// ship on it. A technique binds by hash with no bounds check, so any slot the")
    print("				// source has no texture for has to be filled rather than left out.")
    for techset in sorted(required):
        names = [FILLABLE[s] for s in sorted(required[techset])]
        print('					{"%s",%s{%s}},'
              % (techset, " " * max(1, 38 - len(techset)), ", ".join(names)))

    if args.report:
        import sys
        for key in ("mapped", "with packed", "with packed alpha", "no exact slot match",
                    "no slots", "unstructured"):
            print("%-22s %d" % (key, stats[key]), file=sys.stderr)


if __name__ == "__main__":
    main()
