"""
Decoder for hknpCompressedMeshShape / hknpCompressedMeshShapeData as IW7 ships them
(hk_2014.2.5-r1, x64 little-endian).

Every offset here comes from IW7's own runtime hkClass tables -- see
docs/iw7-havok-reflection.txt. Nothing is inferred from another SDK version.

The point of this module is to turn a shipped .hkx back into triangles so the encoding
can be checked against known-good data. It is the inverse of the builder that still has
to be written.
"""

import struct
from dataclasses import dataclass, field
from typing import List, Optional, Tuple

def u8(d, o):   return d[o]
def u16(d, o):  return struct.unpack_from("<H", d, o)[0]
def u32(d, o):  return struct.unpack_from("<I", d, o)[0]
def i32(d, o):  return struct.unpack_from("<i", d, o)[0]
def u64(d, o):  return struct.unpack_from("<Q", d, o)[0]
def f32(d, o):  return struct.unpack_from("<f", d, o)[0]
def vec4(d, o): return struct.unpack_from("<4f", d, o)


@dataclass
class HkArray:
    """hkArray<T>: { T* m_data; int m_size; int m_capacityAndFlags; } -- 16 bytes.

    In serialized data m_data is a file offset (patched by a local fixup) and
    m_capacityAndFlags carries 0x80000000 (DONT_DEALLOCATE).
    """
    offset: int
    data: int
    size: int
    capacity_and_flags: int

    @property
    def capacity(self) -> int:
        return self.capacity_and_flags & 0x3FFFFFFF

    @property
    def dont_deallocate(self) -> bool:
        return bool(self.capacity_and_flags & 0x80000000)

    def __repr__(self):
        return "hkArray(@%d -> %d, size=%d, cap=0x%08X)" % (
            self.offset, self.data, self.size, self.capacity_and_flags)


def read_hkarray(d, o, fixups) -> HkArray:
    size = i32(d, o + 8)
    cap = u32(d, o + 12)
    return HkArray(o, fixups.get(o, 0), size, cap)


@dataclass
class Section:
    """hkcdStaticMeshTreeBaseSection, 96 bytes, reflection version 3.

    Inherits hkcdStaticTreeTree<hkcdStaticTreeDynamicStorage4> (48 bytes):
        +0  nodes   hkArray<hkcdStaticTreeCodec3Axis4>
        +16 domain  hkAabb
    """
    index: int
    nodes: HkArray
    domain: Tuple[float, ...]
    codec_parms: Tuple[float, ...]
    first_packed_vertex: int
    shared_vertices_raw: int
    primitives_raw: int
    data_runs_raw: int
    num_packed_vertices: int
    num_shared_indices: int
    leaf_index: int
    page: int
    flags: int
    layer_data: int
    unused_data: int


@dataclass
class MeshTree:
    """hknpCompressedMeshShapeTree = hkcdStaticMeshTree<...>, 160 bytes.

    Inherits hkcdStaticMeshTreeBase (112), which inherits
    hkcdStaticTreeTree<hkcdStaticTreeDynamicStorage5> (48).
    """
    nodes: HkArray
    domain: Tuple[float, ...]
    num_primitive_keys: int
    bits_per_key: int
    max_key_value: int
    sections: HkArray
    primitives: HkArray
    shared_vertices_index: HkArray
    packed_vertices: HkArray
    shared_vertices: HkArray
    primitive_data_runs: HkArray


@dataclass
class CompressedMeshShape:
    offset: int
    flags: int
    num_shape_key_bits: int
    dispatch_type: int
    convex_radius: float
    user_data: int
    shape_tag_codec_info: int
    data_ptr: int
    num_triangles: int
    num_convex_shapes: int


SIZEOF_SECTION = 96
SIZEOF_PRIMITIVE = 4
SIZEOF_NODE5 = 5
SIZEOF_NODE4 = 4
SIZEOF_DATARUN = 4


def read_shape(d, o) -> CompressedMeshShape:
    """hknpCompressedMeshShape, objectSize 160, reflection version 5."""
    return CompressedMeshShape(
        offset=o,
        flags=u16(d, o + 16),
        num_shape_key_bits=u8(d, o + 18),
        dispatch_type=u8(d, o + 19),
        convex_radius=f32(d, o + 20),
        user_data=u64(d, o + 24),
        shape_tag_codec_info=u32(d, o + 88),
        data_ptr=o + 96,
        num_triangles=i32(d, o + 152),
        num_convex_shapes=i32(d, o + 156),
    )


def read_mesh_tree(d, o, fixups) -> MeshTree:
    return MeshTree(
        nodes=read_hkarray(d, o + 0, fixups),
        domain=vec4(d, o + 16) + vec4(d, o + 32),
        num_primitive_keys=i32(d, o + 48),
        bits_per_key=i32(d, o + 52),
        max_key_value=u32(d, o + 56),
        sections=read_hkarray(d, o + 64, fixups),
        primitives=read_hkarray(d, o + 80, fixups),
        shared_vertices_index=read_hkarray(d, o + 96, fixups),
        packed_vertices=read_hkarray(d, o + 112, fixups),
        shared_vertices=read_hkarray(d, o + 128, fixups),
        primitive_data_runs=read_hkarray(d, o + 144, fixups),
    )


def read_section(d, base, index, fixups) -> Section:
    o = base + index * SIZEOF_SECTION
    return Section(
        index=index,
        nodes=read_hkarray(d, o + 0, fixups),
        domain=vec4(d, o + 16) + vec4(d, o + 32),
        codec_parms=struct.unpack_from("<6f", d, o + 48),
        first_packed_vertex=u32(d, o + 72),
        shared_vertices_raw=u32(d, o + 76),
        primitives_raw=u32(d, o + 80),
        data_runs_raw=u32(d, o + 84),
        num_packed_vertices=u8(d, o + 88),
        num_shared_indices=u8(d, o + 89),
        leaf_index=u16(d, o + 90),
        page=u8(d, o + 92),
        flags=u8(d, o + 93),
        layer_data=u8(d, o + 94),
        unused_data=u8(d, o + 95),
    )


COD_UNITS_PER_HAVOK_UNIT = 32.0

SHARED_VERTEX_BITS = (21, 21, 22)
SHARED_VERTEX_INV_BIT_SCALES = (2.0 ** -21, 2.0 ** -21, 2.0 ** -22)

SHARED_VERTEX_PAGE_SIZE = 0x10000


def decode_shared_vertex(packed: int, domain) -> Tuple[float, float, float]:
    """64-bit shared vertex -> position, in tree-domain space."""
    rx = packed & 0x1FFFFF
    ry = (packed >> 21) & 0x1FFFFF
    rz = (packed >> 42) & 0x3FFFFF
    mn = domain[0:3]
    mx = domain[4:7]
    return tuple(mn[i] + r * (mx[i] - mn[i]) * SHARED_VERTEX_INV_BIT_SCALES[i]
                 for i, r in enumerate((rx, ry, rz)))


BVH_INSET_DIVISOR = 226.0


def decode_section_tree(d, section):
    """Decode a section's BVH. -> list of (primitive_index, aabb_min, aabb_max)."""
    leaves = []
    dmn, dmx = section.domain[0:3], section.domain[4:7]
    stack, seen = [(0, dmn, dmx)], set()
    while stack:
        n, pmin, pmax = stack.pop()
        if n in seen or n >= section.nodes.size:
            continue
        seen.add(n)
        o = section.nodes.data + n * 4
        xyz, data = (d[o], d[o + 1], d[o + 2]), d[o + 3]
        cmin, cmax = [0.0] * 3, [0.0] * 3
        for k in range(3):
            step = (pmax[k] - pmin[k]) / BVH_INSET_DIVISOR
            cmin[k] = pmin[k] + (xyz[k] >> 4) ** 2 * step
            cmax[k] = pmax[k] - (xyz[k] & 0x0F) ** 2 * step
        cmin, cmax = tuple(cmin), tuple(cmax)
        if data & 1:
            stack.append((n + (data & 0xFE), cmin, cmax))
            stack.append((n + 1, cmin, cmax))
        else:
            leaves.append((data >> 1, cmin, cmax))
    return leaves


def custom_shape_type(d, mesh_tree, section, index0) -> int:
    """Shape type of a custom primitive: the low nibble of the sharedVerticesIndex word
    its indices[0] points at, indexing IW8's
    hknpCompressedMeshShapeInternals::s_customPrimitiveToShapeType. Stock IW7 world blobs
    use 2 exclusively, and type 2 is a CONVEX -- see decode_custom. (It was long
    described here as a NOP; it is not: IW7's player movement cast collides with these
    and with nothing else in the world mesh.)"""
    if index0 < section.num_packed_vertices:
        return -1
    j = (section.shared_vertices_raw >> 8) + index0 - section.num_packed_vertices
    if not (0 <= j < mesh_tree.shared_vertices_index.size):
        return -1
    return u16(d, mesh_tree.shared_vertices_index.data + j * 2) & 0xF


CUSTOM_PRIMITIVE_CONVEX = 2


@dataclass
class DecodedCustom:
    """A convex custom primitive (type 2), as stock IW7 stores brushes.

    For a primitive whose indices[1] == indices[2] == indices[3], with r = indices[0]
    and svi = sharedVerticesIndex[first + r - numPackedVertices ...]:

        svi[r]   descriptor = (numVertices << 8) | (layer << 4) | type
        svi[r+1] start, page-relative
        vertices = sharedVertices[page*65536 + start .. page*65536 + start + numVertices]

    Verified on stock mp_frontend and mp_afghan: 7,798 of 7,798 decode this way. The run
    is not listed in sharedVerticesIndex beyond the record.
    """
    section: int
    primitive: int
    record_slot: int
    descriptor: int
    start: int
    run_start: int
    vertices: Optional[List[Tuple[float, float, float]]] = None

    @property
    def shape_type(self) -> int:
        return self.descriptor & 0xF if self.descriptor >= 0 else -1

    @property
    def layer(self) -> int:
        return (self.descriptor >> 4) & 0x3 if self.descriptor >= 0 else -1

    @property
    def num_vertices(self) -> int:
        return self.descriptor >> 8 if self.descriptor >= 0 else -1


def decode_custom(d, mesh_tree, section, primitive_index, index0) -> DecodedCustom:
    """Decode one custom primitive's record and (for any type) its vertex run.
    Never raises: unreadable parts come back as -1 / None so a checker can count them."""
    out = DecodedCustom(section.index, primitive_index, index0, -1, -1, -1, None)
    if index0 < section.num_packed_vertices:
        return out
    j = (section.shared_vertices_raw >> 8) + index0 - section.num_packed_vertices
    svi = mesh_tree.shared_vertices_index
    if not (0 <= j and j + 1 < svi.size):
        return out
    out.descriptor = u16(d, svi.data + j * 2)
    out.start = u16(d, svi.data + (j + 1) * 2)
    out.run_start = SHARED_VERTEX_PAGE_SIZE * section.page + out.start
    n = out.num_vertices
    if n > 0 and out.run_start + n <= mesh_tree.shared_vertices.size:
        out.vertices = [
            decode_shared_vertex(u64(d, mesh_tree.shared_vertices.data + (out.run_start + k) * 8),
                                 mesh_tree.domain)
            for k in range(n)]
    return out


def unpack_section_field(raw: int) -> Tuple[int, int]:
    """Section's packed (offset, count) fields: raw = (offset << 8) | count.

    Applies to primitives_raw and data_runs_raw. For shared_vertices_raw the low
    byte is numPackedVertices instead of a count -- the count is num_shared_indices.
    """
    return raw >> 8, raw & 0xFF


def decode_packed_vertex(packed: int, codec_parms) -> Tuple[float, float, float]:
    """32-bit packed vertex -> position, in Havok units.

    Bit layout is x = bits 0..10 (11 bits), y = bits 11..21 (11 bits),
    z = bits 22..31 (10 bits). codec_parms is float[6]: [ox, oy, oz, sx, sy, sz]
    where the offset is the section's true geometry minimum and the scale is
    extent / (2^bits - 1).
    """
    rx = packed & 0x7FF
    ry = (packed >> 11) & 0x7FF
    rz = (packed >> 22) & 0x3FF
    return (codec_parms[0] + rx * codec_parms[3],
            codec_parms[1] + ry * codec_parms[4],
            codec_parms[2] + rz * codec_parms[5])


@dataclass
class DecodedMesh:
    vertices: List[Tuple[float, float, float]]
    triangles: List[Tuple[int, int, int]]
    quads: List[Tuple[int, int, int, int]]
    primitive_sections: List[int]
    domain: Tuple[float, ...]
    convex_radius: float
    custom_primitives: List[Tuple[int, int]] = field(default_factory=list)
    customs: List[DecodedCustom] = field(default_factory=list)

    def bounds(self):
        xs = [v[0] for v in self.vertices]
        ys = [v[1] for v in self.vertices]
        zs = [v[2] for v in self.vertices]
        return (min(xs), min(ys), min(zs)), (max(xs), max(ys), max(zs))


def decode_mesh(d, mesh_tree: MeshTree, convex_radius: float, fixups) -> DecodedMesh:
    """Decode every section of a compressed mesh tree into world-space geometry.

    A primitive is 4 uint8 indices into the section's local vertex pool. Indices
    below num_packed_vertices select from packedVertices (offset by
    first_packed_vertex); the rest select shared vertices via sharedVerticesIndex.
    A primitive with indices[2] == indices[3] is a triangle, otherwise a quad.
    """
    verts: List[Tuple[float, float, float]] = []
    tris: List[Tuple[int, int, int]] = []
    quads: List[Tuple[int, int, int, int]] = []
    prim_section: List[int] = []
    custom: List[Tuple[int, int]] = []
    customs: List[DecodedCustom] = []

    pv_base = mesh_tree.packed_vertices.data
    prim_base = mesh_tree.primitives.data
    svi_base = mesh_tree.shared_vertices_index.data

    for si in range(mesh_tree.sections.size):
        s = read_section(d, mesh_tree.sections.data, si, fixups)
        prim_off, prim_count = unpack_section_field(s.primitives_raw)
        first_shared = s.shared_vertices_raw >> 8
        page_base = SHARED_VERTEX_PAGE_SIZE * s.page
        cache = {}

        def fetch(vi):
            """IW8 hkcdStaticMeshTree::SectionDecoder:
                 index <  numPackedVertices -> packedVertices, section codec
                 index >= numPackedVertices -> sharedVerticesIndex[first + index - numPV]
                                               -> sharedVertices[0x10000*page + that]
               There is no cap at num_shared_indices; that field is not the pool size."""
            if vi in cache:
                return cache[vi]
            if vi < s.num_packed_vertices:
                packed = u32(d, pv_base + (s.first_packed_vertex + vi) * 4)
                pos = decode_packed_vertex(packed, s.codec_parms)
            else:
                j = first_shared + vi - s.num_packed_vertices
                if j >= mesh_tree.shared_vertices_index.size:
                    raise NotImplementedError(
                        "section %d: sharedVerticesIndex[%d] is past the end of a %d-entry "
                        "array. This is the single-section numPackedVertices==0 variant "
                        "whose sharedVerticesIndex holds a stale constant pattern -- see "
                        "docs/iw7-havok-collision.md 5a. World blobs are unaffected."
                        % (si, j, mesh_tree.shared_vertices_index.size))
                sidx = u16(d, svi_base + j * 2)
                k = page_base + sidx
                if k >= mesh_tree.shared_vertices.size:
                    raise NotImplementedError(
                        "section %d: sharedVertices[%d] past end of %d entries"
                        % (si, k, mesh_tree.shared_vertices.size))
                packed = u64(d, mesh_tree.shared_vertices.data + k * 8)
                pos = decode_shared_vertex(packed, mesh_tree.domain)
            cache[vi] = len(verts)
            verts.append(pos)
            return cache[vi]

        for pi in range(prim_count):
            o = prim_base + (prim_off + pi) * SIZEOF_PRIMITIVE
            a, b, c, e = d[o], d[o + 1], d[o + 2], d[o + 3]

            if (a, b, c, e) == (0xDE, 0xAD, 0xDE, 0xAD):
                continue

            if b == c == e:
                custom.append((si, custom_shape_type(d, mesh_tree, s, a)))
                customs.append(decode_custom(d, mesh_tree, s, pi, a))
                continue

            ia, ib, ic = fetch(a), fetch(b), fetch(c)
            prim_section.append(si)
            if c == e:
                tris.append((ia, ib, ic))
            else:
                ie = fetch(e)
                quads.append((ia, ib, ic, ie))
                tris.append((ia, ib, ic))
                tris.append((ia, ic, ie))

    return DecodedMesh(verts, tris, quads, prim_section,
                       mesh_tree.domain, convex_radius, custom, customs)


def load_compressed_meshes(path):
    """Yield (shape, mesh_tree, decoded) for every compressed mesh in a packfile."""
    from hkpackfile import Packfile
    pf = Packfile.load(path)
    sec = pf.sections[2]
    d = sec.data
    fixups = dict(pf.local_fixups(sec))
    fixups.update({s: dst for s, _si, dst in pf.global_fixups(sec)})
    objs = pf.objects()
    shapes = [o for _si, o, n in objs if n == "hknpCompressedMeshShape"]
    datas = [o for _si, o, n in objs if n == "hknpCompressedMeshShapeData"]
    for sh_off, da_off in zip(shapes, datas):
        shape = read_shape(d, sh_off)
        mt = read_mesh_tree(d, da_off + 16, fixups)
        yield shape, mt, decode_mesh(d, mt, shape.convex_radius, fixups)
