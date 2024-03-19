#pragma once
#include <d3d11.h>

#define PTR64 * __ptr64
#define PTR32 * __ptr32

#pragma pack(push, 8)

namespace ZoneTool::IW7
{
	typedef float vec_t;
	typedef vec_t vec2_t[2];
	typedef vec_t vec3_t[3];
	typedef vec_t vec4_t[4];

	enum scr_string_t : std::int32_t
	{
	};

	enum XAssetType : std::int32_t
	{
		ASSET_TYPE_PHYSICSLIBRARY = 0,
		ASSET_TYPE_PHYSICS_SFX_EVENT_ASSET = 1,
		ASSET_TYPE_PHYSICS_VFX_EVENT_ASSET = 2,
		ASSET_TYPE_PHYSICSASSET = 3,
		ASSET_TYPE_PHYSICS_FX_PIPELINE = 4,
		ASSET_TYPE_PHYSICS_FX_SHAPE = 5,
		ASSET_TYPE_XANIMPARTS = 6,
		ASSET_TYPE_XMODEL_SURFS = 7,
		ASSET_TYPE_XMODEL = 8,
		ASSET_TYPE_MAYHEM = 9,
		ASSET_TYPE_MATERIAL = 10,
		ASSET_TYPE_COMPUTESHADER = 11,
		ASSET_TYPE_VERTEXSHADER = 12,
		ASSET_TYPE_HULLSHADER = 13,
		ASSET_TYPE_DOMAINSHADER = 14,
		ASSET_TYPE_PIXELSHADER = 15,
		ASSET_TYPE_VERTEXDECL = 16,
		ASSET_TYPE_TECHNIQUE_SET = 17,
		ASSET_TYPE_IMAGE = 18,
		ASSET_TYPE_SOUND_GLOBALS = 19,
		ASSET_TYPE_SOUND_BANK = 20,
		ASSET_TYPE_SOUND_BANK_TRANSIENT = 21,
		ASSET_TYPE_CLIPMAP = 22,
		ASSET_TYPE_COMWORLD = 23,
		ASSET_TYPE_GLASSWORLD = 24,
		ASSET_TYPE_PATHDATA = 25,
		ASSET_TYPE_NAVMESH = 26,
		ASSET_TYPE_MAP_ENTS = 27,
		ASSET_TYPE_FXWORLD = 28,
		ASSET_TYPE_GFXWORLD = 29,
		ASSET_TYPE_GFXWORLD_TRANSIENT_ZONE = 30,
		ASSET_TYPE_IESPROFILE = 31, // unused
		ASSET_TYPE_LIGHT_DEF = 32,
		ASSET_TYPE_UI_MAP = 33, // unused
		ASSET_TYPE_ANIMCLASS = 34,
		ASSET_TYPE_PLAYERANIM = 35,
		ASSET_TYPE_GESTURE = 36,
		ASSET_TYPE_LOCALIZE_ENTRY = 37,
		ASSET_TYPE_ATTACHMENT = 38,
		ASSET_TYPE_WEAPON = 39,
		ASSET_TYPE_VFX = 40,
		ASSET_TYPE_FX = 41,
		ASSET_TYPE_IMPACT_FX = 42,
		ASSET_TYPE_SURFACE_FX = 43,
		ASSET_TYPE_AITYPE = 44, // unused
		ASSET_TYPE_MPTYPE = 45, // unused
		ASSET_TYPE_CHARACTER = 46, // unused
		ASSET_TYPE_XMODELALIAS = 47, // unused
		ASSET_TYPE_RAWFILE = 48,
		ASSET_TYPE_SCRIPTFILE = 49,
		ASSET_TYPE_STRINGTABLE = 50,
		ASSET_TYPE_LEADERBOARD = 51,
		ASSET_TYPE_VIRTUAL_LEADERBOARD = 52,
		ASSET_TYPE_STRUCTUREDDATADEF = 53,
		ASSET_TYPE_DDL = 54,
		ASSET_TYPE_TRACER = 55,
		ASSET_TYPE_VEHICLE = 56,
		ASSET_TYPE_ADDON_MAP_ENTS = 57,
		ASSET_TYPE_NET_CONST_STRINGS = 58,
		ASSET_TYPE_LUA_FILE = 59,
		ASSET_TYPE_SCRIPTABLE = 60,
		ASSET_TYPE_EQUIPMENT_SND_TABLE = 61,
		ASSET_TYPE_VECTORFIELD = 62,
		ASSET_TYPE_PARTICLE_SIM_ANIMATION = 63,
		ASSET_TYPE_STREAMING_INFO = 64,
		ASSET_TYPE_LASER = 65,
		ASSET_TYPE_TTF = 66,
		ASSET_TYPE_SUIT = 67,
		ASSET_TYPE_SUITANIMPACKAGE = 68,
		ASSET_TYPE_SPACESHIPTARGET = 69,
		ASSET_TYPE_RUMBLE = 70,
		ASSET_TYPE_RUMBLE_GRAPH = 71,
		ASSET_TYPE_ANIM_PACKAGE = 72,
		ASSET_TYPE_SFX_PACKAGE = 73,
		ASSET_TYPE_VFX_PACKAGE = 74,
		ASSET_TYPE_BEHAVIOR_TREE = 75,
		ASSET_TYPE_XANIM_ARCHETYPE = 76,
		ASSET_TYPE_XANIM_PROCEDURALBONES = 77,
		ASSET_TYPE_RETICLE = 78,
		ASSET_TYPE_GFXLIGHTMAP = 79,
		ASSET_TYPE_COUNT = 80
	};

	struct PhysicsLibrary;
	struct PhysicsSFXEventAsset;
	struct PhysicsVFXEventAsset;
	struct PhysicsAsset;
	struct PhysicsFXPipeline;
	struct PhysicsFXShape;
	struct XAnimParts;
	struct XModelSurfs;
	struct XModel;
	struct Mayhem;
	struct Material;
	struct ComputeShader;
	struct MaterialVertexShader;
	struct MaterialHullShader;
	struct MaterialDomainShader;
	struct MaterialPixelShader;
	struct MaterialVertexDeclaration;
	struct MaterialTechniqueSet;
	struct GfxImage;
	struct SndGlobals;
	struct SndBank;
	struct SndBankTransient;
	struct clipMap_t;
	struct ComWorld;
	struct GlassWorld;
	struct PathData;
	struct NavMeshData;
	struct MapEnts;
	struct FxWorld;
	struct GfxWorld;
	struct GfxWorldTransientZone;
	//ASSET_TYPE_IESPROFILE = 31, // unused
	struct GfxLightDef;
	//ASSET_TYPE_UI_MAP = 33, // unused
	struct AnimationClass;
	struct PlayerAnimScript;
	struct Gesture;
	struct LocalizeEntry;
	struct WeaponAttachment;
	struct WeaponCompleteDef;
	struct ParticleSystemDef;
	struct FxEffectDef;
	struct FxImpactTable;
	struct SurfaceFxTable;
	//ASSET_TYPE_AITYPE = 44, // unused
	//ASSET_TYPE_MPTYPE = 45, // unused
	//ASSET_TYPE_CHARACTER = 46, // unused
	//ASSET_TYPE_XMODELALIAS = 47, // unused
	struct RawFile;
	struct ScriptFile;
	struct StringTable;
	struct LeaderBoardDef;
	struct VirtualLeaderboardDef;
	struct StructuredDataDefSet;
	struct DDLFile;
	struct TracerDef;
	struct VehicleDef;
	struct AddonMapEnts;
	struct NetConstStrings;
	struct LuaFile;
	struct ScriptableDef;
	struct EquipmentSoundTable;
	struct VectorField;
	struct FxParticleSimAnimation;
	struct StreamingInfo;
	struct LaserDef;
	struct TTFDef;
	struct SuitDef;
	struct SuitAnimPackage;
	struct SpaceshipTargetDef;
	struct RumbleInfo;
	struct RumbleGraph;
	struct WeaponAnimPackage;
	struct WeaponSFXPackage;
	struct WeaponVFXPackage;
	struct BehaviorTree;
	struct XAnimArcheType;
	struct XAnimProceduralBones;
	struct ReticleDef;
	struct GfxLightMap;

	struct Bounds
	{
		vec3_t midPoint;
		vec3_t halfSize;
	};

	struct ExtentBounds
	{
		vec3_t mins;
		vec3_t maxs;
	};

	union FxCombinedUnion
	{
		FxEffectDef PTR64 fx;
		ParticleSystemDef PTR64 particleSystemDef;
	};

	enum FxCombinedType : std::uint8_t
	{
		FX_COMBINED_DEFAULT,
		FX_COMBINED_PARTICLE_SYSTEM,
	};

	struct FxCombinedDef
	{
		FxCombinedUnion u;
		FxCombinedType type;
	};

	//typedef const char PTR64 SndAliasLookup;

	struct PhysicsLibrary
	{
		const char PTR64 name;
		bool isMaterialList;
		bool isBodyQualityList;
		bool isMotionPropertiesList;
		bool isGlobalTypeCompendium;
		unsigned int havokDataSize;
		char PTR64 havokData;
	}; assert_sizeof(PhysicsLibrary, 0x18);

	struct PhysicsSFXEventAssetRule;
	struct PhysicsSFXEventAssetRules
	{
		int numrules;
		PhysicsSFXEventAssetRule PTR64 rules;
	};

	enum PhysicsSFXEventAssetRuleType
	{
		Types_PhysicsSFXEventRule = 0x0,
		Types_PhysicsSFXEventSoundRule = 0x1,
		Types_PhysicsSFXEventMaterialRule = 0x2,
		Types_PhysicsSFXEventAngleRule = 0x3,
		Types_PhysicsSFXEventSpeedRule = 0x4,
		Types_PhysicsSFXEventMassRule = 0x5,
		Types_PhysicsSFXEventGravityRule = 0x6,
		Types_PhysicsSFXEventAtmosphereRule = 0x7,
		Types_PhysicsSFXEventCameraDistanceRule = 0x8,
		Types_PhysicsSFXEventFrequencyRule = 0x9,
		Types_PhysicsSFXEventRuleCount = 0xA,
	};

	struct PhysicsSFXEventAssetSoundRule
	{
		char PTR64 hitSoundAlias;
		char PTR64 scrapeSoundAlias;
		float scrapeSoundVolumeSpeedThresholdMin;
		float scrapeSoundVolumeSpeedThresholdMax;
		float scrapeSoundVolumeBlendSpeed;
	};

	struct PhysicsSFXEventAssetMaterialEntry
	{
		int surfaceType;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetMaterialRule
	{
		int numentries;
		PhysicsSFXEventAssetMaterialEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetAngleEntry
	{
		float angle;
		float hitSoundVolumeModifierMin;
		float hitSoundVolumeModifierMax;
		float hitSoundPitchModifierMin;
		float hitSoundPitchModifierMax;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetAngleRule
	{
		int numentries;
		PhysicsSFXEventAssetAngleEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetSpeedEntry
	{
		float speedThreshold;
		float hitSoundVolumeModifierMin;
		float hitSoundVolumeModifierMax;
		float hitSoundPitchModifierMin;
		float hitSoundPitchModifierMax;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetSpeedRule
	{
		int numentries;
		PhysicsSFXEventAssetSpeedEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetMassEntry
	{
		float massThreshold;
		float hitSoundVolumeModifierMin;
		float hitSoundVolumeModifierMax;
		float hitSoundPitchModifierMin;
		float hitSoundPitchModifierMax;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetMassRule
	{
		int numentries;
		PhysicsSFXEventAssetMassEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetGravityEntry
	{
		bool gravity;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetGravityRule
	{
		int numentries;
		PhysicsSFXEventAssetGravityEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetAtmosphereEntry
	{
		bool atmosphere;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetAtmosphereRule
	{
		int numentries;
		PhysicsSFXEventAssetAtmosphereEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetCameraDistanceEntry
	{
		float distance;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetCameraDistanceRule
	{
		int numentries;
		PhysicsSFXEventAssetCameraDistanceEntry PTR64 entries;
	};

	struct PhysicsSFXEventAssetFrequencyEntry
	{
		int maxEvents;
		PhysicsSFXEventAssetRules rules;
	};

	struct PhysicsSFXEventAssetFrequencyRule
	{
		int numentries;
		PhysicsSFXEventAssetFrequencyEntry PTR64 entries;
	};

	union PhysicsSFXEventAssetRuleUnion
	{
		PhysicsSFXEventAssetSoundRule soundRule;
		PhysicsSFXEventAssetMaterialRule materialRule;
		PhysicsSFXEventAssetAngleRule angleRule;
		PhysicsSFXEventAssetSpeedRule speedRule;
		PhysicsSFXEventAssetMassRule massRule;
		PhysicsSFXEventAssetGravityRule gravityRule;
		PhysicsSFXEventAssetAtmosphereRule atmosphereRule;
		PhysicsSFXEventAssetCameraDistanceRule cameraDistanceRule;
		PhysicsSFXEventAssetFrequencyRule frequencyRule;
	};

	struct PhysicsSFXEventAssetRule
	{
		PhysicsSFXEventAssetRuleType type;
		PhysicsSFXEventAssetRuleUnion u;
	};

	struct PhysicsSFXEventAsset
	{
		const char PTR64 name;
		int priority;
		PhysicsSFXEventAssetRules rules;
	}; assert_sizeof(PhysicsSFXEventAsset, 0x20);

	struct PhysicsVFXEventAssetRule;
	struct PhysicsVFXEventAssetRules
	{
		int numrules;
		PhysicsVFXEventAssetRule PTR64 rules;
	};

	enum PhysicsVFXEventAssetRuleType
	{
		Types_PhysicsVFXEventRule = 0x0,
		Types_PhysicsVFXEventParticleEffectRule = 0x1,
		Types_PhysicsVFXEventMaterialRule = 0x2,
		Types_PhysicsVFXEventAngleRule = 0x3,
		Types_PhysicsVFXEventSpeedRule = 0x4,
		Types_PhysicsVFXEventMassRule = 0x5,
		Types_PhysicsVFXEventGravityRule = 0x6,
		Types_PhysicsVFXEventAtmosphereRule = 0x7,
		Types_PhysicsVFXEventCameraDistanceRule = 0x8,
		Types_PhysicsVFXEventFrequencyRule = 0x9,
		Types_PhysicsVFXEventRuleCount = 0xA,
	};

	struct PhysicsVFXEventAssetParticleEffectRule
	{
		char PTR64 hitParticleEffectAlias;
		char PTR64 scrapeParticleEffectAlias;
	};

	struct PhysicsVFXEventAssetMaterialEntry
	{
		int surfaceType;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetMaterialRule
	{
		int numentries;
		PhysicsVFXEventAssetMaterialEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetAngleEntry
	{
		float angle;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetAngleRule
	{
		int numentries;
		PhysicsVFXEventAssetAngleEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetSpeedEntry
	{
		float speedThreshold;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetSpeedRule
	{
		int numentries;
		PhysicsVFXEventAssetSpeedEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetMassEntry
	{
		float massThreshold;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetMassRule
	{
		int numentries;
		PhysicsVFXEventAssetMassEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetGravityEntry
	{
		bool gravity;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetGravityRule
	{
		int numentries;
		PhysicsVFXEventAssetGravityEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetAtmosphereEntry
	{
		bool atmosphere;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetAtmosphereRule
	{
		int numentries;
		PhysicsVFXEventAssetAtmosphereEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetCameraDistanceEntry
	{
		float distance;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetCameraDistanceRule
	{
		int numentries;
		PhysicsVFXEventAssetCameraDistanceEntry PTR64 entries;
	};

	struct PhysicsVFXEventAssetFrequencyEntry
	{
		int maxEvents;
		PhysicsVFXEventAssetRules rules;
	};

	struct PhysicsVFXEventAssetFrequencyRule
	{
		int numentries;
		PhysicsVFXEventAssetFrequencyEntry PTR64 entries;
	};

	union PhysicsVFXEventAssetRuleUnion
	{
		PhysicsVFXEventAssetParticleEffectRule particleEffectRule;
		PhysicsVFXEventAssetMaterialRule materialRule;
		PhysicsVFXEventAssetAngleRule angleRule;
		PhysicsVFXEventAssetSpeedRule speedRule;
		PhysicsVFXEventAssetMassRule massRule;
		PhysicsVFXEventAssetGravityRule gravityRule;
		PhysicsVFXEventAssetAtmosphereRule atmosphereRule;
		PhysicsVFXEventAssetCameraDistanceRule cameraDistanceRule;
		PhysicsVFXEventAssetFrequencyRule frequencyRule;
	};

	struct PhysicsVFXEventAssetRule
	{
		PhysicsVFXEventAssetRuleType type;
		PhysicsVFXEventAssetRuleUnion u;
	};

	struct PhysicsVFXEventAsset
	{
		const char PTR64 name;
		int priority;
		PhysicsVFXEventAssetRules rules;
	}; assert_sizeof(PhysicsVFXEventAsset, 0x20);

	struct PhysicsAsset
	{
		const char PTR64 name;
		unsigned int havokDataSize;
		char PTR64 havokData;
		char __pad0[8];
		int numConstraints;
		int numSFXEventAssets;
		PhysicsSFXEventAsset PTR64  PTR64 sfxEventAssets;
		int numVFXEventAssets;
		PhysicsVFXEventAsset PTR64  PTR64 vfxEventAssets;
		char __pad1[16];
	}; assert_sizeof(PhysicsAsset, 0x50);

	struct PhysicsFXPipeline
	{
		const char PTR64 name;
		char __pad0[24];
	}; assert_sizeof(PhysicsFXPipeline, 0x20);

	struct PhysicsFXShape
	{
		const char PTR64 name;
		unsigned int size;
		vec3_t PTR64 vecs;
	}; assert_sizeof(PhysicsFXShape, 0x18);

	union XAnimIndices
	{
		unsigned char PTR64 _1;
		unsigned short PTR64 _2;
		void PTR64 data;
	};

	struct XAnimNotifyInfo
	{
		scr_string_t name;
		float time;
	};

	union XAnimDynamicFrames
	{
		unsigned char( PTR64 _1)[3];
		unsigned short( PTR64 _2)[3];
	};

	union XAnimDynamicIndices
	{
		unsigned char _1[1];
		unsigned short _2[1];
	};

	struct XAnimPartTransFrames
	{
		vec3_t mins;
		vec3_t size;
		XAnimDynamicFrames frames;
		XAnimDynamicIndices indices;
	};

	union XAnimPartTransData
	{
		XAnimPartTransFrames frames;
		vec3_t frame0;
	};

	struct XAnimPartTrans
	{
		unsigned short size;
		unsigned char smallTrans;
		XAnimPartTransData u;
	};

	struct XAnimDeltaPartQuatDataFrames2
	{
		short( PTR64 frames)[2];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData2
	{
		XAnimDeltaPartQuatDataFrames2 frames;
		short frame0[2];
	};

	struct XAnimDeltaPartQuat2
	{
		unsigned short size;
		XAnimDeltaPartQuatData2 u;
	};

	struct XAnimDeltaPartQuatDataFrames
	{
		short( PTR64 frames)[4];
		XAnimDynamicIndices indices;
	};

	union XAnimDeltaPartQuatData
	{
		XAnimDeltaPartQuatDataFrames frames;
		short frame0[4];
	};

	struct XAnimDeltaPartQuat
	{
		unsigned short size;
		XAnimDeltaPartQuatData u;
	};

	struct XAnimDeltaPart
	{
		XAnimPartTrans PTR64 trans;
		XAnimDeltaPartQuat2 PTR64 quat2;
		XAnimDeltaPartQuat PTR64 quat;
	};

	struct XAnimParts
	{
		const char PTR64 name; // 0
		scr_string_t PTR64 names; // 8
		unsigned char PTR64 dataByte; // 16
		short PTR64 dataShort; // 24
		int PTR64 dataInt; // 32
		short PTR64 randomDataShort; // 40
		unsigned char PTR64 randomDataByte; // 48
		int PTR64 randomDataInt; // 56
		XAnimIndices indices; // 64
		XAnimNotifyInfo PTR64 notify; // 72
		XAnimDeltaPart PTR64 deltaPart; // 80
		unsigned int randomDataShortCount; // 88
		unsigned int randomDataByteCount; // 92
		unsigned int indexCount; // 96
		float framerate; // 100
		float frequency; // 104
		unsigned short dataByteCount; // 108
		unsigned short dataShortCount; // 110
		unsigned short dataIntCount; // 112
		unsigned short randomDataIntCount; // 114
		unsigned short numframes; // 116
		unsigned char flags; // 118
		unsigned char boneCount[10]; // 119
		unsigned char notifyCount; // 129
		unsigned char assetType; // 130
		unsigned char ikType; // 131
	}; assert_sizeof(XAnimParts, 0x88);

	struct XSurfaceCollisionAabb
	{
		unsigned short mins[3];
		unsigned short maxs[3];
	};

	struct XSurfaceCollisionNode
	{
		XSurfaceCollisionAabb aabb;
		unsigned short childBeginIndex;
		unsigned short childCount;
	};

	struct XSurfaceCollisionLeaf
	{
		unsigned short triangleBeginIndex;
	};

	struct XSurfaceCollisionTree
	{
		float trans[3];
		float scale[3];
		unsigned int nodeCount;
		XSurfaceCollisionNode PTR64 nodes;
		unsigned int leafCount;
		XSurfaceCollisionLeaf PTR64 leafs;
	};

	struct XRigidVertList
	{
		unsigned short boneOffset;
		unsigned short vertCount;
		unsigned short triOffset;
		unsigned short triCount;
		XSurfaceCollisionTree PTR64 collisionTree;
	};

	union PackedUnitVec
	{
		unsigned int packed;
		unsigned char array[4];
	};

	union PackedTexCoords
	{
		unsigned int packed;
		unsigned char array[4];
	};

	union GfxColor
	{
		unsigned char array[4];
		unsigned int packed;
	};

	struct PackedSelfVisibility
	{
		unsigned int packed;
	};

	struct GfxPackedVertex
	{
		float xyz[3];
		PackedSelfVisibility selfVisibility;
		GfxColor color;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct GfxPackedMotionVertex
	{
		float xyz[3];
		float binormalSignAndHeight;
		GfxColor pieceIndex;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	union GfxVertexUnion0
	{
		GfxPackedVertex PTR64 packedVerts0;
		GfxPackedMotionVertex PTR64 packedMotionVerts0;
		void PTR64 verts0;
	};

	struct Face
	{
		unsigned short v1;
		unsigned short v2;
		unsigned short v3;
	};

	struct XSubdivRigidVertList
	{
		unsigned int firstFace;
		unsigned int faceCount;
		unsigned int firstRegularPatch;
		unsigned int regularPatchCount;
	};

	struct XSurfaceSubdivLevel
	{
		XSubdivRigidVertList PTR64 rigidVertLists;
		unsigned int faceCount;
		unsigned int regularPatchCount;
		unsigned int regularPatchOffset;
		unsigned int facePointCount;
		unsigned int facePointValence4Count;
		unsigned int facePointBufferSize;
		unsigned int edgePointCount;
		unsigned int edgePointSmoothEnd;
		unsigned int edgePointUVBorderEnd;
		unsigned int vertexPointCount;
		unsigned int vertexPointValence4Count;
		unsigned int vertexPointBufferSize;
		unsigned int normalCount;
		unsigned int normalBufferSize;
		unsigned int transitionPointCount;
		unsigned int vertCount;
		unsigned int vertOffset;
		unsigned short PTR64 faceIndices;
		unsigned short PTR64 regularPatchIndices;
		unsigned int PTR64 regularPatchFlags;
		unsigned int PTR64 facePoints;
		unsigned int PTR64 edgePoints;
		unsigned int PTR64 vertexPoints;
		unsigned int PTR64 normals;
		unsigned int PTR64 transitionPoints;
		float PTR64 regularPatchCones;
		ID3D11Buffer PTR64 regularPatchIndexBuffer;
		ID3D11Buffer PTR64 faceIndexBuffer;
		ID3D11ShaderResourceView PTR64 regularPatchIndexBufferView;
		ID3D11ShaderResourceView PTR64 regularPatchFlagsView;
		ID3D11ShaderResourceView PTR64 facePointsView;
		ID3D11ShaderResourceView PTR64 edgePointsView;
		ID3D11ShaderResourceView PTR64 vertexPointsView;
		ID3D11ShaderResourceView PTR64 normalsView;
		ID3D11ShaderResourceView PTR64 transitionPointsView;
		ID3D11ShaderResourceView PTR64 regularPatchConesView;
	}; assert_sizeof(XSurfaceSubdivLevel, 0xE8);

	struct GfxSubdivCache
	{
		unsigned int size;
		ID3D11Buffer PTR64 subdivCacheBuffer;
		ID3D11ShaderResourceView PTR64 subdivCacheView;
	}; assert_sizeof(GfxSubdivCache, 0x18);

	struct XSurfaceSubdivInfo
	{
		XSurfaceSubdivLevel PTR64 levels;
		char __pad0[24];
		GfxSubdivCache cache;
	}; assert_sizeof(XSurfaceSubdivInfo, 0x38);

	struct SHProbeSimplexData2
	{
		char __pad0[24];
	};

	struct SHProbeSimplexData1
	{
		char __pad0[8];
	};

	struct SHProbeSimplexData0
	{
		SHProbeSimplexData2 a; // coulbereversed?
		SHProbeSimplexData1 b; // ^
	};

	union SHProbeSimplexDataUnion
	{
		SHProbeSimplexData0 PTR64 data0;
		SHProbeSimplexData1 PTR64 data1;
		SHProbeSimplexData2 PTR64 data2;
	};

	typedef unsigned short XBlendInfo;

	struct XSurface
	{
		unsigned short flags;
		unsigned short vertCount;
		unsigned short triCount;
		unsigned char rigidVertListCount;
		char subdivLevelCount;
		short blendVertCounts[8];
		int blendVertSize;
		char __pad0[4];
		GfxVertexUnion0 verts0;
		Face PTR64 triIndices;
		ID3D11Buffer PTR64 vb0;
		ID3D11ShaderResourceView PTR64 vb0View;
		ID3D11Buffer PTR64 indexBuffer;
		XRigidVertList PTR64 rigidVertLists;
		XBlendInfo PTR64 blendVerts;
		ID3D11Buffer PTR64 blendVertsBuffer;
		ID3D11ShaderResourceView PTR64 blendVertsView;
		float( PTR64 lmapUnwrap)[2];
		ID3D11Buffer PTR64 vblmapBuffer;
		ID3D11ShaderResourceView PTR64 vblmapView;
		XSurfaceSubdivInfo PTR64 subdiv;
		float PTR64 tensionData;
		unsigned short PTR64 tensionAccumTable;
		ID3D11Buffer PTR64 tensionAccumTableBuffer;
		ID3D11ShaderResourceView PTR64 tensionAccumTableView;
		ID3D11Buffer PTR64 tensionDataBuffer;
		ID3D11ShaderResourceView PTR64 tensionDataView;
		ID3D11ShaderResourceView PTR64 indexBufferView;
		int unk; // vertexLightingIndex
		int pad;
		SHProbeSimplexDataUnion shProbeSimplexVertData;
		ID3D11Buffer PTR64 shProbeSimplexVertBuffer;
		ID3D11ShaderResourceView PTR64 shProbeSimplexVertBufferView;
		int partBits[8];
	}; assert_sizeof(XSurface, 0x100);

	struct XModelSurfs
	{
		const char PTR64 name;
		XSurface PTR64 surfs;
		unsigned short numsurfs;
		int partBits[8];
	}; assert_sizeof(XModelSurfs, 0x38);

	struct XModelAngle
	{
		short x;
		short y;
		short z;
		short base;
	};

	struct XModelTagPos
	{
		float x;
		float y;
		float z;
	};

	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};

	struct ReactiveMotionModelPart
	{
		float center[3];
		float stiffness;
	};

	struct ReactiveMotionModelTweaks
	{
		float scale[4];
	};

	struct XModelLodInfo
	{
		float dist;
		unsigned short numsurfs;
		unsigned short surfIndex;
		XModelSurfs PTR64 modelSurfs;
		int partBits[8];
		XSurface PTR64 surfs;
		int unk; // subdivLodValidMask?
		char flags;
		char pad[3];
	}; assert_sizeof(XModelLodInfo, 0x40);

	struct XModelCollSurf_s
	{
		Bounds bounds;
		int boneIdx;
		int contents;
		int surfFlags;
	}; assert_sizeof(XModelCollSurf_s, 36);

	struct XBoneInfo
	{
		Bounds bounds;
		union
		{
			float radiusSquared;
			unsigned int radiusSquaredAsInt;
		};
	};

	struct unk_1453E14D8
	{
		char __pad0[24];
	};

	enum XModelCharCollBoundsType : std::uint8_t
	{
		CharCollBoundsType_None = 0x0,
		CharCollBoundsType_Human = 0x1,
		CharCollBoundsType_C12 = 0x2,
		CharCollBoundsType_C8 = 0x3,
		CharCollBoundsType_Seeker = 0x4,
		CharCollBoundsType_Zombie = 0x5,
		CharCollBoundsType_LargeZombie = 0x6,
		CharCollBoundsType_Alien = 0x7,
		CharCollBoundsType_LargeAlien = 0x8,
		CharCollBoundsType_ExtraLargeZombie = 0x9,
		CharCollBoundsType_Num = 0xA,
	};

	struct XModel
	{
		const char PTR64 name;
		char unused01;
		unsigned char unknown01;
		char maxLoadedLod;
		unsigned char numLods;
		unsigned char collLod;
		unsigned char shadowCutoffLod;
		unsigned char characterCollBoundsType;
		int flags;
		unsigned char numBones;
		unsigned char numRootBones;
		unsigned char numReactiveMotionParts;
		unsigned short numClientBones;
		unsigned short numsurfs;
		float scale;
		unsigned short numCollSurfs;
		int contents;
		float radius;
		Bounds bounds;
		int memUsage;
		unsigned int unknown02Count;
		char unk_01[12]; // unknown data
		ScriptableDef PTR64 scriptableMoverDef;
		XAnimProceduralBones PTR64 proceduralBones;
		scr_string_t PTR64 aimAssistBones;
		unsigned char numAimAssistBones;
		unsigned int noScalePartBits[8];
		scr_string_t PTR64 boneNames;
		unsigned char PTR64 parentList;
		XModelAngle PTR64 tagAngles;
		XModelTagPos PTR64 tagPositions;
		unsigned char PTR64 partClassification;
		DObjAnimMat PTR64 baseMat;
		ReactiveMotionModelPart PTR64 reactiveMotionParts;
		ReactiveMotionModelTweaks PTR64 reactiveMotionTweaks;
		Material PTR64  PTR64 materialHandles;
		XModelLodInfo lodInfo[6];
		XModelCollSurf_s PTR64 collSurfs;
		XBoneInfo PTR64 boneInfo;
		unsigned short PTR64 invHighMipRadius;
		PhysicsAsset PTR64 physAsset;
		PhysicsFXShape PTR64 physFxShape;
		char PTR64 unknown02;
		unsigned short unknownNamesCount;
		char unk_02[6]; // unknown data
		scr_string_t PTR64 unknownNames;
		unsigned char impactType;
		char unk_03[15]; // unknown data
		unsigned char unknown03Count;
		char PTR64 unknown03;
		unsigned char unknownIndex;
		unsigned char unknownVec3Count;
		char unk_04[6]; // unknown data
		vec3_t PTR64 unknownVec3;
		unsigned char unk;
		unsigned char unknown04Count;
		char unk_05[6]; // unknown data
		unk_1453E14D8 PTR64 unknown04;
	}; assert_sizeof(XModel, 0x2E0); // 736

	struct MayhemModel
	{
		XModel PTR64 model;
	};

	struct MayhemTransBounds
	{
		vec3_t mins;
		vec3_t size;
	};

	struct GfxWrappedBaseBuffer
	{
		ID3D11Resource PTR64 buffer;
		//ID3D11ShaderResourceView PTR64 view;
	};

	struct MayhemAnimFramesSplineCompressed
	{
		char PTR64 diskQuat;
		char PTR64 diskPos;
		unsigned __int16 PTR64 diskQuatFrames;
		unsigned __int16 PTR64 diskPosFrames;
		unsigned __int16 PTR64 numDiskQuatFrames;
		unsigned __int16 PTR64 numDiskPosFrames;
		MayhemTransBounds PTR64 transBounds;
		GfxWrappedBaseBuffer quat;
		GfxWrappedBaseBuffer pos;
		unsigned int quatStride;
		unsigned int posStride;
		unsigned int totalCompressedQuatFrames;
		unsigned int totalCompressedPosFrames;
	}; assert_sizeof(MayhemAnimFramesSplineCompressed, 0x58);

	struct MayhemAnimFramesUncompressed
	{
		char PTR64 diskQuat;
		char PTR64 diskPos;
		MayhemTransBounds PTR64 transBounds;
		GfxWrappedBaseBuffer quat;
		GfxWrappedBaseBuffer pos;
		unsigned int quatStride;
		unsigned int posStride;
	}; assert_sizeof(MayhemAnimFramesUncompressed, 0x30);

	union MayhemFramesUnion
	{
		void PTR64 data;
		MayhemAnimFramesSplineCompressed PTR64 splineCompressedFrames;
		MayhemAnimFramesUncompressed PTR64 uncompressedFrames;
	};

	struct MayhemDataKeysSplineCompressed
	{
		char PTR64 keys;
		unsigned __int16 PTR64 numKeys;
		unsigned __int16 PTR64 keyFrames;
		unsigned int totalCompressedKeyFrames;
		unsigned int numStreams;
		unsigned int keyStride;
	}; assert_sizeof(MayhemDataKeysSplineCompressed, 0x28);

	struct MayhemDataKeysUncompressed
	{
		char PTR64 keys;
		unsigned int numStreams;
		unsigned int keyStride;
	}; assert_sizeof(MayhemDataKeysUncompressed, 0x10);

	union MayhemDataChannelsUnion
	{
		void PTR64 data;
		MayhemDataKeysSplineCompressed PTR64 splineCompressedKeys;
		MayhemDataKeysUncompressed PTR64 uncompressedKeys;
	};

	struct MayhemAnim
	{
		MayhemFramesUnion frames;
		unsigned int numBones;
		unsigned int numFrames;
		float framerate;
		float frequency;
		unsigned int notifyCount;
		unsigned int dataChannelCount;
		bool isLooping;
		bool isSplineCompressed;
		bool quantizeQuats;
		bool quantizeTrans;
		bool quantizeChannels;
		XAnimNotifyInfo PTR64 notify;
		MayhemDataChannelsUnion dataChannels;
	}; assert_sizeof(MayhemAnim, 56);

	struct MayhemObject
	{
		unsigned int modelIndex;
		unsigned int animIndex;
	};

	struct MayhemData
	{
		const char PTR64 name;
		XModel PTR64 preModel;
		XModel PTR64 postModel;
		unsigned int numModels;
		MayhemModel PTR64 models;
		unsigned int numAnims;
		MayhemAnim PTR64 anims;
		unsigned int numObjects;
		MayhemObject PTR64 objects;
		float length;
	}; assert_sizeof(MayhemData, 0x50);

	enum MaterialTechniqueType
	{
		TECHNIQUE_DEPTH_PREPASS = 0,
		TECHNIQUE_DEPTH_PREPASS_VELOCITY_RIGID = 1,
		TECHNIQUE_DEPTH_PREPASS_VELOCITY_SKINNED = 2,
		TECHNIQUE_DEPTH_PREPASS_OBJECTID = 3,
		TECHNIQUE_DEPTH_PREPASS_OBJECTID_VELOCITY_RIGID = 1,
		TECHNIQUE_DEPTH_PREPASS_OBJECTID_VELOCITY_SKINNED = 2,
		TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 6,
		TECHNIQUE_BUILD_SHADOWMAP_COLOR = 7,
		TECHNIQUE_UNLIT = 8,
		TECHNIQUE_UNLIT_UNK = 9,
		TECHNIQUE_EMISSIVE = 10,
		TECHNIQUE_EMISSIVE_UNK = 11,
		TECHNIQUE_EMISSIVE_DEBUG = 12,
		TECHNIQUE_LIT = 13,
		//TECHNIQUE_LIT_ = 14
		//TECHNIQUE_LIT_ = 15
		//TECHNIQUE_LIT_ = 16
		//TECHNIQUE_LIT_ = 17
		//TECHNIQUE_LIT_ = 18
		//TECHNIQUE_LIT_ = 19
		//TECHNIQUE_LIT_ = 20
		//TECHNIQUE_LIT_ = 21
		//TECHNIQUE_LIT_ = 22
		//TECHNIQUE_LIT_ = 23
		//TECHNIQUE_LIT_ = 24
		//TECHNIQUE_LIT_ = 25
		//TECHNIQUE_LIT_ = 26
		TECHNIQUE_THERMAL = 27,
		TECHNIQUE_VELOCITY_RIGID = 28,
		TECHNIQUE_VELOCITY_SKINNED = 29,
		TECHNIQUE_DEBUG_BUMPMAP = 30,
		// 31
		// 32
		// 33
		// 34
		// 35
		// 36
		// 37
		TECHNIQUE_INSTANCED_DEPTH_PREPASS = 38,
		TECHNIQUE_INSTANCED_DEPTH_PREPASS_VELOCITY_RIGID = 39,
		TECHNIQUE_INSTANCED_DEPTH_PREPASS_VELOCITY_SKINNED = 40,
		TECHNIQUE_INSTANCED_DEPTH_PREPASS_OBJECTID = 41,
		TECHNIQUE_INSTANCED_DEPTH_PREPASS_OBJECTID_VELOCITY_RIGID = 42,
		TECHNIQUE_INSTANCED_DEPTH_PREPASS_OBJECTID_VELOCITY_SKINNED = 43,
		TECHNIQUE_INSTANCED_BUILD_SHADOWMAP_DEPTH = 44,
		TECHNIQUE_INSTANCED_BUILD_SHADOWMAP_COLOR = 45,
		TECHNIQUE_INSTANCED_UNLIT = 46,
		TECHNIQUE_INSTANCED_UNLIT_UNK = 47,
		TECHNIQUE_INSTANCED_EMISSIVE = 48,
		TECHNIQUE_INSTANCED_EMISSIVE_UNK = 49,
		TECHNIQUE_INSTANCED_EMISSIVE_DEBUG = 50,
		TECHNIQUE_INSTANCED_LIT = 51,
		//TECHNIQUE_INSTANCED_LIT_ = 52
		//TECHNIQUE_INSTANCED_LIT_ = 53
		//TECHNIQUE_INSTANCED_LIT_ = 54
		//TECHNIQUE_INSTANCED_LIT_ = 55
		//TECHNIQUE_INSTANCED_LIT_ = 56
		//TECHNIQUE_INSTANCED_LIT_ = 57
		//TECHNIQUE_INSTANCED_LIT_ = 58
		//TECHNIQUE_INSTANCED_LIT_ = 59
		//TECHNIQUE_INSTANCED_LIT_ = 60
		//TECHNIQUE_INSTANCED_LIT_ = 61
		//TECHNIQUE_INSTANCED_LIT_ = 62
		//TECHNIQUE_INSTANCED_LIT_ = 63
		//TECHNIQUE_INSTANCED_LIT_ = 64
		TECHNIQUE_INSTANCED_THERMAL = 65,
		TECHNIQUE_INSTANCED_VELOCITY_RIGID = 66,
		TECHNIQUE_INSTANCED_VELOCITY_SKINNED = 67,
		TECHNIQUE_INSTANCED_DEBUG_BUMPMAP = 68,
		// 69
		// 70
		// 71
		// 72
		// 73
		// 74
		// 75
		TECHNIQUE_SUBDIV_DEPTH_PREPASS = 76,
		TECHNIQUE_SUBDIV_DEPTH_PREPASS_VELOCITY_RIGID = 77,
		TECHNIQUE_SUBDIV_DEPTH_PREPASS_VELOCITY_SKINNED = 78,
		TECHNIQUE_SUBDIV_DEPTH_PREPASS_OBJECTID = 79,
		TECHNIQUE_SUBDIV_DEPTH_PREPASS_OBJECTID_VELOCITY_RIGID = 80,
		TECHNIQUE_SUBDIV_DEPTH_PREPASS_OBJECTID_VELOCITY_SKINNED = 81,
		TECHNIQUE_SUBDIV_BUILD_SHADOWMAP_DEPTH = 82,
		TECHNIQUE_SUBDIV_BUILD_SHADOWMAP_COLOR = 83,
		TECHNIQUE_SUBDIV_UNLIT = 84,
		TECHNIQUE_SUBDIV_UNLIT_UNK = 85,
		TECHNIQUE_SUBDIV_EMISSIVE = 86,
		TECHNIQUE_SUBDIV_EMISSIVE_UNK = 87,
		TECHNIQUE_SUBDIV_EMISSIVE_DEBUG = 88,
		TECHNIQUE_SUBDIV_LIT = 89,
		//TECHNIQUE_SUBDIV_LIT_ = 90
		//TECHNIQUE_SUBDIV_LIT_ = 91
		//TECHNIQUE_SUBDIV_LIT_ = 92
		//TECHNIQUE_SUBDIV_LIT_ = 93
		//TECHNIQUE_SUBDIV_LIT_ = 94
		//TECHNIQUE_SUBDIV_LIT_ = 95
		//TECHNIQUE_SUBDIV_LIT_ = 96
		//TECHNIQUE_SUBDIV_LIT_ = 97
		//TECHNIQUE_SUBDIV_LIT_ = 98
		//TECHNIQUE_SUBDIV_LIT_ = 99
		//TECHNIQUE_SUBDIV_LIT_ = 100
		//TECHNIQUE_SUBDIV_LIT_ = 101
		//TECHNIQUE_SUBDIV_LIT_ = 102
		TECHNIQUE_SUBDIV_THERMAL = 103,
		TECHNIQUE_SUBDIV_VELOCITY_RIGID = 104,
		TECHNIQUE_SUBDIV_VELOCITY_SKINNED = 105,
		TECHNIQUE_SUBDIV_DEBUG_BUMPMAP = 106,
		// 107
		// 108
		// 109
		// 110
		// 111
		// 112
		// 113
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS = 114,
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS_VELOCITY_RIGID = 115,
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS_VELOCITY_SKINNED = 116,
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS_OBJECTID = 117,
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS_OBJECTID_VELOCITY_RIGID = 118,
		TECHNIQUE_NO_DISPLACEMENT_DEPTH_PREPASS_OBJECTID_VELOCITY_SKINNED = 119,
		TECHNIQUE_NO_DISPLACEMENT_BUILD_SHADOWMAP_DEPTH = 120,
		TECHNIQUE_NO_DISPLACEMENT_BUILD_SHADOWMAP_COLOR = 121,
		TECHNIQUE_NO_DISPLACEMENT_UNLIT = 122,
		TECHNIQUE_NO_DISPLACEMENT_UNLIT_UNK = 123,
		TECHNIQUE_NO_DISPLACEMENT_EMISSIVE = 124,
		TECHNIQUE_NO_DISPLACEMENT_EMISSIVE_UNK = 125,
		TECHNIQUE_NO_DISPLACEMENT_EMISSIVE_DEBUG = 126,
		TECHNIQUE_NO_DISPLACEMENT_LIT = 127,
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 128
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 129
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 130
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 131
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 132
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 133
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 134
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 135
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 136
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 137
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 138
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 139
		//TECHNIQUE_NO_DISPLACEMENT_LIT_ = 140
		TECHNIQUE_NO_DISPLACEMENT_THERMAL = 141,
		TECHNIQUE_NO_DISPLACEMENT_VELOCITY_RIGID = 142,
		TECHNIQUE_NO_DISPLACEMENT_VELOCITY_SKINNED = 143,
		TECHNIQUE_NO_DISPLACEMENT_DEBUG_BUMPMAP = 144,
		// 145
		// 146
		// 147
		// 148
		// 149
		// 150
		// 151
		TECHNIQUE_COUNT = 152,
	};

	struct Packed128
	{
		std::uint64_t p0;
		std::uint64_t p1;
	};

	struct GfxDrawSurfFields
	{

	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		Packed128 packed;
	};

	enum SurfaceTypeBits : std::uint64_t
	{

	};

	struct MaterialInfo
	{
		const char PTR64 name;
		unsigned char gameFlags;
		unsigned char unkFlags;
		unsigned char sortKey;
		unsigned char textureAtlasRowCount;
		unsigned char textureAtlasColumnCount;
		unsigned char textureAtlasFrameBlend;
		unsigned char textureAtlasAsArray;
		unsigned char renderFlags;
		GfxDrawSurf drawSurf;
		SurfaceTypeBits surfaceTypeBits;
		unsigned int hashIndex;
	}; assert_sizeof(MaterialInfo, 48);

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		unsigned char samplerState;
		unsigned char semantic;
		GfxImage PTR64 image;
	}; assert_sizeof(MaterialTextureDef, 16);

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	}; assert_sizeof(MaterialConstantDef, 32);

	struct GfxStateBits
	{
		unsigned int loadBits[6]; // loadbits[3], blendstatebits[3]
		unsigned short zone;
		unsigned char depthStencilState[14];
		unsigned char blendState;
		unsigned char rasterizerState;
	}; assert_sizeof(GfxStateBits, 44);
	assert_offsetof(GfxStateBits, zone, 24);

	struct MaterialConstantBufferDef
	{
		unsigned int vsDataSize;
		unsigned int hsDataSize;
		unsigned int dsDataSize;
		unsigned int psDataSize;
		unsigned int vsOffsetDataSize;
		unsigned int hsOffsetDataSize;
		unsigned int dsOffsetDataSize;
		unsigned int psOffsetDataSize;
		unsigned char PTR64 vsData;
		unsigned char PTR64 hsData;
		unsigned char PTR64 dsData;
		unsigned char PTR64 psData;
		unsigned short PTR64 vsOffsetData;
		unsigned short PTR64 hsOffsetData;
		unsigned short PTR64 dsOffsetData;
		unsigned short PTR64 psOffsetData;
		ID3D11Buffer PTR64 vsConstantBuffer;
		ID3D11Buffer PTR64 hsConstantBuffer;
		ID3D11Buffer PTR64 dsConstantBuffer;
		ID3D11Buffer PTR64 psConstantBuffer;
	};

	struct Material
	{
		union
		{
			const char PTR64 name;
			MaterialInfo info;
		};
		unsigned char textureCount;
		unsigned char constantCount;
		unsigned char stateFlags;
		unsigned char cameraRegion;
		unsigned char materialType;
		unsigned char layerCount;
		unsigned char assetFlags;
		char pad;
		MaterialTechniqueSet PTR64 techniqueSet;
		MaterialTextureDef PTR64 textureTable;
		MaterialConstantDef PTR64 constantTable;
		unsigned char stateBitsEntry[152];
		unsigned char stateBitsCount;
		GfxStateBits PTR64 stateBitsTable;
		unsigned char PTR64 constantBufferIndex; // [152]
		MaterialConstantBufferDef PTR64 constantBufferTable;
		unsigned char constantBufferCount;
		const char PTR64  PTR64 subMaterials;
	}; assert_sizeof(Material, 0x118);
	assert_offsetof(Material, techniqueSet, 56);
	assert_offsetof(Material, textureCount, 48);
	assert_offsetof(Material, constantCount, 49);
	assert_offsetof(Material, stateBitsTable, 240);
	assert_offsetof(Material, constantBufferIndex, 248);
	assert_offsetof(Material, stateBitsCount, 232);
	assert_offsetof(Material, constantBufferTable, 256);
	assert_offsetof(Material, constantBufferCount, 264);
	assert_offsetof(Material, subMaterials, 272);
	assert_offsetof(Material, layerCount, 53);

	struct GfxComputeShaderLoadDef
	{
		unsigned char PTR64 program;
		unsigned int programSize;
	};

	struct ComputeShaderProgram
	{
		ID3D11ComputeShader PTR64 cs;
		GfxComputeShaderLoadDef loadDef;
	};

	struct ComputeShader
	{
		const char PTR64 name;
		const char PTR64 debugName;
		ComputeShaderProgram prog;
	}; assert_sizeof(ComputeShader, 0x28);

	struct GfxPixelShaderLoadDef
	{
		unsigned char PTR64 program;
		unsigned int programSize;
		unsigned int microCodeCrc;
	};

	struct MaterialPixelShaderProgram
	{
		ID3D11PixelShader PTR64 ps;
		GfxPixelShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char PTR64 name;
		const char PTR64 debugName;
		MaterialPixelShaderProgram prog;
	}; assert_sizeof(MaterialPixelShader, 0x28);

	struct GfxVertexShaderLoadDef
	{
		unsigned char PTR64 program;
		unsigned int programSize;
		unsigned int microCodeCrc;
	};

	struct MaterialVertexShaderProgram
	{
		ID3D11VertexShader PTR64 vs;
		GfxVertexShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char PTR64 name;
		const char PTR64 debugName;
		MaterialVertexShaderProgram prog;
	}; assert_sizeof(MaterialVertexShader, 0x28);

	struct GfxHullShaderLoadDef
	{
		unsigned char PTR64 program;
		unsigned int programSize;
	};

	struct MaterialHullShaderProgram
	{
		ID3D11HullShader PTR64 hs;
		GfxHullShaderLoadDef loadDef;
	};

	struct MaterialHullShader
	{
		const char PTR64 name;
		const char PTR64 debugName;
		MaterialHullShaderProgram prog;
	}; assert_sizeof(MaterialHullShader, 0x28);

	struct GfxDomainShaderLoadDef
	{
		unsigned char PTR64 program;
		unsigned int programSize;
	};

	struct MaterialDomainShaderProgram
	{
		ID3D11DomainShader PTR64 ds;
		GfxDomainShaderLoadDef loadDef;
	};

	struct MaterialDomainShader
	{
		const char PTR64 name;
		const char PTR64 debugName;
		MaterialDomainShaderProgram prog;
	}; assert_sizeof(MaterialDomainShader, 0x28);

	struct MaterialStreamRouting
	{
		unsigned char source;
		unsigned char dest;
		unsigned char mask;
	};

	struct MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[34];
		ID3D11InputLayout PTR64 decl[270];
	};

	struct MaterialVertexDeclaration
	{
		const char PTR64 name;
		unsigned char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
	}; assert_sizeof(MaterialVertexDeclaration, 0x8E8);

	struct MaterialArgumentCodeConst
	{
		unsigned short index;
		unsigned char firstRow;
		unsigned char rowCount;
	};

	union MaterialArgumentDef
	{
		const float PTR64 literalConst;
		MaterialArgumentCodeConst codeConst;
		unsigned int codeSampler;
		unsigned int nameHash;
	};

	enum MaterialShaderArgumentType : std::uint8_t
	{

	};

	struct MaterialShaderArgument
	{
		unsigned char type;
		unsigned char shader;
		unsigned short dest;
		MaterialArgumentDef u;
	}; assert_sizeof(MaterialShaderArgument, 0x10);

	struct MaterialPass
	{
		MaterialVertexShader PTR64 vertexShader;
		MaterialVertexDeclaration PTR64 vertexDecl;
		MaterialHullShader PTR64 hullShader;
		MaterialDomainShader PTR64 domainShader;
		MaterialPixelShader PTR64 pixelShader;
		unsigned char pixelOutputMask;
		unsigned char perPrimArgCount;
		unsigned char perObjArgCount;
		unsigned char stableArgCount;
		unsigned short perPrimArgSize;
		unsigned short perObjArgSize;
		unsigned short stableArgSize;
		unsigned short zone;
		unsigned char perPrimConstantBuffer;
		unsigned char perObjConstantBuffer;
		unsigned char stableConstantBuffer;
		unsigned int customBufferFlags;
		unsigned char customSamplerFlags;
		unsigned char precompiledIndex;
		unsigned char stageConfig;
		char __pad0[33];
		MaterialShaderArgument PTR64 args;
	}; assert_sizeof(MaterialPass, 104);
	assert_offsetof(MaterialPass, zone, 50);
	assert_offsetof(MaterialPass, args, 96);

	struct MaterialTechniqueHeader
	{
		const char PTR64 name;
		unsigned short flags;
		unsigned short passCount;
	}; assert_sizeof(MaterialTechniqueHeader, 0x10);

	struct MaterialTechnique
	{
		MaterialTechniqueHeader hdr;
		MaterialPass passArray[1];
	};

	enum TechniqueMask
	{
		TECHNIQUE_MASK = 0x3F,
		NUM_TECHNIQUE_MASK_ELEMS = 3, // TECHNIQUE_COUNT / 64
	};

	struct MaterialTechniqueSet
	{
		const char PTR64 name;
		unsigned short flags;
		unsigned char worldVertFormat;
		unsigned char preDisplacementOnlyCount;
		unsigned short techniqueCount;
		short techniqueMaskStartIndex[3];
		short unk[2];
		unsigned __int64 techniqueMask[3];
		MaterialTechnique PTR64  PTR64 techniques;
	}; assert_sizeof(MaterialTechniqueSet, 0x38);
	assert_offsetof(MaterialTechniqueSet, techniqueCount, 12);
	assert_offsetof(MaterialTechniqueSet, techniques, 48);

	enum GfxImageFlags : std::uint32_t
	{
		IMG_FLAG_NONE = 0x0,
		IMG_DISK_FLAG_NOPICMIP = 0x1,
		IMG_DISK_FLAG_NOMIPMAPS = 0x2,
		IMG_DISK_FLAG_UNUSED = 0x4,
		IMG_DISK_FLAG_NORMAL_OCCLUSON_GLOSS = 0x8,
		IMG_DISK_FLAG_CLAMP_U = 0x10,
		IMG_DISK_FLAG_CLAMP_V = 0x20,
		IMG_DISK_FLAG_STREAMED = 0x40,
		IMG_DISK_FLAG_USE_OODLE_COMPRESSION = 0x80,
		IMG_DISK_FLAG_GAMMA_SRGB = 0x100,
		IMG_DISK_FLAG_PACKED_ATLAS = 0x200,
		IMG_CREATE_FLAG_UNTILED = 0x400,
		IMG_CREATE_FLAG_CPU_READ = 0x800,
		IMG_CREATE_FLAG_CPU_WRITE = 0x1000,
		IMG_DISK_FLAG_AUTOMETALNESS = 0x2000,
		IMG_DISK_FLAG_AUTODISPLACEMENT = 0x4000,
		IMG_DISK_FLAG_MAPTYPE_2D = 0x0,
		IMG_DISK_FLAG_MAPTYPE_CUBE = 0x8000,
		IMG_DISK_FLAG_MAPTYPE_3D = 0x10000,
		IMG_DISK_FLAG_MAPTYPE_1D = 0x18000,
		IMG_DISK_FLAG_MAPTYPE_ARRAY = 0x20000,
		IMG_DISK_FLAG_MAPTYPE_CUBE_ARRAY = 0x28000,
		IMG_DISK_FLAG_INVERT_ALPHA = 0x40000,
		IMG_DISK_FLAG_PREMUL_ALPHA = 0x80000,
		IMG_DISK_FLAG_MIPGEN_ORIGINAL = 0x0,
		IMG_DISK_FLAG_MIPGEN_LANCZOS3 = 0x100000,
		IMG_DISK_FLAG_MIPGEN_CATMULL_ROM = 0x200000,
		IMG_DISK_FLAG_MIPGEN_CUBIC_BSPLINE = 0x300000,
		IMG_DISK_FLAG_MIPGEN_BOX = 0x400000,
		IMG_DISK_FLAG_MIPGEN_COVERAGE_PRESERVING = 0x500000,
		IMG_CREATE_FLAG_RW_VIEW = 0x800000,
		IMG_CREATE_FLAG_DYNAMIC = 0x1000000,
		IMG_DISK_FLAG_PREMUL_KEEP_ALPHA = 0x2000000,
		IMG_DISK_FLAG_RTT = 0x4000000,
		IMG_DISK_FLAG_EXTRACT_ALPHA = 0x8000000,
		IMG_DISK_FLAG_OCTAHEDRON = 0x10000000,
		IMG_CREATE_FLAG_STAGING = 0x20000000,
		IMG_CREATE_FLAG_VOLUMETRIC_LAYOUT_OVERRIDE = 0x40000000,
		IMG_CREATE_FLAG_TYPELESS = 0x80000000,
	};

	enum MapType : std::uint8_t
	{
		MAPTYPE_NONE = 0x0,
		MAPTYPE_INVALID1 = 0x1,
		MAPTYPE_1D = 0x2,
		MAPTYPE_2D = 0x3,
		MAPTYPE_3D = 0x4,
		MAPTYPE_CUBE = 0x5,
		MAPTYPE_ARRAY = 0x6,
		MAPTYPE_CUBE_ARRAY = 0x7,
		MAPTYPE_COUNT = 0x8,
	};

	enum TextureSemantic : std::uint8_t
	{
		TS_2D = 0x0,
		TS_FUNCTION = 0x1,
		TS_COLOR_MAP = 0x2,
		TS_DETAIL_MAP = 0x3,
		TS_UNUSED_4 = 0x4,
		TS_NORMAL_MAP = 0x5,
		TS_UNUSED_6 = 0x6,
		TS_UNUSED_7 = 0x7,
		TS_SPECULAR_MAP = 0x8,
		TS_SPECULAR_OCCLUSION_MAP = 0x9,
		TS_UNUSED_10 = 0xA,
		TS_THINFILM_MAP = 0xB,
		TS_DISPLACEMENT_MAP = 0xC,
		TS_PARALLAX_MAP = 0xD,
		TS_COLOR_SPECULAR_MAP = 0xE,
		TS_NORMAL_OCCLUSSION_GLOSS_MAP = 0xF,
		TS_ALPHA_REVEAL_THICKNESS_MAP = 0x10,
		TS_COUNT = 0x11,
	};

	enum GfxImageCategory : std::uint8_t
	{
		IMG_CATEGORY_UNKNOWN = 0x0,
		IMG_CATEGORY_AUTO_GENERATED = 0x1,
		IMG_CATEGORY_LIGHTMAP = 0x2,
		IMG_CATEGORY_LOAD_FROM_FILE = 0x3,
		IMG_CATEGORY_RAW = 0x4,
		IMG_CATEGORY_FIRST_UNMANAGED = 0x5,
		IMG_CATEGORY_RENDERTARGET = 0x5,
		IMG_CATEGORY_TEMP = 0x6,
	};

	struct GfxImageLoadDef
	{
		char levelCount;
		char numElements;
		char pad[2];
		int flags;
		int format;
		int resourceSize;
		char data[1];
	};

	struct GfxTexture
	{
		union
		{
			ID3D11Texture1D PTR64 linemap;
			ID3D11Texture2D PTR64 map;
			ID3D11Texture3D PTR64 volmap;
			ID3D11Texture2D PTR64 cubemap;
			GfxImageLoadDef PTR64 loadDef;
		};
		ID3D11ShaderResourceView PTR64 shaderView;
		ID3D11ShaderResourceView PTR64 shaderViewAlternate;
	};

	struct PicMip
	{
		unsigned char platform[2];
	};

	struct CardMemory
	{
		unsigned char platform[2];
	};

	struct GfxImageStreamLevelCountAndSize
	{
		unsigned int pixelSize : 26;
		unsigned int levelCount : 6;
	};

	struct GfxImageStreamData
	{
		unsigned short width;
		unsigned short height;
		GfxImageStreamLevelCountAndSize levelCountAndSize;
	};

	struct GfxImage
	{
		GfxTexture texture;
		DXGI_FORMAT imageFormat;
		unsigned int flags;
		MapType mapType;
		TextureSemantic semantic;
		GfxImageCategory category;
		PicMip picmip;
		CardMemory cardMemory;
		unsigned int dataLen1;
		unsigned int dataLen2;
		unsigned short width;
		unsigned short height;
		unsigned short depth;
		unsigned short numElements;
		unsigned char levelCount;
		unsigned char streamed;
		unsigned char unknown1;
		unsigned char PTR64 pixelData;
		GfxImageStreamData streams[4];
		const char PTR64 name;
	}; assert_sizeof(GfxImage, 0x70);

	struct snd_volmod_info_t
	{
		char name[64];
		unsigned int id;
		float value;
	};

	enum SndEntchannelSpaitalType
	{
		SND_ENTCHAN_TYPE_2D = 0x0,
		SND_ENTCHAN_TYPE_3D = 0x1,
		SND_ENTCHAN_TYPE_PA_SPEAKER = 0x2,
	};

	enum SndLimitBehavior
	{
		LIMIT_BEHAVIOR_NO_NEW = 0x0,
		LIMIT_BEHAVIOR_REPLACE_QUIETER = 0x1,
		LIMIT_BEHAVIOR_REPLACE_OLDEST = 0x2,
		LIMIT_BEHAVIOR_REPLACE_FARTHEST = 0x3,
		LIMIT_BEHAVIOR_COUNT = 0x4,
	};

	enum SndFarReverbBehavior
	{
		SND_FAR_REVERB_NONE = 0x0,
		SND_FAR_REVERB_FULL = 0x1,
		SND_FAR_REVERB_WET_ONLY = 0x2,
	};

	struct snd_entchannel_info_t
	{
		char name[64];
		unsigned int id;
		int priority;
		SndEntchannelSpaitalType spatialType;
		bool isRestricted;
		bool isPausable;
		int maxVoices;
		SndLimitBehavior limitBehavior;
		bool centerSpeakerPan;
		SndFarReverbBehavior mpFarReverbBehavior;
		SndFarReverbBehavior spFarReverbBehavior;
		SndFarReverbBehavior cpFarReverbBehavior;
	}; assert_sizeof(snd_entchannel_info_t, 104);

	struct DopplerPreset
	{
		char name[64];
		unsigned int id;
		float speedOfSound;
		float playerVelocityScale;
		float minPitch;
		float maxPitch;
		float smoothing;
	}; assert_sizeof(DopplerPreset, 88);

	struct OcclusionShape
	{
		char name[64];
		unsigned int id;
		float unk;
		float innerAngleVolume;
		float outerAngleVolume;
		float occludedVolume;
		float innerAngleLPF;
		float outerAngleLPF;
		float occludedLPF;
	}; assert_sizeof(OcclusionShape, 96);

	struct SndCurve
	{
		char name[64];
		unsigned int id;
		int numPoints;
		vec2_t points[16];
	};
	assert_sizeof(SndCurve, 200);

	struct SpeakerMap
	{
		char name[64];
		unsigned int id;
		float monoToStereo[2];
		float stereoToStereo[4];
		float monoTo51[6];
		float stereoTo51[12];
		float monoTo71[8];
		float stereoTo71[16];
	}; assert_sizeof(SpeakerMap, 260);

	struct SndContext
	{
		char PTR64 type;
		unsigned int typeId;
		int numValues;
		int startIndex;
		bool allowDefaults;
		bool includeDefaultsInRandom;
		bool canBlend;
	}; assert_sizeof(SndContext, 24);

	struct SndContextValue
	{
		char PTR64 value;
		unsigned int valueId;
	};

	struct SndMasterEqParam
	{
		int enabled;
		float gain;
		float frequency;
		float q;
	};

	struct SndMasterEqParamBank
	{
		SndMasterEqParam low;
		SndMasterEqParam peak1;
		SndMasterEqParam peak2;
		SndMasterEqParam high;
	};

	struct SndDynamicsParams
	{
		int enable;
		float preGain;
		float postGain;
		float threshold;
		float ratio;
		float timeAttack;
		float timeRelease;
		float spread;
		int linear;
		int ITU1770;
	};

	struct SndMaster
	{
		char name[64];
		unsigned int id;
		SndMasterEqParamBank dialogEq;
		SndMasterEqParamBank weapExpScenesEq;
		SndMasterEqParamBank sfxEq;
		SndMasterEqParamBank mainEq;
		SndDynamicsParams dialogDyn;
		SndDynamicsParams sfxDyn;
		SndDynamicsParams mainDyn;
		float busDialogGain;
		float busWeapExpSceneGain;
		float busSfxGain;
		float busReverbGain;
		float busMusicGain;
		float busMovieGain;
		float busReferenceGain;
		int busDialogEnable;
		int busWeapExpSceneEnable;
		int busSfxEnable;
		int busReverbEnable;
		int busMusicEnable;
		int busMovieEnable;
		int busReferenceEnable;
	}; assert_sizeof(SndMaster, 500);

	struct SndGlobals
	{
		const char PTR64 name;
		float globalVolumeModifier;
		float binkVolumeModifier;
		unsigned int volmodinfoCount;
		snd_volmod_info_t PTR64 volmodinfo;
		unsigned int entchannelCount;
		snd_entchannel_info_t PTR64 entchannelInfo;
		unsigned int dopplerPresetCount;
		DopplerPreset PTR64 dopplerPresets;
		unsigned int occlusionShapeCount;
		OcclusionShape PTR64 occlusionShapes;
		unsigned int vfCurveCount;
		SndCurve PTR64 vfCurves;
		unsigned int lpfCurveCount;
		SndCurve PTR64 lpfCurves;
		unsigned int hpfCurveCount;
		SndCurve PTR64 hpfCurves;
		unsigned int rvbCurveCount;
		SndCurve PTR64 rvbCurves;
		unsigned int speakerMapCount;
		SpeakerMap PTR64 speakerMaps;
		unsigned int contextCount;
		SndContext PTR64 contexts;
		unsigned int contextValueCount;
		SndContextValue PTR64 contextValues;
		unsigned int masterCount;
		SndMaster PTR64 masters;
	}; assert_sizeof(SndGlobals, 0xD0);

	enum SoundVolMod : std::int32_t
	{
		SND_VOLMOD_DEFAULT,
		SND_VOLMOD_HUD,
		SND_VOLMOD_VOICEOVER = 28,
	};

	struct SndAlias
	{
		const char PTR64 aliasName;
		const char PTR64 subtitle;
		const char PTR64 secondaryAliasName;
		const char PTR64 unk_24;
		const char PTR64 assetFileName;
		unsigned int id;
		unsigned int secondaryId;
		unsigned int unk_48;
		unsigned int assetId;
		unsigned int contextType;
		unsigned int contextValue;
		unsigned int duck;
		int sequence;
		float volMin;
		float volMax;
		int volModIndex;
		float pitchMin;
		float pitchMax;
		float donutFadeEnd;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		int masterPriority;
		float masterPercentage;
		float slavePercentage;
		float probability;
		float lfePercentage;
		float centerPercentage;
		int startDelay;
		int volumeFalloffCurve; // guess
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		int speakerMap; // guess
		float reverbMultiplier;
		float farReverbMultiplier;
		int dopplerPreset; // guess
		float smartPanDistance2d;
		float smartPanDistance3d;
		float smartPanAttenuation2d;
		float stereoSpreadMinDist;
		float stereoSpreadMaxDist;
		float stereoSpreadMidPoint;
		int stereoSpreadMaxAngle;
	}; assert_sizeof(SndAlias, 200);
	assert_offsetof(SndAlias, flags, 108);

	struct SndAliasList
	{
		const char PTR64 aliasName;
		unsigned int id;
		SndAlias PTR64 head;
		int count;
		int sequence;
	}; assert_sizeof(SndAliasList, 32);
	assert_offsetof(SndAliasList, head, 16);
	assert_offsetof(SndAliasList, count, 24);

	struct SndIndexEntry
	{
		unsigned short value;
		unsigned short next;
	}; assert_sizeof(SndIndexEntry, 4);

	struct SndSendEffectParams
	{
		char name[64];
		unsigned int id;
		float smoothing;
		float earlyTime;
		float lateTime;
		float earlyGain;
		float lateGain;
		float lateGainProx;
		float returnGain;
		float earlyLpf;
		float lateLpf;
		float inputLpf;
		float dampLpf;
		float wallReflect;
		float dryGain;
		float earlySize;
		float lateSize;
		float diffusion;
		float rearLevel;
	}; assert_sizeof(SndSendEffectParams, 136);

	enum ADSRCurve
	{
		ADSR_CURVE_LINEAR = 0x0,
		ADSR_CURVE_LOG_FAST = 0x1,
		ADSR_CURVE_LOG_SLOW = 0x2,
		ADSR_CURVE_FLAT_ENDED = 0x3,
		ADSR_CURVE_FLAT_MIDDLE = 0x4,
	};

	struct ADSRSetting
	{
		const char PTR64 name;
		unsigned int id;
		float attackLength;
		ADSRCurve attackCurve;
		float decayLength;
		ADSRCurve decayCurve;
		float releaseLength;
		ADSRCurve releaseCurve;
		float sustainLevel;
		float sustainLength;
	};

	struct AmbientDef
	{
		const char PTR64 name;
		unsigned int id;
		unsigned __int16 ambientEventIndex;
		unsigned __int16 numEvents;
		float timeMin;
		float timeMax;
	};

	struct AmbientEvent
	{
		unsigned int id;
		unsigned __int16 ambientElementIndex;
		float weight;
	};

	struct AmbientElement
	{
		unsigned int id;
		const char PTR64 unusedNameField;
		const char PTR64 aliasName;
		float rangeMin;
		float rangeMax;
		float coneMin;
		float coneMax;
	};

	enum SND_EQTYPE
	{
		SND_EQTYPE_FIRST = 0x0,
		SND_EQTYPE_LOWPASS = 0x0,
		SND_EQTYPE_HIGHPASS = 0x1,
		SND_EQTYPE_LOWSHELF = 0x2,
		SND_EQTYPE_HIGHSHELF = 0x3,
		SND_EQTYPE_BELL = 0x4,
		SND_EQTYPE_LAST = 0x4,
		SND_EQTYPE_COUNT = 0x5,
		SND_EQTYPE_INVALID = 0x5,
	};

	struct FilterDef
	{
		unsigned int id;
		char entChannelIdx;
		char band;
		SND_EQTYPE type;
		float freq;
		float gain;
		float q;
	};

	struct MixDef
	{
		unsigned int id;
		unsigned __int16 volModIndex;
		float volume;
		float fade;
	};

	struct AdsrZoneEntry
	{
		const char PTR64 name;
		unsigned int id;
		const char PTR64 weaponName;
		int adsrIdx;
		unsigned int weaponIdx;
	};

	struct OccludeDef
	{
		unsigned int id;
		unsigned __int16 entChannelIdx;
		float cutoffLevel1;
		float cutoffLevel2;
		float cutoffLevel3;
		float cutoffLevel4;
		float attnLevel1;
		float attnLevel2;
		float attnLevel3;
		float attnLevel4;
	};

	struct ReverbDef
	{
		unsigned int id;
		unsigned int roomTypeId;
		char roomType[64];
		float dryLevel;
		float wetLevel;
		float fadeTime;
	}; assert_sizeof(ReverbDef, 84);

	struct TimescaleEntry
	{
		unsigned int id;
		unsigned int presetName;
		int entChannelIdx;
		float scale;
	}; assert_sizeof(TimescaleEntry, 16);

	struct ZoneDef
	{
		unsigned int id;
		unsigned int stateId;
		__int16 reverbIndex;
		__int16 startOcclusionIndex;
		__int16 numOcclusion;
		__int16 startFilterIndex;
		__int16 numFilter;
		__int16 startMixIndex;
		__int16 numMix;
		const char PTR64 ambientStream;
		__int16 startAdsrZoneIndex;
		__int16 numAdsrZone;
		__int16 startNPCAdsrZoneIndex;
		__int16 numNPCAdsrZone;
		__int16 ambientDefIndex;
		__int16 numAmbientDef; // idk
		__int16 startFullOccIndex;
		__int16 numDisableFullOcc;
		__int16 startPlayerBreathStateIndex;
		__int16 numPlayerBreathStates;
		unsigned int weapReflId;
		//bool exterior;
		const char PTR64 zoneName;
		const char PTR64 stateName;
		const char PTR64 ambientName;
		const char PTR64 mixName;
		const char PTR64 reverbName;
		const char PTR64 filterName;
		const char PTR64 occlusionName;
		const char PTR64 plrAdsrName;
		const char PTR64 npcAdsrName;
		const char PTR64 weapReflName;
		const char PTR64 fullOccName;
		const char PTR64 playerBreathStateName;
		unsigned int contextType1;
		unsigned int contextValue1;
		unsigned int contextType2;
		unsigned int contextValue2;
		unsigned int contextType3;
		unsigned int contextValue3;
		unsigned int contextType4;
		unsigned int contextValue4;
		//unsigned int duck;
	}; assert_sizeof(ZoneDef, 184);

	struct unk_1453E2FD8
	{
		unsigned int id;
		int __pad0[13]; //char __pad0[56];
	}; assert_sizeof(unk_1453E2FD8, 56);

	struct FullOcclusionDef
	{
		unsigned int id;
		unsigned int presetName;
		int entChannelIdx;
	};

	struct PlayerBreathStateDef
	{
		unsigned int stateType;
		const char PTR64 inhaleAlias;
		const char PTR64 exhaleAlias;
		int minBreaths;
	};

	struct SoundTable
	{
		unsigned int id;
		ADSRSetting PTR64 adsrSettings;
		unsigned int adsrCount;
		AmbientDef PTR64 ambientDefs;
		unsigned int ambientDefCount;
		AmbientEvent PTR64 ambientEvents;
		unsigned int ambientEventCount;
		AmbientElement PTR64 ambientElements;
		unsigned int ambientElementsCount;
		FilterDef PTR64 filters;
		unsigned int filterCount;
		MixDef PTR64 mixes;
		unsigned int mixCount;
		AdsrZoneEntry PTR64 npcADSRZones;
		unsigned int npcADSRZoneCount;
		OccludeDef PTR64 occlusionFilters;
		unsigned int occlusionFilterCount;
		AdsrZoneEntry PTR64 playerADSRZones;
		unsigned int playerADSRZoneCount;
		ReverbDef PTR64 reverbs;
		unsigned int reverbCount;
		TimescaleEntry PTR64 timeScaleSettings;
		unsigned int timeScaleSettingCount;
		ZoneDef PTR64 zones;
		unsigned int zoneCount;
		unk_1453E2FD8 PTR64 unk;
		unsigned int unkCount;
		FullOcclusionDef PTR64 fullOcclusionDefs;
		unsigned int fullOcclusionDefCount;
		PlayerBreathStateDef PTR64 plrBreathStateDefs;
		unsigned int plrBreathStateDefCount;
	}; assert_sizeof(SoundTable, 248);

	struct SndDuck
	{
		char name[64];
		unsigned int id;
		float fadeIn;
		float fadeOut;
		float startDelay;
		float minDistance;
		float distance;
		float length;
		unsigned int fadeInCurve;
		unsigned int fadeOutCurve;
		float PTR64 hpf;
		float PTR64 lpf;
		bool updateWhilePaused;
		bool trackAmplitude;
		bool disableInSplitscreen;
		char pad;
		int unk1;
		int unk2;
		float aliasHpf;
		float aliasLpf;
		unsigned int duckAlias;
	}; assert_sizeof(SndDuck, 144);

	enum SndMusicAssetType
	{
		SND_MUSIC_INTRO = 0x0,
		SND_MUSIC_LOOP = 0x1,
		SND_MUSIC_EXIT = 0x2,
	};

	struct SndMusicAsset
	{
		char alias[64];
		unsigned int aliasId;
		int inactive;
		int completeLoop;
		int removeAfterPlay;
		int firstRandom;
		int startSync;
		int stopSync;
		int completeOnStop;
		unsigned int loopStartOffset;
		int bpm;
		int assetType;
		int loopNumber;
		unsigned int sampleCount;
		int startDelayBeats;
		int startFadeBeats;
		int stopDelayBeats;
		int stopFadeBeats;
		//int startOffsetFrames;
		int meter;
		unsigned int sampleRate;
	}; assert_sizeof(SndMusicAsset, 140);

	enum SndMusicStateStatus
	{
		SND_MUSIC_STATE_INACTIVE = 0x0,
		SND_MUSIC_STATE_ACTIVE = 0x1,
	};

	struct SndMusicState
	{
		char name[64];
		unsigned int id;
		SndMusicAsset intro;
		SndMusicAsset exit;
		unsigned int loopCount;
		SndMusicAsset PTR64 loops;
		int order;
		int interruptPriority;
		int persistPriority;
		bool isRandom;
		bool isSequential;
		bool skipPreviousExit;
		bool wallClockSync;
		unsigned int refCount;
		SndMusicStateStatus status;
	}; assert_sizeof(SndMusicState, 384);

	struct SndMusicSet
	{
		char name[64];
		unsigned int id;
		unsigned int stateCount;
		SndMusicState PTR64 states;
	}; assert_sizeof(SndMusicSet, 80);
	assert_offsetof(SndMusicSet, stateCount, 68);
	assert_offsetof(SndMusicSet, states, 72);

	struct SndBank
	{
		const char PTR64 name;
		const char PTR64 zone;
		const char PTR64 gameLanguage;
		const char PTR64 soundLanguage;
		unsigned int aliasCount;
		SndAliasList PTR64 alias;
		SndIndexEntry PTR64 aliasIndex;
		unsigned int sendEffectCount;
		SndSendEffectParams PTR64 sendEffects;
		SoundTable soundTable;
		unsigned int duckCount;
		SndDuck PTR64 ducks;
		unsigned int musicSetCount;
		SndMusicSet PTR64 musicSets;
	};
	assert_offsetof(SndBank, name, 0);
	assert_offsetof(SndBank, zone, 8);
	assert_offsetof(SndBank, gameLanguage, 16);
	assert_offsetof(SndBank, soundLanguage, 24);
	assert_offsetof(SndBank, aliasCount, 32);
	assert_offsetof(SndBank, aliasIndex, 48);
	assert_offsetof(SndBank, sendEffectCount, 56);
	assert_offsetof(SndBank, sendEffects, 64);
	assert_offsetof(SndBank, soundTable, 72);
	assert_offsetof(SndBank, duckCount, 320);
	assert_offsetof(SndBank, ducks, 328);
	assert_offsetof(SndBank, musicSetCount, 336);
	assert_offsetof(SndBank, musicSets, 344);

	struct SndBankResident
	{
		SndBank bank;
	}; assert_sizeof(SndBankResident, 0x160);

	struct SndBankTransient
	{
		const char PTR64 name;
		unsigned int elementCount;
		unsigned int PTR64 elements;
	}; assert_sizeof(SndBankTransient, 0x18);

	struct cplane_s
	{
		float normal[3];
		float dist;
		unsigned char type;
		unsigned char pad[3];
	}; assert_sizeof(cplane_s, 20);

	struct ClipInfo
	{
		int planeCount;
		cplane_s PTR64 planes;
	}; assert_sizeof(ClipInfo, 16);

	struct cStaticModel_s
	{
		XModel PTR64 xmodel;
		float origin[3];
		float invScaledAxis[3][3];
		float unk[2];
	}; assert_sizeof(cStaticModel_s, 0x40);

	struct unk_1453E2338
	{
		unsigned int num;
		int PTR64 unk;
	};

	struct Stage
	{
		const char PTR64 name;
		vec3_t origin;
		unsigned __int16 triggerIndex;
		char sunPrimaryLightIndex;
		unsigned int entityUID;
		char unk[20];
	}; assert_sizeof(Stage, 48);

	struct PhysicsCapacities
	{
		int maxNumRigidBodiesServer;
		int maxNumDetailRigidBodiesServer;
		int maxNumConstraintsServer;
		int maxNumMotionsServer;
		int maxNumRigidBodiesClient;
		int maxNumDetailRigidBodiesClient;
		int maxNumConstraintsClient;
		int maxNumMotionsClient;
	};

	struct CollisionHeatmapEntry
	{
		int vertexCount;
		float vertexDensity;
		vec3_t minExtent;
		vec3_t maxExtent;
	};

	struct TopDownMapDataHeader
	{
		int version;
		int samplesPerAxis;
		vec2_t bottomLeft;
		vec2_t topRight;
	};

	struct TopDownMapDataContent
	{
		char navMeshVisible[8193];
	};

	struct TopDownMapData
	{
		TopDownMapDataHeader header;
		TopDownMapDataContent content;
	}; assert_sizeof(TopDownMapData, 8220);

	struct TriggerModel
	{
		int contents;
		unsigned short hullCount;
		unsigned short firstHull;
		unsigned short windingCount;
		unsigned short firstWinding;
		unsigned int flags;
		PhysicsAsset PTR64 physicsAsset;
		unsigned short physicsShapeOverrideIdx;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned short slabCount;
		unsigned short firstSlab;
	};

	struct TriggerSlab
	{
		vec3_t dir;
		float midPoint;
		float halfSize;
	};

	struct TriggerWinding
	{
		vec3_t dir;
		unsigned short pointCount;
		unsigned short firstPoint;
		unsigned int flags;
	};

	struct TriggerWindingPoint
	{
		vec3_t loc;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel PTR64 models;
		unsigned int hullCount;
		TriggerHull PTR64 hulls;
		unsigned int slabCount;
		TriggerSlab PTR64 slabs;
		unsigned int windingCount;
		TriggerWinding PTR64 windings;
		unsigned int windingPointCount;
		TriggerWindingPoint PTR64 windingPoints;
	}; assert_sizeof(MapTriggers, 0x50);

	struct clipMap_t // __declspec(align(128))
	{
		const char PTR64 name;
		int isInUse;
		ClipInfo info;
		ClipInfo PTR64 pInfo;
		unsigned int numStaticModels;
		cStaticModel_s PTR64 staticModelList;
		unk_1453E2338 unk01;
		unsigned int numUnk02;
		unk_1453E2338 PTR64 unk02;
		MapEnts PTR64 mapEnts;
		Stage PTR64 stages;
		unsigned char stageCount;
		MapTriggers stageTrigger;
		vec3_t broadphaseMin;
		vec3_t broadphaseMax;
		PhysicsCapacities physicsCapacities;
		unsigned int havokWorldShapeDataSize;
		char PTR64 havokWorldShapeData;
		unsigned int numCollisionHeatmapEntries;
		CollisionHeatmapEntry PTR64 collisionHeatmap;
		TopDownMapData PTR64 topDownMapData;
		unsigned int checksum;
		char padding[88]; // alignment pad
	}; assert_sizeof(clipMap_t, 0x180);

	enum GfxLightType : std::uint8_t
	{
		GFX_LIGHT_TYPE_NONE = 0x0,
		GFX_LIGHT_TYPE_DIR = 0x1,
		GFX_LIGHT_TYPE_SPOT = 0x2,
		GFX_LIGHT_TYPE_OMNI = 0x3,
		GFX_LIGHT_TYPE_COUNT = 0x4,
		GFX_LIGHT_TYPE_DIR_SHADOWMAP = 0x4,
		GFX_LIGHT_TYPE_SPOT_SHADOWMAP = 0x5,
		GFX_LIGHT_TYPE_OMNI_SHADOWMAP = 0x6,
		GFX_LIGHT_TYPE_COUNT_WITH_SHADOWMAP_VERSIONS = 0x7,
		GFX_LIGHT_TYPE_SPOT_SHADOWMAP_CUCOLORIS = 0x7,
		GFX_LIGHT_TYPE_COUNT_WITH_ALL_VERSIONS = 0x8,
	};

	struct ComPrimaryLight
	{
		GfxLightType type;
		unsigned char canUseShadowMap;
		unsigned char needsDynamicShadows;
		unsigned char isVolumetric;
		unsigned char exponent;
		char unused[3];
		unsigned int transientZoneList;
		unsigned int entityId;
		float uvIntensity;
		float heatIntensity;
		float color[3];
		float dir[3];
		float up[3];
		float origin[3];
		float radius;
		vec2_t fadeOffsetRt;
		float bulbRadius;
		vec3_t bulbLength;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		float shadowSoftness;
		float shadowBias;
		float shadowArea;
		float distanceFalloff;
		float rotationLimit;
		float translationLimit;
		const char PTR64 defName;
	}; assert_sizeof(ComPrimaryLight, 144);

	struct ComPrimaryLightEnv
	{
		unsigned short primaryLightIndices[4];
		unsigned char numIndices;
	}; assert_sizeof(ComPrimaryLightEnv, 10);

	struct ComChangeListInfo
	{
		unsigned int changeListNumber;
		int time;
		const char PTR64 userName;
	}; assert_sizeof(ComChangeListInfo, 16);

	struct ComWorld
	{
		const char PTR64 name;
		int isInUse;
		int useForwardPlus;
		unsigned int bakeQuality;
		unsigned int primaryLightCount;
		ComPrimaryLight PTR64 primaryLights;
		unsigned int scriptablePrimaryLightCount;
		unsigned int firstScriptablePrimaryLight;
		unsigned int primaryLightEnvCount;
		ComPrimaryLightEnv PTR64 primaryLightEnvs;
		ComChangeListInfo changeListInfo;
		unsigned int numUmbraGates;
		const char PTR64 PTR64 umbraGateNames;
		int umbraGateInitialStates[4];
	}; assert_sizeof(ComWorld, 0x68);

	struct G_GlassPiece
	{
		unsigned short damageTaken;
		unsigned short collapseTime;
		int lastStateChangeTime;
		char impactDir;
		char impactPos[2];
	};

	struct G_GlassName
	{
		char PTR64 nameStr;
		scr_string_t name;
		unsigned short pieceCount;
		unsigned short PTR64 pieceIndices;
	};

	struct G_GlassData
	{
		G_GlassPiece PTR64 glassPieces;
		unsigned int pieceCount;
		unsigned short damageToWeaken;
		unsigned short damageToDestroy;
		unsigned int glassNameCount;
		G_GlassName PTR64 glassNames;
	};

	struct GlassWorld
	{
		const char PTR64 name;
		G_GlassData PTR64 g_glassData;
	};

	struct pathnode_t;
	struct pathnode_tree_t;

	struct pathnode_yaworient_t
	{
		float fLocalAngle;
		vec2_t localForward;
	};

	union PathNodeOrientationUnion
	{
		pathnode_yaworient_t yaw_orient;
		vec3_t angles;
	};

	union PathNodeParentUnion
	{
		scr_string_t name;
		unsigned short index;
	};

	enum PathNodeErrorCode
	{
		PNERR_NONE = 0x0,
		PNERR_INSOLID = 0x1,
		PNERR_FLOATING = 0x2,
		PNERR_NOLINK = 0x3,
		PNERR_DUPLICATE = 0x4,
		PNERR_NOSTANCE = 0x5,
		PNERR_INVALIDDOOR = 0x6,
		PNERR_NOANGLES = 0x7,
		PNERR_NOPEEKOUT = 0x8,
		PNERR_NEARSOLID = 0x9,
		PNERR_NOCOVER = 0xA,
		NUM_PATH_NODE_ERRORS = 0xB,
	};

	union $96C58BBB7F3ED2CCC5F07A7E763FE6AE
	{
		float minUseDistSq;
		PathNodeErrorCode error;
	};

	struct pathlink_s
	{
		float fDist;
		unsigned short nodeNum;
		char disconnectCount;
		char negotiationLink;
		char flags;
		char ubBadPlaceCount[3];
	};

	enum nodeType : std::uint16_t
	{
		NODE_ERROR = 0x0,
		NODE_PATHNODE = 0x1,
		NODE_COVER_STAND = 0x2,
		NODE_COVER_CROUCH = 0x3,
		NODE_COVER_CROUCH_WINDOW = 0x4,
		NODE_COVER_PRONE = 0x5,
		NODE_COVER_RIGHT = 0x6,
		NODE_COVER_LEFT = 0x7,
		NODE_AMBUSH = 0x8,
		NODE_EXPOSED = 0x9,
		NODE_CONCEALMENT_STAND = 0xA,
		NODE_CONCEALMENT_CROUCH = 0xB,
		NODE_CONCEALMENT_PRONE = 0xC,
		NODE_DOOR = 0xD,
		NODE_DOOR_INTERIOR = 0xE,
		NODE_SCRIPTED = 0xF,
		NODE_NEGOTIATION_BEGIN = 0x10,
		NODE_NEGOTIATION_END = 0x11,
		NODE_TURRET = 0x12,
		NODE_GUARD = 0x13,
		NODE_PATHNODE_3D = 0x14,
		NODE_COVER_3D = 0x15,
		NODE_COVER_STAND_3D = 0x16,
		UNUSED_0 = 0x17,
		UNUSED_1 = 0x18,
		NODE_EXPOSED_3D = 0x19,
		NODE_SCRIPTED_3D = 0x1A,
		NODE_NEGOTIATION_BEGIN_3D = 0x1B,
		NODE_NEGOTIATION_END_3D = 0x1C,
		NODE_JUMP = 0x1D,
		NODE_JUMP_ATTACK = 0x1E,
		NODE_COVER_MULTI = 0x1F,
		NODE_NUMTYPES = 0x20,
	};

	struct pathnode_constant_t
	{
		unsigned short type;
		unsigned int spawnflags;
		scr_string_t targetname;
		scr_string_t script_linkName;
		scr_string_t script_noteworthy;
		scr_string_t target;
		scr_string_t animscript;
		int animscriptfunc;
		vec3_t vLocalOrigin;
		PathNodeOrientationUnion orientation;
		PathNodeParentUnion parent;
		$96C58BBB7F3ED2CCC5F07A7E763FE6AE ___u11;
		unsigned short wOverlapNode[2];
		unsigned short totalLinkCount;
		pathlink_s PTR64 Links;
	}; assert_sizeof(pathnode_constant_t, 80);
	assert_offsetof(pathnode_constant_t, parent, 56);
	assert_offsetof(pathnode_constant_t, animscript, 24);
	assert_offsetof(pathnode_constant_t, Links, 72);

	struct SentientHandle
	{
		unsigned short number;
		unsigned short infoIndex;
	};

	struct pathnode_dynamic_t
	{
		SentientHandle pOwner;
		int iFreeTime;
		int iValidTime[3];
		short wLinkCount;
		short wOverlapCount;
		short turretEntNumber;
		unsigned char userCount;
		unsigned char hasBadPlaceLink;
		int spreadUsedTime[2];
		short flags;
		short dangerousCount;
		int recentUseProxTime;
	};

	union $73F238679C0419BE2C31C6559E8604FC
	{
		float nodeCost;
		int linkIndex;
	};

	struct pathnode_transient_t
	{
		int iSearchFrame;
		pathnode_t PTR64 pNextOpen;
		pathnode_t PTR64 pPrevOpen;
		pathnode_t PTR64 pParent;
		float fCost;
		float fHeuristic;
		$73F238679C0419BE2C31C6559E8604FC ___u6;
	};

	struct pathnode_t
	{
		pathnode_constant_t constant;
		pathnode_dynamic_t dynamic;
		pathnode_transient_t transient;
	}; assert_sizeof(pathnode_t, 176);

	struct pathnode_tree_nodes_t
	{
		int nodeCount;
		unsigned short PTR64 nodes;
	};

	union pathnode_tree_info_t
	{
		pathnode_tree_t PTR64 child[2];
		pathnode_tree_nodes_t s;
	};

	struct pathnode_tree_t
	{
		int axis;
		float dist;
		pathnode_tree_info_t u;
	};

	struct PathDynamicNodeGroup
	{
		unsigned short parentIndex;
		int nodeTreeCount;
		pathnode_tree_t PTR64 nodeTree;
	};

	struct PathData
	{
		const char PTR64 name;
		unsigned int nodeCount;
		pathnode_t PTR64 nodes;
		bool parentIndexResolved;
		unsigned __int16 version;
		int visBytes;
		char PTR64 pathVis;
		int nodeTreeCount;
		pathnode_tree_t PTR64 nodeTree;
		int dynamicNodeGroupCount;
		PathDynamicNodeGroup PTR64 dynamicNodeGroups;
		int exposureBytes;
		char PTR64 pathExposure;
		int noPeekVisBytes;
		char PTR64 pathNoPeekVis;
		int zoneCount;
		int zonesBytes;
		char PTR64 pathZones;
		int fixedNodeCount;
		int maxDynamicSpawnedNodeCount;
		int dynStatesBytes;
		char PTR64 pathDynStates;
	}; assert_sizeof(PathData, 0x90);

	struct nav_resource_s;

	struct nav_resource_s
	{
		scr_string_t targetName;
		int modelIdx;
		int targetEntNum;
		void PTR64 pSpace;
		int graphSize;
		vec3_t localOffsetPos;
		vec4_t localOffsetRot;
		int offsetLayer;
		nav_resource_s PTR64 pPrev;
		nav_resource_s PTR64 pNext;
		//int buildError;
		unsigned int layerFlags;
		bool bDockable;
		bool bIsVolume;
		char PTR64 pGraphBuffer;
		char PTR64 pWorkingGraph;
	}; assert_sizeof(nav_resource_s, 104);
	assert_offsetof(nav_resource_s, pGraphBuffer, 88);

	struct nav_boundary_plane_s
	{
		vec3_t m_Normal;
		float m_DistFromCenter;
	};

	struct nav_obstacle_hull_s
	{
		nav_boundary_plane_s PTR64 m_Boundaries;
		int m_NumBoundaries;
		float m_BoundsX;
		float m_BoundsY;
		float m_BoundsZ;
		vec3_t m_Offset;
		bool m_bUseBounds;
	};

	struct nav_obstacle_bounds_s
	{
		nav_obstacle_hull_s PTR64 m_Hulls;
		int m_NumHulls;
	};

	struct nav_glass_bounds_s
	{
		nav_boundary_plane_s PTR64 m_Boundaries;
		int m_NumBoundaries;
		vec3_t m_Pos;
		unsigned int m_GlassPieceIndex;
	};

	struct nav_modifier_s
	{
		nav_boundary_plane_s PTR64 m_Boundaries;
		int m_NumBoundaries;
		vec3_t m_Pos;
		scr_string_t m_TargetName;
		//scr_string_t m_Target;
		//scr_string_t m_ScriptNoteworthy;
		//scr_string_t m_ScriptLinkName;
		unsigned int m_UserFlags;
		unsigned int m_LayerFlags;
		float m_Weight;
		bool m_bActiveOnLoad;
	}; assert_sizeof(nav_modifier_s, 48);
	assert_offsetof(nav_modifier_s, m_TargetName, 24);

	struct nav_link_point_s
	{
		vec3_t m_Pt1;
		vec3_t m_Pt2;
	};

	struct nav_link_creation_data_s
	{
		nav_link_point_s m_Start;
		nav_link_point_s m_End;
		scr_string_t m_Animscript;
		scr_string_t m_Target;
		scr_string_t m_Parent;
		unsigned int m_UsageFlags;
		float m_PenaltyMult;
		bool m_bBidirectional;
	}; assert_sizeof(nav_link_creation_data_s, 72);
	assert_offsetof(nav_link_creation_data_s, m_Animscript, 48);

	struct nav_raw_volume_s
	{
		vec3_t m_MidPoint;
		vec3_t m_HalfSize;
		float m_MinVoxelSize;
		float m_ClearanceXY;
		float m_ClearanceZ;
	}; assert_sizeof(nav_raw_volume_s, 36);

	struct nav_raw_custom_volume_tri_s
	{
		vec3_t m_Verts[3];
	}; assert_sizeof(nav_raw_custom_volume_tri_s, 36);

	struct nav_raw_custom_volume_s
	{
		nav_raw_custom_volume_tri_s PTR64 m_Tris;
		int m_NumTris;
	}; assert_sizeof(nav_raw_custom_volume_s, 16);

	struct NavMeshData
	{
		const char PTR64 name;
		int version;
		int hasExposureData;
		int numNavResources;
		nav_resource_s PTR64 navResources;
		int numObstacleBounds;
		nav_obstacle_bounds_s PTR64 obstacleBounds;
		int numGlassBounds;
		nav_glass_bounds_s PTR64 glassBounds;
		int numModifiers;
		nav_modifier_s PTR64 modifiers;
		int numLinkCreationData;
		nav_link_creation_data_s PTR64 linkCreationData;
		int numVolumeSeeds;
		vec3_t PTR64 volumeSeeds;
		int numRawVolumes;
		nav_raw_volume_s PTR64 rawVolumes;
		int numRawCustomVolumes;
		nav_raw_custom_volume_s PTR64 rawCustomVolumes;
	}; assert_sizeof(NavMeshData, 0x90);
	assert_offsetof(NavMeshData, rawCustomVolumes, 136);

	struct CTAudRvbPanInfo
	{
		bool hasCustomPosition;
		vec3_t position;
		float maxWallDistance;
		float minReverbVolume;
	};

	struct ClientEntityLinkToDef
	{
		int anchorIndex;
		vec3_t originOffset;
		vec3_t angleOffset;
	};

	struct ClientTriggers
	{
		MapTriggers trigger;
		unsigned int triggerStringLength;
		char PTR64 triggerString;
		short PTR64 visionSetTriggers;
		unsigned char PTR64 triggerType;
		vec3_t PTR64 origins;
		float PTR64 scriptDelay;
		short PTR64 audioTriggers;
		short PTR64 blendLookup;
		short PTR64 npcTriggers;
		short PTR64 audioStateIds;
		CTAudRvbPanInfo PTR64 audioRvbPanInfo;
		short PTR64 transientIndex; // guess
		ClientEntityLinkToDef PTR64  PTR64 linkTo;
	}; assert_sizeof(ClientTriggers, 0xB8);

	struct ClientTriggerBlendNode
	{
		vec3_t pointA;
		vec3_t pointB;
		unsigned short triggerA;
		unsigned short triggerB;
	};

	struct ClientTriggerBlend
	{
		unsigned short numClientTriggerBlendNodes;
		ClientTriggerBlendNode PTR64 blendNodes;
	};

	struct SpawnPointEntityRecord
	{
		unsigned short index;
		scr_string_t name;
		scr_string_t target;
		scr_string_t script_noteworthy;
		vec3_t origin;
		vec3_t angles;
	};

	struct SpawnPointRecordList
	{
		unsigned short spawnsCount;
		SpawnPointEntityRecord PTR64 spawns;
	};

	struct SplinePointEntityRecord
	{
		int splineId;
		int splineNodeId;
		scr_string_t splineNodeLabel;
		scr_string_t targetname;
		scr_string_t target;
		scr_string_t string;
		float speed;
		float splineNodeTension;
		vec3_t origin;
		vec3_t angles;
		float throttle;
		vec2_t corridorDims;
		vec3_t tangent;
		float distToNextNode;
		vec3_t positionCubic[4];
		vec3_t tangentQuadratic[3];
	};

	struct SplinePointRecordList
	{
		unsigned short splinePointCount;
		float splineLength;
		SplinePointEntityRecord PTR64 splinePoints;
	};

	struct SplineRecordList
	{
		unsigned short splineCount;
		SplinePointRecordList PTR64 splines;
	};

	struct cmodel_t
	{
		Bounds bounds;
		float radius;
		ClipInfo PTR64 info;
		PhysicsAsset PTR64 physicsAsset;
		//unsigned __int16 physicsShapeOverrideIdx;
		//unsigned __int16 navObstacleIdx;
		unsigned int edgeFirstIndex;
		unsigned int edgeTotalCount;
	}; assert_sizeof(cmodel_t, 56);

	enum DynEntityType : std::int32_t
	{
		DYNENT_TYPE_INVALID = 0x0,
	};

	struct GfxPlacement
	{
		float quat[4];
		float origin[3];
	};

	struct DynEntityLinkToDef
	{
		int anchorIndex;
		float originOffset[3];
		float angleOffset[3];
	};

	struct DynEntityDef
	{
		DynEntityType type;
		char __pad0[28];
		GfxPlacement pose;
		char __pad1[4];
		XModel PTR64 baseModel;
		char __pad2[16];
		DynEntityLinkToDef PTR64 linkTo;
		char __pad3[16];
	}; assert_sizeof(DynEntityDef, 112);
	assert_offsetof(DynEntityDef, baseModel, 64);
	assert_offsetof(DynEntityDef, linkTo, 88);

	struct unk_1453E3260
	{
		char __pad0[28];
	}; assert_sizeof(unk_1453E3260, 28);

	struct unk_1453E4268
	{
		char __pad0[44];
		unsigned int unk01Count;
		unk_1453E3260 PTR64 unk01;
		char PTR64 unk02;
		char __pad1[8];
	}; assert_sizeof(unk_1453E4268, 72);
	assert_offsetof(unk_1453E4268, unk02, 56);

	struct unk_1453E4278
	{
		char __pad0[56];
	}; assert_sizeof(unk_1453E4278, 56);

	struct unk_1453E4238
	{
		char __pad0[8];
	}; assert_sizeof(unk_1453E4238, 8);

	struct unk_1453E4280
	{
		char __pad0[8];
	}; assert_sizeof(unk_1453E4280, 8);

	struct unk_1453E4298
	{
		char __pad0[32];
		unsigned int unk01Count;
		unk_1453E4280 PTR64 unk01;
	}; assert_sizeof(unk_1453E4298, 48);

	struct unk_1453E42A8
	{
		char __pad0[8];
	}; assert_sizeof(unk_1453E42A8, 8);

	struct unk_1453E1130
	{
		char unk;
	}; assert_sizeof(unk_1453E1130, 1);

	struct unk_1453E20F0
	{
		int unk1;
		scr_string_t unk2;
	}; assert_sizeof(unk_1453E20F0, 8);

	struct ScriptablePhysicsLimits
	{
		unsigned int clientStandaloneMainRigidBodyCount;
		unsigned int clientStandaloneDetailedRigidBodyCount;
		unsigned int clientStandaloneMotionCount;
		unsigned int serverStandaloneMainRigidBodyCount;
		unsigned int serverStandaloneDetailedRigidBodyCount;
		unsigned int serverStandaloneMotionCount;
	};

	struct unk_1453E24B0
	{
		XModel PTR64 model;
		unsigned int count;
		char __pad0[4];
	}; assert_sizeof(unk_1453E24B0, 16);

	struct unk_1453E2510
	{
		ScriptableDef PTR64 def;
		char __pad0[64];
		unk_1453E24B0 unk01;
		char PTR64 unk02;
		char __pad1[16];
	}; assert_sizeof(unk_1453E2510, 112);

	struct unk_1453E2520
	{
		unk_1453E2510 unk01;
		char __pad0[16];
	}; assert_sizeof(unk_1453E2520, 128);

	struct unk_1453E2530
	{
		unk_1453E2510 unk01;
		char __pad0[40];
	}; assert_sizeof(unk_1453E2530, 152);

	struct ScriptableInstance
	{
		unk_1453E2520 unk01;
		unk_1453E2530 unk02[2];
		scr_string_t unk03;
		char __pad0[8];
		scr_string_t unk04;
		char __pad1[8];
		scr_string_t unk05;
	}; assert_sizeof(ScriptableInstance, 464);
	assert_offsetof(ScriptableInstance, unk03, 432);
	assert_offsetof(ScriptableInstance, unk05, 456);

	struct ScriptableReservedDynent
	{
		unsigned int dynentId;
		__int16 next;
	};

	struct ScriptableReservedDynents
	{
		__int16 freeHead;
		unsigned int numReservedDynents;
		ScriptableReservedDynent PTR64 reservedDynents;
	};

	struct unk_1453E2558
	{
		int id;
	};

	struct unk_1453E2560
	{
		int unk01Count;
		unk_1453E2558 PTR64 unk01;
		int unk02Count;
		unk_1453E2558 PTR64 unk02_1;
		unk_1453E2558 PTR64 unk02_2;
	};

	struct Scriptable_EventSun_Data
	{
		int startTime;
		int transTime;
		vec3_t startColorLinearSrgb;
		float startIntensity;
		float targetIntensity;
		vec3_t startAngles;
		vec3_t targetAngles;
	};

	struct ScriptableMapEnts
	{
		unsigned int instanceCount;
		unsigned int unkCount1;
		unsigned int unkCount2;
		unsigned int unkCount3;
		ScriptableInstance PTR64 instances;
		unk_1453E2560 unk;
		Scriptable_EventSun_Data sunClientDatas[2];
		ScriptableReservedDynents reservedDynents[2];
		unsigned int ffMemCost;
	}; assert_sizeof(ScriptableMapEnts, 0xD0);
	assert_offsetof(ScriptableMapEnts, unk, 24);
	assert_offsetof(ScriptableMapEnts, reservedDynents, 168);

	struct MayhemInstance
	{
		GfxPlacement initialPose;
		MayhemData PTR64 mayhem;
		ClientEntityLinkToDef PTR64 linkTo;
		scr_string_t scriptName;
		float curTime;
		float oldTime;
		unsigned int initialFlags;
		unsigned int flags;
		unsigned int mapEntLookup;
		//unsigned __int16 transientIndexStored;
	}; assert_sizeof(MayhemInstance, 72);

	struct SpawnerField
	{
		scr_string_t key;
		unsigned int keyCanonical;
		scr_string_t value;
		char type;
	}; assert_sizeof(SpawnerField, 16);

	struct Spawner
	{
		vec3_t origin;
		vec3_t angles;
		SpawnerField PTR64 fields;
		int flags;
		int count;
		unsigned int numFields;
		scr_string_t targetname;
		scr_string_t classname;
	}; assert_sizeof(Spawner, 56);

	struct SpawnerList
	{
		unsigned int spawnerCount;
		Spawner PTR64 spanwerList;
	};

	struct AudioPASpeaker
	{
		vec3_t origin;
		unsigned int nameHash;
		unsigned int entChannelHash;
	};

	struct MapEnts
	{
		const char PTR64 name;
		char PTR64 entityString;
		int numEntityChars;
		MapTriggers trigger;
		ClientTriggers clientTrigger;
		ClientTriggerBlend clientTriggerBlend;
		SpawnPointRecordList spawnList;
		SplineRecordList splineList;
		unsigned int havokEntsShapeDataSize;
		char PTR64 havokEntsShapeData;
		unsigned int numSubModels;
		cmodel_t PTR64 cmodels;
		unsigned short dynEntCount[2];
		unsigned short dynEntCountTotal;
		DynEntityDef PTR64 dynEntDefList[2];
		unk_1453E4268 PTR64 dynEntUnk01List[4];
		unk_1453E4278 PTR64 dynEntUnk02List[4];
		char __pad0[16];
		unk_1453E4238 PTR64 unk1[2];
		char __pad1[8];
		unsigned int unk2Count;
		unk_1453E4298 PTR64 unk2;
		unk_1453E42A8 PTR64 unk2_1[2];
		unk_1453E1130 PTR64 unk2_2[2];
		unsigned int unk3Count;
		unsigned int PTR64 unk3;
		unsigned int unk4Count; // dynEntAnchorCount
		unk_1453E20F0 PTR64 unk4; // DynEntityAnchor
		ScriptableMapEnts scriptableMapEnts;
		unsigned int numMayhemScenes;
		MayhemInstance PTR64 mayhemScenes;
		SpawnerList spawners;
		unsigned int audioPASpeakerCount;
		AudioPASpeaker PTR64 audioPASpeakers;
	}; assert_sizeof(MapEnts, 0x340);
	assert_offsetof(MapEnts, havokEntsShapeDataSize, 336);
	assert_offsetof(MapEnts, cmodels, 360);
	assert_offsetof(MapEnts, dynEntDefList, 376);
	assert_offsetof(MapEnts, unk1, 472);
	assert_offsetof(MapEnts, unk2, 504);
	assert_offsetof(MapEnts, scriptableMapEnts, 576);
	assert_offsetof(MapEnts, audioPASpeakers, 824);

	struct FxGlassDef
	{
		float halfThickness;
		vec2_t texVecs[2];
		GfxColor color;
		Material PTR64 material;
		Material PTR64 materialShattered;
		PhysicsAsset PTR64 physicsAsset;
		FxCombinedDef pieceBreakEffect;
		FxCombinedDef shatterEffect;
		FxCombinedDef shatterSmallEffect;
		FxCombinedDef crackDecalEffect;
		const char PTR64 damagedSound;
		const char PTR64 destroyedSound;
		const char PTR64 destroyedQuietSound;
		float highMipRadiusInvSq;
		float shatteredHighMipRadiusInvSq;
		int numCrackRings;
		bool isOpaque;
	};

	struct FxSpatialFrame
	{
		vec4_t quat;
		vec3_t origin;
	};

	struct $03A8A7B39FA20F64B5AB79125E07CD62
	{
		FxSpatialFrame frame;
		float radius;
	};

	union FxGlassPiecePlace
	{
		$03A8A7B39FA20F64B5AB79125E07CD62 __s0;
		unsigned int nextFree;
	};

	struct FxGlassPieceState
	{
		float texCoordOrigin[2];
		unsigned int supportMask;
		unsigned __int16 initIndex;
		unsigned __int16 geoDataStart;
		unsigned __int16 lightingIndex;
		unsigned __int8 defIndex;
		unsigned __int8 pad[3];
		unsigned __int8 vertCount;
		unsigned __int8 holeDataCount;
		unsigned __int8 crackDataCount;
		unsigned __int8 fanDataCount;
		unsigned __int16 flags;
		float areaX2;
	};

	struct FxGlassPieceDynamics
	{
		int fallTime;
		unsigned int physicsInstance;
		unsigned int physicsDetailInstance;
		vec3_t vel;
		vec3_t avel;
		bool pendingCreation;
	};

	struct FxGlassVertex
	{
		short x;
		short y;
	};

	struct FxGlassHoleHeader
	{
		unsigned short uniqueVertCount;
		unsigned char touchVert;
		unsigned char pad[1];
	};

	struct FxGlassCrackHeader
	{
		unsigned short uniqueVertCount;
		unsigned char beginVertIndex;
		unsigned char endVertIndex;
	};

	union FxGlassGeometryData
	{
		FxGlassVertex vert;
		FxGlassHoleHeader hole;
		FxGlassCrackHeader crack;
		unsigned char asBytes[4];
		short anonymous[2];
	};

	struct FxGlassInitPieceState
	{
		FxSpatialFrame frame;
		float radius;
		vec2_t texCoordOrigin;
		unsigned int supportMask;
		float areaX2;
		unsigned short lightingIndex;
		unsigned char defIndex;
		unsigned char vertCount;
		unsigned char fanDataCount;
		unsigned char pad[1];
	};

	struct FxGlassSystem
	{
		int time;
		int prevTime;
		unsigned int defCount;
		unsigned int pieceLimit;
		unsigned int pieceWordCount;
		unsigned int initPieceCount;
		unsigned int cellCount;
		unsigned int activePieceCount;
		unsigned int firstFreePiece;
		unsigned int geoDataLimit;
		unsigned int geoDataCount;
		unsigned int initGeoDataCount;
		FxGlassDef PTR64 defs;
		FxGlassPiecePlace PTR64 piecePlaces;
		FxGlassPieceState PTR64 pieceStates;
		FxGlassPieceDynamics PTR64 pieceDynamics;
		FxGlassGeometryData PTR64 geoData;
		unsigned int PTR64 isInUse;
		unsigned int PTR64 cellBits;
		unsigned char PTR64 visData;
		vec3_t PTR64 linkOrg;
		float PTR64 halfThickness;
		unsigned short PTR64 lightingHandles;
		FxGlassInitPieceState PTR64 initPieceStates;
		FxGlassGeometryData PTR64 initGeoData;
		bool needToCompactData;
		unsigned char initCount;
		float effectChanceAccum;
		int lastPieceDeletionTime;
	};

	struct FxWorld
	{
		const char PTR64 name;
		FxGlassSystem glassSys;
	};

	struct GfxPortal;

	struct GfxSky
	{
		int skySurfCount;
		int PTR64 skyStartSurfs;
		GfxImage PTR64 skyImage;
		unsigned __int8 skySamplerState;
	}; assert_sizeof(GfxSky, 32);

	struct GfxWorldDpvsPlanes
	{
		int cellCount;
		cplane_s PTR64 planes;
		unsigned short PTR64 nodes;
		unsigned int PTR64 sceneEntCellBits;
	}; assert_sizeof(GfxWorldDpvsPlanes, 32);

	struct GfxPortalWritable
	{
		bool isQueued;
		bool isAncestor;
		char recursionDepth;
		char hullPointCount;
		vec2_t PTR64 hullPoints;
		GfxPortal PTR64 queuedParent;
	};

	struct DpvsPlane
	{
		vec4_t coeffs;
	};

	struct GfxPortal
	{
		GfxPortalWritable writable;
		DpvsPlane plane;
		vec3_t PTR64 vertices;
		unsigned __int16 cellIndex;
		unsigned __int16 closeDistance;
		char vertexCount;
		vec3_t hullAxis[2];
	};

	struct GfxCell
	{
		Bounds bounds;
		unsigned __int16 portalCount;
		GfxPortal PTR64 portals;
	};

	struct GfxCellTransientInfo
	{
		unsigned __int16 aabbTreeIndex;
		unsigned __int16 transientZone;
	};

	struct GfxReflectionProbe
	{
		char PTR64 livePath;
		vec3_t origin;
		vec3_t angles;
		unsigned __int16 PTR64 probeInstances;
		unsigned __int16 probeInstanceCount;
		unsigned __int16 probeRelightingIndex;
		unsigned int probeImageIndirection;
	};

	struct GfxReflectionProbeRelightingData
	{
		unsigned int reflectionProbeIndex;
		unsigned __int16 relightingFlags;
		unsigned __int16 zoneCount;
		unsigned int gBufferAlbedoImageIndex;
		unsigned int gBufferNormalImageIndex;
		unsigned int gBufferSecondaryDiffuseImageIndex;
		float relightingScale;
		unsigned __int16 PTR64 zones;
	};

	struct GfxReflectionProbeObb
	{
		vec3_t center;
		vec3_t xAxis;
		vec3_t yAxis;
		vec3_t zAxis;
		vec3_t halfSize;
	};

	struct GfxReflectionProbeInstance
	{
		char PTR64 livePath;
		char PTR64 livePath2;
		vec3_t probePosition;
		unsigned __int16 probeImageIndex;
		char lodLevel;
		char flags;
		vec4_t probeRotation;
		GfxReflectionProbeObb volumeObb;
		float priority;
		vec3_t feather;
		vec3_t expandProjectionNeg;
		vec3_t expandProjectionPos;
	}; assert_sizeof(GfxReflectionProbeInstance, 152);

	struct GfxRawTexture : GfxTexture
	{
	}; assert_sizeof(GfxRawTexture, 24);

	struct GfxReflectionProbeSampleData
	{
		float unk[8];
	}; assert_sizeof(GfxReflectionProbeSampleData, 32);

	struct GfxWorldReflectionProbeData
	{
		unsigned int reflectionProbeCount;
		unsigned int sharedReflectionProbeCount;
		GfxReflectionProbe PTR64 reflectionProbes;
		GfxImage PTR64 reflectionProbeArrayImage;
		unsigned int probeRelightingCount;
		GfxReflectionProbeRelightingData PTR64 probeRelightingData;
		unsigned int reflectionProbeGBufferImageCount;
		GfxImage PTR64  PTR64 reflectionProbeGBufferImages;
		GfxRawTexture PTR64 reflectionProbeGBufferTextures;
		unsigned int reflectionProbeInstanceCount;
		GfxReflectionProbeInstance PTR64 reflectionProbeInstances;
		GfxReflectionProbeSampleData PTR64 reflectionProbeLightgridSampleData;
		void PTR64 reflectionProbeLightgridSampleDataBuffer;
		void PTR64 reflectionProbeLightgridSampleDataBufferView;
		void PTR64 reflectionProbeLightgridSampleDataBufferRWView;
	}; assert_sizeof(GfxWorldReflectionProbeData, 112);

	struct GfxWorldLightmapReindexDataElement
	{
		unsigned int index;
		unsigned int posX;
		unsigned int posY;
		unsigned int width;
		unsigned int height;
	}; assert_sizeof(GfxWorldLightmapReindexDataElement, 20);

	struct GfxWorldPackedLightmap
	{
		unsigned int imageWidth;
		unsigned int imageHeight;
	};

	struct GfxWorldLightmapReindexData
	{
		unsigned int imagePixelSize;
		unsigned int reindexCount;
		GfxWorldLightmapReindexDataElement PTR64 reindexElement;
		unsigned int packedLightmapCount;
		GfxWorldPackedLightmap PTR64 packedLightmap;
	}; assert_sizeof(GfxWorldLightmapReindexData, 32);

	struct unk_1453E41D8
	{
		char __pad0[388];
	}; assert_sizeof(unk_1453E41D8, 388);

	struct unk_1453E4A70
	{
		char __pad0[24];
	}; assert_sizeof(unk_1453E4A70, 24);

	struct GfxOrientedBoundingBox
	{
		vec3_t center;
		vec3_t xAxis;
		vec3_t yAxis;
		vec3_t zAxis;
		vec3_t halfSize;
	};

	enum VolumetricMaskType
	{
		VOLUMETRIC_MASK_UNUSED = 0x0,
		VOLUMETRIC_MASK_HEIGHTMAP = 0x1,
		VOLUMETRIC_MASK_OPACITYMAP = 0x2,
		VOLUMETRIC_MASK_TYPE_COUNT = 0x3,
	};

	enum VolumetricAxis
	{
		VOLUMETRIC_X_AXIS = 0x0,
		VOLUMETRIC_Y_AXIS = 0x1,
		VOLUMETRIC_Z_AXIS = 0x2,
		VOLUMETRIC_AXIS_COUNT = 0x3,
		VOLUMETRIC_NEGATVE_AXIS_FLAG = 0x4,
	};

	struct GfxVolumetricMask
	{
		VolumetricMaskType type;
		VolumetricAxis axis;
		GfxImage PTR64 image;
		vec2_t scale;
		vec2_t offset;
		vec2_t scroll;
	}; assert_sizeof(GfxVolumetricMask, 40);

	struct GfxVolumetric
	{
		char PTR64 livePath;
		unsigned int flags;
		GfxOrientedBoundingBox obb;
		float unk;
		GfxVolumetricMask masks[4];
	}; assert_sizeof(GfxVolumetric, 240);
	assert_offsetof(GfxVolumetric, masks, 80);

	struct GfxWorldVolumetrics
	{
		unsigned int volumetricCount;
		GfxVolumetric PTR64 volumetrics;
	};

	struct GfxWorldDraw
	{
		GfxWorldReflectionProbeData reflectionProbeData;
		GfxWorldLightmapReindexData lightmapReindexData;
		GfxImage PTR64 iesLookupTexture;
		unsigned int unk01Count;
		unk_1453E41D8 PTR64 unk01;
		GfxImage PTR64 lightmapOverridePrimary;
		GfxImage PTR64 lightmapOverrideSecondary;
		unsigned int lightMapCount;
		GfxLightMap PTR64  PTR64 lightMaps;
		unk_1453E4A70 PTR64 unk02;
		char __pad0[24];
		unsigned int transientZoneCount;
		GfxWorldTransientZone PTR64 transientZones[32];
		unsigned int indexCount;
		unsigned short PTR64 indices;
		void PTR64 indexBuffer;
		GfxWorldVolumetrics volumetrics;
	}; assert_sizeof(GfxWorldDraw, 536);
	assert_offsetof(GfxWorldDraw, iesLookupTexture, 144);
	assert_offsetof(GfxWorldDraw, unk01Count, 152);
	assert_offsetof(GfxWorldDraw, unk01, 160);
	assert_offsetof(GfxWorldDraw, transientZones, 240);
	assert_offsetof(GfxWorldDraw, indices, 504);
	assert_offsetof(GfxWorldDraw, indexBuffer, 512);
	assert_offsetof(GfxWorldDraw, volumetrics, 520);

	struct GfxWorld
	{
		const char PTR64 name;
		const char PTR64 baseName;
		unsigned int bspVersion;
		int planeCount;
		int nodeCount;
		unsigned int surfaceCount;
		int skyCount;
		GfxSky PTR64 skies; // 40
		unsigned int lastSunPrimaryLightIndex;
		unsigned int primaryLightCount;
		unsigned int unknown;
		unsigned int sortKeyLitDecal;
		unsigned int sortKeyEffectDecal;
		unsigned int sortKeyTopDecal;
		unsigned int sortKeyEffectAuto;
		unsigned int sortKeyDistortion;
		unsigned int sortKeyEffectDistortion;
		unsigned int sortKey2D;
		unsigned int sortKeyOpaqueBegin;
		unsigned int sortKeyOpaqueEnd;
		unsigned int sortKeyDecalBegin;
		unsigned int sortKeyDecalEnd;
		unsigned int sortKeyTransBegin;
		unsigned int sortKeyTransEnd;
		unsigned int sortKeyEmissiveBegin;
		unsigned int sortKeyEmissiveEnd;
		GfxWorldDpvsPlanes dpvsPlanes; // 120
		GfxCellTransientInfo PTR64 cellTransientInfos;
		GfxCell PTR64 cells;
		GfxWorldDraw draw;
		char __pad0[3816]; // todo
	}; assert_sizeof(GfxWorld, 0x11A8);
	assert_offsetof(GfxWorld, dpvsPlanes, 120);

	struct GfxWorldVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		float texCoord[2];
		float lmapCoord[2];
		PackedUnitVec normal;
		PackedUnitVec tangent;
	}; assert_sizeof(GfxWorldVertex, 44);

	union GfxWorldVertex0Union
	{
		GfxWorldVertex PTR64 vertices;
	};

	struct GfxWorldVertexData
	{
		GfxWorldVertex PTR64 vertices;
		ID3D11Buffer PTR64 worldVb;
	}; assert_sizeof(GfxWorldVertexData, 16);

	struct GfxWorldVertexLayerData
	{
		unsigned char PTR64 data;
		ID3D11Buffer PTR64 layerVb;
	}; assert_sizeof(GfxWorldVertexLayerData, 16);

	struct GfxCellTreeCount
	{
		int aabbTreeCount;
	};

	struct GfxAabbTree
	{
		Bounds bounds;
		unsigned __int16 childCount;
		unsigned __int16 surfaceCount;
		unsigned int startSurfIndex;
		unsigned __int16 smodelIndexCount;
		unsigned __int16 PTR64 smodelIndexes;
		int childrenOffset;
	}; assert_sizeof(GfxAabbTree, 56);

	struct GfxCellTree
	{
		GfxAabbTree PTR64 aabbTree;
	};

	struct GfxWorldTransientZone
	{
		const char PTR64 name;
		unsigned int transientZoneIndex;
		unsigned int vertexCount;
		GfxWorldVertexData vd;
		unsigned int vertexLayerDataSize;
		GfxWorldVertexLayerData vld;
		unsigned int cellCount;
		GfxCellTreeCount PTR64 aabbTreeCounts;
		GfxCellTree PTR64 aabbTrees;
	}; assert_sizeof(GfxWorldTransientZone, 0x50);

	struct GfxLightDef
	{
		const char PTR64 name;
		const char PTR64 iesProfile;
		char __pad0[24];
	}; assert_sizeof(GfxLightDef, 0x28);

	struct AnimationEntry
	{
		scr_string_t animName;
		int aimSetIndex;
	};

	struct AnimAliasInfo
	{
		char animIndex;
		float animWeight;
	};

	struct AnimAlias
	{
		scr_string_t aliasName;
		char animCount;
		AnimAliasInfo PTR64 aliasInfo;
	};

	struct AnimationState
	{
		scr_string_t name;
		scr_string_t notify;
		float blendTime;
		float blendOutTime;
		char flags;
		char entryCount;
		char aliasCount;
		int aimSetIndex;
		AnimationEntry PTR64 animEntries;
		unsigned __int64 PTR64 animIndices;
		AnimAlias PTR64 aliasList;
	};

	struct AnimationAimSet
	{
		scr_string_t name;
		scr_string_t rootName;
		int animCount;
		scr_string_t PTR64 animName;
		unsigned __int64 rootIndex;
		unsigned __int64 PTR64 animIndices;
		unsigned __int64 PTR64 aimNodeIndices;
	};

	struct AnimationStateMachine
	{
		scr_string_t name;
		unsigned __int16 stateCount;
		unsigned __int16 aimSetCount;
		AnimationState PTR64 states;
		AnimationAimSet PTR64 aimSets;
	};

	enum AnimationController
	{
		ANIMCTRL_NONE = 0x0,
		ANIMCTRL_PLAYER = 0x1,
		ANIMCTRL_DOG = 0x2,
		ANIMCTRL_NUM = 0x3,
	};

	struct AnimationClass
	{
		const char PTR64 className;
		AnimationStateMachine PTR64 stateMachine;
		AnimationController animCtrl;
		scr_string_t animTree;
		ScriptableDef PTR64 scriptable;
		unsigned __int16 soundCount;
		unsigned __int16 effectCount;
		scr_string_t PTR64 soundNotes;
		scr_string_t PTR64 soundNames;
		scr_string_t PTR64 soundOptions;
		scr_string_t PTR64 effectNotes;
		FxCombinedDef PTR64 effectDefs;
		scr_string_t PTR64 effectTags;
	}; assert_sizeof(AnimationClass, 0x58);

	struct PlayerAnimEntry
	{
		scr_string_t entryName;
		scr_string_t animName;
		scr_string_t shadowAnimName;
		char __pad0[68];
	}; assert_sizeof(PlayerAnimEntry, 80);

	struct PlayerAnimScriptEntry
	{
		unsigned int flags;
		unsigned int itemCount;
		unsigned int transitionCount;
		unsigned int PTR64 items;
		unsigned int PTR64 transitions;
	};

	struct PlayerAnimScriptCondition
	{
		unsigned int index;
		unsigned int value[4];
	}; assert_sizeof(PlayerAnimScriptCondition, 20);

	struct PlayerAnimScriptCommand
	{
		unsigned __int16 bodyPart;
		unsigned __int16 animIndex;
		unsigned __int16 animDuration;
	};

	struct PlayerAnimScriptItem
	{
		unsigned int conditionCount;
		unsigned int commandCount;
		PlayerAnimScriptCondition PTR64 conditions;
		PlayerAnimScriptCommand PTR64 commands;
	};

	enum PlayerAnimScriptTransitionTriggerType
	{
		ANIM_TRANSITIONTRIGGERTYPE_MOVETYPE = 0x0,
		ANIM_TRANSITIONTRIGGERTYPE_MOVETYPE_NOT_STRAFING = 0x1,
		ANIM_TRANSITIONTRIGGERTYPE_ANIMCOMPLETE = 0x2,
		ANIM_TRANSITIONTRIGGERTYPE_ANIMCHANGE = 0x3,
		NUM_ANIM_TRANSITION_TRIGGER_TYPES = 0x4,
	};

	enum PlayerAnimScriptMoveType
	{
		ANIM_MT_UNUSED = 0x0,
		ANIM_MT_IDLE = 0x1,
		ANIM_MT_IDLECR = 0x2,
		ANIM_MT_IDLEPRONE = 0x3,
		ANIM_MT_WALK = 0x4,
		ANIM_MT_WALKBK = 0x5,
		ANIM_MT_WALKCR = 0x6,
		ANIM_MT_WALKCRBK = 0x7,
		ANIM_MT_WALKPRONE = 0x8,
		ANIM_MT_WALKPRONEBK = 0x9,
		ANIM_MT_RUN = 0xA,
		ANIM_MT_RUNBK = 0xB,
		ANIM_MT_RUNCR = 0xC,
		ANIM_MT_RUNCRBK = 0xD,
		ANIM_MT_CLIMBUP = 0xE,
		ANIM_MT_LADDERSLIDE = 0xF,
		ANIM_MT_CLIMBDOWN = 0x10,
		ANIM_MT_JOG = 0x11,
		ANIM_MT_SPRINT = 0x12,
		ANIM_MT_SUPERSPRINT = 0x13,
		ANIM_MT_MANTLE = 0x14,
		ANIM_MT_IDLELASTSTAND = 0x15,
		ANIM_MT_CRAWLLASTSTAND = 0x16,
		ANIM_MT_CRAWLLASTSTANDBK = 0x17,
		ANIM_MT_SLIDE = 0x18,
		ANIM_MT_SLIDEBK = 0x19,
		ANIM_MT_MOUNTED_TOP = 0x1A,
		ANIM_MT_MOUNTED_LEFT = 0x1B,
		ANIM_MT_MOUNTED_RIGHT = 0x1C,
		ANIM_MT_BOOSTAIRDODGE = 0x1D,
		ANIM_MT_BOOSTAIRDODGELEFT = 0x1E,
		ANIM_MT_BOOSTAIRDODGERIGHT = 0x1F,
		ANIM_MT_BOOSTAIRDODGEBACK = 0x20,
		ANIM_MT_WALLRUN = 0x21,
		ANIM_MT_AIR = 0x22,
		ANIM_MT_KNOCKBACK = 0x23,
		ANIM_MT_KNOCKBACKBK = 0x24,
		ANIM_MT_PARACHUTE = 0x25,
		NUM_ANIM_CODEMOVETYPES = 0x26,
		FIRST_TRANSITION_MOVETYPE = 0x26,
		NUM_ANIM_MOVETYPES = 0x80,
	};

	struct PlayerAnimTriggerParam
	{
		PlayerAnimScriptMoveType moveType;
	};

	struct PlayerAnimScriptTransition
	{
		PlayerAnimScriptTransitionTriggerType triggerType;
		PlayerAnimTriggerParam triggerParam;
		PlayerAnimScriptMoveType targetMoveType;
	};

	struct PlayerAnimScriptIdleTurn
	{
		unsigned __int16 turnleft;
		unsigned __int16 turnright;
	};

	struct PlayerAnimScriptIdleTwitch
	{
		unsigned int twitchCount;
		float cycleLength;
		unsigned __int16 PTR64 twitches;
	};

	struct PlayerAnimScriptAimSet
	{
		unsigned __int16 aim_1;
		unsigned __int16 aim_2;
		unsigned __int16 aim_3;
		unsigned __int16 aim_4;
		unsigned __int16 aim_6;
		unsigned __int16 aim_7;
		unsigned __int16 aim_8;
		unsigned __int16 aim_9;
	};

	struct PlayerAnimScriptLeanSet
	{
		unsigned __int16 lean_left;
		unsigned __int16 lean_right;
	};

	struct unk_1453E3788
	{
		char __pad0[48];
	};

	struct PlayerAnimScript
	{
		const char PTR64 scriptName;
		unsigned int animationCount;
		unsigned int scriptItemCount;
		unsigned int scriptTransitionCount;
		unsigned int scriptIdleTurnCount;
		unsigned int scriptIdleTwitchCount;
		unsigned int scriptAimSetCount;
		unsigned int scriptLeanSetCount;
		unsigned int unkCount;
		unsigned int torsoAnimCount;
		unsigned int legsAnimCount;
		PlayerAnimEntry PTR64 animations;
		PlayerAnimScriptEntry PTR64 scriptAnims; // count: 121
		PlayerAnimScriptEntry PTR64 scriptEvents; // count: 55
		PlayerAnimScriptItem PTR64 scriptItems;
		PlayerAnimScriptTransition PTR64 scriptTransitions;
		PlayerAnimScriptIdleTurn PTR64 scriptIdleTurns;
		PlayerAnimScriptIdleTwitch PTR64 scriptIdleTwitches;
		PlayerAnimScriptAimSet PTR64 scriptAimSets;
		PlayerAnimScriptLeanSet PTR64 scriptLeanSets;
		unk_1453E3788 PTR64 unk;
		unsigned __int16 PTR64 torsoAnimPackMap;
		unsigned __int16 PTR64 torsoAnimUnpackMap;
		unsigned __int16 PTR64 legsAnimPackMap;
		unsigned __int16 PTR64 legsAnimUnpackMap;
		unsigned int xAnimCount;
		XAnimParts PTR64  PTR64 xAnims;
	}; assert_sizeof(PlayerAnimScript, 0xB0);

	enum GestureType
	{
		GESTURE_TYPE_NON_DIRECTIONAL = 0x0,
		GESTURE_TYPE_DIRECTIONAL = 0x1,
		GESTURE_TYPE_LOOK_AROUND = 0x2,
		GESTURE_TYPE_IK_TARGET = 0x3,
		GESTURE_TYPE_NUM = 0x4,
	};

	enum GesturePriority
	{
		GESTURE_PRIORITY_OFFHAND_SHIELD = 0x0,
		GESTURE_PRIORITY_OFFHAND_THROWN_WEAPON = 0x1,
		GESTURE_PRIORITY_OFFHAND_SCRIPT_WEAPON = 0x2,
		GESTURE_PRIORITY_SPACE_JUMP = 0x3,
		GESTURE_PRIORITY_SCRIPT = 0x4,
		GESTURE_PRIORITY_SLIDE = 0x5,
		GESTURE_PRIORITY_MANTLE = 0x6,
		GESTURE_PRIORITY_GROUND_POUND = 0x7,
		GESTURE_PRIORITY_WALL_RUN = 0x8,
		GESTURE_PRIORITY_DEMEANOR = 0x9,
		GESTURE_PRIORITY_COUNT = 0xC,
	};

	struct GestureWeaponSettings
	{
		unsigned __int16 blendToStates;
		bool hideReticle;
		float fireDelay;
		float sprintDelay;
		bool useLeftIdleAkimbo;
		bool splitAnimsAkimbo;
		bool blendToDemeanorLoop;
		bool blendOutRaise;
	};

	struct GestureDirectionalSettings
	{
		float maxAngle;
		float lerpAtMaxAngle;
		float widthCushionAngle;
		float lerpAtMinCushionAngle;
		float lerpAtMaxCushionAngle;
		float limitLeft;
		float limitRight;
		float limitUp;
		float limitDown;
	};

	struct FootstepTime
	{
		float time;
		bool isLeft;
	};

	struct MovementTime
	{
		float time;
		bool isLeadIn;
	};

	struct FootstepAnim
	{
		int leftCount;
		FootstepTime step[4];
		MovementTime movement[4];
	};

	struct GestureLookAroundSettings
	{
		float yawLerpIn;
		float yawLerpOut;
		unsigned __int16 walkTime;
		FootstepAnim walkFootStepAnim;
	};

	enum GestureDirectionalAssetIndex
	{
		GESTURE_ASSET_LEFT_CENTER = 0,
		GESTURE_ASSET_LEFT_DOWN = 1,
		GESTURE_ASSET_LEFT_LEFT = 2,
		GESTURE_ASSET_LEFT_RIGHT = 3,
		GESTURE_ASSET_LEFT_UP = 4,
		GESTURE_ASSET_RIGHT_CENTER = 5,
		GESTURE_ASSET_RIGHT_DOWN = 6,
		GESTURE_ASSET_RIGHT_LEFT = 7,
		GESTURE_ASSET_RIGHT_RIGHT = 8,
		GESTURE_ASSET_RIGHT_UP = 9,
		GESTURE_ASSET_IN = 10,
		GESTURE_ASSET_OUT = 11,
		GESTURE_ASSET_IN_ADDITIVE = 12,
		GESTURE_ASSET_OUT_ADDITIVE = 13,
		GESTURE_ASSET_PITCH = 14,
		GESTURE_ASSET_YAW = 15,
		GESTURE_ASSET_WEAPON_CHECK = 16,
		GESTURE_ASSET_WALK_ADDITIVE = 17,
		GESTURE_ASSET_NUM = 18,
	};

	struct Gesture
	{
		const char PTR64 name;
		GestureType type;
		GesturePriority priority;
		bool looping;
		XAnimParts PTR64  PTR64 anims; // array: 18
		GestureWeaponSettings weaponSettings;
		GestureDirectionalSettings directionalSettings;
		GestureLookAroundSettings lookAroundSettings;
	}; assert_sizeof(Gesture, 0xA8);
	assert_offsetof(Gesture, anims, 24);

	struct LocalizeEntry
	{
		const char PTR64 value;
		const char PTR64 name;
	};

	enum OffhandGestureTypes
	{
		OHGT_WEAPON,
		OHGT_PULLBACK,
		OHGT_THROW,
		OHGT_DETONATE,
		OHGT_SHIELD_DEPLOY,
		OHGT_SHIELD_DEPLOY_WHILE_FIRING,
		OHGT_SHIELD_FIRE_WEAPON,
		OHGT_SHIELD_RETRACT_WHILE_FIRING,
		OHGT_SHIELD_BASH,
		OHGT_NUM_TYPES,
		OHGT_ANY_TYPE,
	};

	enum AdsAltSwitchInterpType : std::int32_t
	{
		ADS_ALT_SWITCH_INTERP_TYPE_LINEAR = 0x0,
		ADS_ALT_SWITCH_INTERP_TYPE_COSINE = 0x1,
		ADS_ALT_SWITCH_INTERP_TYPE_SINE = 0x2,
		ADS_ALT_SWITCH_INTERP_TYPE_COUNT = 0x3,
	};

	enum AttachmentType : std::int32_t
	{
		ATTACHMENT_SCOPE = 0x0,
		ATTACHMENT_UNDERBARREL = 0x1,
		ATTACHMENT_OTHER = 0x2,
		ATTACHMENT_COUNT = 0x3,
	};

	enum weapType_t : std::int32_t
	{
		WEAPTYPE_NONE = 0x0,
		WEAPTYPE_BULLET = 0x1,
		WEAPTYPE_GRENADE = 0x2,
		WEAPTYPE_PROJECTILE = 0x3,
		WEAPTYPE_RIOTSHIELD = 0x4,
		WEAPTYPE_SCRIPT = 0x5,
		WEAPTYPE_SHIELD = 0x6,
		WEAPTYPE_CHARGE_SHIELD = 0x7,
		WEAPTYPE_UNK8 = 0x8,
		WEAPTYPE_UNK9 = 0x9,
		WEAPTYPE_UNK10 = 0xA,
		WEAPTYPE_UNK11 = 0xB,
		WEAPTYPE_EQUIP_DEPLOY = 0xC,
		WEAPTYPE_NUM = 0xD,
	};

	enum weapClass_t : std::int32_t
	{
		WEAPCLASS_RIFLE = 0x0,
		WEAPCLASS_SNIPER = 0x1,
		WEAPCLASS_MG = 0x2,
		WEAPCLASS_SMG = 0x3,
		WEAPCLASS_SPREAD = 0x4,
		WEAPCLASS_PISTOL = 0x5,
		WEAPCLASS_GRENADE = 0x6,
		WEAPCLASS_ROCKETLAUNCHER = 0x7,
		WEAPCLASS_TURRET = 0x8,
		WEAPCLASS_THROWINGKNIFE = 0x9,
		WEAPCLASS_NON_PLAYER = 0xA,
		WEAPCLASS_ITEM = 0xB,
		WEAPCLASS_BEAM = 0xC,
		WEAPCLASS_BALL = 0xD,
		WEAPCLASS_NONE = 0xE,
		WEAPCLASS_NUM = 0xF,
	};

	enum weapFireType_t : std::int32_t
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_SINGLESHOT = 0x1,
		WEAPON_FIRETYPE_BURST = 0x2,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x3,
		WEAPON_FIRETYPE_DOUBLEBARREL_DUALTRIGGER = 0x4,
		WEAPON_FIRETYPE_BEAM = 0x5,
		WEAPON_FIRETYPECOUNT = 0x6,
	};

	enum ImpactType : std::int32_t
	{
		IMPACT_TYPE_NONE = 0,
		IMPACT_TYPE_COUNT = 37,
	};

	enum MeleeImpactType : std::int32_t
	{
		MELEE_IMPACT_TYPE_NONE = 0,
	};

	enum tracerStyle_t : std::int32_t
	{
		TRACERSTYLE_TRACER = 0x0,
		TRACERSTYLE_BEAM = 0x1,
		TRACERSTYLE_NUM = 0x2,
	};

	enum PenetrateType : std::int32_t
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,
		PENETRATE_TYPE_MAXIMUM = 0x4,
		PENETRATE_TYPE_TABLE_ENTRY_COUNT = 0x4,
		PENETRATE_TYPE_RICOCHET = 0x5,
		PENETRATE_TYPE_COUNT = 0x6,
	};

	enum ReticleType : std::int32_t
	{
		RETICLE_TYPE_FOUR_SIDED = 0x0,
		RETICLE_TYPE_ONE_PIECE = 0x1,
		RETICLE_TYPE_COUNT = 0x2,
	};

	enum targetAssistType_t : std::int32_t
	{
		TARGET_ASSISTTYPPE_DEFAULT = 0x0,
		TARGET_ASSISTTYPPE_CONE = 0x1,
		TARGET_ASSISTTYPPE_COUNT = 0x2,
	};

	enum targetAssistBehavior_t : std::int32_t
	{
		TARGET_ASSISTBEHAVE_DEFAULT = 0x0,
		TARGET_ASSISTBEHAVE_DIRECT_DAMAGE = 0x1,
		TARGET_ASSISTBEHAVE_TARGET_ONLY = 0x2,
		TARGET_ASSISTBEHAVE_BEAM = 0x3,
		TARGET_ASSISTBEHAVE_SMART_PELLET = 0x4,
		TARGET_ASSISTBEHAVE_COUNT = 0x5,
	};

	enum AnimDamageType : std::int32_t
	{
		ANIM_DAMAGETYPE_NONE = 0x0,
		ANIM_DAMAGETYPE_EXPLOSION_LIGHT = 0x1,
		ANIM_DAMAGETYPE_EXPLOSION = 0x2,
		ANIM_DAMAGETYPE_MELEE = 0x3,
		ANIM_DAMAGETYPE_MELEE_DOG = 0x4,
		ANIM_DAMAGETYPE_MELEE_ALIEN = 0x5,
		ANIM_DAMAGETYPE_ENERGY_BULLET = 0x6,
		ANIM_DAMAGETYPE_FIRE_EXPLOSION = 0x7,
		ANIM_DAMAGETYPE_BULLET_SM = 0x8,
		ANIM_DAMAGETYPE_BULLET_MD = 0x9,
		ANIM_DAMAGETYPE_BULLET_LG = 0xA,
		ANIM_DAMAGETYPE_FALL = 0xB,
		ANIM_DAMAGETYPE_COUNT = 0xC,
	};

	enum weapOverlayReticle_t : std::int32_t
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	enum ammoCounterClipType_t : std::int32_t
	{
		AMMO_COUNTER_CLIP_NONE = 0x0,
		AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
		AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
		AMMO_COUNTER_CLIP_ROCKET = 0x4,
		AMMO_COUNTER_CLIP_BELTFED = 0x5,
		AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
		AMMO_COUNTER_CLIP_COUNT = 0x7,
	};

	enum weapProjExposion_t : std::int32_t
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_NUM = 0x7,
	};

	enum WeapStickinessType : std::int32_t
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_GROUND_ORIENT = 0x5,
		WEAPSTICKINESS_KNIFE = 0x6,
		WEAPSTICKINESS_COUNT = 0x7,
	};

	enum WeapOverlayInteface_t : std::int32_t
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
		WEAPOVERLAYINTERFACECOUNT = 0x3,
	};

	enum weaponIconRatioType_t : std::int32_t
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,
		WEAPON_ICON_RATIO_COUNT = 0x3,
	};

	enum guidedMissileType_t : std::int32_t
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_ROBOTECH = 0x4,
		MISSILE_GUIDANCE_SOFTLOCKON = 0x5,
		MISSILE_GUIDANCE_COUNT = 0x6,
	};

	enum offhandShieldMaxSpeed_t : std::int32_t
	{
		WEAP_OFFHAND_SHIELD_SPEED_WALK = 0x0,
		WEAP_OFFHAND_SHIELD_SPEED_RUN = 0x1,
		WEAP_OFFHAND_SHIELD_SPEED_SPRINT = 0x2,
		WEAP_OFFHAND_SHIELD_SPEED_COUNT = 0x3,
	};

	enum WeaponSlot : std::int32_t
	{
		WEAPON_SLOT_NONE = 0x0,
		WEAPON_SLOT_PRIMARY = 0x1,
		WEAPON_SLOT_HEAVY = 0x2,
		WEAPON_SLOT_MELEE = 0x3,
		WEAPON_SLOT_EXECUTION = 0x4,
		WEAPON_SLOT_ACCESSORY = 0x5,
		WEAPON_SLOT_NUM = 0x6,
	};

	enum weapInventoryType_t : std::int32_t
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORY_MODEL_ONLY = 0x6,
		WEAPINVENTORYCOUNT = 0x7,
	};

	enum OffhandClass : std::int32_t
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_SHIELD = 0x5,
		OFFHAND_CLASS_OTHER = 0x6,
		OFFHAND_CLASS_COUNT = 0x7,
	};

	enum activeReticleType_t : std::int32_t
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	};

	enum DualWieldType : std::int32_t
	{
		DUAL_WIELD_TYPE_DEFAULT = 0x0,
		DUAL_WIELD_TYPE_ALT_MODE = 0x1,
		DUAL_WIELD_TYPE_COUNT = 0x2,
	};

	enum weapStance_t : std::int32_t
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,
		WEAPSTANCE_NUM = 0x3,
	};

	enum scriptedAnimEvent_t : std::int32_t
	{
		SCRIPTEDANIMEVENT_POWER_ACTIVE = 0x0,
		SCRIPTEDANIMEVENT_POWER_ACTIVE_CP = 0x1,
		SCRIPTEDANIMEVENT_COUNT = 0x2,
	};

	enum playerAnimType_t : std::int32_t
	{
		PLAYERANIMTYPE_NONE,
		PLAYERANIMTYPE_OTHER,
		PLAYERANIMTYPE_PISTOL,
		PLAYERANIMTYPE_SMG,
		PLAYERANIMTYPE_AUTORIFLE,
		PLAYERANIMTYPE_MG,
		PLAYERANIMTYPE_SNIPER,
		PLAYERANIMTYPE_ROCKETLAUNCHER,
		PLAYERANIMTYPE_EXPLOSIVE,
		PLAYERANIMTYPE_GRENADE,
		PLAYERANIMTYPE_TURRET,
		PLAYERANIMTYPE_C4,
		PLAYERANIMTYPE_M203,
		PLAYERANIMTYPE_HOLD,
		PLAYERANIMTYPE_BRIEFCASE,
		PLAYERANIMTYPE_RIOTSHIELD,
		PLAYERANIMTYPE_LAPTOP,
		PLAYERANIMTYPE_THROWINGKNIFE,
		PLAYERANIMTYPE_MORTAR,
		PLAYERANIMTYPE_KNIFE,
		PLAYERANIMTYPE_CLAYMORE,
		PLAYERANIMTYPE_MINIGUN,
		PLAYERANIMTYPE_DRILL,
		PLAYERANIMTYPE_KILLSTREAKTRIGGER,
		PLAYERANIMTYPE_TROPHYSYSTEM,
		PLAYERANIMTYPE_GRENADE_TROPHY,
		PLAYERANIMTYPE_GRENADE_FRISBEE,
		PLAYERANIMTYPE_GRENADE_LARGE,
		PLAYERANIMTYPE_GRENADE_UNDERHAND,
		PLAYERANIMTYPE_GRENADE_CHUCK,
		PLAYERANIMTYPE_GRENADE_BASKETBALL,
		PLAYERANIMTYPE_GRENADE_SKEEBALL,
		PLAYERANIMTYPE_GRENADE_BASEBALL,
		PLAYERANIMTYPE_CHARGESHIELD,
		PLAYERANIMTYPE_AXE,
		PLAYERANIMTYPE_CLAW,
		PLAYERANIMTYPE_SMG_ENERGY,
		PLAYERANIMTYPE_ERAD,
		PLAYERANIMTYPE_AR57,
		PLAYERANIMTYPE_KBS,
		PLAYERANIMTYPE_CRB,
		PLAYERANIMTYPE_M4,
		PLAYERANIMTYPE_ACR,
		PLAYERANIMTYPE_M1,
		PLAYERANIMTYPE_SPAS,
		PLAYERANIMTYPE_DEVASTATOR,
		PLAYERANIMTYPE_NRG,
		PLAYERANIMTYPE_GAUNTLET,
		PLAYERANIMTYPE_BALL,
		PLAYERANIMTYPE_FHR,
		PLAYERANIMTYPE_REVOLVER,
		PLAYERANIMTYPE_AKE,
		PLAYERANIMTYPE_RIPPER,
		PLAYERANIMTYPE_FMG,
		PLAYERANIMTYPE_SDFLMG,
		PLAYERANIMTYPE_LMGTURRET,
		PLAYERANIMTYPE_SDFSHOTTY,
		PLAYERANIMTYPE_SONIC,
		PLAYERANIMTYPE_LONGBOW,
		PLAYERANIMTYPE_M200,
		PLAYERANIMTYPE_M8,
		PLAYERANIMTYPE_CHARGESHOT,
		PLAYERANIMTYPE_ROLLERCOASTERSEATED,
		PLAYERANIMTYPE_CANDYBOX,
		PLAYERANIMTYPE_C6_SUPER,
		PLAYERANIMTYPE_UMP45,
		PLAYERANIMTYPE_SDFAR,
		PLAYERANIMTYPE_SDFAR_LEGENDARY,
		PLAYERANIMTYPE_REVOLVER_LEGENDARY,
		PLAYERANIMTYPE_ACR_LEGENDARY,
		PLAYERANIMTYPE_AR57_LEGENDARY,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_01,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_02,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_03,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_04,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_05,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_06,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_07,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_08,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_09,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_10,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_11,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_12,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_13,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_14,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_15,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_16,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_17,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_18,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_19,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_20,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_21,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_22,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_23,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_24,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_25,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_26,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_27,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_28,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_29,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_30,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_31,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_32,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_33,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_34,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_35,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_36,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_37,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_38,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_39,
		PLAYERANIMTYPE_ADDITIONAL_WEAPON_40,
		PLAYERANIMTYPE_NUM,
	};

	enum scriptedAnimType_t : std::int32_t
	{
		SCRIPTEDANIMTYPE_NONE,
		SCRIPTEDANIMTYPE_OVERCHARGE,
		SCRIPTEDANIMTYPE_ADRENALINE,
		SCRIPTEDANIMTYPE_MULTIVISOR,
		SCRIPTEDANIMTYPE_SURGE,
		SCRIPTEDANIMTYPE_KINETICWAVE,
		SCRIPTEDANIMTYPE_PHASESHIFT,
		SCRIPTEDANIMTYPE_OPTICWAVE,
		SCRIPTEDANIMTYPE_CAMO,
		SCRIPTEDANIMTYPE_TELEPORT,
		SCRIPTEDANIMTYPE_REWIND,
		SCRIPTEDANIMTYPE_KILLSTREAKCALLOUT,
		SCRIPTEDANIMTYPE_GESTURE000,
		SCRIPTEDANIMTYPE_GESTURE001,
		SCRIPTEDANIMTYPE_GESTURE002,
		SCRIPTEDANIMTYPE_GESTURE003,
		SCRIPTEDANIMTYPE_GESTURE004,
		SCRIPTEDANIMTYPE_GESTURE005,
		SCRIPTEDANIMTYPE_GESTURE006,
		SCRIPTEDANIMTYPE_GESTURE007,
		SCRIPTEDANIMTYPE_GESTURE008,
		SCRIPTEDANIMTYPE_GESTURE009,
		SCRIPTEDANIMTYPE_GESTURE010,
		SCRIPTEDANIMTYPE_GESTURE011,
		SCRIPTEDANIMTYPE_GESTURE012,
		SCRIPTEDANIMTYPE_GESTURE013,
		SCRIPTEDANIMTYPE_GESTURE014,
		SCRIPTEDANIMTYPE_GESTURE015,
		SCRIPTEDANIMTYPE_GESTURE016,
		SCRIPTEDANIMTYPE_GESTURE017,
		SCRIPTEDANIMTYPE_GESTURE018,
		SCRIPTEDANIMTYPE_GESTURE019,
		SCRIPTEDANIMTYPE_GESTURE020,
		SCRIPTEDANIMTYPE_GESTURE021,
		SCRIPTEDANIMTYPE_GESTURE022,
		SCRIPTEDANIMTYPE_GESTURE023,
		SCRIPTEDANIMTYPE_GESTURE024,
		SCRIPTEDANIMTYPE_GESTURE025,
		SCRIPTEDANIMTYPE_GESTURE026,
		SCRIPTEDANIMTYPE_GESTURE027,
		SCRIPTEDANIMTYPE_GESTURE028,
		SCRIPTEDANIMTYPE_GESTURE029,
		SCRIPTEDANIMTYPE_GESTURE030,
		SCRIPTEDANIMTYPE_GESTURE031,
		SCRIPTEDANIMTYPE_GESTURE032,
		SCRIPTEDANIMTYPE_GESTURE033,
		SCRIPTEDANIMTYPE_GESTURE034,
		SCRIPTEDANIMTYPE_GESTURE035,
		SCRIPTEDANIMTYPE_GESTURE036,
		SCRIPTEDANIMTYPE_GESTURE037,
		SCRIPTEDANIMTYPE_GESTURE038,
		SCRIPTEDANIMTYPE_GESTURE039,
		SCRIPTEDANIMTYPE_GESTURE040,
		SCRIPTEDANIMTYPE_GESTURE041,
		SCRIPTEDANIMTYPE_GESTURE042,
		SCRIPTEDANIMTYPE_GESTURE043,
		SCRIPTEDANIMTYPE_GESTURE044,
		SCRIPTEDANIMTYPE_GESTURE045,
		SCRIPTEDANIMTYPE_GESTURE046,
		SCRIPTEDANIMTYPE_GESTURE047,
		SCRIPTEDANIMTYPE_GESTURE048,
		SCRIPTEDANIMTYPE_GESTURE049,
		SCRIPTEDANIMTYPE_GESTURE050,
		SCRIPTEDANIMTYPE_GESTURE051,
		SCRIPTEDANIMTYPE_GESTURE052,
		SCRIPTEDANIMTYPE_GESTURE053,
		SCRIPTEDANIMTYPE_GESTURE054,
		SCRIPTEDANIMTYPE_GESTURE055,
		SCRIPTEDANIMTYPE_GESTURE056,
		SCRIPTEDANIMTYPE_GESTURE057,
		SCRIPTEDANIMTYPE_GESTURE058,
		SCRIPTEDANIMTYPE_GESTURE059,
		SCRIPTEDANIMTYPE_GESTURE060,
		SCRIPTEDANIMTYPE_GESTURE061,
		SCRIPTEDANIMTYPE_GESTURE062,
		SCRIPTEDANIMTYPE_GESTURE063,
		SCRIPTEDANIMTYPE_GESTURE064,
		SCRIPTEDANIMTYPE_GESTURE065,
		SCRIPTEDANIMTYPE_GESTURE066,
		SCRIPTEDANIMTYPE_GESTURE067,
		SCRIPTEDANIMTYPE_GESTURE068,
		SCRIPTEDANIMTYPE_GESTURE069,
		SCRIPTEDANIMTYPE_GESTURE070,
		SCRIPTEDANIMTYPE_GESTURE071,
		SCRIPTEDANIMTYPE_GESTURE072,
		SCRIPTEDANIMTYPE_GESTURE073,
		SCRIPTEDANIMTYPE_GESTURE074,
		SCRIPTEDANIMTYPE_GESTURE075,
		SCRIPTEDANIMTYPE_GESTURE076,
		SCRIPTEDANIMTYPE_GESTURE077,
		SCRIPTEDANIMTYPE_GESTURE078,
		SCRIPTEDANIMTYPE_GESTURE079,
		SCRIPTEDANIMTYPE_GESTURE080,
		SCRIPTEDANIMTYPE_GESTURE081,
		SCRIPTEDANIMTYPE_GESTURE082,
		SCRIPTEDANIMTYPE_GESTURE083,
		SCRIPTEDANIMTYPE_GESTURE084,
		SCRIPTEDANIMTYPE_GESTURE085,
		SCRIPTEDANIMTYPE_GESTURE086,
		SCRIPTEDANIMTYPE_GESTURE087,
		SCRIPTEDANIMTYPE_GESTURE088,
		SCRIPTEDANIMTYPE_GESTURE089,
		SCRIPTEDANIMTYPE_GESTURE090,
		SCRIPTEDANIMTYPE_GESTURE091,
		SCRIPTEDANIMTYPE_GESTURE092,
		SCRIPTEDANIMTYPE_GESTURE093,
		SCRIPTEDANIMTYPE_GESTURE094,
		SCRIPTEDANIMTYPE_GESTURE095,
		SCRIPTEDANIMTYPE_GESTURE096,
		SCRIPTEDANIMTYPE_GESTURE097,
		SCRIPTEDANIMTYPE_GESTURE098,
		SCRIPTEDANIMTYPE_GESTURE099,
		SCRIPTEDANIMTYPE_GESTURE100,
		SCRIPTEDANIMTYPE_GESTURE101,
		SCRIPTEDANIMTYPE_GESTURE102,
		SCRIPTEDANIMTYPE_GESTURE103,
		SCRIPTEDANIMTYPE_GESTURE104,
		SCRIPTEDANIMTYPE_GESTURE105,
		SCRIPTEDANIMTYPE_GESTURE106,
		SCRIPTEDANIMTYPE_GESTURE107,
		SCRIPTEDANIMTYPE_GESTURE108,
		SCRIPTEDANIMTYPE_GESTURE109,
		SCRIPTEDANIMTYPE_GESTURE110,
		SCRIPTEDANIMTYPE_GESTURE111,
		SCRIPTEDANIMTYPE_GESTURE112,
		SCRIPTEDANIMTYPE_GESTURE113,
		SCRIPTEDANIMTYPE_GESTURE114,
		SCRIPTEDANIMTYPE_GESTURE115,
		SCRIPTEDANIMTYPE_NUM,
	};

	enum weapAnimFiles_t
	{
		WEAP_ANIM_ROOT = 0,
		WEAP_ANIM_INNER_ROOT = 1,
		WEAP_ANIM_GESTURE_IK_TARGET_1 = 2,
		WEAP_ANIM_GESTURE_IK_TARGET_2 = 3,
		WEAP_ANIM_GESTURE_IK_TARGET_3 = 4,
		WEAP_ANIM_GESTURE_IK_TARGET_4 = 5,
		WEAP_ANIM_ADDITIVE_WALK = 31,
		WEAP_ANIM_RELOAD_ADS = 171,
		WEAP_ANIM_RELOAD_EMPTY_ADS = 172,
		WEAP_ANIM_FAST_RELOAD_ADS = 175,
		WEAP_ANIM_FAST_RELOAD_EMPTY_ADS = 176,
		WEAP_ANIM_RELOAD_MULTIPLE_1 = 233,
		WEAP_ANIM_RELOAD_MULTIPLE_2 = 234,
		WEAP_ANIM_RELOAD_MULTIPLE_3 = 235,
		WEAP_ANIM_RELOAD_MULTIPLE_4 = 236,
		WEAP_ANIM_RELOAD_MULTIPLE_5 = 237,
		WEAP_ANIM_RELOAD_MULTIPLE_6 = 238,
		WEAP_ANIM_RELOAD_MULTIPLE_7 = 239,
		WEAP_ANIM_RELOAD_MULTIPLE_8 = 240,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_1 = 241,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_2 = 242,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_3 = 243,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_4 = 244,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_5 = 245,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_6 = 246,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_7 = 247,
		WEAP_ANIM_RELOAD_MULTIPLE_FAST_8 = 248,
		NUM_WEAP_ANIMS = 9999,
	};

	struct AttAmmoGeneral
	{
		ImpactType vfxImpactType;
		ImpactType sfxImpactType;
		MeleeImpactType meleeImpactType;
		weapFireType_t fireType;
		int burstCount;
	}; assert_sizeof(AttAmmoGeneral, 0x14);

	struct AttAmmoTracer
	{
		TracerDef PTR64 tracerType;
		tracerStyle_t tracerStyle;
	}; assert_sizeof(AttAmmoTracer, 0x10);

	struct AttPenetration
	{
		PenetrateType penetrateType;
		float penetrateMultiplier;
		bool rifleBullet;
		bool armorPiercing;
		bool impaling;
	}; assert_sizeof(AttPenetration, 0xC);

	struct AttSight
	{
		float blurSceneAdsInFraction;
		float blurSceneAdsOutFraction;
		bool aimDownSight;
		bool adsFire;
		bool rechamberWhileAds;
		bool noAdsWhenMagEmpty;
		bool canVariableZoom;
		bool hideRailWithThisScope;
		bool forceIronSightDown;
		bool useScopeDrift;
		bool useDualFOV;
	}; assert_sizeof(AttSight, 0x14);

	struct AttHoldBreath
	{
		bool canHoldBreath;
	};

	struct AttReload
	{
		bool noPartialReload;
		bool segmentedReload;
		bool reloadDisabled;
	};

	struct AttAddOns
	{
		bool motionTracker;
		bool silenced;
		bool riotShield;
	};

	struct AttGeneral
	{
		bool boltAction;
		bool inheritsPerks;
		bool reticleSpin45;
		bool adsShouldShowCrosshair;
		float enemyCrosshairRange;
		ReticleType reticleType;
		Material PTR64 reticleCenter;
		Material PTR64 reticleSide;
		Material PTR64 reticleOnePiece;
		int reticleCenterSize;
		int reticleSideSize;
		const char PTR64 szLUICrosshairWidget;
	}; assert_sizeof(AttGeneral, 0x38);

	struct AttLaser
	{
		LaserDef PTR64 laserTypeFriendly;
		LaserDef PTR64 laserTypeEnemy;
		bool forceLaserOn;
	}; assert_sizeof(AttLaser, 0x18);

	struct AttAimAssist
	{
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimAssistPitchSlowdown;
		float aimAssistPitchSlowdownAds;
		float aimAssistYawSlowdown;
		float aimAssistYawSlowdownAds;
		float aimAssistLockonStrength;
	}; assert_sizeof(AttAimAssist, 0x20);

	struct AttTargetAssist
	{
		targetAssistType_t targetAssistType;
		targetAssistBehavior_t targetAssistBehavior;
		float targetAssistRange;
		float targetAssistAngle;
		float targetAssistLosOffsetForward;
		float targetAssistLosOffsetRight;
		float targetAssistLosOffsetUp;
		bool targetAssistOnlyAvailableInAds;
	}; assert_sizeof(AttTargetAssist, 0x20);

	struct AttUnknown01
	{
		Material PTR64 material;
		float unk_0;
		int unk_1;
		int unk_2;
		float unk_3;
		float unk_4;
		float unk_5;
		int unk_6;
		float unk_7;
		float unk_8;
		int unk_9;
		int unk_10;
		int unk_11;
		int unk_12;
		float unk_13;
		float unk_14;
		float unk_15;
		float unk_16;
		float unk_17;
		float unk_18;
		float unk_19;
		float unk_20;
		float unk_21;
		float unk_22;
		float unk_23;
		float unk_24;
		float unk_25;
		float unk_26;
		float unk_27;
		float unk_28;
		float unk_29;
		float unk_30;
		float unk_31;
		float unk_32;
		float unk_33;
		float unk_34;
		float unk_35;
		float unk_36;
		float unk_37;
		float unk_38;
		int unk_39;
		int unk_40;
		int unk_41;
		int unk_42;
		int unk_43;
		int unk_44;
		int unk_45;
		int unk_46;
		bool unk_47;
		bool unk_48;
		bool pad0;
		bool pad1;
	}; assert_sizeof(AttUnknown01, 0xC8);

	struct AttAmmunition
	{
		int maxAmmo;
		int startAmmo;
		int clipSize;
		int shotCount;
		int reloadAmmoAdd;
		int reloadStartAdd;
		bool requireAmmoUsedPerShot;
	}; assert_sizeof(AttAmmunition, 0x1C);

	struct AttDamage
	{
		int damage;
		int mid1Damage;
		int mid2Damage;
		int mid3Damage;
		int minDamage;
		int meleeDamage;
		float maxDamageRange;
		float mid1DamageRange;
		float mid2DamageRange;
		float mid3DamageRange;
		float minDamageRange;
		int playerDamage;
		int mid1PlayerDamage;
		int mid2PlayerDamage;
		int mid3PlayerDamage;
		int minPlayerDamage;
		AnimDamageType deathAnimDamageType;
	}; assert_sizeof(AttDamage, 0x44);

	struct AttIdleSettings
	{
		float hipIdleAmount;
		float hipIdleSpeed;
		float idleCrouchFactor;
		float idleProneFactor;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
	}; assert_sizeof(AttIdleSettings, 0x18);

	struct AttADSSettings
	{
		float adsSpread;
		float adsAimPitch;
		float adsTransInTime;
		float adsTransOutTime;
		int adsReloadTransTime;
		float adsCrosshairInFrac;
		float adsCrosshairOutFrac;
		float adsInCrosshairAlphaStart;
		float adsInCrosshairAlphaEnd;
		float adsOutCrosshairAlphaStart;
		float adsOutCrosshairAlphaEnd;
		float adsZoomFov;
		float adsZoomInFrac;
		float adsZoomOutFrac;
		float adsFovLerpTime;
		float adsBobFactor;
		float adsViewBobMult;
		float adsFireRateScale;
		float adsDamageRangeScale;
		float adsFireAnimFrac;
		float fireTimerLerpToAdsScale;
		bool alwaysFireAtMaxRangeInAds;
		bool adsAlignEnabled;
		bool disableTagAlignX;
	}; assert_sizeof(AttADSSettings, 0x58);

	struct AttScopeDriftSettings
	{
		float fScopeDriftDelay;
		float fScopeDriftLerpInTime;
		float fScopeDriftSteadyTime;
		float fScopeDriftLerpOutTime;
		float fScopeDriftSteadyFactor;
		float fScopeDriftUnsteadyFactor;
	}; assert_sizeof(AttScopeDriftSettings, 0x18);

	struct AttHipSpread
	{
		float hipSpreadStandMin;
		float hipSpreadDuckedMin;
		float hipSpreadProneMin;
		float hipSpreadSprintMin;
		float hipSpreadInAirMin;
		float hipSpreadMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float hipSpreadSprintMax;
		float hipSpreadInAirMax;
		float hipSpreadFireAdd;
		float hipSpreadTurnAdd;
		float hipSpreadMoveAdd;
		float hipSpreadDecayRate;
		float hipSpreadDuckedDecay;
		float hipSpreadProneDecay;
		float hipSpreadSprintDecay;
		float hipSpreadInAirDecay;
	}; assert_sizeof(AttHipSpread, 0x48);

	struct AttSlideSpread
	{
		float slideSpreadMin;
		float slideSpreadMax;
		float slideSpreadDecayRate;
		float slideSpreadFireAdd;
		float slideSpreadTurnAdd;
	}; assert_sizeof(AttSlideSpread, 0x14);

	struct AttGunKick
	{
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float hipGunKickPitchMin;
		float hipGunKickPitchMax;
		float hipGunKickYawMin;
		float hipGunKickYawMax;
		float hipGunKickMagMin;
		float hipGunKickAccel;
		float hipGunKickSpeedMax;
		float hipGunKickSpeedDecay;
		float hipGunKickStaticDecay;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float adsGunKickPitchMin;
		float adsGunKickPitchMax;
		float adsGunKickYawMin;
		float adsGunKickYawMax;
		float adsGunKickMagMin;
		float adsGunKickAccel;
		float adsGunKickSpeedMax;
		float adsGunKickSpeedDecay;
		float adsGunKickStaticDecay;
	}; assert_sizeof(AttGunKick, 0x58);

	struct AttViewKick
	{
		float hipViewKickPitchMin;
		float hipViewKickPitchMax;
		float hipViewKickYawMin;
		float hipViewKickYawMax;
		float hipViewKickMagMin;
		float hipViewKickCenterSpeed;
		float adsViewKickPitchMin;
		float adsViewKickPitchMax;
		float adsViewKickYawMin;
		float adsViewKickYawMax;
		float adsViewKickMagMin;
		float adsViewKickCenterSpeed;
		float kickAlignedInputScalar;
		float kickOpposedInputScalar;
	}; assert_sizeof(AttViewKick, 0x38);

	struct ADSOverlay
	{
		Material PTR64 shader;
		Material PTR64 shaderLowRes;
		Material PTR64 shaderEMP;
		Material PTR64 shaderEMPLowRes;
		weapOverlayReticle_t reticle;
		float width;
		float height;
		float widthSplitscreen;
		float heightSplitscreen;
	}; assert_sizeof(ADSOverlay, 0x38);

	struct AttADSOverlay
	{
		ADSOverlay overlay;
		bool hybridToggle;
		bool thermalScope;
		bool thermalToggle;
		bool outlineEnemies;
	}; assert_sizeof(AttADSOverlay, 0x40);

	struct AttOutline
	{
		vec4_t outlineColor;
		vec4_t outlineAltColor;
		vec4_t outlineFillColor0;
		vec4_t outlineFillColor1;
		vec4_t outlineOccludedOutlineColor;
		vec4_t outlineOccludedInlineColor;
		vec4_t outlineOccludedInteriorColor;
		float outlineWidth;
		bool outlineEnemies;
		bool outlineDepthTest;
		bool outlineFill;
		bool outlineScriptControlled;
		bool outlineVehicles;
		bool outlineTurrets;
		bool outlineCharacters;
		bool outlineAgents;
		bool outlineScriptMovers;
		bool outlineLockOn;
	}; assert_sizeof(AttOutline, 0x80);

	struct AttUI
	{
		Material PTR64 hudIcon;
		Material PTR64 pickupIcon;
		Material PTR64 dangerIcon;
		Material PTR64 throwBackIcon;
		bool hideWarningIcons;
		float warningIconsDelay;
		Material PTR64 dpadIcon;
		Material PTR64 ammoCounterIcon;
		ammoCounterClipType_t ammoCounterClip;
		float grenadeDangerIconDistance;
	}; assert_sizeof(AttUI, 0x40);

	struct AttRumbles
	{
		RumbleInfo PTR64 fireRumble;
		RumbleInfo PTR64 meleeImpactRumble;
	}; assert_sizeof(AttRumbles, 0x10);

	struct AttProjectile
	{
		int explosionRadius;
		int explosionForceRadius;
		int explosionInnerDamage;
		int explosionOuterDamage;
		float damageConeAngle;
		int projectileSpeed;
		int projectileSpeedUp;
		int projectileActivateDist;
		float projectileLifetime;
		float projectileLifetimeStdDeviation;
		XModel PTR64 projectileModel;
		weapProjExposion_t projExplosionType;
		FxCombinedDef projExplosionEffect;
		bool projExplosionEffectForceNormalUp;
		const char PTR64 projExplosionSound;
		FxCombinedDef projDudEffect;
		const char PTR64 projDudSound;
		bool projImpactExplode;
		bool disableProjectileCrumpleCheck;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		FxCombinedDef projBodyEffect;
		FxCombinedDef projTrailEffect;
		FxCombinedDef projBeaconEffect;
		int projIgnitionDelay;
		FxCombinedDef projIgnitionEffect;
		const char PTR64 projIgnitionSound;
		WeapStickinessType stickiness;
		int fuseTime;
		int aiFuseTime;
		bool stickToPlayers;
		bool stickToVehicles;
		bool stickToTurrets;
		bool stickToNonStick;
		bool timedDetonation;
		bool isPredictedProjectile;
		bool useSteppedExplosionDamage;
		float reactiveMotionRadiusScale;
		float reactiveMotionFrequencyScale;
		float reactiveMotionAmplitudeScale;
		float reactiveMotionFalloff;
		float reactiveMotionLifetime;
	}; assert_sizeof(AttProjectile, 0xF8);

	enum WeaponChargeType : std::int32_t
	{
	};

	struct AttCharged
	{
		WeaponChargeType chargeType;
		float chargeGain;
		float chargeCostPerShot;
		float chargeLossWhenIdle;
		float chargeEmptyCooldown;
		float chargeFireAtMaxDamageMultiplier;
		int chargeMeterEffectBoneCount;
		FxCombinedDef chargeMeterEffect;
		const char PTR64 chargeUpSound;
		const char PTR64 chargeDownSound;
		const char PTR64 chargeDownToUpSound;
		const char PTR64 chargeUpToDownSound;
		const char PTR64 chargeMaxSound;
		const char PTR64 chargeUpSoundPlayer;
		const char PTR64 chargeDownSoundPlayer;
		const char PTR64 chargeDownToUpSoundPlayer;
		const char PTR64 chargeUpToDownSoundPlayer;
		const char PTR64 chargeMaxSoundPlayer;
		bool chargeHudReveal;
		RumbleInfo PTR64 chargeRumble;
	}; assert_sizeof(AttCharged, 0x90);

	struct AdsAltSwitch
	{
		float fovInterpTimeSecMainToAlt;
		float fovInterpDelaySecMainToAlt;
		float dualFovSwitchRateMainToAlt;
		AdsAltSwitchInterpType fovInterpTypeMainToAlt;
		float fovInterpTimeSecAltToMain;
		float fovInterpDelaySecAltToMain;
		float dualFovSwitchRateAltToMain;
		AdsAltSwitchInterpType fovInterpTypeAltToMain;
	}; assert_sizeof(AdsAltSwitch, 0x20);

	struct AttRegeneration
	{
		bool regenerationEnabled;
		int regenerationTimeMs;
		int regenerationAddTimeMs;
		int regenerationAmount;
		bool regenerationConsumeStock;
		bool regenerationDisableWhileFiring;
	}; assert_sizeof(AttRegeneration, 0x14);

	struct AttMovement
	{
		float moveSpeedScale;
		float adsMoveSpeedScale;
		bool fastADS3PAnims;
	}; assert_sizeof(AttMovement, 0xC);

	struct AttBurst
	{
		int burstFireCooldown;
		bool burstFireAuto;
	}; assert_sizeof(AttBurst, 8);

	struct WeaponAttachment
	{
		union
		{
			const char PTR64 szInternalName;
			const char PTR64 name;
		};
		const char PTR64 szDisplayName;
		scr_string_t internalName;
		bool papAttachment; // packapunch
		AttachmentType type;
		weapType_t weaponType;
		weapClass_t weapClass;
		int numReticles;
		int numAltReticles;
		int unk;
		XModel PTR64 worldModelCamo;
		XModel PTR64 viewModelCamo;
		XModel PTR64  PTR64 worldModelVariations;
		XModel PTR64  PTR64 viewModelVariations;
		unsigned int numModelVariations;
		Material PTR64  PTR64 worldModelCamoMaterials;
		Material PTR64  PTR64 viewModelCamoMaterials;
		unsigned int numWorldModelCamoMaterials;
		unsigned int numViewModelCamoMaterials;
		scr_string_t attachPoint;
		ReticleDef PTR64  PTR64 reticles;
		ReticleDef PTR64  PTR64 altReticles;
		AttAmmoGeneral PTR64 ammogeneral;
		AttAmmoTracer PTR64 tracer;
		AttPenetration PTR64 penetration;
		AttSight PTR64 sight;
		AttHoldBreath PTR64 holdBreath;
		AttReload PTR64 reload;
		AttAddOns PTR64 addOns;
		AttLaser PTR64 laser;
		AttGeneral PTR64 general;
		AttAimAssist PTR64 aimAssist;
		AttTargetAssist PTR64 targetAssist;
		AttUnknown01 PTR64 unkAtt01;
		AttAmmunition PTR64 ammunition;
		AttDamage PTR64 damage;
		AttIdleSettings PTR64 idleSettings;
		AttADSSettings PTR64 adsSettings;
		AttADSSettings PTR64 adsSettingsMain;
		AttScopeDriftSettings PTR64 scopeDriftSettings;
		AttScopeDriftSettings PTR64 scopeDriftSettingsMain;
		AttHipSpread PTR64 hipSpread;
		AttSlideSpread PTR64 slideSpread;
		AttGunKick PTR64 gunKick;
		AttViewKick PTR64 viewKick;
		AttADSOverlay PTR64 adsOverlay;
		AttOutline PTR64 outline;
		AttUI PTR64 ui;
		AttRumbles PTR64 rumbles;
		AttProjectile PTR64 projectile;
		AttCharged PTR64 charged;
		AdsAltSwitch PTR64 adsAltSwitch;
		AttRegeneration PTR64 regeneration;
		AttMovement PTR64 movement;
		AttBurst PTR64 burst;
		float PTR64 locationDamage;
		float ammunitionScale;
		float damageScale;
		float stateTimersScale;
		float reloadTimersScale;
		int fireTimeOverride;
		int fireTimeAkimboOverride;
		float fireTimersScale;
		float burstFireCooldownScale;
		float idleHipMotionScale;
		float idleADSMotionScale;
		float idleADSMotionTimeScale;
		float adsSettingsScale;
		float adsSettingsScaleMain;
		float hipSpreadScale;
		float slideSpreadScale;
		float gunKickScale;
		float viewKickScale;
		float viewCenterScale;
		float adsSwayScale;
		float adsSwayScale2;
		float adsSwayScale3;
		int iAmmoIndex;
		int loadIndex;
		bool useAlternateViewModelLaser;
		bool hideIronSightsWithThisAttachment;
		bool shareAmmoWithAlt;
		bool useLeftTriggerAltFire;
		bool containsIKTag;
		bool isAkimboAttachment;
		bool attachLeftWeaponAkimbo;
		bool attachRightWeaponAkimbo;
		bool luiWeaponInfoWidgetUsesScopeStencil;
		const char PTR64 szAltModeName;
		const char PTR64 szLUIWeaponInfoWidgetName;
		const char PTR64 szLUIWeaponInfoWidgetTag;
	}; assert_sizeof(WeaponAttachment, 0x218);

	struct AnimOverride
	{
		scr_string_t attachment1;
		scr_string_t attachment2;
		WeaponAnimPackage PTR64 overrides;
		WeaponAnimPackage PTR64 overridesAlt;
	}; assert_sizeof(AnimOverride, 24);

	struct SFXOverride
	{
		scr_string_t attachment1;
		scr_string_t attachment2;
		WeaponSFXPackage PTR64 overrides;
		WeaponSFXPackage PTR64 overridesAlt;
	}; assert_sizeof(SFXOverride, 24);

	struct VFXOverride
	{
		scr_string_t attachment1;
		scr_string_t attachment2;
		WeaponVFXPackage PTR64 overrides;
		WeaponVFXPackage PTR64 overridesAlt;
	}; assert_sizeof(VFXOverride, 24);

	enum GrenadeRotationDirection : std::int32_t
	{
		GRD_RANDOM = 0x0,
		GRD_CLOCKWISE = 0x1,
		GRD_COUNTERCLOCKWISE = 0x2,
		GRD_COUNT = 0x3,
	};

	struct GrenadeRotationParams
	{
		float initialPitch;
		float initialYaw;
		float initialRoll;
		GrenadeRotationDirection rotationPitchDir;
		int rotationPitchMin;
		int rotationPitchMax;
		GrenadeRotationDirection rotationYawDir;
		int rotationYawMin;
		int rotationYawMax;
		GrenadeRotationDirection rotationRollDir;
		int rotationRollMin;
		int rotationRollMax;
		bool rotate;
	};

	struct WeaponDef
	{
		const char PTR64 szOverlayName;
		XModel PTR64 gunXModel;
		XModel PTR64 gunXModelLeftHand;
		XModel PTR64 gunXModelRightHand;
		XModel PTR64 defaultViewModel;
		XModel PTR64 defaultWorldModelLeftHand;
		XModel PTR64 defaultWorldModelRightHand;
		XModel PTR64 worldModel;
		XModel PTR64 worldXModelLeftHand;
		XModel PTR64 worldXModelRightHand;
		XModel PTR64 defaultWorldModel;
		XModel PTR64 playerShadowModel;
		XModel PTR64 playerShadowModelLeftHand;
		XModel PTR64 playerShadowModelRightHand;
		XModel PTR64 handXModel;
		XModel PTR64  PTR64 complexWorldModel;
		XModel PTR64  PTR64 complexWorldModelLeftHand;
		XModel PTR64  PTR64 complexWorldModelRightHand;
		XModel PTR64  PTR64 complexGunXModel;
		XModel PTR64  PTR64 complexGunXModelLeftHand;
		XModel PTR64  PTR64 complexGunXModelRightHand;
		unsigned int numComplexModels;
		int pad; // padding
		Material PTR64 camoWorldModelMaterialOverride[16];
		Material PTR64 camoViewModelMaterialOverride[16];
		float unk_0; // set but unused?
		float unk_1; // set but unused?
		float unk_2; // set but unused?
		float unk_3; // set but unused?
		WeaponAnimPackage PTR64 szXAnims;
		WeaponAnimPackage PTR64 szXAnimsRightHanded;
		WeaponAnimPackage PTR64 szXAnimsLeftHanded;
		bool unk_4_0; // meleeAnims? // 1407448B0
		bool unk_4_1; // weaponCamo? // 140718630
		char pad17[2]; // padding
		int iFireTime;
		int iFireDelay;
		int iFireTimeAkimbo;
		int iFireDelayAkimbo;
		int pad3; // padding
		const char PTR64 szModeName;
		scr_string_t PTR64 notetrackRumbleMapKeys; //  array: 16
		scr_string_t PTR64 notetrackRumbleMapValues; //  array: 16
		scr_string_t PTR64 notetrackFXMapKeys; //  array: 16
		FxCombinedDef PTR64 notetrackFXMapValues; //  array: 16
		scr_string_t PTR64 notetrackFXMapTagValues; //  array: 16
		playerAnimType_t playerAnimType;
		scriptedAnimEvent_t scriptedAnimEvent;
		scriptedAnimType_t scriptedAnimType;
		weapType_t weapType;
		unsigned int whizbyType; // guessed // 140747580
		weapClass_t weapClass;
		PenetrateType penetrateType;
		AnimDamageType deathAnimDamageType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		int burstCount;
		targetAssistType_t targetAssistType;
		targetAssistBehavior_t targetAssistBehavior;
		float pad28; // padding
		Material PTR64 unkMaterial; // -start AttUnknown01 // 140101130
		float unk_18;
		int unk_19;
		float unk_20;
		float unk_21;
		float unk_22;
		float unk_23;
		float unk_24;
		float unk_25;
		float unk_26;
		float unk_27;
		float unk_28;
		float unk_29;
		float unk_30;
		float unk_31;
		float unk_32;
		float unk_33;
		float unk_34;
		float unk_35;
		float unk_36;
		float unk_37;
		float unk_38;
		float unk_39;
		float unk_40;
		float unk_41;
		float unk_42;
		float unk_43;
		float unk_44;
		float unk_45;
		float unk_46;
		float unk_47;
		float unk_48;
		float unk_49;
		float unk_50;
		float unk_51;
		int unk_52;
		int unk_53;
		int unk_54;
		int unk_55;
		int unk_56;
		int unk_57;
		int unk_58;
		int unk_59;
		int unk_60;
		int unk_61;
		float unk_62;
		float unk_63;
		float unk_64;
		bool unk_65_0;
		bool unk_65_1;
		bool unk_65_2;
		bool unk_65_3; // -end
		float targetAssistRange;
		float targetAssistAngle;
		float targetAssistLosOffsetForward;
		float targetAssistLosOffsetRight;
		float targetAssistLosOffsetUp;
		bool targetAssistOnlyAvailableInAds;
		bool unk_71_1; // unused
		bool unk_71_2; // unused
		bool unk_71_3; // unused
		bool bSegmentedReload;
		bool unk_72_1; // unused/padding
		bool unk_72_2; // unused/padding
		bool unk_72_3; // unused/padding
		float burstFireCooldown;
		bool burstFireAuto;
		bool pad27[3]; // padding
		OffhandClass offhandClass;
		weapStance_t stance;
		float pad18; // padding
		WeaponVFXPackage PTR64 vfxPackage;
		WeaponSFXPackage PTR64 sfxPackage;
		ReticleType reticleType;
		float pad8; // padding
		Material PTR64 reticleCenter;
		Material PTR64 reticleSide;
		Material PTR64 reticleOnePiece;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		bool reticleCenterPulse;
		char pad25[3]; // padding
		activeReticleType_t activeReticleType;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		float pad4; // padding
		XModel PTR64 worldClipModel;
		XModel PTR64 rocketModel;
		XModel PTR64 knifeModel;
		XModel PTR64 worldKnifeModel;
		Material PTR64 hudIcon;
		Material PTR64 pickupIcon;
		Material PTR64 dangerIcon;
		Material PTR64 throwBackIcon;
		bool hideWarningIcons;
		char pad6[3]; // padding
		float warningIconsDelay;
		Material PTR64 ammoCounterIcon;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		int iPerkStartAmmo;
		int iPerkMaxAmmo;
		const char PTR64 szAmmoName;
		int iAmmoIndex;
		int iMaxAmmo;
		int shotCount;
		const char PTR64 szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int iAmmoUsedPerShot;
		bool requireAmmoUsedPerShot;
		char pad24[3]; // padding
		float lowAmmoWarningThreshold;
		bool disableNoAmmoWarning;
		char pad19[3]; // padding
		int damage;
		int playerDamage;
		int meleeDamage;
		int iDamageType;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimAssistPitchSlowdown;
		float aimAssistPitchSlowdownAds;
		float aimAssistYawSlowdown;
		float aimAssistYawSlowdownAds;
		float aimAssistLockonStrength;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float sprintRestoreDelay;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		ADSOverlay overlay;
		WeapOverlayInteface_t overlayInterface;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadSprintMin;
		float hipSpreadInAirMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float hipSpreadSprintMax;
		float hipSpreadInAirMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float hipSpreadSprintDecay;
		float hipSpreadInAirDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
		float slideSpreadMin;
		float slideSpreadMax;
		float slideSpreadDecayRate;
		float slideSpreadFireAdd;
		float slideSpreadTurnAdd;
		float swayMaxAngleSteadyAim;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSway_UNKNOWN_Scale; // set but unused
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsFireRateScale;
		float adsDamageRangeScale;
		float adsFireAnimFrac;
		float fireTimerLerpToAdsScale;
		bool alwaysFireAtMaxRangeInAds;
		char pad23[3]; // padding
		float dualWieldViewModelOffset;
		float fScopeDriftDelay;
		float fScopeDriftLerpInTime;
		float fScopeDriftSteadyTime;
		float fScopeDriftLerpOutTime;
		float fScopeDriftSteadyFactor;
		float fScopeDriftUnsteadyFactor;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionForceRadius;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		int iProjectileDetonationRadius;
		float projLifetime;
		float projLifetimeStdDeviation;
		float timeToAccelerate;
		float projectileCurvature;
		float pad2; // padding
		XModel PTR64 projectileModel;
		weapProjExposion_t projExplosion;
		FxCombinedDef projExplosionEffect;
		FxCombinedDef projDudEffect;
		WeapStickinessType stickiness;
		float ricochetChance;
		bool riotShieldEnableDamage;
		int riotShieldHealth;
		float riotShieldDamageMult;
		float pad7; // padding
		float PTR64 parallelBounce; // array: 64
		float PTR64 perpendicularBounce; // array: 64
		FxCombinedDef projBodyEffect;
		FxCombinedDef projTrailEffect;
		FxCombinedDef projBeaconEffect;
		vec3_t vProjectileColor;
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		FxCombinedDef projIgnitionEffect;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		float adsInCrosshairAlphaStart;
		float adsInCrosshairAlphaEnd;
		float adsOutCrosshairAlphaStart;
		float adsOutCrosshairAlphaEnd;
		bool adsShouldShowCrosshair;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickMagMin;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewKickMagMin;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int iVisibilityAxis;
		float fVisibilityUpOffset;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickMagMin;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewKickMagMin;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float multipleReloadClipPercentage;
		float kickAlignedInputScalar;
		float kickOpposedInputScalar;
		float fightDist;
		float maxDist;
		const char PTR64 accuracyGraphName[2];
		vec2_t PTR64 originalAccuracyGraphKnots[2];
		unsigned __int16 originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		bool softLeftRightArc;
		char pad20[3]; // padding
		float accuracy;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char PTR64 szUseHintString;
		const char PTR64 dropHintString;
		unsigned int iUseHintStringIndex;
		unsigned int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char PTR64 szScript;
		float adsSpeedMs[2];
		int minDamage;
		int minPlayerDamage;
		int mid1Damage;
		int mid2Damage;
		int mid3Damage;
		int mid1PlayerDamage;
		int mid2PlayerDamage;
		int mid3PlayerDamage;
		float maxDamageRange;
		float mid1DamageRange;
		float mid2DamageRange;
		float mid3DamageRange;
		float minDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float robotechMaxPitch;
		float robotechMaxYaw;
		float robotechFrequency;
		float robotechVariancePitch;
		float robotechVarianceYaw;
		float robotechVarianceFrequency;
		float PTR64 locationDamageMultipliers;
		char PTR64 hitLocPriorityMap;
		float unittypeMultipliers[10];
		RumbleInfo PTR64 fireRumble;
		RumbleInfo PTR64 meleeImpactRumble;
		tracerStyle_t tracerStyle;
		TracerDef PTR64 tracerType;
		TracerDef PTR64 overchargeTracerType;
		LaserDef PTR64 laserTypeFriendly;
		LaserDef PTR64 laserTypeEnemy;
		bool turretADSEnabled;
		float turretADSTime;
		float turretFov;
		float turretFovADS;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		const char PTR64 turretOverheatSound;
		FxCombinedDef turretOverheatEffect;
		RumbleInfo PTR64 turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		const char PTR64 turretBarrelSpinMaxSnd;
		const char PTR64 turretBarrelSpinUpSnd[4];
		const char PTR64 turretBarrelSpinDownSnd[4];
		const char PTR64 missileConeSoundAlias;
		const char PTR64 missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		scr_string_t knifeAttachTagOverride;
		scr_string_t knifeAttachTagOverride2;
		bool knifeAlwaysAttached;
		bool meleeOverrideValues;
		char pad26[2]; // padding
		float aim_automelee_lerp;
		float aim_automelee_region_height;
		float aim_automelee_region_width;
		float aim_automelee_maxPitchMovement;
		float aim_automelee_maxYawMovement;
		float player_meleeHeight;
		float player_meleeWidth;
		float playerMeleeRangeStanding;
		float playerMeleeRangeCrouched;
		float playerMeleeRangeProne;
		float playerMeleeRangeChargeStanding;
		float playerMeleeRangeChargeCrouched;
		float playerMeleeChargeHeightTolerance;
		bool shieldAllowFiring;
		bool shieldUnkBool; // shieldAllowGesture? // 14004CCE0
		char pad13[2]; // padding
		offhandShieldMaxSpeed_t shieldMaxSpeed;
		bool shieldAlwaysDisplay;
		char pad14[3]; // padding
		Gesture PTR64 shieldDeployGesture;
		Gesture PTR64 shieldFireWeapGesture;
		Gesture PTR64 shieldDeployWhileFiring;
		Gesture PTR64 shieldRetractWhileFiring;
		Gesture PTR64 shieldBashGesture;
		FxCombinedDef shieldMeleeFx;
		float shieldMeleeFxDelay;
		float HitEarthquakeScale;
		float HitEarthquakeDuration;
		float HitEarthquakeRadius;
		RumbleInfo PTR64 shieldHitRumble;
		float MissEarthquakeScale;
		float MissEarthquakeDuration;
		float MissEarthquakeRadius;
		RumbleInfo PTR64 shieldMissRumble;
		int shieldDeployButton;
		bool shieldUsesEnergy;
		float shieldMaxEnergy;
		float shieldConsumptionRate;
		float shieldMeleeEnergyCost;
		float shieldMeleeHitEnergyCost;
		float reactiveMotionRadiusScale;
		float reactiveMotionFrequencyScale;
		float reactiveMotionAmplitudeScale;
		float reactiveMotionFalloff;
		float reactiveMotionLifetime;
		bool hasAnyTransientModels;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool isAirburstWeapon;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool allowGrenadeSwitching;
		bool inheritsPerks;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool bEnergyBullet;
		bool armorPiercing;
		bool impaling;
		bool bBoltAction;
		bool aimDownSight;
		bool canHoldBreath;
		bool meleeOnly;
		bool supportsAlternateMelee;
		bool canVariableZoom;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool reticleSpin45;
		bool bClipOnly;
		bool bDoesNotConsumeAmmo;
		bool bRemoveWeaponOnEmpty;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoPrimaryDisplay;
		bool suppressAmmoReserveDisplay;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		DualWieldType dualWieldType;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool reloadDisabled;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool dropGrenadeHeldOnDeath;
		bool projExplosionEffectForceNormalUp;
		bool projExplosionEffectInheritParentDirection;
		bool bProjImpactExplode;
		bool disableProjectileCrumpleCheck;
		bool bProjTrajectoryEvents;
		bool bProjWhizByEnabled;
		bool stickToPlayers;
		bool stickToVehicles;
		bool stickToTurrets;
		bool stickToNonStick;
		bool projEnableMissileStickiness;
		bool thrownSideways;
		bool hasDetonator;
		bool disableFiring;
		bool firesOnWeaponSwitch;
		bool disableHolding;
		bool timedDetonation;
		int explosiveDamageDelay;
		int fuseTime;
		int aiFuseTime;
		int maxHoldTime;
		GrenadeRotationParams rotationParams;
		bool holdButtonToThrow;
		bool infiniteHold;
		bool freezeMovementWhenFiring;
		bool offhandAllowsSprint;
		bool thermalScope;
		bool thermalToggle;
		bool outlineEnemies;
		bool outlineDepthTest;
		bool outlineFill;
		char pad10[3]; // padding
		float enemyOutlineR;
		float enemyOutlineG;
		float enemyOutlineB;
		float enemyOutlineA;
		float allyOutlineR;
		float allyOutlineG;
		float allyOutlineB;
		float allyOutlineA;
		bool depthScan;
		char pad11[3]; // padding
		float depthScanThickness;
		float depthScanR;
		float depthScanG;
		float depthScanB;
		float depthScanA;
		float depthScanOutlineThickness;
		float depthScanOutlineR;
		float depthScanOutlineG;
		float depthScanOutlineB;
		float depthScanOutlineA;
		bool depthScanOverlay;
		char pad12[3]; // padding
		float depthScanOverlayStrength;
		float depthScanOverlayXTiles;
		float depthScanOverlayYTiles;
		float depthScanOverlayXScroll;
		float depthScanOverlayYScroll;
		float blurSceneAdsInFraction;
		float blurSceneAdsOutFraction;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
		bool doNotAllowAttachmentsToOverrideSpread;
		bool useScopeDrift;
		bool alwaysShatterGlassOnImpact;
		bool oldWeapon;
		bool jumpSpread;
		bool noFullViewmodelAnimations;
		float killcamOffset;
		bool useDualFOV;
		bool disableDrop;
		bool preferredDrop;
		char pad21[5]; // pad
		Gesture PTR64 gestureAnimation;
		float gestureFireStateTime;
		Gesture PTR64 gesturePullback;
		float minPullbackTime;
		Gesture PTR64 gestureThrow;
		float gestureFireTime;
		Gesture PTR64 gestureDetonate;
		float gestureDetonationTime;
		float unk_433; // 1400688A0
		const char PTR64 unknownString1;
		float unk_434; // 1400688A0
		char pad22[4]; // pad
		const char PTR64 unknownString2;
		bool gesturesDisablePrimary;
		char pad15[7]; // pad
		FxCombinedDef cameraFireEffect;
		float cameraFireEffectDurationSec;
		float changedFireTime;
		float changedFireTimeAkimbo;
		int changedFireTimeNumBullets;
		WeaponChargeType chargeType;
		float chargeGain;
		float chargeCostPerShot;
		float chargeLossWhenIdle;
		float chargeEmptyCooldown;
		float chargeFireAtMaxDamageMultiplier;
		int chargeMeterEffectBoneCount;
		FxCombinedDef chargeMeterEffect;
		const char PTR64 chargeUpSound;
		const char PTR64 chargeDownSound;
		const char PTR64 chargeUpSoundPlayer;
		const char PTR64 chargeDownSoundPlayer;
		const char PTR64 chargeDownToUpSound;
		const char PTR64 chargeDownToUpSoundPlayer;
		const char PTR64 chargeUpToDownSound;
		const char PTR64 chargeUpToDownSoundPlayer;
		const char PTR64 chargeMaxSound;
		const char PTR64 chargeMaxSoundPlayer;
		bool chargeHudReveal;
		RumbleInfo PTR64 chargeRumble;
		scr_string_t stowTag;
		XModel PTR64 stowOffsetModel;
		WeaponSlot slot;
		float maxTargetAngle;
		bool spaceshipSecondaryWeapon;
		float impulseFieldRadius;
		float impulseFieldInitialSpeed;
		float impulseFieldMaxSpeed;
		float impulseFieldAcceleration;
		float impulseFieldInAirImpulseMultiplier;
		float impulseFieldInAirImpulseMultiplierInterpTime;
		float impulseFieldSlideMultiplier;
		float impulseFieldSlideMultiplierInterpTime;
		bool impulseFieldIsPush;
		bool impulseFieldAffectsFriendlies;
		bool impulseFieldAffectsSelf;
		bool impulseFieldAffectsProne;
		bool regenerationEnabled;
		int regenerationTimeMs;
		int regenerationAddTimeMs;
		int regenerationAmount;
		bool regenerationConsumeStock;
		bool regenerationDisableWhileFiring;
		bool deployRequireOnWalkableSurface;
		bool deployRequireOnNavmesh;
		bool deployRequireSkyAbove;
		bool deployRequireNoOverhang;
		bool deployAlwaysUpright;
		bool deployEdgeSnap;
		float deployCylinderRadius;
		float deployCylinderHeight;
		float deployMaxDistance;
		float pad16;  // pad
		FxCombinedDef deployEffect;
		int deployValidGroupId;
		int deployIndoorGroupId;
		int deployInvalidGroupId;
		int deployOutOfRangeGroupId;
		AnimOverride animOverrides[21];
		SFXOverride sfxOverrides[21];
		VFXOverride vfxOverrides[21];
		float reactiveEmitterDelay;
		float grenadeDangerIconDistance;
		bool unk_466_0; // unk // 14074E570
		char pad29[7]; // pad
	}; assert_sizeof(WeaponDef, 0x1418);
	assert_offsetof(WeaponDef, handXModel, 112);
	assert_offsetof(WeaponDef, camoWorldModelMaterialOverride, 176);
	assert_offsetof(WeaponDef, camoViewModelMaterialOverride, 304);
	assert_offsetof(WeaponDef, szXAnims, 448);
	assert_offsetof(WeaponDef, szModeName, 496);
	assert_offsetof(WeaponDef, notetrackFXMapTagValues, 536);
	assert_offsetof(WeaponDef, reticleOnePiece, 888);
	assert_offsetof(WeaponDef, hudIcon, 1112);
	assert_offsetof(WeaponDef, szAmmoName, 1176);
	assert_offsetof(WeaponDef, szSharedAmmoCapName, 1200);
	assert_offsetof(WeaponDef, projDudEffect, 1752);
	assert_offsetof(WeaponDef, parallelBounce, 1792);
	assert_offsetof(WeaponDef, projIgnitionEffect, 1880);
	assert_offsetof(WeaponDef, accuracyGraphName, 2104);
	assert_offsetof(WeaponDef, szUseHintString, 2216);
	assert_offsetof(WeaponDef, szScript, 2264);
	assert_offsetof(WeaponDef, locationDamageMultipliers, 2368);
	assert_offsetof(WeaponDef, fireRumble, 2424);
	assert_offsetof(WeaponDef, laserTypeEnemy, 2472);
	assert_offsetof(WeaponDef, turretOverheatSound, 2520);
	assert_offsetof(WeaponDef, missileConeSoundAliasAtBase, 2648);
	assert_offsetof(WeaponDef, knifeAttachTagOverride, 2708);
	assert_offsetof(WeaponDef, shieldDeployGesture, 2784);
	assert_offsetof(WeaponDef, shieldHitRumble, 2856);
	assert_offsetof(WeaponDef, shieldMissRumble, 2880);
	assert_offsetof(WeaponDef, gestureAnimation, 3208);
	assert_offsetof(WeaponDef, gestureDetonate, 3256);
	assert_offsetof(WeaponDef, unknownString2, 3288);
	assert_offsetof(WeaponDef, cameraFireEffect, 3304);
	assert_offsetof(WeaponDef, chargeMeterEffect, 3368);
	assert_offsetof(WeaponDef, chargeRumble, 3472);
	assert_offsetof(WeaponDef, stowOffsetModel, 3488);

	struct NoteTrackToSoundEntry
	{
		unsigned int numSoundMappings;
		scr_string_t attachment;
		scr_string_t PTR64 notetrackSoundMapKeys;
		scr_string_t PTR64 notetrackSoundMapValues;
	};

	enum SuitAnimType : std::int32_t
	{
		ANIM_SUIT_HUMAN = 0x0,
		ANIM_SUIT_ROBOTIC = 0x1,
		ANIM_SUIT_C8 = 0x2,
		ANIM_SUIT_REAPER = 0x3,
		NUM_ANIM_SUIT_STATE = 0x4,
		ANIM_SUIT_INVALID = 0x4,
	};

	struct NoteTrackToSuitSoundEntry
	{
		unsigned int numSoundMappings;
		SuitAnimType suitAnimState;
		scr_string_t PTR64 notetrackSoundMapKeys;
		scr_string_t PTR64 notetrackSoundMapValues;
	};

	struct WeaponCompleteDef
	{
		union
		{
			const char PTR64 szInternalName;
			const char PTR64 name;
		};
		WeaponDef PTR64 weapDef;
		const char PTR64 szDisplayName;
		const char PTR64 szLootTable;
		scr_string_t PTR64 hideTags;
		unsigned int numAttachments;
		unsigned int numAttachments2;
		unsigned int numAttachments3; // underbarrel
		unsigned int numAttachments4;
		unsigned int numAttachments5; // cosmetic
		unsigned int numAttachments6;
		int numLootVariants; // runtime data
		int pad; // padding
		WeaponAttachment PTR64  PTR64 attachments;
		WeaponAttachment PTR64  PTR64 attachments2;
		WeaponAttachment PTR64  PTR64 attachments3;
		WeaponAttachment PTR64  PTR64 attachments4;
		WeaponAttachment PTR64  PTR64 attachments5;
		WeaponAttachment PTR64  PTR64 attachments6;
		unsigned int numNotetrackSoundMappings;
		int pad2; // padding
		scr_string_t PTR64 notetrackSoundMapKeys;
		scr_string_t PTR64 notetrackSoundMapValues;
		unsigned int numNotetrackOverrides;
		NoteTrackToSoundEntry PTR64 notetrackOverrides;
		unsigned int numNotetrackSuitEntries;
		NoteTrackToSuitSoundEntry PTR64 notetrackSuitEntries;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType vfxImpactType;
		ImpactType sfxImpactType;
		MeleeImpactType meleeImpactType;
		float penetrateMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char PTR64 szAltWeaponName;
		Material PTR64 killIconMat;
		Material PTR64 dpadIconMat;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned short accuracyGraphKnotCount[2];
		vec2_t PTR64 accuracyGraphKnots[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
		bool luiWeaponInfoWidgetUsesScopeStencil;
		const char PTR64 szAdsrBaseSetting;
		const char PTR64 szLUIWeaponInfoWidgetName;
		const char PTR64 szLUIWeaponInfoWidgetTag;
		const char PTR64 szLUICrosshairWidget;
	}; assert_sizeof(WeaponCompleteDef, 0x138);
	assert_offsetof(WeaponCompleteDef, attachments, 72);
	assert_offsetof(WeaponCompleteDef, notetrackSuitEntries, 168);
	assert_offsetof(WeaponCompleteDef, killIconMat, 224);
	assert_offsetof(WeaponCompleteDef, notetrackSuitEntries, 168);
	assert_offsetof(WeaponCompleteDef, accuracyGraphKnotCount, 252);
	assert_offsetof(WeaponCompleteDef, accuracyGraphKnots, 256);
	assert_offsetof(WeaponCompleteDef, szAdsrBaseSetting, 280);

	enum PARTICLE_FLAG
	{
		PARTICLE_FLAG_KILL = 0x1,
		PARTICLE_FLAG_PENDING_DEFERRED_PHYSICS = 0x2,
		PARTICLE_FLAG_IMPACT = 0x4,
		PARTICLE_FLAG_IMPACT_WITH_RAYCAST = 0x8,
		PARTICLE_FLAG_AT_REST = 0x10,
		PARTICLE_FLAG_SENT_FIRST_RAY_CAST = 0x20,
		PARTICLE_FLAG_PENDING_DEFERRED_PHYSICS_UPDATE = 0x40,
		PARTICLE_FLAG_HAS_SOUND = 0x80,
	};

	enum PARTICLE_MODULE_FLAG
	{
		PARTICLE_MODULE_FLAG_DISABLED = 0x1,
		PARTICLE_MODULE_FLAG_HAS_CURVES = 0x2,
		PARTICLE_MODULE_FLAG_USE_EMITTER_LIFE = 0x4,
		PARTICLE_MODULE_FLAG_HAS_ASSETS = 0x8,
		PARTICLE_MODULE_FLAG_RANDOMIZE_BETWEEN_CURVES = 0x10,
		PARTICLE_MODULE_FLAG_USE_NON_UNIFORM_INTERPOLATION = 0x20,
		PARTICLE_MODULE_FLAG_NO_LERP = 0x40,
		PARTICLE_MODULE_FLAG_USE_WORLD_SPACE = 0x80,
		PARTICLE_MODULE_FLAG_GRAPH_BY_LENGTH = 0x100,
		PARTICLE_MODULE_FLAG_UPDATE_EXTERNAL = 0x200,
		PARTICLE_MODULE_FLAG_GRAPH_ADDITIVE = 0x400,
		PARTICLE_MODULE_FLAG_HAS_LIGHT_DEFS = 0x800,
		PARTICLE_MODULE_FLAG_GRAPH_IS_LINEAR = 0x1000,
		PARTICLE_MODULE_FLAG_MODEL_IGNORE_EMITTER_ORIENTATION = 0x2000,
		PARTICLE_MODULE_FLAG_USE_OCCLUSION_QUERY_WORLD_SIZE = 0x4000,
		PARTICLE_MODULE_FLAG_EMISSION_CURVE_SCRUBBED_BY_GAME = 0x8000,
		PARTICLE_MODULE_FLAG_ON_IMPACT_BOLT_TO_ENTITY = 0x10000,
		PARTICLE_MODULE_FLAG_RAYCAST_COLLIDE_WITH_WZ_TRAIN = 0x20000,
		PARTICLE_MODULE_FLAGS_ALL = 0xFFFFFFFF,
	};

	enum PARTICLE_EMITTER_DEF_FLAG
	{
		PARTICLE_EMITTER_DEF_FLAG_DISABLED = 0x1,
		PARTICLE_EMITTER_DEF_FLAG_USE_BURST_MODE = 0x2,
		PARTICLE_EMITTER_DEF_FLAG_DRAW_PAST_FOG = 0x4,
		PARTICLE_EMITTER_DEF_FLAG_INFINITE_PARTICLE_LIFE = 0x8,
		PARTICLE_EMITTER_DEF_FLAG_LOOP_INFINITE_PARTICLES = 0x10,
		PARTICLE_EMITTER_DEF_FLAG_HAS_PHYSICS_HEAVY = 0x20,
		PARTICLE_EMITTER_DEF_FLAG_HAS_SCRIPTED_INPUTS = 0x40,
		PARTICLE_EMITTER_DEF_FLAG_HAS_LIGHTS = 0x80,
		PARTICLE_EMITTER_DEF_FLAG_USE_SCRIPTED_VELOCITY = 0x100,
		PARTICLE_EMITTER_DEF_FLAG_EMIT_BY_DISTANCE = 0x200,
		PARTICLE_EMITTER_DEF_FLAG_USE_OCCLUSION_QUERY = 0x400,
		PARTICLE_EMITTER_DEF_FLAG_HAS_TRANS_SHADOWS = 0x800,
		PARTICLE_EMITTER_DEF_FLAG_GROUP_ONLY_WHEN_NVG_ON = 0x1000,
		PARTICLE_EMITTER_DEF_FLAG_GROUP_ONLY_WHEN_NVG_OFF = 0x2000,
		PARTICLE_EMITTER_DEF_FLAG_GROUP_ONLY_WHEN_THERMAL_ON = 0x4000,
		PARTICLE_EMITTER_DEF_FLAG_GROUP_ONLY_WHEN_THERMAL_OFF = 0x8000,
		PARTICLE_EMITTER_DEF_FLAG_DISABLE_IN_SP = 0x10000,
		PARTICLE_EMITTER_DEF_FLAG_DISABLE_IN_MP_LPC = 0x20000,
		PARTICLE_EMITTER_DEF_FLAG_DISABLE_IN_MP_HPC = 0x40000,
		PARTICLE_EMITTER_DEF_FLAG_DISABLE_IN_CP = 0x80000,
		PARTICLE_EMITTER_DEF_FLAG_HAS_INSTANCE_POOL = 0x100000,
		PARTICLE_EMITTER_DEF_FLAG_FORCE_HALF_RES = 0x200000,
		PARTICLE_EMITTER_DEF_FLAG_FORCE_FULL_RES = 0x400000,
		PARTICLE_EMITTER_DEF_FLAG_IGNORE_MODIFIERS = 0x800000,
		PARTICLE_EMITTER_DEF_FLAG_HAS_BARREL_HEAT_SCALE = 0x1000000,
		PARTICLE_EMITTER_DEF_FLAG_IGNORE_FOV_SCALE = 0x2000000,
	};

	enum PARTICLE_ELEMENT_TYPE
	{
		PARTICLE_ELEMENT_TYPE_BILLBOARD_SPRITE = 0x0,
		PARTICLE_ELEMENT_TYPE_BEAM = 0x1,
		PARTICLE_ELEMENT_TYPE_DECAL = 0x2,
		PARTICLE_ELEMENT_TYPE_FLARE = 0x3,
		PARTICLE_ELEMENT_TYPE_GEO_TRAIL = 0x4,
		PARTICLE_ELEMENT_TYPE_LIGHT_OMNI = 0x5,
		PARTICLE_ELEMENT_TYPE_LIGHT_SPOT = 0x6,
		PARTICLE_ELEMENT_TYPE_MODEL = 0x7,
		PARTICLE_ELEMENT_TYPE_ORIENTED_SPRITE = 0x8,
		PARTICLE_ELEMENT_TYPE_RUNNER = 0x9,
		PARTICLE_ELEMENT_TYPE_TAIL = 0xA,
		PARTICLE_ELEMENT_TYPE_VECTOR_FIELD = 0xB,
		PARTICLE_ELEMENT_TYPE_VOLUMETRIC = 0xC,
		PARTICLE_ELEMENT_TYPE_DISMEMBER = 0xD,
	};

	enum PARTICLE_STATE_DEF_FLAG
	{
		PARTICLE_STATE_DEF_FLAG_DISABLED = 0x1,
		PARTICLE_STATE_DEF_FLAG_HAS_CAMERA_OFFSET = 0x2,
		PARTICLE_STATE_DEF_FLAG_HAS_SPAWN_SHAPE = 0x4,
		PARTICLE_STATE_DEF_FLAG_HAS_POSITION_CURVE = 0x8,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_1D_CURVE = 0x10,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_3D_CURVE = 0x20,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_1D_INIT = 0x40,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_3D_INIT = 0x80,
		PARTICLE_STATE_DEF_FLAG_HAS_VELOCITY_CURVE_LOCAL = 0x100,
		PARTICLE_STATE_DEF_FLAG_HAS_VELOCITY_CURVE_WORLD = 0x200,
		PARTICLE_STATE_DEF_FLAG_USE_PHYSICS = 0x400,
		PARTICLE_STATE_DEF_FLAG_MIRROR_TEXTURE_HORIZONTALLY = 0x800,
		PARTICLE_STATE_DEF_FLAG_MIRROR_TEXTURE_HORIZONTALLY_RANDOM = 0x1000,
		PARTICLE_STATE_DEF_FLAG_MIRROR_TEXTURE_VERTICALLY = 0x2000,
		PARTICLE_STATE_DEF_FLAG_MIRROR_TEXTURE_VERTICALLY_RANDOM = 0x4000,
		PARTICLE_STATE_DEF_FLAG_SORT_PARTICLES = 0x8000,
		PARTICLE_STATE_DEF_FLAG_HANDLE_ON_IMPACT = 0x10000,
		PARTICLE_STATE_DEF_FLAG_PLAYER_FACING = 0x20000,
		PARTICLE_STATE_DEF_FLAG_PLAYER_FACING_LOCK_UP_VECTOR = 0x40000,
		PARTICLE_STATE_DEF_FLAG_USE_OCCLUSION_QUERY = 0x80000,
		PARTICLE_STATE_DEF_FLAG_HAS_COLOR = 0x100000,
		PARTICLE_STATE_DEF_FLAG_HAS_RAY_CAST_PHYSICS = 0x200000,
		PARTICLE_STATE_DEF_FLAG_HAS_EMISSIVE_CURVE = 0x400000,
		PARTICLE_STATE_DEF_FLAG_HAS_INTENSITY_CURVE = 0x800000,
		PARTICLE_STATE_DEF_FLAG_USE_VECTOR_FIELDS = 0x1000000,
		PARTICLE_STATE_DEF_FLAG_INHERIT_PARENT_VELOCITY = 0x2000000,
		PARTICLE_STATE_DEF_FLAG_DRAW_WITH_VIEW_MODEL = 0x4000000,
		PARTICLE_STATE_DEF_FLAG_PLAY_SOUNDS = 0x8000000,
		PARTICLE_STATE_DEF_FLAG_HAS_CAMERA_OFFSET_POSITION_ONLY = 0x10000000,
		PARTICLE_STATE_DEF_FLAG_ON_IMPACT_USE_SURFACE_TYPE = 0x20000000,
		PARTICLE_STATE_DEF_FLAG_IS_SPRITE = 0x40000000,
		PARTICLE_STATE_DEF_FLAG_HAS_TRANS_SHADOWS = 0x80000000,
		PARTICLE_STATE_DEF_FLAG_HAS_CHILD_EFFECTS = 0x0,
		PARTICLE_STATE_DEF_FLAG_BLOCKS_SIGHT = 0x0,
		PARTICLE_STATE_DEF_FLAG_HANDLE_TIME_IN_STATE = 0x0,
		PARTICLE_STATE_DEF_FLAG_SCALE_BY_DISTANCE = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_VECTOR_FIELD_CURVE = 0x0,
		PARTICLE_STATE_DEF_FLAG_USE_LOCAL_VECTOR_FIELDS_ONLY = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_SHADER_CURVE = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_SIZE_CURVE = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_SIZE_LERP = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_TEMPERATURE_CURVE = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_LIGHTING_FRACTION_CURVE = 0x0,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_CURVE = 0x30,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_1D = 0x50,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION_3D = 0xA0,
		PARTICLE_STATE_DEF_FLAG_HAS_ROTATION = 0xF0,
		PARTICLE_STATE_DEF_FLAG_HAS_MIRROR_TEXTURE = 0x7800,
		PARTICLE_STATE_DEF_FLAG_HAS_VELOCITY_CURVE = 0x300,
		PARTICLE_STATE_DEF_FLAG_REQUIRES_WORLD_COLLISION = 0x200400,
	};

	enum PARTICLE_SYSTEM_DEF_FLAG
	{
		PARTICLE_SYSTEM_DEF_FLAG_HAS_SPRITES = 0x1,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_NON_SPRITES = 0x2,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_LIGHTS = 0x4,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_PHYSICS_HEAVY = 0x8,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_PHYSICS_LIGHT = 0x10,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_SCRIPTED_INPUTS = 0x20,
		PARTICLE_SYSTEM_DEF_FLAG_USE_OCCLUSION_QUERY = 0x40,
		PARTICLE_SYSTEM_DEF_FLAG_USE_OCCLUSION_QUERY_OVERRIDE_POS = 0x80,
		PARTICLE_SYSTEM_DEF_FLAG_KILL_ON_OWNER_ENTITY_DEATH = 0x100,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_TRANS_SHADOWS = 0x200,
		PARTICLE_SYSTEM_DEF_FLAG_ALIGN_TO_SUN = 0x400,
		PARTICLE_SYSTEM_DEF_FLAG_KILL_ON_KILLCAM_TRANSITION = 0x800,
		PARTICLE_SYSTEM_DEF_FLAG_CANNOT_PRE_ROLL = 0x1000,
		PARTICLE_SYSTEM_DEF_FLAG_ALWAYS_UPDATE_BONE_INDEX = 0x2000,
		PARTICLE_SYSTEM_DEF_FLAG_AFFECTS_GAMEPLAY = 0x4000,
		PARTICLE_SYSTEM_DEF_FLAG_UPDATE_CHILDREN_AFTER_BOLTING = 0x8000,
		PARTICLE_SYSTEM_DEF_FLAG_PRE_ROLL_CHILD_EFFECTS = 0x10000,
		PARTICLE_SYSTEM_DEF_FLAG_KILL_ON_KILLCAM_ENTITY_TRANSITION = 0x20000,
		PARTICLE_SYSTEM_DEF_FLAG_KILL_STOPPED_INFINITE_EFFECTS = 0x40000,
		PARTICLE_SYSTEM_DEF_FLAG_PARENT_UPDATES_CHILD = 0x80000,
		PARTICLE_SYSTEM_DEF_FLAG_STOP_ON_DYNAMIC_BOLT_DEATH = 0x100000,
		PARTICLE_SYSTEM_DEF_FLAG_DISABLE_IN_SPLIT_SCREEN = 0x200000,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_EMITTER_GROUP_IDS = 0x400000,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_EMITTER_NVG_OR_THERMAL = 0x800000,
		PARTICLE_SYSTEM_DEF_FLAG_HAS_INSTANCE_POOL = 0x1000000,
		PARTICLE_SYSTEM_DEF_FLAG_HIDE_IF_BONE_IS_HIDDEN = 0x2000000,
		PARTICLE_SYSTEM_DEF_FLAG_FOV_CULL = 0x4000000,
		PARTICLE_SYSTEM_DEF_FLAG_USE_OCCLUSION_QUERY_OVERRIDE_LOC = 0x8000000,
	};

	enum ParticleModuleType : std::uint16_t
	{
		PARTICLE_MODULE_INIT_ATLAS = 0x0,
		PARTICLE_MODULE_INIT_ATTRIBUTES = 0x1,
		PARTICLE_MODULE_INIT_BEAM = 0x2,
		PARTICLE_MODULE_INIT_CAMERA_OFFSET = 0x3,
		PARTICLE_MODULE_INIT_CLOUD = 0x4,
		PARTICLE_MODULE_INIT_DECAL = 0x5,
		PARTICLE_MODULE_INIT_FLARE = 0x6,
		PARTICLE_MODULE_INIT_GEO_TRAIL = 0x7,
		PARTICLE_MODULE_INIT_LIGHT_OMNI = 0x8,
		PARTICLE_MODULE_INIT_LIGHT_SPOT = 0x9,
		PARTICLE_MODULE_INIT_MATERIAL = 0xA,
		PARTICLE_MODULE_INIT_MIRROR_TEXTURE = 0xB,
		PARTICLE_MODULE_INIT_MODEL = 0xC,
		PARTICLE_MODULE_INIT_OCCLUSION_QUERY = 0xD,
		PARTICLE_MODULE_INIT_ORIENTED_SPRITE = 0xE,
		PARTICLE_MODULE_INIT_PARTICLE_SIM = 0xF,
		PARTICLE_MODULE_INIT_PLAYER_FACING = 0x10,
		PARTICLE_MODULE_INIT_RELATIVE_VELOCITY = 0x11,
		PARTICLE_MODULE_INIT_ROTATION = 0x12,
		PARTICLE_MODULE_INIT_ROTATION_3D = 0x13,
		PARTICLE_MODULE_INIT_RUNNER = 0x14,
		PARTICLE_MODULE_INIT_SOUND = 0x15,
		PARTICLE_MODULE_INIT_SPAWN = 0x16,
		PARTICLE_MODULE_INIT_SPAWN_SHAPE_BOX = 0x17,
		PARTICLE_MODULE_INIT_SPAWN_SHAPE_CYLINDER = 0x18,
		PARTICLE_MODULE_INIT_SPAWN_SHAPE_ELLIPSOID = 0x19,
		PARTICLE_MODULE_INIT_SPAWN_SHAPE_MESH = 0x1A,
		PARTICLE_MODULE_INIT_SPAWN_SHAPE_SPHERE = 0x1B,
		PARTICLE_MODULE_INIT_TAIL = 0x1C,
		PARTICLE_MODULE_INIT_VECTOR_FIELD = 0x1D,
		PARTICLE_MODULE_INIT_VOLUMETRIC = 0x1E,
		PARTICLE_MODULE_ATTRACTOR = 0x1F,
		PARTICLE_MODULE_COLOR_GRAPH = 0x20,
		PARTICLE_MODULE_COLOR_LERP = 0x21,
		PARTICLE_MODULE_EMISSION_GRAPH = 0x22,
		PARTICLE_MODULE_EMISSIVE_GRAPH = 0x23,
		PARTICLE_MODULE_FORCE = 0x24,
		PARTICLE_MODULE_GRAVITY = 0x25,
		PARTICLE_MODULE_INTENSITY_GRAPH = 0x26,
		PARTICLE_MODULE_TEMPERATURE_GRAPH = 0x27,
		PARTICLE_MODULE_PHYSICS_LIGHT = 0x28,
		PARTICLE_MODULE_PHYSICS_RAY_CAST = 0x29,
		PARTICLE_MODULE_POSITION_GRAPH = 0x2A,
		PARTICLE_MODULE_ROTATION_GRAPH = 0x2B,
		PARTICLE_MODULE_ROTATION_GRAPH_3D = 0x2C,
		PARTICLE_MODULE_SIZE_GRAPH = 0x2D,
		PARTICLE_MODULE_SIZE_LERP = 0x2E,
		PARTICLE_MODULE_VELOCITY_GRAPH = 0x2F,
		PARTICLE_MODULE_TEST_BIRTH = 0x30,
		PARTICLE_MODULE_TEST_DEATH = 0x31,
		PARTICLE_MODULE_TEST_GRAVITY = 0x32,
		PARTICLE_MODULE_TEST_IMPACT = 0x33,
		PARTICLE_MODULE_TEST_POS = 0x34,
		PARTICLE_MODULE_TEST_TIME_IN_STATE = 0x35,
		PARTICLE_MODULE_COUNT = 0x36,
		PARTICLE_MODULE_INVALID = 0xFF,
	};

	struct float4
	{
		float v[4];
	};

	struct ParticleFloatRange
	{
		float min;
		float max;
	};

	struct ParticleIntRange
	{
		int min;
		int max;
	};

	struct ParticlePhysicsFXData
	{
		PhysicsFXPipeline PTR64 physicsFXPipeline;
		PhysicsFXShape PTR64 physicsFXShape;
	};

	struct ParticleMarkVisuals
	{
		Material PTR64 materials[3];
	};

	union ParticleLinkedAssetDef
	{
		Material PTR64 material;
		XModel PTR64 model;
		ParticleSystemDef PTR64 particleSystem;
		ParticlePhysicsFXData physicsFXData;
		FxParticleSimAnimation PTR64 particleSim;
		ParticleMarkVisuals decal;
		const char PTR64 sound;
		VectorField PTR64 vectorField;
		GfxLightDef PTR64 lightDef;
		char pad[32];
	}; assert_sizeof(ParticleLinkedAssetDef, 32);

	struct ParticleModule
	{
		ParticleModuleType type;
		unsigned int m_flags;
	};

	struct ParticleCurveControlPointDef
	{
		float time;
		float value;
		float invTimeDelta;
		unsigned int pad[1];
	};

	struct ParticleCurveDef
	{
		ParticleCurveControlPointDef PTR64 controlPoints;
		int numControlPoints;
		float scale;
	};

	struct ParticleModuleInitAtlas : ParticleModule
	{
		int m_startFrame;
		int m_loopCount;
		bool m_randomIndex;
		bool m_playOverLife;
	}; assert_sizeof(ParticleModuleInitAtlas, 20);

	struct ParticleModuleInitAttributes : ParticleModule
	{
		bool m_useNonUniformInterpolationForColor;
		bool m_useNonUniformInterpolationForSize;
		char m_pad[6];
		float4 m_sizeMin;
		float4 m_sizeMax;
		float4 m_colorMin;
		float4 m_colorMax;
		float4 m_velocityMin;
		float4 m_velocityMax;
	}; assert_sizeof(ParticleModuleInitAttributes, 112);

	enum ParticleModuleInitBeamFlags
	{
		PARTICLE_MODULE_INIT_BEAM_FLAG_TILE = 0x1,
		PARTICLE_MODULE_INIT_BEAM_FLAG_USE_CURVE_POINTS = 0x2,
		PARTICLE_MODULE_INIT_BEAM_FLAG_CAMERA_FACING = 0x4,
	};

	struct ParticleLinkedAssetListDef
	{
		ParticleLinkedAssetDef PTR64 assetList;
		int numAssets;
	};

	struct ParticleModuleInitBeam : ParticleModule
	{
		ParticleModuleInitBeamFlags m_beamFlags;
		float m_splitDistance;
		float4 m_startPos;
		float4 m_endPos;
		float4 m_offset;
		float4 m_curvePoint1;
		float4 m_curvePoint2;
		ParticleLinkedAssetListDef m_linkedAssetList;
		float m_scrollRateUV;
		float m_scrollRateSpiralGraph;
		float m_spiralRepeatDistance;
	}; assert_sizeof(ParticleModuleInitBeam, 128);

	struct ParticleModuleInitCameraOffset : ParticleModule
	{
		unsigned int m_pad[2];
	}; assert_sizeof(ParticleModuleInitCameraOffset, 16);

	struct ParticleModuleInitCloud : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleCurveDef curves[2];
	}; assert_sizeof(ParticleModuleInitCloud, 48);

	struct ParticleModuleInitDecal : ParticleModule
	{
		unsigned __int16 m_fadeInTime;
		unsigned __int16 m_fadeOutTime;
		unsigned __int16 m_stoppableFadeOutTime;
		unsigned __int16 m_lerpWaitTime;
		float4 m_lerpColor;
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitDecal, 48);
	assert_offsetof(ParticleModuleInitDecal, m_linkedAssetList, 32);

	struct ParticleModuleInitFlare : ParticleModule
	{
		unsigned int m_pad[1];
		float m_position;
		float4 m_direction;
		int m_angularRotCount;
		unsigned int m_flareFlags;
		ParticleFloatRange m_depthScaleRange;
		ParticleFloatRange m_depthScaleValue;
		ParticleFloatRange m_radialRot;
		ParticleFloatRange m_radialScaleX;
		ParticleFloatRange m_radialScaleY;
		ParticleCurveDef m_curves[4];
	}; assert_sizeof(ParticleModuleInitFlare, 144);
	assert_offsetof(ParticleModuleInitFlare, m_curves, 80);

	struct ParticleModuleInitGeoTrail : ParticleModule
	{
		unsigned int m_numPointsMax;
		float m_splitDistance;
		float m_splitAngle;
		float m_centerOffset;
		unsigned int m_numSheets;
		float m_fadeInDistance;
		float m_fadeOutDistance;
		float m_tileDistance;
		ParticleFloatRange m_tileOffset;
		float m_scrollTime;
		bool m_useLocalVelocity;
		bool m_useVerticalTexture;
		bool m_cameraFacing;
		bool m_fixLeadingEdge;
		bool m_clampUVs;
		char m_pad[3];
		unsigned int m_pad2[1];
	}; assert_sizeof(ParticleModuleInitGeoTrail, 64);

	struct ParticleModuleInitLightOmni : ParticleModule
	{
		ParticleLinkedAssetListDef m_linkedAssetList;
		float m_fovOuter;
		float m_fovInner;
		float m_bulbRadius;
		float m_bulbLength;
		bool m_disableVolumetric;
		bool m_disableShadowMap;
		bool m_disableDynamicShadows;
		bool m_scriptScale;
	}; assert_sizeof(ParticleModuleInitLightOmni, 48);

	struct ParticleModuleInitLightSpot : ParticleModule
	{
		float m_fovOuter;
		float m_fovInner;
		float m_bulbRadius;
		float m_bulbLength;
		float m_distanceFalloff;
		//float m_fovCollimation;
		float m_brightness;
		float m_intensityUV;
		float m_intensityIR;
		//float m_intensityHeat;
		float m_shadowSoftness;
		float m_shadowBias;
		float m_shadowArea;
		float m_shadowNearPlane;
		float m_toneMappingScaleFactor;
		bool m_disableVolumetric;
		bool m_disableShadowMap;
		bool m_disableDynamicShadows;
		bool m_scriptScale;
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitLightSpot, 80);
	assert_offsetof(ParticleModuleInitLightSpot, m_linkedAssetList, 64);

	struct ParticleModuleInitMaterial : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitMaterial, 32);

	enum ParticleMirrorTextureType
	{
		PARTICLE_MIRROR_TEXTURE_TYPE_NONE = 0x0,
		PARTICLE_MIRROR_TEXTURE_TYPE_STANDARD = 0x1,
		PARTICLE_MIRROR_TEXTURE_TYPE_RANDOM = 0x2,
		PARTICLE_MIRROR_TEXTURE_TYPE_COUNT = 0x3,
	};

	struct ParticleModuleInitMirrorTexture : ParticleModule
	{
		ParticleMirrorTextureType m_mirrorHorizontal;
		ParticleMirrorTextureType m_mirrorVertical;
	}; assert_sizeof(ParticleModuleInitMirrorTexture, 16);

	struct ParticleModuleInitModel : ParticleModule
	{
		bool m_usePhysics;
		bool m_motionBlurHQ;
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitModel, 32);
	assert_offsetof(ParticleModuleInitModel, m_linkedAssetList, 16);

	struct ParticleModuleInitOcclusionQuery : ParticleModule
	{
		float m_fadeInTime;
		float m_fadeOutTime;
		ParticleFloatRange m_scale;
		vec2_t m_worldSize;
	}; assert_sizeof(ParticleModuleInitOcclusionQuery, 32);

	struct ParticleModuleInitOrientedSprite : ParticleModule
	{
		unsigned int m_pad[2];
		float4 m_orientationQuat;
	}; assert_sizeof(ParticleModuleInitOrientedSprite, 32);

	struct ParticleModuleInitParticleSim : ParticleModule
	{
		ParticleLinkedAssetListDef m_linkedAssetList;
		ParticleFloatRange m_scaleFactor;
		bool m_holdLastFrame;
		unsigned int m_pad[3];
	}; assert_sizeof(ParticleModuleInitParticleSim, 48);

	struct ParticleModuleInitPlayerFacing : ParticleModule
	{
		unsigned int m_pad[2];
	}; assert_sizeof(ParticleModuleInitPlayerFacing, 16);

	enum ParticleRelativeVelocityType
	{
		PARTICLE_RELATIVE_VELOCITY_TYPE_LOCAL = 0x0,
		PARTICLE_RELATIVE_VELOCITY_TYPE_WORLD = 0x1,
		PARTICLE_RELATIVE_VELOCITY_TYPE_RELATIVE_TO_EFFECT_ORIGIN = 0x2,
		PARTICLE_RELATIVE_VELOCITY_TYPE_COUNT = 0x3,
		PARTICLE_RELATIVE_VELOCITY_TYPE_LOCAL_WITH_BOLT_INFO = 0x3,
		PARTICLE_RELATIVE_VELOCITY_TYPE_WORLD_WITH_BOLT_INFO = 0x4,
		PARTICLE_RELATIVE_VELOCITY_TYPE_RELATIVE_TO_EFFECT_ORIGIN_WITH_BOLT_INFO = 0x5,
	};

	struct ParticleModuleInitRelativeVelocity : ParticleModule
	{
		ParticleRelativeVelocityType m_velocityType;
		bool m_useBoltInfo;
	}; assert_sizeof(ParticleModuleInitRelativeVelocity, 16);

	struct ParticleModuleInitRotation : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleFloatRange m_rotationAngle;
		ParticleFloatRange m_rotationRate;
	}; assert_sizeof(ParticleModuleInitRotation, 32);

	struct ParticleModuleInitRotation3D : ParticleModule
	{
		unsigned int m_pad[2];
		float4 m_rotationAngleMin;
		float4 m_rotationAngleMax;
		float4 m_rotationRateMin;
		float4 m_rotationRateMax;
	}; assert_sizeof(ParticleModuleInitRotation3D, 80);

	struct ParticleModuleInitRunner : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitRunner, 32);

	struct ParticleModuleInitSound : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitSound, 32);

	struct ParticleModuleInitSpawn : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleCurveDef m_curves[1];
	}; assert_sizeof(ParticleModuleInitSpawn, 32);

	struct ParticleModuleInitSpawnShape : ParticleModule
	{
		char m_axisFlags[1];
		char m_spawnFlags[1];
		char m_normalAxis[1];
		char m_spawnType[1];
		float m_volumeCubeRoot;
		//float4 m_calculationOffset;
		float4 m_offset;
	};

	struct ParticleModuleInitSpawnShapeBox : ParticleModuleInitSpawnShape
	{
		bool m_useBeamInfo;
		char m_pad[15];
		float4 m_dimensionsMin;
		float4 m_dimensionsMax;
	}; assert_sizeof(ParticleModuleInitSpawnShapeBox, 80);

	struct ParticleModuleInitSpawnShapeCylinder : ParticleModuleInitSpawnShape
	{
		bool m_hasRotation;
		bool m_rotateCalculatedOffset;
		float m_halfHeight;
		ParticleFloatRange m_radius;
		float4 m_directionQuat;
		unsigned int m_pad[4];
	}; assert_sizeof(ParticleModuleInitSpawnShapeCylinder, 80);

	struct ParticleModuleInitSpawnShapeEllipsoid : ParticleModuleInitSpawnShape
	{
		float4 m_radiusMin;
		float4 m_radiusMax;
		unsigned int m_pad[4];
	}; assert_sizeof(ParticleModuleInitSpawnShapeEllipsoid, 80);

	struct ParticleSpawnMeshAssetDef
	{
		unsigned int m_numVertsTotal;
		unsigned int m_numTrisTotal;
		unsigned int m_pad[2];
	};

	struct ParticleModuleInitSpawnShapeMesh : ParticleModuleInitSpawnShape
	{
		unsigned int m_numMeshAssets;
		ParticleLinkedAssetListDef m_linkedAssetList;
		ParticleSpawnMeshAssetDef PTR64 m_meshAssetData;
		unsigned int m_pad[3];
	}; assert_sizeof(ParticleModuleInitSpawnShapeMesh, 80);
	assert_offsetof(ParticleModuleInitSpawnShapeMesh, m_numMeshAssets, 32);

	struct ParticleModuleInitSpawnShapeSphere : ParticleModuleInitSpawnShape
	{
		unsigned int m_pad[2];
		ParticleFloatRange m_radius;
		unsigned int m_pad2[4];
	}; assert_sizeof(ParticleModuleInitSpawnShapeSphere, 64);

	struct ParticleModuleInitTail : ParticleModule
	{
		unsigned __int16 m_averagePastVelocities;
		unsigned __int16 m_maxParentSpeed;
		bool m_tailLeading;
		bool m_scaleWithVelocity;
		bool m_rotateAroundPivot;
	}; assert_sizeof(ParticleModuleInitTail, 16);

	struct ParticleModuleInitVectorField : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModuleInitVectorField, 32);

	struct ParticleModuleInitVolumetric : ParticleModule
	{
		float m_density;
		float m_falloff;
		float m_noiseAmplitude;
		unsigned int m_noiseMode;
		unsigned int m_pad[2];
	}; assert_sizeof(ParticleModuleInitVolumetric, 32);

	struct ParticleModuleAttractor : ParticleModule
	{
		unsigned int m_pad[3];
		bool m_killWhenNear;
		float m_forceMag;
		float m_nearDistanceSq;
		float4 m_attractPoint;
	}; assert_sizeof(ParticleModuleAttractor, 48);

	struct ParticleModuleColorGraph : ParticleModule
	{
		bool firstCurve;
		char m_pad[3];
		bool m_modulateColorByAlpha;
		ParticleCurveDef m_curves[8];
	}; assert_sizeof(ParticleModuleColorGraph, 144);

	struct ParticleModuleColorLerp : ParticleModule
	{
		unsigned int m_pad[2];
		float4 m_colorBegin;
		float4 m_colorEnd;
	}; assert_sizeof(ParticleModuleColorLerp, 48);

	struct ParticleModuleEmissionGraph : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleCurveDef m_curves[2];
	}; assert_sizeof(ParticleModuleEmissionGraph, 48);

	struct ParticleModuleEmissiveGraph : ParticleModule
	{
		bool firstCurve;
		char m_pad[7];
		ParticleCurveDef m_curves[2];
	}; assert_sizeof(ParticleModuleEmissiveGraph, 48);
	assert_offsetof(ParticleModuleEmissiveGraph, m_curves, 16);

	struct ParticleModuleForce : ParticleModule
	{
		unsigned int m_pad[2];
		float4 m_forceMin;
		float4 m_forceMax;
	}; assert_sizeof(ParticleModuleForce, 48);

	struct ParticleModuleGravity : ParticleModule
	{
		ParticleFloatRange m_gravityPercentage;
	}; assert_sizeof(ParticleModuleGravity, 16);

	struct ParticleModuleIntensityGraph : ParticleModule
	{
		bool firstCurve;
		char m_pad[7];
		ParticleCurveDef m_curves[2];
	}; assert_sizeof(ParticleModuleIntensityGraph, 48);

	struct ParticleModuleTemperatureGraph : ParticleModule
	{
		bool firstCurve;
		char m_pad[7];
		ParticleCurveDef m_curves[2];
	}; assert_sizeof(ParticleModuleTemperatureGraph, 48);

	struct ParticleModulePhysicsLight : ParticleModule
	{
		bool m_ignoreEmitterOrientation;
		bool m_useSurfaceType;
		char m_pad[6];
		ParticleLinkedAssetListDef m_linkedAssetList;
	}; assert_sizeof(ParticleModulePhysicsLight, 32);

	struct ParticleModulePhysicsRayCast : ParticleModule
	{
		ParticleFloatRange m_bounce;
		Bounds m_bounds;
		bool m_useItemClip;
		bool m_useSurfaceType;
		bool m_collideWithWater;
		bool m_ignoreContentItem;
		char m_pad[3];
	}; assert_sizeof(ParticleModulePhysicsRayCast, 48);

	struct ParticleModulePositionGraph : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleCurveDef m_curves[6];
	}; assert_sizeof(ParticleModulePositionGraph, 112);

	struct ParticleModuleRotationGraph : ParticleModule
	{
		bool m_useRotationRate;
		unsigned int m_pad[1];
		ParticleCurveDef m_curves[2];
	}; assert_sizeof(ParticleModuleRotationGraph, 48);

	struct ParticleModuleRotationGraph3D : ParticleModule
	{
		bool m_useRotationRate;
		unsigned int m_pad[1];
		ParticleCurveDef m_curves[6];
	}; assert_sizeof(ParticleModuleRotationGraph3D, 112);

	struct ParticleModuleSizeGraph : ParticleModule
	{
		bool firstCurve;
		char m_pad[7];
		ParticleCurveDef m_curves[6];
		float4 m_sizeBegin;
		float4 m_sizeEnd;
	}; assert_sizeof(ParticleModuleSizeGraph, 144);

	struct ParticleModuleSizeLerp : ParticleModule
	{
		unsigned int m_pad[2];
		float4 m_sizeBegin;
		float4 m_sizeEnd;
	}; assert_sizeof(ParticleModuleSizeLerp, 48);

	struct ParticleModuleVelocityGraph : ParticleModule
	{
		unsigned int m_pad[2];
		ParticleCurveDef m_curves[6];
		float4 m_velocityBegin;
		float4 m_velocityEnd;
	}; assert_sizeof(ParticleModuleVelocityGraph, 144);

	struct ParticleModuleTestEventHandlerData
	{
		unsigned int m_nextState;
		ParticleLinkedAssetListDef m_linkedAssetList;
		bool m_kill;
		unsigned int m_pad[1];
	};

	struct ParticleModuleTest : ParticleModule
	{
		unsigned __int16 m_moduleIndex;
		char m_useOrientationOptions[1];
		char m_useScaleOptions[1];
		char m_useVelocityOptions[1];
		ParticleModuleTestEventHandlerData m_eventHandlerData;
	}; assert_sizeof(ParticleModuleTest, 48);
	assert_offsetof(ParticleModuleTest, m_eventHandlerData, 16);

	struct ParticleModuleTestBirth : ParticleModuleTest
	{
	};

	struct ParticleModuleTestDeath : ParticleModuleTest
	{
	};

	struct ParticleModuleTestGravity : ParticleModuleTest
	{
	};

	struct ParticleModuleTestImpact : ParticleModuleTest
	{
	};

	struct ParticleModuleTestPos : ParticleModuleTest
	{
	};

	struct ParticleModuleTestTimeInState : ParticleModuleTest
	{
	};

	union ParticleModuleTypeDef
	{
		ParticleModule moduleBase;
		ParticleModuleInitAtlas initAtlas;
		ParticleModuleInitAttributes initAttributes;
		ParticleModuleInitBeam initBeam;
		ParticleModuleInitCameraOffset initCameraOffset;
		ParticleModuleInitCloud initCloud; // maybe different
		ParticleModuleInitDecal initDecal; // maybe wrong fields
		ParticleModuleInitFlare initFlare;
		ParticleModuleInitGeoTrail initGeoTrail;
		ParticleModuleInitLightOmni initLightOmni; // maybe wrong fields
		ParticleModuleInitLightSpot initLightSpot; // maybe wrong fields
		ParticleModuleInitMaterial initMaterial;
		ParticleModuleInitMirrorTexture initMirrorTexture;
		ParticleModuleInitModel initModel;
		ParticleModuleInitOcclusionQuery initOcclusionQuery; // maybe wrong fields
		ParticleModuleInitOrientedSprite initOrientedSprite;
		ParticleModuleInitParticleSim initParticleSim;
		ParticleModuleInitPlayerFacing initPlayerFacing;
		ParticleModuleInitRelativeVelocity initRelativeVelocity;
		ParticleModuleInitRotation initRotation;
		ParticleModuleInitRotation3D initRotation3D;
		ParticleModuleInitRunner initRunner; // maybe wrong
		ParticleModuleInitSound initSound;
		ParticleModuleInitSpawn initSpawn;
		ParticleModuleInitSpawnShapeBox initSpawnShapeBox; // maybe wrong fields
		ParticleModuleInitSpawnShapeCylinder initSpawnShapeCylinder; // maybe wrong fields
		ParticleModuleInitSpawnShapeEllipsoid initSpawnShapeEllipsoid; // maybe wrong
		ParticleModuleInitSpawnShapeMesh initSpawnShapeMesh;  // maybe wrong
		ParticleModuleInitSpawnShapeSphere initSpawnShapeSphere;  // maybe wrong
		ParticleModuleInitTail initTail;
		ParticleModuleInitVectorField initVectorField; // maybe wrong
		ParticleModuleInitVolumetric initVolumetric;
		ParticleModuleAttractor attractor;
		ParticleModuleColorGraph colorGraph;
		ParticleModuleColorLerp colorLerp;
		ParticleModuleEmissionGraph emissionGraph;
		ParticleModuleEmissiveGraph emissiveGraph;
		ParticleModuleForce force;
		ParticleModuleGravity gravity;
		ParticleModuleIntensityGraph intensityGraph;
		ParticleModuleTemperatureGraph temperatureGraph;
		ParticleModulePhysicsLight physicsLight;
		ParticleModulePhysicsRayCast physicsRayCast;
		ParticleModulePositionGraph positionGraph;
		ParticleModuleRotationGraph rotationGraph;
		ParticleModuleRotationGraph3D rotationGraph3D;
		ParticleModuleSizeGraph sizeGraph;
		ParticleModuleSizeLerp sizeLerp;
		ParticleModuleVelocityGraph velocityGraph;
		ParticleModuleTestBirth testBirth;
		ParticleModuleTestDeath testDeath;
		ParticleModuleTestGravity testGravity;
		ParticleModuleTestImpact testImpact;
		ParticleModuleTestPos testPos;
		ParticleModuleTestTimeInState testTimeInState;
	};

	struct ParticleModuleDef
	{
		ParticleModuleType type;
		unsigned int m_pad[3];
		ParticleModuleTypeDef moduleData;
	}; assert_sizeof(ParticleModuleDef, 160);

	enum ParticleGravityOptions
	{
		PARTICLE_GRAVITY_OPTION_NONE = 0x0,
		PARTICLE_GRAVITY_OPTION_GRAVITY_ONLY = 0x1,
		PARTICLE_GRAVITY_OPTION_GRAVITY_NEVER = 0x2,
		PARTICLE_GRAVITY_OPTION_COUNT = 0x3,
	};

	enum ParticleInstancePoolAction
	{
		PARTICLE_INSTANCE_POOL_ACTION_NO_SPAWN = 0x0,
		PARTICLE_INSTANCE_POOL_ACTION_KILL_OLDEST_AND_SPAWN = 0x1,
		PARTICLE_INSTANCE_POOL_ACTION_COUNT = 0x2,
	};

	enum ParticleDataFlags
	{
		USE_NONE = 0x0,
		USE_POSITION = 0x1,
		USE_VELOCITY = 0x2,
		USE_COLOR = 0x4,
		USE_ROTATION_ANGLE = 0x8,
		USE_ROTATION_RATE = 0x10,
		USE_SPAWN_POS = 0x20,
		USE_SPAWN_QUAT = 0x40,
		USE_SIZE = 0x80,
		USE_EMISSIVE = 0x100,
		USE_PARENT_VELOCITY = 0x200,
		USE_CHILD_SYSTEM = 0x400,
		USE_SPAWN_TIME = 0x800,
		USE_LIFE = 0x1000,
		USE_STATE = 0x2000,
		USE_RANDOM_SEED = 0x4000,
		USE_FLAGS = 0x8000,
		USE_MODULE_TESTS = 0x10000,
		USE_HANDLE = 0x20000,
		USE_INTENSITY = 0x40000,
		USE_TEMPERATURE = 0x80000,
		USE_CAMERA_DISTANCE = 0x100000,
		USE_INHERIT_PERCENTAGE = 0x200000,
		USE_RAY_CAST_HANDLE = 0x400000,
		USE_ATLAS_INDEX = 0x800000,
		USE_VECTOR_FIELD_SCALE = 0x1000000,
		USE_LIGHTING_FRAC = 0x2000000,
		USE_PREV_PLACEMENT = 0x4000000,
		USE_SHADER_PARAMS = 0x8000000,
		CHECK_FIELD_COUNT = 0x8000001,
		USE_ALL = 0xFFFFFFF,
		USE_BASE = 0x192F8FF,
		USE_EMISSIVE_CURVES = 0x2040100,
	};

	struct ParticleModuleGroupDef
	{
		ParticleModuleDef PTR64 moduleDefs;
		int numModules;
		bool disabled;
	};

	struct ParticleStateDef
	{
		ParticleModuleGroupDef PTR64 moduleGroupDefs; // size: 3
		unsigned int elementType;
		unsigned __int64 flags;
		unsigned int pad[2];
	};

	struct ParticleEmitterDef
	{
		ParticleStateDef PTR64 stateDefs;
		int numStates;
		ParticleFloatRange particleSpawnRate;
		ParticleFloatRange particleLife;
		ParticleFloatRange particleDelay;
		unsigned int particleCountMax;
		ParticleIntRange particleBurstCount;
		ParticleFloatRange emitterLife;
		ParticleFloatRange emitterDelay;
		int randomSeed;
		ParticleFloatRange spawnRangeSq;
		float fadeOutMaxDistance;
		ParticleCurveDef fadeCurveDef;
		float spawnFrustumCullRadius;
		unsigned int flags;
		ParticleGravityOptions gravityOptions;
		//int groupIDs[4];
		ParticleFloatRange emitByDistanceDensity;
		unsigned int instancePool;
		unsigned int soloInstanceMax;
		ParticleInstancePoolAction instanceAction;
		ParticleDataFlags m_dataFlags;
		ParticleFloatRange particleSpawnShapeRange;
		unsigned int pad[1];
	}; assert_sizeof(ParticleEmitterDef, 144);

	enum ParticleScriptedInputNodeType
	{
		PARTICLE_SCRIPTED_INPUT_NODE_INVALID = 0xFFFFFFFF,
		PARTICLE_SCRIPTED_INPUT_NODE_KVP = 0x0,
		PARTICLE_SCRIPTED_INPUT_NODE_EMITTER_DISABLE = 0x1,
		PARTICLE_SCRIPTED_INPUT_NODE_COUNT = 0x2,
	};

	struct ParticleScriptedInputNode
	{
		ParticleScriptedInputNodeType m_type;
		unsigned int m_flags;
		unsigned int m_emitterIndex;
		unsigned int m_pad[5];
	};

	enum ParticleScriptedInputKey
	{
	};

	struct ParticleScriptedInputRecord
	{
		ParticleScriptedInputKey key;
		bool dirty;
		bool value;
		unsigned int pad[2];
	};

	struct ParticleScriptedInputNodeKVP : ParticleScriptedInputNode
	{
		ParticleScriptedInputRecord m_inputRecord;
	};

	struct ParticleScriptedInputNodeEmitterDisable : ParticleScriptedInputNode
	{
	};

	union ParticleScriptedInputNodeDef // maybe wrong
	{
		ParticleScriptedInputNode nodeBase;
		ParticleScriptedInputNodeKVP KVP;
		ParticleScriptedInputNodeEmitterDisable emitterDisable;
	}; assert_sizeof(ParticleScriptedInputNodeDef, 48);

	enum ParticlePhaseOptions
	{
		PARTICLE_PHASE_OPTION_PHASE_NEVER = 0x0,
		PARTICLE_PHASE_OPTION_PHASE_ONLY = 0x1,
		PARTICLE_PHASE_OPTION_ALWAYS = 0x2,
		PARTICLE_PHASE_OPTION_COUNT = 0x3,
	};

	struct ParticleSystemDef
	{
		const char PTR64 name;
		ParticleEmitterDef PTR64 emitterDefs;
		ParticleScriptedInputNodeDef PTR64 scriptedInputNodeDefs;
		int version;
		int numEmitters;
		int numScriptedInputNodes;
		unsigned int flags;
		int occlusionOverrideEmitterIndex;
		ParticlePhaseOptions phaseOptions;
		float drawFrustumCullRadius;
		float updateFrustumCullRadius;
		float sunDistance;
		int preRollMSec;
		float4 editorPosition;
		float4 editorRotation;
		float4 gameTweakPosition;
		float4 gameTweakRotation;
	}; assert_sizeof(ParticleSystemDef, 0x80);

	struct FxFloatRange
	{
		float base;
		float amplitude;
	};

	struct FxIntRange
	{
		int base;
		int amplitude;
	};

	struct FxElemVec3Range
	{
		float base[3];
		float amplitude[3];
	};

	struct FxSpawnDefLooping
	{
		int intervalMsec;
		int count;
	};

	struct FxSpawnDefOneShot
	{
		FxIntRange count;
	};

	union FxSpawnDef
	{
		FxSpawnDefLooping looping;
		FxSpawnDefOneShot oneShot;
	};

	struct FxElemAtlas
	{
		unsigned char behavior;
		unsigned char index;
		unsigned char fps;
		unsigned char loopCount;
		unsigned char colIndexBits;
		unsigned char rowIndexBits;
		short entryCount;
	};

	struct FxElemVelStateInFrame
	{
		FxElemVec3Range velocity;
		FxElemVec3Range totalDelta;
	};

	struct FxElemVelStateSample
	{
		FxElemVelStateInFrame local;
		FxElemVelStateInFrame world;
	};

	struct FxElemVisualState
	{
		float color[4];
		float rotationDelta;
		float rotationTotal;
		float size[2];
		float scale;
	};

	struct FxElemVisStateSample
	{
		FxElemVisualState base;
		FxElemVisualState amplitude;
	};

	struct FxElemMarkVisuals
	{
		Material PTR64 materials[3];
	};

	union FxEffectDefRef
	{
		FxEffectDef PTR64 handle;
		const char PTR64 name;
	};

	union FxElemVisuals
	{
		const void PTR64 anonymous;
		Material PTR64 material;
		XModel PTR64 model;
		FxEffectDefRef effectDef;
		const char PTR64 soundName;
		const char PTR64 vectorFieldName;
		GfxLightDef PTR64 lightDef;
		FxParticleSimAnimation PTR64 particleSimAnimation;
	};

	union FxElemDefVisuals
	{
		FxElemMarkVisuals PTR64 markArray;
		FxElemVisuals PTR64 array;
		FxElemVisuals instance;
	};

	struct FxTrailVertex
	{
		vec2_t pos;
		vec2_t normal;
		vec2_t texCoord;
	};

	struct FxTrailDef
	{
		int scrollTimeMsec;
		int repeatDist;
		float invSplitDist;
		float invSplitArcDist;
		float invSplitTime;
		int vertCount;
		FxTrailVertex PTR64 verts;
		int indCount;
		unsigned short PTR64 inds;
	};

	struct FxSparkFountainDef
	{
		float gravity;
		float bounceFrac;
		float bounceRand;
		float sparkSpacing;
		float sparkLength;
		int sparkCount;
		float loopTime;
		float velMin;
		float velMax;
		float velConeFrac;
		float restSpeed;
		float boostTime;
		float boostFactor;
	};

	struct FxSpotLightDef
	{
		float fovInnerFraction;
		float startRadius;
		float endRadius;
		float brightness;
		float maxLength;
		int exponent;
	};

	struct FxFlareDef
	{
		float position;
		int angularRotCount;
		int flags;
		FxFloatRange depthScaleRange;
		FxFloatRange depthScaleValue;
		FxFloatRange radialRot;
		FxFloatRange radialScaleX;
		FxFloatRange radialScaleY;
		vec3_t dir;
		int intensityXIntervalCount;
		int intensityYIntervalCount;
		int srcCosIntensityIntervalCount;
		int srcCosScaleIntervalCount;
		float PTR64 intensityX;
		float PTR64 intensityY;
		float PTR64 srcCosIntensity;
		float PTR64 srcCosScale;
	};

	union FxElemExtendedDefPtr
	{
		FxTrailDef PTR64 trailDef;
		FxSparkFountainDef PTR64 sparkFountainDef;
		FxSpotLightDef PTR64 spotLightDef;
		FxFlareDef PTR64 flareDef;
		void PTR64 unknownDef;
	};

	enum FxElemType : std::uint8_t
	{
		FX_ELEM_TYPE_SPRITE_BILLBOARD = 0,
		FX_ELEM_TYPE_SPRITE_ORIENTED = 1,
		FX_ELEM_TYPE_SPRITE_ROTATED = 2,
		FX_ELEM_TYPE_TAIL = 3,
		FX_ELEM_TYPE_LINE = 4,
		FX_ELEM_TYPE_TRAIL = 5,
		FX_ELEM_TYPE_FLARE = 6,
		FX_ELEM_TYPE_PARTICLE_SIM_ANIMATION = 7,
		FX_ELEM_TYPE_CLOUD = 8,
		FX_ELEM_TYPE_SPARK_CLOUD = 9,
		FX_ELEM_TYPE_SPARK_FOUNTAIN = 10,
		FX_ELEM_TYPE_MODEL = 11,
		FX_ELEM_TYPE_OMNI_LIGHT = 12,
		FX_ELEM_TYPE_SPOT_LIGHT = 13,
		FX_ELEM_TYPE_SOUND = 14,
		FX_ELEM_TYPE_DECAL = 15,
		FX_ELEM_TYPE_RUNNER = 16,
		FX_ELEM_TYPE_VECTORFIELD = 17,
	};

	enum FxElemDefFlags : std::uint32_t
	{
		FX_ELEM_SPAWN_RELATIVE_TO_EFFECT = 0x2,
		FX_ELEM_SPAWN_FRUSTUM_CULL = 0x4,
		FX_ELEM_RUNNER_USES_RAND_ROT = 0x8,
		FX_ELEM_SPAWN_OFFSET_NONE = 0x0,
		FX_ELEM_SPAWN_OFFSET_SPHERE = 0x10,
		FX_ELEM_SPAWN_OFFSET_CYLINDER = 0x20,
		FX_ELEM_SPAWN_OFFSET_MASK = 0x30,
		FX_ELEM_RUN_RELATIVE_TO_WORLD = 0x0,
		FX_ELEM_RUN_RELATIVE_TO_SPAWN = 0x40,
		FX_ELEM_RUN_RELATIVE_TO_EFFECT = 0x80,
		FX_ELEM_RUN_RELATIVE_TO_OFFSET = 0xC0,
		FX_ELEM_RUN_RELATIVE_TO_CAMERA = 0x100,
		FX_ELEM_RUN_MASK = 0x1C0,
		FX_ELEM_DIE_ON_TOUCH = 0x200,
		FX_ELEM_DRAW_PAST_FOG = 0x400,
		FX_ELEM_DRAW_WITH_VIEWMODEL = 0x800,
		FX_ELEM_BLOCK_SIGHT = 0x1000,
		FX_ELEM_DRAW_IN_THERMAL_VIEW_ONLY = 0x2000,
		FX_ELEM_TRAIL_ORIENT_BY_VELOCITY = 0x4000,
		FX_ELEM_EMIT_BOLT = 0x80000000,
		FX_ELEM_EMIT_ORIENT_BY_ELEM = 0x8000,
		FX_ELEM_USE_OCCLUSION_QUERY = 0x10000,
		FX_ELEM_NODRAW_IN_THERMAL_VIEW = 0x20000,
		FX_ELEM_THERMAL_MASK = 0x22000,
		FX_ELEM_SPAWN_IMPACT_FX_WITH_SURFACE_NAME = 0x40000,
		FX_ELEM_RECEIVE_DYNAMIC_LIGHT = 0x80000,
		FX_ELEM_VOLUMETRIC_TRAIL = 0x100000,
		FX_ELEM_USE_COLLISION = 0x200000,
		FX_ELEM_USE_VECTORFIELDS = 0x400000,
		FX_ELEM_NO_SURFACE_HDR_SCALAR = 0x800000,
		FX_ELEM_HAS_VELOCITY_GRAPH_LOCAL = 0x1000000,
		FX_ELEM_HAS_VELOCITY_GRAPH_WORLD = 0x2000000,
		FX_ELEM_HAS_GRAVITY = 0x4000000,
		FX_ELEM_USE_MODEL_PHYSICS = 0x8000000,
		FX_ELEM_NONUNIFORM_SCALE = 0x10000000,
		FX_ELEM_CLOUD_SHAPE_CUBE = 0x0,
		FX_ELEM_CLOUD_SHAPE_SPHERE_LARGE = 0x20000000,
		FX_ELEM_CLOUD_SHAPE_SPHERE_MEDIUM = 0x40000000,
		FX_ELEM_CLOUD_SHAPE_SPHERE_SMALL = 0x60000000,
		FX_ELEM_CLOUD_SHAPE_MASK = 0x60000000,
		FX_ELEM_FOUNTAIN_DISABLE_COLLISION = 0x80000000,
	};

	enum FxElemDefExtraFlags : std::uint32_t
	{

	};

	struct FxElemDef
	{
		int flags;
		int flags2;
		FxSpawnDef spawn;
		FxFloatRange spawnRange;
		FxFloatRange fadeInRange;
		FxFloatRange fadeOutRange;
		float spawnFrustumCullRadius;
		FxIntRange spawnDelayMsec;
		FxIntRange lifeSpanMsec;
		FxFloatRange spawnOrigin[3];
		FxFloatRange spawnOffsetRadius;
		FxFloatRange spawnOffsetHeight;
		FxFloatRange spawnAngles[3];
		FxFloatRange angularVelocity[3];
		FxFloatRange initialRotation;
		FxFloatRange gravity;
		FxFloatRange reflectionFactor;
		FxElemAtlas atlas;
		char unk[2];
		unsigned char elemType;
		unsigned char visualCount;
		unsigned char velIntervalCount;
		unsigned char visStateIntervalCount;
		FxElemVelStateSample PTR64 velSamples;
		FxElemVisStateSample PTR64 visSamples;
		FxElemDefVisuals visuals;
		Bounds collBounds;
		FxEffectDefRef effectOnImpact;
		FxEffectDefRef effectOnDeath;
		FxEffectDefRef effectEmitted;
		FxFloatRange emitDist;
		FxFloatRange emitDistVariance;
		FxElemExtendedDefPtr extended;
		unsigned char sortOrder;
		unsigned char lightingFrac;
		unsigned char useItemClip;
		unsigned char fadeInfo;
		int randomSeed;
		float litMaxColorChangePerSec;
		float litUnlitBlendFactor;
	}; assert_sizeof(FxElemDef, 304);
	assert_offsetof(FxElemDef, elemType, 182);
	assert_offsetof(FxElemDef, visualCount, 183);
	assert_offsetof(FxElemDef, visuals, 208);
	assert_offsetof(FxElemDef, extended, 280);

	struct FxEffectDef
	{
		const char PTR64 name;
		int flags;
		int totalSize;
		int msecLoopingLife;
		int elemDefCountLooping;
		int elemDefCountOneShot;
		int elemDefCountEmission;
		float elemMaxRadius;
		float occlusionQueryDepthBias;
		int occlusionQueryFadeIn;
		int occlusionQueryFadeOut;
		FxFloatRange occlusionQueryScaleRange;
		FxElemDef PTR64 elemDefs;
	}; assert_sizeof(FxEffectDef, 0x40);

	struct FxImpactEntry
	{
		FxCombinedDef nonflesh[64];
		FxCombinedDef flesh[23];
	};

	struct FxImpactTable
	{
		const char PTR64 name;
		FxImpactEntry PTR64 table; // size: 49
	};

	struct SurfaceFxEntry
	{
		FxCombinedDef surfaceEffect[64];
	};

	struct SurfaceFxTable
	{
		const char PTR64 name;
		SurfaceFxEntry PTR64 table; // size: 6
	};

	struct RawFile
	{
		const char PTR64 name;
		int compressedLen;
		int len;
		const char PTR64 buffer;
	};

	struct ScriptFile
	{
		const char PTR64 name;
		int compressedLen;
		int len;
		int bytecodeLen;
		const char PTR64 buffer;
		char PTR64 bytecode;
	};

	struct StringTableCell
	{
		const char PTR64 string;
		int hash;
	};

	struct StringTable
	{
		const char PTR64 name;
		int columnCount;
		int rowCount;
		StringTableCell PTR64 values;
	};

	enum LbColType
	{
		LBCOL_TYPE_NUMBER = 0x0,
		LBCOL_TYPE_TIME = 0x1,
		LBCOL_TYPE_LEVELXP = 0x2,
		LBCOL_TYPE_PRESTIGE = 0x3,
		LBCOL_TYPE_BIGNUMBER = 0x4,
		LBCOL_TYPE_PERCENT = 0x5,
		LBCOL_TYPE_TIME_FULL = 0x6,
		LBCOL_TYPE_COUNT = 0x7,
	};

	enum LbAggType
	{
		LBAGG_TYPE_MIN = 0x0,
		LBAGG_TYPE_MAX = 0x1,
		LBAGG_TYPE_SUM = 0x2,
		LBAGG_TYPE_LAST = 0x3,
		LBAGG_TYPE_COUNT = 0x4,
	};

	struct LbColumnDef
	{
		const char PTR64 name;
		int id;
		int propertyId;
		bool hidden;
		int statsGroup;
		const char PTR64 statName;
		LbColType type;
		int precision;
		LbAggType agg;
		int uiCalColX;
		int uiCalColY;
	};

	enum LbUpdateType
	{
		LBUPDATE_TYPE_NORMAL = 0x0,
		LBUPDATE_TYPE_RANK = 0x1,
		LBUPDATE_TYPE_COMBINE = 0x2,
		LBUPDATE_TYPE_VIRTUAL = 0x3,
		LBUPDATE_TYPE_COUNT = 0x4,
	};

	struct LeaderboardDef
	{
		const char PTR64 name;
		int id;
		int sourceLbId;
		int sourceLbWidth;
		int columnCount;
		int xpColId;
		int prestigeColId;
		LbColumnDef PTR64 columns;
		LbUpdateType updateType;
		int trackTypes;
		int rankColIdX;
		int rankColIdY;
	};

	struct LbVrColumnDef
	{
		const char PTR64 name;
		int id;
		int uiCalColX;
		int uiCalColY;
	};

	struct VirtualLeaderboardDef
	{
		const char PTR64 name;
		const char PTR64 sourceName;
		int id;
		int sourceId;
		LbVrColumnDef PTR64 columns;
		int columnCount;
		int rankColIdX;
		int rankColIdY;
	};

	struct StructuredDataEnumEntry
	{
		scr_string_t string;
		unsigned short index;
	};

	struct StructuredDataEnum
	{
		int entryCount;
		int reservedEntryCount;
		StructuredDataEnumEntry PTR64 entries;
	};

	enum StructuredDataTypeCategory
	{
		DATA_INT = 0x0,
		DATA_BYTE = 0x1,
		DATA_BOOL = 0x2,
		DATA_STRING = 0x3,
		DATA_ENUM = 0x4,
		DATA_STRUCT = 0x5,
		DATA_INDEXED_ARRAY = 0x6,
		DATA_ENUM_ARRAY = 0x7,
		DATA_FLOAT = 0x8,
		DATA_SHORT = 0x9,
		DATA_COUNT = 0xA,
	};

	union StructuredDataTypeUnion
	{
		unsigned int stringDataLength;
		int enumIndex;
		int structIndex;
		int indexedArrayIndex;
		int enumedArrayIndex;
		int index;
	};

	struct StructuredDataType
	{
		StructuredDataTypeCategory type;
		StructuredDataTypeUnion u;
	};

	enum StructuredDataValidationType
	{
		VALIDATION_NONE = 0x0,
	};

	struct StructuredDataStructProperty
	{
		scr_string_t name;
		StructuredDataType type;
		unsigned int offset;
		StructuredDataValidationType validation;
	};

	struct StructuredDataStruct
	{
		int propertyCount;
		StructuredDataStructProperty PTR64 properties;
		int size;
		unsigned int bitOffset;
	};

	struct StructuredDataIndexedArray
	{
		int arraySize;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataEnumedArray
	{
		int enumIndex;
		StructuredDataType elementType;
		unsigned int elementSize;
	};

	struct StructuredDataDef
	{
		int version;
		unsigned int formatChecksum;
		int enumCount;
		StructuredDataEnum PTR64 enums;
		int structCount;
		StructuredDataStruct PTR64 structs;
		int indexedArrayCount;
		StructuredDataIndexedArray PTR64 indexedArrays;
		int enumedArrayCount;
		StructuredDataEnumedArray PTR64 enumedArrays;
		StructuredDataType rootType;
		unsigned int size;
	};

	struct StructuredDataDefSet
	{
		const char PTR64 name;
		unsigned int defCount;
		StructuredDataDef PTR64 defs;
	};

	struct DDLMember
	{
		const char PTR64 name;
		int index;
		void PTR64 parent;
		int bitSize;
		int limitSize;
		int offset;
		int type;
		int externalIndex;
		unsigned int rangeLimit;
		unsigned int serverDelta;
		unsigned int clientDelta;
		int arraySize;
		int enumIndex;
		int permission;
	};

	struct DDLHash
	{
		unsigned int hash;
		int index;
	};

	struct DDLHashTable
	{
		DDLHash PTR64 list;
		int count;
		int max;
	};

	struct DDLStruct
	{
		const char PTR64 name;
		int bitSize;
		int memberCount;
		DDLMember PTR64 members;
		DDLHashTable hashTableUpper;
		DDLHashTable hashTableLower;
	};

	struct DDLEnum
	{
		const char PTR64 name;
		int memberCount;
		const char PTR64  PTR64 members;
		DDLHashTable hashTable;
	};

	struct DDLDef
	{
		char PTR64 name;
		unsigned short version;
		unsigned int checksum;
		unsigned char flags;
		int bitSize;
		int byteSize;
		DDLStruct PTR64 structList;
		int structCount;
		DDLEnum PTR64 enumList;
		int enumCount;
		DDLDef PTR64 next;
		int headerBitSize;
		int headerByteSize;
		int reserveSize;
		int userFlagsSize;
		bool paddingUsed;
	};

	struct DDLFile
	{
		char PTR64 name;
		DDLDef PTR64 ddlDef;
	};

	struct TracerDef
	{
		const char PTR64 name;
		Material PTR64 material;
		unsigned int drawInterval;
		int unk1;
		float unk2;
		float speed;
		float beamLength;
		float beamWidth;
		float screwRadius;
		float screwDist;
		vec4_t colors[5];
	}; assert_sizeof(TracerDef, 0x80);

	struct SpaceshipAnimParts
	{
		XAnimParts PTR64 anim[2];
	};

	enum VehCamZOffsetMode
	{
		VEHCAM_ZMODE_WORLD = 0x0,
		VEHCAM_ZMODE_VEHICLE = 0x1,
		VEHCAM_ZMODE_VIEW = 0x2,
		VEHCAM_ZMODE_COUNT = 0x3,
	};

	enum VehicleTurretFireType
	{
		VEH_TURRET_SINGLE_FIRE = 0x0,
		VEH_TURRET_DUAL_FIRE = 0x1,
		VEH_TURRET_ALT_FIRE = 0x2,
		VEH_TURRET_FIRE_TYPE_COUNT = 0x3,
	};

	struct VehiclePhysicsDef
	{
		int physicsEnabled;
		float unk_1;
		float unk_2;
		int unk_3;
		int unk_4;
		int unk_5;
		float unk_6;
		float unk_7;
		float unk_8;
		float unk_9;
		float unk_10;
		float unk_11;
		float unk_12;
		float unk_13;
		float unk_14;
		float unk_15;
		float unk_16;
		float unk_17;
		float unk_18;
		float unk_19;
		float unk_20;
		float unk_21;
		float unk_22;
		float unk_23;
		float unk_24;
		float unk_25;
		float unk_26;
		float unk_27;
		float unk_28;
		float unk_29;
		float unk_30;
		float unk_31;
		float unk_32;
		float unk_33;
		float unk_34;
		float unk_35;
		float unk_36;
		float unk_37;
		float unk_38;
		float unk_39;
		float unk_40;
		float unk_41;
		float unk_42;
		float unk_43;
		float unk_44;
		float unk_45;
		float unk_46;
		float unk_47;
		float unk_48;
		float unk_49;
		int unk_50;
		float unk_51;
		float unk_52;
		float unk_53;
		float unk_54;
		float unk_55;
		float unk_56;
		float unk_57;
		float unk_58;
		float unk_59;
		float unk_60;
		float unk_61;
		float unk_62;
		float unk_63;
		float unk_64;
		float unk_65;
		float unk_66;
		float unk_67;
		float unk_68;
		float unk_69;
		float unk_70;
		float unk_71;
		float unk_72;
		float unk_73;
		float unk_74;
		float unk_75;
		float unk_76;
		float unk_77;
		float unk_78;
		float unk_79;
		float unk_80;
		float unk_81;
		float unk_82;
		float unk_83;
		float unk_84;
		float unk_85;
		float unk_86;
		float unk_87;
		float unk_88;
		float unk_89;
		float unk_90;
		float unk_91;
		float unk_92;
		float unk_93;
		float unk_94;
		float unk_95;
		float unk_96;
		float unk_97;
		float unk_98;
		float unk_99;
		float unk_100;
		float unk_101;
		float unk_102;
		float unk_103;
		float unk_104;
		float unk_105;
		float unk_106;
		float unk_107;
		float unk_108;
		float unk_109;
		float unk_110;
		float unk_111;
	}; assert_sizeof(VehiclePhysicsDef, 448);

	struct VehicleDef
	{
		const char PTR64 name;
		char type;
		const char PTR64 useHintString;
		int health;
		int hitClientScriptables;
		float texScrollScale;
		float topSpeed;
		float accel;
		float rotRate;
		float rotAccel;
		float maxBodyPitch;
		float maxBodyRoll;
		float fakeBodyAccelPitch;
		float fakeBodyAccelRoll;
		float fakeBodyVelPitch;
		float fakeBodyVelRoll;
		float fakeBodySideVelPitch;
		float fakeBodyPitchStrength;
		float fakeBodyRollStrength;
		float fakeBodyPitchDampening;
		float fakeBodyRollDampening;
		float fakeBodyBoatRockingAmplitude;
		float fakeBodyBoatRockingPeriod;
		float fakeBodyBoatRockingRotationPeriod;
		float fakeBodyBoatRockingFadeoutSpeed;
		float boatBouncingMinForce;
		float boatBouncingMaxForce;
		float boatBouncingRate;
		float boatBouncingFadeinSpeed;
		float boatBouncingFadeoutSteeringAngle;
		float collisionDamage;
		float collisionSpeed;
		vec3_t killcamOffset;
		int playerProtected;
		int bulletDamage;
		int armorPiercingDamage;
		int grenadeDamage;
		int projectileDamage;
		int projectileSplashDamage;
		int heavyExplosiveDamage;
		VehiclePhysicsDef vehPhysDef;
		int vehHelicopterLockAltitude;
		int vehHelicopterOffsetFromMesh;
		float vehHelicopterAltitudeOffset;
		float vehHelicopterPitchOffset;
		float vehHelicopterBoundsRadius;
		float vehHelicopterMaxSpeed;
		float vehHelicopterMaxSpeedVertical;
		float vehHelicopterMaxAccel;
		float vehHelicopterMaxAccelVertical;
		float vehHelicopterDecelerationFwd;
		float vehHelicopterDecelerationSide;
		float vehHelicopterDecelerationUp;
		float vehHelicopterMaxYawRate;
		float vehHelicopterMaxYawAccel;
		float vehHelicopterTiltFromVelocity;
		float vehHelicopterTiltFromControllerAxes;
		float vehHelicopterTiltFromAcceleration;
		float vehHelicopterTiltFromDeceleration;
		float vehHelicopterTiltFromFwdAndYaw_VelAtMaxTilt;
		float vehHelicopterTiltFromFwdAndYaw;
		float vehHelicopterTiltMomentum;
		float vehHelicopterTiltSpeed;
		float vehHelicopterMaxPitch;
		float vehHelicopterMaxRoll;
		float vehHelicopterHoverSpeedThreshold;
		float vehHelicopterJitterJerkyness;
		float vehHelicopterLookaheadTime;
		int vehHelicopterSoftCollisions;
		int vehHelicopterUseGroundFX;
		FxCombinedDef vehHelicopterGroundFx;
		FxCombinedDef vehHelicopterGroundWaterFx;
		float vehHelicopterGroundFxDefaultRepeatRate;
		float vehHelicopterGroundFxSlowestRepeatRate;
		float vehHelicopterGroundFxFastestRepeatRate;
		float vehHelicopterGroundFxMinGroundDist;
		float vehHelicopterGroundFxMaxGroundDist;
		float ssWeaponSwitchDelaySeconds;
		float ssWeaponRaiseDelaySeconds;
		vec3_t ssFlyMaxSpeedMph;
		vec3_t ssFlyMaxAccelerationMphps;
		vec3_t ssFlyMaxCounterAccelerationMphps;
		vec3_t ssFlyFrictionMphps;
		vec3_t ssFlyJukeSpeedMph;
		vec3_t ssHoverMaxSpeedMph;
		vec3_t ssHoverMaxAccelerationMphps;
		vec3_t ssHoverMaxCounterAccelerationMphps;
		vec3_t ssHoverFrictionMphps;
		vec3_t ssHoverJukeSpeedMph;
		float ssFlyJukeRampTime;
		float ssHoverJukeRampTime;
		float ssBrakingFrictionMphps;
		float ssFlyRedirectVelocityScale;
		float ssFlySlowRedirectVelocityScale;
		float ssHoverRedirectVelocityScale;
		float ssFlyMinSpeedRatio;
		bool ssProjectVelocityDesiresToXY;
		bool ssEnforceMinGroundClearance;
		float ssMinGroundClearanceHeight;
		float ssMinGroundClearanceLiftForce;
		bool ssTerrainModeMovement;
		float ssTerrainModeGravity;
		float ssTerrainModeFlyTime;
		vec2_t ssAimOffsetClampDeg;
		vec2_t ssPitchUpSoftLimitDeg;
		vec2_t ssPitchDownSoftLimitDeg;
		float ssClutchPitchSpeedScale;
		vec2_t ssFlyAimSpeedDps;
		vec2_t ssFlySlowAimSpeedDps;
		vec2_t ssHoverAimSpeedDps;
		vec2_t ssFlyAimDriftScale;
		vec2_t ssFlySlowAimDriftScale;
		vec2_t ssHoverAimDriftScale;
		float ssMinSpringOscillation;
		float ssMaxSpringOscillation;
		float ssMinSpringStrength;
		float ssMaxSpringStrength;
		float ssMinSpringAngSpeed;
		float ssMaxSpringAngSpeed;
		float ssSpringControllerContribution;
		float ssTiltSpringOscillation;
		float ssTiltSpringStrength;
		float ssTiltSpringAngleContribution;
		int ssADSToLockOn;
		float ssLockOnMinAngle;
		float ssLockOnMaxAngle;
		float ssPilotAssistNoLockAimScale;
		float ssPilotAssistNoLockMinAngle;
		float ssPilotAssistNoLockMaxAngle;
		float ssPilotAssistAimScale;
		float ssPilotAssistMinAngle;
		float ssPilotAssistMaxAngle;
		vec2_t ssAutoLevelStrengthHover;
		vec2_t ssAutoLevelStrengthFly;
		bool ssIsRollRightStick;
		float ssRollMaxSpeedDps;
		float ssBoostSpeedScale;
		float ssBoostThrustScale;
		bool ssEnableBoostToFly;
		float ssBoostTime;
		float ssBoostRegenTime;
		float ssBoostRegenStallTime;
		float ssBoostMinThresholdRatio;
		float ssCollisionRadiusI;
		float ssCylinderHeightI;
		bool ssUseCylinder;
		bool ssUsePlayerClip;
		float ssCollisionOffsetI;
		float ssCollisionHardThresholdMph;
		float ssFOVFlyOffsetDeg;
		float ssFOVFlyBoostOffsetDeg;
		float ssFOVHoverOffsetDeg;
		float ssZoomBlendSpeedDps;
		float ssZoomMaxAngle;
		float ssZoomMinDistI;
		float ssZoomIdealDistI;
		float ssZoomMaxDistI;
		bool ssShowPilotViewmodel;
		float ssCameraAnimScale;
		vec2_t ssFlyTiltShipAngles;
		float ssFlyTiltCameraScale;
		vec2_t ssHoverTiltShipAngles;
		float ssHoverTiltCameraScale;
		float ssMotionIdleRateMinSpeed;
		float ssMotionIdleRateMaxSpeed;
		float ssMotionIdleMinRate;
		float ssMotionIdleMaxRate;
		scr_string_t ssAnimTree;
		SpaceshipAnimParts ssAnimParts[33];
		FxCombinedDef ssThrustFxLoop;
		FxCombinedDef ssJukeFx;
		RumbleInfo PTR64 ssIdleRumble;
		RumbleInfo PTR64 ssSmallRumble;
		RumbleInfo PTR64 ssMedRumble;
		RumbleInfo PTR64 ssLargeRumble;
		const char PTR64 rattleLoop;
		float rattleLoopMinVolume;
		float rattleLoopMaxVolume;
		const char PTR64 airLoop;
		float airLoopMinVolume;
		float airLoopMaxVolume;
		const char PTR64 engineLoop;
		float engineLoopMinVolume;
		float engineLoopMaxVolume;
		float engineLoopMinPitch;
		float engineLoopMaxPitch;
		const char PTR64 hoverLoop;
		float hoverLoopMinVolume;
		float hoverLoopMaxVolume;
		float hoverLoopMinPitch;
		float hoverLoopMaxPitch;
		const char PTR64 boostLoop;
		float boostLoopMaxVolume;
		float boostLoopMaxPitch;
		const char PTR64 ssThrustLoop;
		float ssThrustLoopMaxVolume;
		float ssThrustLoopMaxPitch;
		const char PTR64 boostStart;
		const char PTR64 boostStop;
		const char PTR64 boostDepleted;
		const char PTR64 boostUnavailable;
		const char PTR64 jukeLeft;
		const char PTR64 jukeRight;
		const char PTR64 jukeUpDown;
		const char PTR64 jukeBack;
		const char PTR64 jukeFront;
		const char PTR64 flightOn;
		const char PTR64 flightOff;
		float flightOnTimer;
		float flightOffTimer;
		const char PTR64 hardCollision;
		const char PTR64 softCollision;
		int camLookEnabled;
		int camRelativeControl;
		int camRemoteDrive;
		float camLerp;
		float camHeight;
		float camRadius;
		float camPitchInfluence;
		float camYawInfluence;
		float camRollInfluence;
		float camFovIncrease;
		float camFovOffset;
		float camFovSpeed;
		float camReturnSpeed;
		float camReturnLerp;
		float camVehicleAnglePitchRate;
		float camVehicleAngleYawRate;
		float camVehicleAngleRollRate;
		int vehCam_UseGDT;
		float vehCam_anglesPitch;
		float vehCam_anglesYaw;
		float vehCam_anglesRoll;
		float vehCam_offsetX;
		float vehCam_offsetY;
		float vehCam_offsetZ;
		float vehCam_radius;
		float vehCam_speedInfluence;
		float vehCam_pitchTurnRate;
		float vehCam_pitchClamp;
		float vehCam_yawTurnRate;
		float vehCam_yawClamp;
		VehCamZOffsetMode vehCam_zOffsetMode;
		float vehCam_anglesPitch3P;
		float vehCam_anglesYaw3P;
		float vehCam_anglesRoll3P;
		float vehCam_offsetX3P;
		float vehCam_offsetY3P;
		float vehCam_offsetZ3P;
		float vehCam_radius3P;
		float vehCam_speedInfluence3P;
		float vehCam_pitchTurnRate3P;
		float vehCam_pitchClamp3P;
		float vehCam_yawTurnRate3P;
		float vehCam_yawClamp3P;
		VehCamZOffsetMode vehCam_zOffsetMode3P;
		const char PTR64 turretWeaponName;
		WeaponCompleteDef PTR64 turretWeapon;
		float turretHorizSpanLeft;
		float turretHorizSpanRight;
		float turretVertSpanUp;
		float turretVertSpanDown;
		float turretHorizResistLeft;
		float turretHorizResistRight;
		float turretVertResistUp;
		float turretVertResistDown;
		float turretRotRate;
		VehicleTurretFireType turretFireType;
		const char PTR64 turretSpinSnd;
		const char PTR64 turretStopSnd;
		int trophyEnabled;
		float trophyRadius;
		float trophyInactiveRadius;
		int trophyAmmoCount;
		float trophyReloadTime;
		scr_string_t trophyTags[4];
		FxCombinedDef trophyExplodeFx;
		FxCombinedDef trophyFlashFx;
		Material PTR64 compassFriendlyIcon;
		Material PTR64 compassEnemyIcon;
		Material PTR64 compassFriendlyAltIcon;
		Material PTR64 compassEnemyAltIcon;
		int compassIconWidth;
		int compassIconHeight;
		const char PTR64 idleLowSnd;
		const char PTR64 idleHighSnd;
		const char PTR64 engineLowSnd;
		const char PTR64 engineHighSnd;
		float engineSndSpeed;
		scr_string_t audioOriginTag;
		const char PTR64 engineStartUpSnd;
		int engineStartUpLength;
		const char PTR64 engineShutdownSnd;
		const char PTR64 engineIdleSnd;
		const char PTR64 engineSustainSnd;
		const char PTR64 engineRampUpSnd;
		int engineRampUpLength;
		const char PTR64 engineRampDownSnd;
		int engineRampDownLength;
		const char PTR64 suspensionSoftSnd;
		float suspensionSoftCompression;
		const char PTR64 suspensionHardSnd;
		float suspensionHardCompression;
		const char PTR64 collisionSnd;
		float collisionBlendSpeed;
		const char PTR64 speedSnd;
		float speedSndBlendSpeed;
		const char PTR64 surfaceSndName;
		float surfaceSndBlendSpeed;
		float slideVolume;
		float slideBlendSpeed;
		float inAirPitch;
		const char PTR64 soundTriggerOverrideZone;
		bool soundTriggerOverrideReverb;
		bool soundTriggerOverrideMix;
		bool soundTriggerOverrideFilter;
		bool soundTriggerOverrideOcclusion;
		bool soundTriggerOverrideAmbient;
		bool soundTriggerOverrideAmbientEvents;
		bool soundTriggerOverrideADSR;
		int visionBlendTime;
		const char PTR64 globalVisionSettings;
		const char PTR64 mapVisionSettings;
	}; assert_sizeof(VehicleDef, 0xA90);

	struct AddonMapEnts
	{
		const char PTR64 name;
		char PTR64 entityString;
		int numEntityChars;
		MapTriggers trigger;
		ClipInfo PTR64 info;
		unsigned int numSubModels;
		cmodel_t PTR64 cmodels;
		void PTR64 models; //GfxBrushModel PTR64 models;
	}; assert_sizeof(AddonMapEnts, 0x88);

	enum NetConstStringType
	{
		NETCONSTSTRINGTYPE_XMODEL = 0, // mdl
		NETCONSTSTRINGTYPE_MATERIAL = 1, // mat
		NETCONSTSTRINGTYPE_RUMBLE = 2, // rmb
		NETCONSTSTRINGTYPE_RUMBLE_GRAPH = 3, // rmg
		NETCONSTSTRINGTYPE_VEHICLES = 4, // veh
		NETCONSTSTRINGTYPE_FX = 5, // efx
		NETCONSTSTRINGTYPE_VFX = 6, // vfx
		NETCONSTSTRINGTYPE_LOCSTRING = 7, //loc
		NETCONSTSTRINGTYPE_SHOCK = 8, // shk
		NETCONSTSTRINGTYPE_CLIENT_TAGS = 9, // tag
		NETCONSTSTRINGTYPE_HEADICON = 10, // hic
		NETCONSTSTRINGTYPE_STATUSICON = 11, // sic
		NETCONSTSTRINGTYPE_NAMEPLATE = 12, // nps
		NETCONSTSTRINGTYPE_MINIMAPICON = 13, // mic
		NETCONSTSTRINGTYPE_WEAPON = 14, // wep
		NETCONSTSTRINGTYPE_HINTSTRING = 15, // hnt
		NETCONSTSTRINGTYPE_ANIM = 16, // anm
		NETCONSTSTRINGTYPE_ANIMCLASS = 17, // acl
		NETCONSTSTRINGTYPE_LUI = 18, // lui
		NETCONSTSTRINGTYPE_SUIT = 19, // sut
		NETCONSTSTRINGTYPE_GESTURE = 20, // ges
		NETCONSTSTRINGTYPE_TGT = 21, // tgt
		NETCONSTSTRINGTYPE_VISION = 22, // vsn
		NETCONSTSTRINGTYPE_COUNT = 25,
		NETCONSTSTRINGTYPE_NONE = 25,
	};

	enum NetConstStringSource
	{
		NETCONSTSTRINGSOURCE_MAP = 0x0,
		NETCONSTSTRINGSOURCE_PRE_MAP = 0x1,
		NETCONSTSTRINGSOURCE_COMMON = 0x2,
		NETCONSTSTRINGSOURCE_COUNT = 0x3,
		NETCONSTSTRINGSOURCE_NONE = 0x3,
	};

	struct NetConstStrings
	{
		const char PTR64 name;
		NetConstStringType stringType;
		NetConstStringSource sourceType;
		unsigned int flags;
		unsigned int entryCount;
		const char PTR64  PTR64 stringList;
	}; assert_sizeof(NetConstStrings, 0x20);

	struct LuaFile
	{
		const char PTR64 name;
		int len;
		char strippingType;
		const char PTR64 buffer;
	};

	struct ScriptableEventDef;
	struct ScriptablePartDef;

	struct ScriptableEventBaseDef
	{
		const char PTR64 name;
		int flags;
	}; assert_sizeof(ScriptableEventBaseDef, 16);

	enum Scriptable_EventType
	{
		Scriptable_EventType_StateChange = 0x0,
		Scriptable_EventType_Wait = 0x1,
		Scriptable_EventType_Random = 0x2,
		Scriptable_EventType_Script = 0x3,
		Scriptable_EventType_Model = 0x4,
		Scriptable_EventType_Collision = 0x5,
		Scriptable_EventType_Animation = 0x6,
		Scriptable_EventType_HideShowBone = 0x7,
		Scriptable_EventType_NoteTrack = 0x8,
		Scriptable_EventType_ChunkDynent = 0x9,
		Scriptable_EventType_SpawnDynent = 0xA,
		Scriptable_EventType_PFX = 0xB,
		Scriptable_EventType_Sound = 0xC,
		Scriptable_EventType_Explosion = 0xD,
		Scriptable_EventType_Light = 0xE,
		Scriptable_EventType_Sun = 0xF,
		Scriptable_EventType_Rumble = 0x10,
		Scriptable_EventType_Screenshake = 0x11,
		Scriptable_EventType_PartDamage = 0x12,
		Scriptable_EventType_SetMayhem = 0x13,
		Scriptable_EventType_PlayMayhem = 0x14,
		Scriptable_EventType_ViewmodelShaderParam = 0x15,
		Scriptable_EventType_ViewmodelChangeImage = 0x16,
		Scriptable_EventType_ClientViewSelector = 0x17,
		Scriptable_EventType_TeamSelector = 0x18,
		Scriptable_EventType_AddModel = 0x19,
		Scriptable_EventType_ApplyForce = 0x1A,
		Scriptable_EventType_CompassIcon = 0x1B,
		Scriptable_EventType_MaterialOverride = 0x1C,
		Scriptable_EventType_Count = 0x1D,
	};

	struct ScriptableEventAnonymousDef
	{
		ScriptableEventBaseDef PTR64 base;
		char buffer[144];
	};

	struct unk_1453E1B90
	{
		const char PTR64 name;
		char __pad0[8];
	}; assert_sizeof(unk_1453E1B90, 0x10);

	struct unk_1453E1BC0
	{
		const char PTR64 name;
	};

	struct unk_1453E1C00
	{
		const char PTR64 name;
	};

	struct unk_1453E1C20
	{
		const char PTR64 name;
		char __pad0[8];
	};

	struct unk_1453E1C70
	{
		const char PTR64 name;
		unsigned int count;
		unsigned int PTR64 val;
	};

	union unk_1453E1C80
	{
		unk_1453E1BC0 __1;
		unk_1453E1C00 __2;
		unk_1453E1C20 __3;
		unk_1453E1C70 __4;
	};

	enum ScriptablePartReferenceType
	{
		type_1453E1BC0,
		type_1453E1C00,
		type_1453E1C20,
		type_1453E1C70,
		unk_1453E1CC8_type_count,
	};

	struct ScriptablePartReference
	{
		unk_1453E1B90 unk01;
		int type;
		unk_1453E1C80 u;
	}; assert_sizeof(ScriptablePartReference, 0x30);

	struct ScriptableEventStateChangeDef
	{
		ScriptableEventBaseDef PTR64 base;
		ScriptablePartReference partReference;
		ScriptablePartDef PTR64 part;
	}; assert_sizeof(ScriptableEventStateChangeDef, 64);

	struct ScriptableEventWaitDef
	{
		ScriptableEventBaseDef PTR64 base;
		float delayMin;
		float delayMax;
		unsigned __int16 eventStreamBufferOffsetServer;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventWaitDef, 24);

	struct ScriptableEventRandomDef
	{
		ScriptableEventBaseDef PTR64 base;
		float threshold;
		unsigned int eventACount;
		ScriptableEventDef PTR64 eventsA;
		unsigned int eventBCount;
		ScriptableEventDef PTR64 eventsB;
		unsigned __int16 eventStreamBufferOffsetServer;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventRandomDef, 48);

	struct ScriptableEventScriptDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 notification;
		scr_string_t scrNotification;
		int param;
		//bool doNotifyCallback;
	}; assert_sizeof(ScriptableEventScriptDef, 24);

	struct ScriptableEventModelDef
	{
		ScriptableEventBaseDef PTR64 base;
		XModel PTR64 model;
		char hudOutlineColor;
		bool hudOutlineActive;
		bool hudOutlineFill;
		bool neverMoves;
		bool dynamicSimulation;
		bool activatePhysics;
	}; assert_sizeof(ScriptableEventModelDef, 24);

	struct ScriptableEventCollisionDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 collmapName;
		bool aiObstacle;
		int clipmapCModelIndex;
		bool neverMoves;
		bool canPush;
		bool canTouch;
		bool destroyOnExit;
	}; assert_sizeof(ScriptableEventCollisionDef, 32);

	struct $6CB7272563F4458FB40A4A5E123C4ABA
	{
		unsigned __int16 index;
		unsigned __int16 tree;
	};

	union $754892263A8270AD7855E320C3BF2A51
	{
		$6CB7272563F4458FB40A4A5E123C4ABA __s0;
		unsigned __int64 linkPointer;
	};

	struct scr_anim_t
	{
		$754892263A8270AD7855E320C3BF2A51 ___u0;
	};

	struct ScriptableEventAnimationDef
	{
		ScriptableEventBaseDef PTR64 base;
		XAnimParts PTR64 animation;
		bool stateful;
		bool overrideAnimation;
		bool pauseOnExit;
		bool clientOnlyInMP;
		float startTimeMin;
		float startTimeMax;
		bool startTimeNormalized;
		float playbackRateMin;
		float playbackRateMax;
		float blendTime;
		unsigned int eventAtEndCount;
		ScriptableEventDef PTR64 eventsAtEnd;
		unsigned __int16 eventStreamBufferOffsetClient;
		unsigned __int16 eventStreamBufferOffsetServer;
		scr_anim_t animationIndex[2];
	}; assert_sizeof(ScriptableEventAnimationDef, 80);

	struct ScriptableEventHideShowBoneDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		bool hide;
		bool allowMissingTag;
		bool hideShowChildren;
	}; assert_sizeof(ScriptableEventHideShowBoneDef, 24);

	struct ScriptableNoteTrackDef
	{
		int flags;
		const char PTR64 noteTrackName;
		scr_string_t scrNoteTrackName;
		unsigned int numEvents;
		ScriptableEventDef PTR64 events;
	}; assert_sizeof(ScriptableNoteTrackDef, 32);

	struct ScriptableEventNoteTrackDef
	{
		ScriptableEventBaseDef PTR64 base;
		unsigned int noteTrackCount;
		ScriptableNoteTrackDef PTR64 noteTracks;
	}; assert_sizeof(ScriptableEventNoteTrackDef, 24);

	struct ScriptableEventChunkDynentDef
	{
		ScriptableEventBaseDef PTR64 base;
		ScriptablePartReference partReference;
		vec3_t launchLinVel;
		vec3_t launchAngVel;
		ScriptablePartDef PTR64 part;
	}; assert_sizeof(ScriptableEventChunkDynentDef, 88);

	struct ScriptableEventSpawnDynentDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool stateful;
		XModel PTR64 model;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		bool allowCauseVelocity;
		bool allowNearestVehicleVelocity;
		bool worldSpaceLinVel;
		bool worldSpaceAngVel;
		bool randomRangeLinVel;
		bool randomRangeAngVel;
		vec3_t launchLinVel;
		vec3_t launchAngVel;
		unsigned __int16 eventStreamBufferOffsetClient;
		bool allowMissingTag;
		bool useRootOnMissingTag;
	}; assert_sizeof(ScriptableEventSpawnDynentDef, 72);

	struct ScriptableEventPFXDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool stateful;
		scr_string_t PTR64 scrTagNames;
		unsigned int scrTagCount;
		scr_string_t PTR64 scrEndTagNames;
		unsigned int scrEndTagCount;
		bool useTagAngles;
		const char PTR64 effectAlias;
		FxCombinedDef effectDef;
		float loopRate;
		bool oneshotLooping;
		unsigned __int16 eventStreamBufferOffsetClient;
		bool allowMissingTag;
		bool useRootOnMissingTag;
		bool allowNearestVehicleVelocity;
		bool isViewmodel;
		bool killOnExit;
		bool useDynamicScriptedBeamLength;
		int beamBoneAxis;
		float beamLength;
		char __pad0[8];
	}; assert_sizeof(ScriptableEventPFXDef, 104);
	assert_offsetof(ScriptableEventPFXDef, effectDef, 56);

	struct ScriptableEventSoundDef
	{
		ScriptableEventBaseDef PTR64 base;
		char __pad0[8];
		const char PTR64 tagName;
		scr_string_t scrTagName;
		const char PTR64 soundAlias;
		const char PTR64 soundAliasCache;
		char __pad1[8];
	}; assert_sizeof(ScriptableEventSoundDef, 56);
	assert_offsetof(ScriptableEventSoundDef, tagName, 16);
	assert_offsetof(ScriptableEventSoundDef, soundAlias, 32);
	assert_offsetof(ScriptableEventSoundDef, soundAliasCache, 40);

	struct ScriptableEventExplosionDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		float radius;
		float dmgOuter;
		float dmgInner;
		bool stateful;
		bool allowMissingTag;
		bool useRootOnMissingTag;
		char __pad0[8];
	}; assert_sizeof(ScriptableEventExplosionDef, 48);

	struct ScriptableEventLightDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 name;
		scr_string_t scrName;
		float intensityScaleMin;
		float intensityScaleMax;
		float radiusMin;
		float radiusMax;
		bool useColor;
		vec4_t colorLinearSrgb;
		bool useStateTransitionTime;
		float transitionMin;
		float transitionMax;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventLightDef, 72);

	struct ScriptableEventSunDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool useIntensity;
		float intensityOverrideMin;
		float intensityOverrideMax;
		bool useColor;
		vec4_t colorLinearSrgb;
		bool useStateTransitionTime;
		float transitionMin;
		float transitionMax;
		float pitchMin;
		float pitchMax;
		float headingMin;
		float headingMax;
		bool useDirection;
	}; assert_sizeof(ScriptableEventSunDef, 72);

	struct ScriptableEventRumbleDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool stateful;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		const char PTR64 rumble;
		RumbleInfo PTR64 rumbleAsset;
		bool allowMissingTag;
		bool useRootOnMissingTag;
	}; assert_sizeof(ScriptableEventRumbleDef, 56);

	struct ScriptableEventScreenshakeDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool stateful;
		bool isEarthquake;
		bool isScreenShake;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		float duration;
		float durationFadeUp;
		float durationFadeDown;
		int radius;
		float scaleEarthquake;
		int scalePitch;
		int scaleYaw;
		int scaleRoll;
		int frequencyPitch;
		int frequencyYaw;
		int frequencyRoll;
		bool allowMissingTag;
		bool useRootOnMissingTag;
	}; assert_sizeof(ScriptableEventScreenshakeDef, 80);

	struct ScriptableEventPartDamageDef
	{
		ScriptableEventBaseDef PTR64 base;
		ScriptablePartReference partReference;
		float amount;
		//bool destroy;
		float amountDoT;
		float intervalDoT;
		unsigned __int16 eventStreamBufferOffsetServer;
		unsigned __int16 eventStreamBufferOffsetClient;
		ScriptablePartDef PTR64 part;
	}; assert_sizeof(ScriptableEventPartDamageDef, 80);

	struct ScriptableEventSetMayhemDef
	{
		ScriptableEventBaseDef PTR64 base;
		MayhemData PTR64 mayhem;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventSetMayhemDef, 24);

	enum Scriptable_MayhemAction
	{
		Scriptable_MayhemAction_Play = 0x0,
		Scriptable_MayhemAction_Pause = 0x1,
		Scriptable_MayhemAction_Count = 0x2,
	};

	struct ScriptableEventPlayMayhemDef
	{
		ScriptableEventBaseDef PTR64 base;
		Scriptable_MayhemAction action;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventPlayMayhemDef, 16);

	enum Scriptable_ShaderParamType
	{
		Scriptable_ShaderParamType_Unknown = 0x0,
		Scriptable_ShaderParamType_ScrollRate_X = 0x1,
		Scriptable_ShaderParamType_ScrollRate_Y = 0x2,
		Scriptable_ShaderParamType_ScrollRate_R = 0x3,
		Scriptable_ShaderParamType_Rotation = 0x4,
		Scriptable_ShaderParamType_Tiling_X = 0x5,
		Scriptable_ShaderParamType_Tiling_Y = 0x6,
		Scriptable_ShaderParamType_Alpha = 0x7,
		Scriptable_ShaderParamType_Emissive = 0x8,
		Scriptable_ShaderParamType_AtlasFrame = 0x9,
		Scriptable_ShaderParamType_Placeholder1 = 0xA,
		Scriptable_ShaderParamType_Placeholder2 = 0xB,
		Scriptable_ShaderParamType_Placeholder3 = 0xC,
		Scriptable_ShaderParamType_Placeholder4 = 0xD,
		Scriptable_ShaderParamType_Count = 0xE,
	};

	struct ScriptableEventViewmodelShaderParamDef
	{
		ScriptableEventBaseDef PTR64 base;
		Scriptable_ShaderParamType shaderParam;
		float floatValue;
		float placeHolderValue1;
		float placeHolderValue2;
		float placeHolderValue3;
		float placeHolderValue4;
		float transitionTime;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventViewmodelShaderParamDef, 40);

	enum Scriptable_ImageId
	{
		Scriptable_ImageId_Unknown = 0x0,
		Scriptable_ImageId_Count = 0x1,
	};

	struct ScriptableEventViewmodelChangeImageDef
	{
		ScriptableEventBaseDef PTR64 base;
		Scriptable_ImageId imageId;
		int imageValue;
	}; assert_sizeof(ScriptableEventViewmodelChangeImageDef, 16);

	struct ScriptableEventClientViewSelectorDef
	{
		ScriptableEventBaseDef PTR64 base;
		unsigned int event1pCount;
		ScriptableEventDef PTR64 events1p;
		unsigned int event3pCount;
		ScriptableEventDef PTR64 events3p;
		unsigned __int16 eventStreamBufferOffsetClient;
	}; assert_sizeof(ScriptableEventClientViewSelectorDef, 48);

	enum Scriptable_TeamFilter
	{
		Scriptable_Team_Filter_All = 0x0,
		Scriptable_Team_Filter_Bad = 0x1,
		Scriptable_Team_Filter_Axis = 0x2,
		Scriptable_Team_Filter_Allies = 0x3,
		Scriptable_Team_Filter_Three = 0x4,
		Scriptable_Team_Filter_Neutral = 0x5,
		Scriptable_Team_Filter_Dead = 0x6,
		Scriptable_Team_Filter_My_Team = 0x7,
		Scriptable_Team_Filter_Enemy_Team = 0x8,
		Scriptable_Team_Filter_All_But_My_Team = 0x9,
		Scriptable_Team_Filter_All_But_Enemy_Team = 0xA,
		Scriptable_Team_Filter_Enemy_Team_And_Me = 0xB,
		Scriptable_Team_Filter_Just_Me = 0xC,
		Scriptable_Team_Filter_Count = 0xD,
	};

	struct ScriptableEventTeamSelectorDef
	{
		ScriptableEventBaseDef PTR64 base;
		Scriptable_TeamFilter teamFilter;
		bool testLocalPlayer;
		unsigned int eventPassCount;
		ScriptableEventDef PTR64 eventsPass;
		unsigned int eventFailCount;
		ScriptableEventDef PTR64 eventsFail;
		unsigned __int16 eventStreamBufferOffsetClient;
		unsigned __int16 eventStreamBufferOffsetServer;
	}; assert_sizeof(ScriptableEventTeamSelectorDef, 56);

	struct ScriptableEventAddModelDef
	{
		ScriptableEventBaseDef PTR64 base;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		XModel PTR64 model;
	}; assert_sizeof(ScriptableEventAddModelDef, 32);

	struct ScriptableEventApplyForceDef
	{
		ScriptableEventBaseDef PTR64 base;
		vec3_t forcePos;
		vec3_t forceVector;
	}; assert_sizeof(ScriptableEventApplyForceDef, 32);

	struct ScriptableEventCompassIconDef
	{
		ScriptableEventBaseDef PTR64 base;
		bool stateful;
		bool friendlyCompassIconAlwaysVisible;
		bool enemyCompassIconAlwaysVisible;
		Material PTR64 friendlyArrow;
		Material PTR64 friendlyFiring;
		Material PTR64 friendlyChatting;
		Material PTR64 friendlyYelling;
		Material PTR64 partyArrow;
		Material PTR64 partyFiring;
		Material PTR64 partyChatting;
		Material PTR64 partyYelling;
		Material PTR64 squadArrow;
		Material PTR64 squadFiring;
		Material PTR64 enemyCompassIconQuiet[3];
		Material PTR64 enemyCompassIconFiring[3];
		Material PTR64 enemyCompassIconDirectional;
	}; assert_sizeof(ScriptableEventCompassIconDef, 152);

	enum Scriptable_MaterialOverrideType
	{
		Scriptable_MaterialOverrideType_Off = 0x0,
		Scriptable_MaterialOverrideType_Refraction = 0x1,
		Scriptable_MaterialOverrideType_Dissolve = 0x2,
		Scriptable_MaterialOverrideType_FlagAmplitudeScale = 0x3,
		Scriptable_MaterialOverrideType_Count = 0x4,
	};

	struct ScriptableEventMaterialOverrideDef
	{
		ScriptableEventBaseDef PTR64 base;
		Scriptable_MaterialOverrideType materialOverrideType;
		char __pad0[4];
		Material PTR64 material;
		int transitionTime;
		char finalValue;
		unsigned __int16 eventStreamBufferOffsetClient;
		char __pad1[8];
	}; assert_sizeof(ScriptableEventMaterialOverrideDef, 40);

	union ScriptableEventDefUnion
	{
		ScriptableEventAnonymousDef anonymous;
		ScriptableEventStateChangeDef stateChange; //
		ScriptableEventWaitDef wait;
		ScriptableEventRandomDef random;
		ScriptableEventScriptDef script; //
		ScriptableEventModelDef model;
		ScriptableEventCollisionDef collision;
		ScriptableEventAnimationDef animation;
		ScriptableEventHideShowBoneDef hideShowBone;
		ScriptableEventNoteTrackDef noteTrack;
		ScriptableEventChunkDynentDef chunkDynent;
		ScriptableEventSpawnDynentDef spawnDynent; //
		ScriptableEventPFXDef particleFX; //
		ScriptableEventSoundDef sound; //
		ScriptableEventExplosionDef explosion; //
		ScriptableEventLightDef light; //
		ScriptableEventSunDef sun;
		ScriptableEventRumbleDef rumble;
		ScriptableEventScreenshakeDef screenshake;
		ScriptableEventPartDamageDef partDamage; //
		ScriptableEventSetMayhemDef setMayhem;
		ScriptableEventPlayMayhemDef playMayhem;
		ScriptableEventViewmodelShaderParamDef viewmodelShaderParam;
		ScriptableEventViewmodelChangeImageDef viewmodelChangeImage;
		ScriptableEventClientViewSelectorDef clientViewSelector;
		ScriptableEventTeamSelectorDef teamSelector;
		ScriptableEventAddModelDef addModel;
		ScriptableEventApplyForceDef applyForce; //
		ScriptableEventCompassIconDef compassIcon;
		ScriptableEventMaterialOverrideDef materialOverride; //
	};

	struct ScriptableEventDef
	{
		ScriptableEventBaseDef base;
		Scriptable_EventType type;
		ScriptableEventDefUnion data;
	}; assert_sizeof(ScriptableEventDef, 176);

	struct ScriptableStateBaseDef
	{
		const char PTR64 name;
		int flags;
		unsigned int numEvents;
		ScriptableEventDef PTR64 events;
	}; assert_sizeof(ScriptableStateBaseDef, 24);

	enum Scriptable_StateType
	{
		Scriptable_StateType_Simple = 0x0,
		Scriptable_StateType_Health = 0x1,
		Scriptable_StateType_Scripted = 0x2,
		Scriptable_StateType_Count = 0x3,
	};

	struct ScriptableStateSimpleDef
	{
		ScriptableStateBaseDef PTR64 base;
	};

	struct ScriptableStateHealthDef
	{
		ScriptableStateBaseDef PTR64 base;
		int health;
		int validDamageCause;
		//int validAttackers;
		//int validAttackerTeams;
		int minimumDamage;
		float damagePropagationToParent;
		float damagePropagationToChild;
		float damagePropagationFromParent;
		float damagePropagationFromChild;
		const char PTR64 script_id;
		scr_string_t scrScript_id;
		bool localizeSplashDamage;
	}; assert_sizeof(ScriptableStateHealthDef, 56);
	assert_offsetof(ScriptableStateHealthDef, scrScript_id, 48);

	struct ScriptableStateScriptedDef
	{
		ScriptableStateBaseDef PTR64 base;
		const char PTR64 script_id;
		scr_string_t scrScript_id;
	};

	union ScriptableStateDefUnion
	{
		ScriptableStateSimpleDef simple;
		ScriptableStateHealthDef health; //
		ScriptableStateScriptedDef scripted;
	};

	struct ScriptableStateDef
	{
		ScriptableStateBaseDef base;
		Scriptable_StateType type;
		ScriptableStateDefUnion data;
	}; assert_sizeof(ScriptableStateDef, 88);
	assert_offsetof(ScriptableStateDef, data, 32);

	struct ScriptableDamageTagOverride
	{
		const char PTR64 tag;
		scr_string_t scrTag;
	};

	struct ScriptablePartDef // unchecked
	{
		const char PTR64 name;
		scr_string_t scrName;
		int flags;
		unsigned int flatId;
		unsigned int serverInstanceFlatId;
		unsigned int serverControlledFlatId;
		const char PTR64 tagName;
		scr_string_t scrTagName;
		unsigned int numStates;
		ScriptableStateDef PTR64 states;
		ScriptablePartDef PTR64 parentPart;
		unsigned int numChildParts;
		ScriptablePartDef PTR64 childParts;
		unsigned int numDamageTagOverrides;
		ScriptableDamageTagOverride PTR64 damageTagOverrides;
		unsigned __int16 eventStreamBufferOffsetServer;
		unsigned __int16 eventStreamBufferOffsetClient;
		unsigned __int16 eventStreamSize;
	}; assert_sizeof(ScriptablePartDef, 104);

	struct ScriptableDef // unchecked
	{
		const char PTR64 name;
		int flags;
		int type;
		ScriptableDef PTR64 nextScriptableDef;
		unsigned int numParts;
		ScriptablePartDef PTR64 parts;
		unsigned int maxNumDynEntsRequired;
		unsigned int partCount;
		unsigned int serverInstancedPartCount;
		unsigned int serverControlledPartCount;
		unsigned int maxNumDynEntPartsBase;
		unsigned int maxNumDynEntPartsForSpawning;
		unsigned __int16 eventStreamSizeRequiredServer;
		unsigned __int16 eventStreamSizeRequiredClient;
		unsigned __int16 eventStreamSize;
		unsigned int ffMemCost;
		scr_string_t animationTreeName;
		void PTR64 animationTreeDef[2];
		unsigned int numXModels;
		XModel PTR64  PTR64 models;
	}; assert_sizeof(ScriptableDef, 0x70);

	struct EquipmentClothData
	{
		char PTR64 foleyName;
		char PTR64 footstepName;
	};

	struct EquipmentWeaponRattleData
	{
		char PTR64 szName;
		float priority;
	};

	struct EquipmentSndChance
	{
		float rattleChance;
		float accentChance;
		float silentChance;
	};

	struct EquipmentChanceMoveTypes
	{
		EquipmentSndChance PTR64 chances;
	};

	struct EquipmentChanceRattleTypes
	{
		EquipmentChanceMoveTypes PTR64 chances;
	};

	struct EquipmentSoundSet
	{
		SndAliasList PTR64 soundPLR;
		SndAliasList PTR64 soundNPC;
	};

	struct EquipSoundSetMoveTypes
	{
		EquipmentSoundSet PTR64 soundSets;
	};

	struct EquipSoundSetMantleTypes
	{
		EquipmentSoundSet soundSets[12];
	}; assert_sizeof(EquipSoundSetMantleTypes, 192);

	struct EquipSoundSetStanceTypes
	{
		EquipmentSoundSet soundSets[4];
	};

	struct EquipSoundSetMeleeVM
	{
		EquipmentSoundSet soundSets[56];
	}; assert_sizeof(EquipSoundSetMeleeVM, 896);

	struct EquipmentSoundTable
	{
		const char PTR64 szName;
		unsigned int numClothTypes;
		unsigned int numWeaponRattleTypes;
		unsigned int numMoveTypes;
		unsigned int numStanceTypes;
		EquipmentClothData PTR64 clothTypes;
		EquipmentWeaponRattleData PTR64 weaponRattleTypes;
		EquipmentChanceRattleTypes PTR64 chancesPLR;
		EquipmentChanceRattleTypes PTR64 chancesNPC;
		EquipSoundSetMoveTypes PTR64 mvmtClothFootstepCeilingSoundSets;
		EquipSoundSetMoveTypes PTR64 mvmtClothFoleySoundSets;
		EquipSoundSetMoveTypes PTR64 mvmtRattleSoundSets;
		EquipSoundSetMoveTypes mvmtAccentSoundSets;
		EquipSoundSetMantleTypes PTR64 mvmtMantleSoundSets;
		EquipSoundSetStanceTypes PTR64 mvmtStanceSoundSets;
		EquipSoundSetMeleeVM PTR64 meleeAttackVMSoundSets;
	}; assert_sizeof(EquipmentSoundTable, 0x70);
	assert_offsetof(EquipmentSoundTable, mvmtStanceSoundSets, 96);

	enum VectorFieldType : std::int32_t
	{
		VECTOR_FIELD_TYPE_NONE = 0x0,
		VECTOR_FIELD_TYPE_FORCE = 0x1,
		VECTOR_FIELD_TYPE_VELOCITY = 0x2,
		VECTOR_FIELD_NUM_TYPES = 0x3,
	};

	struct VectorSubField
	{
		vec4_t PTR64 linearData;
		ExtentBounds worldBounds;
		vec3_t ds;
		unsigned int numEntries[3];
		unsigned int flags;
		VectorFieldType type;
		unsigned int pad[4];
	}; assert_sizeof(VectorSubField, 80);

	struct VectorField
	{
		const char PTR64 name;
		VectorSubField PTR64 subFields;
		ExtentBounds worldBounds;
		unsigned int numSubFields;
		unsigned int pad;
	}; assert_sizeof(VectorField, 48);

	struct FxParticleSimAnimationHeader
	{
		float playbackRate;
		float duration;
		unsigned int frameCount;
		float minX;
		float minY;
		float minZ;
		float boundsXDelta;
		float boundsYDelta;
		float boundsZDelta;
		float maxWidth;
		float maxHeight;
		unsigned int colorTableSize;
		unsigned int particleDataCount;
		unsigned int maxActiveParticles;
		bool evalVisStatePerParticle;
		bool sortParticlesAtRuntime;
		bool hasOrientation3D;
		bool hasIndex;
	};

	struct FxParticleSimAnimationParticleData
	{
		unsigned __int16 xNormalizedPos;
		unsigned __int16 yNormalizedPos;
		unsigned __int16 zNormalizedPos;
		unsigned __int16 xNormalizedWidth;
		unsigned __int16 yNormalizedHeight;
		unsigned __int16 orientation;
		unsigned __int16 lifetime;
		unsigned __int16 particleID;
		unsigned __int16 xNormalizedPosNextFrame;
		unsigned __int16 yNormalizedPosNextFrame;
		unsigned __int16 zNormalizedPosNextFrame;
		unsigned __int16 xNormalizedWidthNextFrame;
		unsigned __int16 yNormalizedHeightNextFrame;
		__int16 orientationDelta;
		unsigned __int16 colorTableIndex;
		unsigned __int16 nextColorTableIndex;
	};

	struct FxParticleSimAnimationParticleDataOrientation3D
	{
		unsigned __int16 yOrientation;
		unsigned __int16 zOrientation;
		__int16 yOrientationDelta;
		__int16 zOrientationDelta;
	};

	struct FxParticleSimAnimationParticleDataIndex
	{
		char index;
		char nextIndex;
	};

	struct FxParticleSimAnimationFrame
	{
		unsigned int particleDataOffset;
		unsigned int numActiveParticles;
	};

	struct FxParticleSimAnimation
	{
		const char PTR64 name;
		Material PTR64 material;
		FxParticleSimAnimationHeader header;
		FxParticleSimAnimationParticleData PTR64 particleData;
		FxParticleSimAnimationParticleDataOrientation3D PTR64 particleDataOrientation3D;
		FxParticleSimAnimationParticleDataIndex PTR64 particleDataIndex;
		FxParticleSimAnimationFrame PTR64 frames;
		vec4_t PTR64 colorTable;
	};

	struct AlwaysloadedFlags
	{
		unsigned int imageCount;
		GfxImage PTR64  PTR64 images;
		unsigned int PTR64 imageFlags;
		unsigned int stringCount;
		const char PTR64  PTR64 strings;
		unsigned int PTR64 stringFlags;
		unsigned int materialCount;
		Material PTR64  PTR64 materials;
		unsigned int PTR64 materialFlags;
	}; assert_sizeof(AlwaysloadedFlags, 72);

	struct AlwaysloadedFlagsPerModel
	{
		XModel PTR64 model;
		AlwaysloadedFlags flags;
	}; assert_sizeof(AlwaysloadedFlagsPerModel, 80);

	struct ForcedStubAssetReference
	{
		const char PTR64 name;
		char type;
	};

	struct TransientFileReference
	{
		const char PTR64 name;
		char type;
	};

	struct TransientAssetReference
	{
		const char PTR64 name;
		char type;
		unsigned int mpParentIndex;
	};

	struct TransientSets
	{
		unsigned int count;
		const char PTR64  PTR64 names;
		unsigned int PTR64 masks;
	};

	struct StreamingInfo
	{
		const char PTR64 name;
		int unused[2];
		AlwaysloadedFlags flags;
		int transientInfoFlags;
		unsigned int modelCount;
		AlwaysloadedFlagsPerModel PTR64 perModelFlags;
		unsigned int forcedStubAssetCount;
		ForcedStubAssetReference PTR64 forcedStubAssets;
		unsigned int transientFileCount;
		TransientFileReference PTR64 transientFiles;
		unsigned int transientAssetCount;
		TransientAssetReference PTR64 transientAssets;
		unsigned int stringCount;
		const char PTR64  PTR64 strings;
		TransientSets transientSets;
	}; assert_sizeof(StreamingInfo, 0xC0);
	assert_offsetof(StreamingInfo, modelCount, 92);

	struct LaserDef
	{
		const char PTR64 name;
		Material PTR64 laserMaterial;
		Material PTR64 laserLightMaterial;
		bool ownerOnly;
		bool nightvisionOnly;
		float range;
		float radius;
		float endOffsetViewmodel;
		float endOffsetOther;
		float flarePct;
		FxCombinedDef beamEffect;
		FxCombinedDef laserEndEffect;
		bool clientCollision;
		vec4_t color;
		vec4_t hdrColorScale;
		bool laserLight;
		bool laserLightNvgOnly;
		float laserLightRadius;
		float laserLightBeginOffset;
		float laserLightEndOffset;
		float laserLightBodyTweak;
		vec4_t laserLightColor;
		vec4_t laserLightHdrColorScale;
		float range_alt;
		float radius_alt;
		float laserLightRadius_alt;
		float flarePct_alt;
	}; assert_sizeof(LaserDef, 0xB8);

	struct TTFDef
	{
		const char PTR64 name;
		int fileLen;
		const char PTR64 file;
		void PTR64 ftFace;
	}; assert_sizeof(TTFDef, 0x20);

	enum SuitBodyAnimType
	{
		SUITBODYANIMTYPE_HUMAN = 0x0,
		SUITBODYANIMTYPE_JUGGERNAUT = 0x1,
		SUITBODYANIMTYPE_COUNT = 0x2,
	};

	struct SuitDef
	{
		const char PTR64 name;
		float cam_minVelocityForFovIncrease;
		float cam_maxVelocityForFovIncrease;
		float cam_velocityToDecreaseFov;
		float cam_fovIncreaseAtMaxVelocity;
		float cam_oneOverFovEaseInTimeMs;
		float cam_oneOverFovEaseOutTimeMs;
		bool enableIKOverride;
		float player_globalAccelScale;
		float player_sprintSpeedScale;
		bool player_sprintUnlimited;
		float player_viewBobScale;
		bool jump_slowdownEnable;
		float jump_height;
		float sprintLeap_height;
		float sprintLeap_forwardVelocityScale;
		int sprintLeap_minSprintTimeMs;
		float doubleJump_accel;
		float doubleJump_speed;
		float doubleJump_speedNoBoost;
		float doubleJump_frictionMin;
		float doubleJump_frictionMax;
		float doubleJump_initialUpBoostAccel;
		float doubleJump_standardUpBoostAccel;
		float doubleJump_energyNeededForInitialUpBoost;
		float doubleJump_energyNeededForStandardUpBoost;
		float doubleJump_maxUpwardsVelocity;
		bool doubleJump_enableMinZVelocity;
		float doubleJump_minZVelocity;
		float doubleJump_energyInitialCost;
		float doubleJump_boostUpEnergyUseRate;
		float doubleJump_energyUsePerButtonPress;
		bool doubleJump_hoverOnly;
		float doubleJump_maxViewPitchDip;
		float doubleJump_maxViewBackwardsPitchDip;
		float doubleJump_maxViewRoll;
		float doubleJump_oneOverEaseInTime;
		float doubleJump_oneOverEaseOutTimeMs;
		bool doubleJump_alwaysDipView;
		const char PTR64 doubleJump_sound;
		const char PTR64 doubleJump_soundPlayer;
		const char PTR64 doubleJump_releaseSound;
		const char PTR64 doubleJump_releaseSoundPlayer;
		int slide_sprint_penalty_ms;
		bool slide_allow_firing;
		bool slide_allow_ads;
		bool slide_allow_weapon_switch;
		float slide_jump_speed_scale;
		float slide_energy_cost_ratio;
		float slide_energy_unknown01;
		float slide_energy_unknown02;
		float slide_energy_unknown03;
		int slide_max_time_ms;
		int slide_max_time_reduced_ms;
		int slide_max_time_base_ms;
		float wallRun_minZVel;
		float wallRun_minTriggerSpeed;
		float wallRun_minMaintainSpeed;
		int wallRun_delayPeriodMs;
		float wallRun_minJumpHeight;
		int wallRun_maxTimeMs;
		int wallRun_fallStageTimeMs;
		float wallRun_maxHeight;
		float wallRun_jumpHeight;
		float wallRun_jumpVelocity;
		float wallRun_frictionScale;
		float wallRun_speedScale;
		float wallRun_speedScaleADS;
		float wallRun_energyInitialCost;
		float wallRun_energyChangePerSecond;
		float wallRun_energyUnknown01;
		float wallRun_energyUnknown02;
		SuitAnimType suitAnimType;
		SuitAnimPackage PTR64 animPackage;
		SuitAnimPackage PTR64 animPackageL;
		SuitAnimPackage PTR64 animPackageR;
		SuitAnimPackage PTR64 animPackageRelaxed;
		SuitAnimPackage PTR64 animPackageSafe;
		char facialAnimType;
		SuitBodyAnimType bodyAnimType;
		ScriptableDef PTR64 scriptableDef;
		int viewheight_stand;
		int viewheight_crouch;
		int viewheight_prone;
		int viewheight_laststand;
		int viewheight_dead;
		int viewheight_swim;
		int viewheight_slide;
		int bounds_radius;
		int bounds_height_stand;
		int bounds_height_crouch;
		int bounds_height_prone;
		Bounds bounds_stand;
		Bounds bounds_crouch;
		Bounds bounds_prone;
		int radialMotionBlur_interpTimeIn;
		int radialMotionBlur_interpTimeOut;
		float radialMotionBlur_sprintMinRadius;
		float radialMotionBlur_sprintMaxRadius;
		float radialMotionBlur_sprintMinStrength;
		float radialMotionBlur_sprintMaxStrength;
		float radialMotionBlur_slideMinRadius;
		float radialMotionBlur_slideMaxRadius;
		float radialMotionBlur_slideMinStrength;
		float radialMotionBlur_slideMaxStrength;
		float radialMotionBlur_doubleJumpMinRadius;
		float radialMotionBlur_doubleJumpMaxRadius;
		float radialMotionBlur_doubleJumpMinStrength;
		float radialMotionBlur_doubleJumpMaxStrength;
		float radialMotionBlur_wallRunMinRadius;
		float radialMotionBlur_wallRunMaxRadius;
		float radialMotionBlur_wallRunMinStrength;
		float radialMotionBlur_wallRunMaxStrength;
		float radialMotionBlur_groundPoundMinRadius;
		float radialMotionBlur_groundPoundMaxRadius;
		float radialMotionBlur_groundPoundMinStrength;
		float radialMotionBlur_groundPoundMaxStrength;
		float radialMotionBlur_rewindMinRadius;
		float radialMotionBlur_rewindMaxRadius;
		float radialMotionBlur_rewindMinStrength;
		float radialMotionBlur_rewindMaxStrength;
		float radialMotionBlur_dodgeMinRadius;
		float radialMotionBlur_dodgeMaxRadius;
		float radialMotionBlur_dodgeMinStrength;
		float radialMotionBlur_dodgeMaxStrength;
		RumbleInfo PTR64 groundPound_activationRumble;
		const char PTR64 groundPound_activationSound;
		const char PTR64 groundPound_activationSoundPlayer;
		RumbleInfo PTR64 groundPound_landingRumble;
		const char PTR64 groundPound_landingSound;
		const char PTR64 groundPound_landingSoundPlayer;
		RumbleInfo PTR64 landing_rumbleLowHeight;
		RumbleInfo PTR64 landing_rumbleMediumHeight;
		RumbleInfo PTR64 landing_rumbleHighHeight;
		RumbleInfo PTR64 landing_rumbleExtremeHeight;
		float landing_speedScale;
		float footstep_shakeBroadcastRadiusInches;
		int footstep_shakeDurationMs;
		float footstep_shakeAmplitude;
		RumbleInfo PTR64 footstep_rumble;
	}; assert_sizeof(SuitDef, 0x2C0);

	struct SuitAnimEntry
	{
		XAnimParts PTR64 anim;
		int time;
		unsigned int animType;
	}; assert_sizeof(SuitAnimEntry, 16);

	enum gestureAnimType_t
	{
		GESTUREANIMTYPE_NONE = 0x0,
		GESTUREANIMTYPE_SLIDE = 0x1,
		GESTUREANIMTYPE_SLIDE_AKIMBO = 0x2,
		GESTUREANIMTYPE_MANTLE_ON_F_LOW = 0x3,
		GESTUREANIMTYPE_MANTLE_ON_F_MIDDLE = 0x4,
		GESTUREANIMTYPE_MANTLE_ON_F_HIGH = 0x5,
		GESTUREANIMTYPE_MANTLE_ON_F_EXTREME = 0x6,
		GESTUREANIMTYPE_MANTLE_ON_B_LOW = 0x7,
		GESTUREANIMTYPE_MANTLE_ON_B_MIDDLE = 0x8,
		GESTUREANIMTYPE_MANTLE_ON_B_HIGH = 0x9,
		GESTUREANIMTYPE_MANTLE_ON_B_EXTREME = 0xA,
		GESTUREANIMTYPE_MANTLE_ON_L_LOW = 0xB,
		GESTUREANIMTYPE_MANTLE_ON_L_MIDDLE = 0xC,
		GESTUREANIMTYPE_MANTLE_ON_L_HIGH = 0xD,
		GESTUREANIMTYPE_MANTLE_ON_L_EXTREME = 0xE,
		GESTUREANIMTYPE_MANTLE_ON_R_LOW = 0xF,
		GESTUREANIMTYPE_MANTLE_ON_R_MIDDLE = 0x10,
		GESTUREANIMTYPE_MANTLE_ON_R_HIGH = 0x11,
		GESTUREANIMTYPE_MANTLE_ON_R_EXTREME = 0x12,
		GESTUREANIMTYPE_MANTLE_OVER_F_LOW = 0x13,
		GESTUREANIMTYPE_MANTLE_OVER_F_MIDDLE = 0x14,
		GESTUREANIMTYPE_MANTLE_OVER_F_HIGH = 0x15,
		GESTUREANIMTYPE_MANTLE_OVER_F_EXTREME = 0x16,
		GESTUREANIMTYPE_MANTLE_OVER_B_LOW = 0x17,
		GESTUREANIMTYPE_MANTLE_OVER_B_MIDDLE = 0x18,
		GESTUREANIMTYPE_MANTLE_OVER_B_HIGH = 0x19,
		GESTUREANIMTYPE_MANTLE_OVER_B_EXTREME = 0x1A,
		GESTUREANIMTYPE_MANTLE_OVER_L_LOW = 0x1B,
		GESTUREANIMTYPE_MANTLE_OVER_L_MIDDLE = 0x1C,
		GESTUREANIMTYPE_MANTLE_OVER_L_HIGH = 0x1D,
		GESTUREANIMTYPE_MANTLE_OVER_L_EXTREME = 0x1E,
		GESTUREANIMTYPE_MANTLE_OVER_R_LOW = 0x1F,
		GESTUREANIMTYPE_MANTLE_OVER_R_MIDDLE = 0x20,
		GESTUREANIMTYPE_MANTLE_OVER_R_HIGH = 0x21,
		GESTUREANIMTYPE_MANTLE_OVER_R_EXTREME = 0x22,
		GESTUREANIMTYPE_MANTLE_LADDER_LOW = 0x23,
		GESTUREANIMTYPE_MANTLE_LADDER_MIDDLE = 0x24,
		GESTUREANIMTYPE_MANTLE_LADDER_HIGH = 0x25,
		GESTUREANIMTYPE_WALLRUN_LEFT = 0x26,
		GESTUREANIMTYPE_WALLRUN_RIGHT = 0x27,
		GESTUREANIMTYPE_WALLRUN_LEFT_AKIMBO = 0x28,
		GESTUREANIMTYPE_WALLRUN_RIGHT_AKIMBO = 0x29,
		GESTUREANIMTYPE_MOUNT_REACH = 0x2A,
		GESTUREANIMTYPE_MOUNT_TOP = 0x2B,
		GESTUREANIMTYPE_MOUNT_LEFT = 0x2C,
		GESTUREANIMTYPE_MOUNT_RIGHT = 0x2D,
		GESTUREANIMTYPE_GROUND_POUND = 0x2E,
		GESTUREANIMTYPE_NVG_ON = 0x2F,
		GESTUREANIMTYPE_NVG_OFF = 0x30,
		GESTUREANIMTYPE_NUM = 0x36,
	};

	struct SuitGestureEntry
	{
		Gesture PTR64 gesture;
		gestureAnimType_t gestureAnimType;
	};

	struct SuitAnimPerWeapClass
	{
		SuitAnimEntry PTR64 anims;
		unsigned int numAnims;
		int weapClasses;
		SuitGestureEntry PTR64 gestures;
		int numGestures;
		FootstepAnim footstep[9];
	}; assert_sizeof(SuitAnimPerWeapClass, 640);

	struct SuitAnimPackage
	{
		const char PTR64 name;
		SuitAnimPerWeapClass animOverrides[6];
	}; assert_sizeof(SuitAnimPackage, 0xF08);

	struct SpaceshipTargetDef
	{
		const char PTR64 name;
		scr_string_t targetTag;
		float annotationOffsetX;
		float annotationOffsetY;
		float annotationOffsetZ;
		bool disableLeading;
		float lock_minDistance;
		float lock_maxDistance;
		float lock_cutoffDistance;
		float lock_minRate;
		float lock_maxRate;
		float lock_maxZoomFOV;
		float lock_followDistance;
		float lockCooldown_rate;
		float aa_closeDistance;
		float aa_farDistance;
		float aa_closeMinAngle;
		float aa_closeMaxAngle;
		float aa_closeBlendMax;
		float aa_farMinAngle;
		float aa_farMaxAngle;
		float aa_farBlendMax;
		float aaLocked_closeDistance;
		float aaLocked_farDistance;
		float aaLocked_closeMinAngle;
		float aaLocked_closeMaxAngle;
		float aaLocked_closeBlendMax;
		float aaLocked_farMinAngle;
		float aaLocked_farMaxAngle;
		float aaLocked_farBlendMax;
		float pilotAssistScale;
		float callout_maxDistance;
		float callout_maxAngle;
	};

	enum RumbleGraphs
	{
		RUMBLEGRAPH_HIGH = 0x0,
		RUMBLEGRAPH_LOW = 0x1,
		RUMBLEGRAPH_COUNT = 0x2,
	};

	struct RumbleInfo
	{
		const char PTR64 name;
		int duration;
		float range;
		RumbleGraph PTR64 highRumbleGraph;
		RumbleGraph PTR64 lowRumbleGraph;
		bool fadeWithDistance;
		bool broadcast;
	};

	struct RumbleGraph
	{
		const char PTR64 name;
		vec2_t knots[16];
		unsigned short knotCount;
	};

	struct WeaponAnimPackageStateTimers
	{
		unsigned __int16 iFireDelay;
		unsigned __int16 iMeleeDelay;
		unsigned __int16 iDetonateDelay;
		unsigned __int16 iFirstRaiseTime;
		unsigned __int16 iAltRaiseTime;
		unsigned __int16 iAltRaiseADSTime;
		unsigned __int16 iAltRaiseAkimboTime;
		unsigned __int16 iRechamberTime;
		unsigned __int16 rechamberTimeOneHanded;
		unsigned __int16 iRechamberBoltTime;
		unsigned __int16 iHoldFireTime;
		unsigned __int16 iHoldPrimeTime;
		unsigned __int16 iDetonateTime;
		unsigned __int16 iMeleeTime;
		unsigned __int16 meleeChargeTime;
		unsigned __int16 meleeUnkTime;
		unsigned __int16 altMeleeTime;
		unsigned __int16 altMeleeChargeTime;
		unsigned __int16 altMeleeUnkTime;
		unsigned __int16 iReloadTime;
		unsigned __int16 iFastReloadTime;
		unsigned __int16 reloadShowRocketTime;
		unsigned __int16 iReloadEmptyTime;
		unsigned __int16 iFastReloadEmptyTime;
		unsigned __int16 iReloadAddTime;
		unsigned __int16 iFastReloadAddTime;
		unsigned __int16 iReloadEmptyAddTime;
		unsigned __int16 iFastReloadEmptyAddTime;
		unsigned __int16 iReloadStartTime;
		unsigned __int16 iAltOverride3PInTime;
		unsigned __int16 iAltOverride3POutTime;
		unsigned __int16 iReloadStartAddTime;
		unsigned __int16 iFastReloadStartAddTime;
		unsigned __int16 iReloadEndTime;
		unsigned __int16 iFastReloadEndTime;
		unsigned __int16 iDropTime;
		unsigned __int16 iRaiseTime;
		unsigned __int16 iAltDropTime;
		unsigned __int16 iAltDropADSTime;
		unsigned __int16 iAltDropAkimboTime;
		unsigned __int16 quickDropTime;
		unsigned __int16 quickRaiseTime;
		unsigned __int16 iBreachRaiseTime;
		unsigned __int16 iEmptyRaiseTime;
		unsigned __int16 iEmptyDropTime;
		unsigned __int16 sprintInTime;
		unsigned __int16 sprintLoopTime;
		unsigned __int16 sprintOutTime;
		unsigned __int16 walkTime;
		unsigned __int16 gungHoTime;
		unsigned __int16 crawlTime;
		unsigned __int16 stunnedTimeBegin;
		unsigned __int16 stunnedTimeLoop;
		unsigned __int16 stunnedTimeEnd;
		unsigned __int16 nightVisionWearTime;
		unsigned __int16 nightVisionWearTimeFadeOutEnd;
		unsigned __int16 nightVisionWearTimePowerUp;
		unsigned __int16 nightVisionRemoveTime;
		unsigned __int16 nightVisionRemoveTimePowerDown;
		unsigned __int16 nightVisionRemoveTimeFadeInStart;
		unsigned __int16 primeTime;
		bool bHoldFullPrime;
		bool bAltOverride3PADSOnly;
		unsigned __int16 blastFrontTime;
		unsigned __int16 blastRightTime;
		unsigned __int16 blastBackTime;
		unsigned __int16 blastLeftTime;
		unsigned __int16 slideInTime;
		unsigned __int16 slideLoopTime;
		unsigned __int16 slideOutTime;
		unsigned __int16 dodgeTime;
		unsigned __int16 wallRunInTime;
		unsigned __int16 wallRunOutTime;
		unsigned __int16 leapInTime;
		unsigned __int16 leapLoopTime;
		unsigned __int16 leapOutTime;
		unsigned __int16 leapCancelTime;
		unsigned __int16 chargeInTime;
		unsigned __int16 chargeLoopTime;
		unsigned __int16 chargeOutTime;
		unsigned __int16 iRegenerationTime;
		unsigned __int16 iRegenerationAddTime;
		unsigned __int16 iReloadInterruptTime;
		unsigned __int16 iReloadEmptyInterruptTime;
		unsigned __int16 iReloadEndInterruptTime;
		unsigned __int16 iReloadMultiple1InterruptTime;
		unsigned __int16 iReloadMultiple2InterruptTime;
		unsigned __int16 iReloadMultiple3InterruptTime;
		unsigned __int16 iReloadMultiple4InterruptTime;
		unsigned __int16 iReloadMultiple5InterruptTime;
		unsigned __int16 iReloadMultiple6InterruptTime;
		unsigned __int16 iReloadMultiple7InterruptTime;
		unsigned __int16 iReloadMultiple8InterruptTime;
		unsigned __int16 iFastReloadInterruptTime;
		unsigned __int16 iFastReloadEmptyInterruptTime;
		unsigned __int16 iFastReloadEndInterruptTime;
		unsigned __int16 iFastReloadMultiple1InterruptTime;
		unsigned __int16 iFastReloadMultiple2InterruptTime;
		unsigned __int16 iFastReloadMultiple3InterruptTime;
		unsigned __int16 iFastReloadMultiple4InterruptTime;
		unsigned __int16 iFastReloadMultiple5InterruptTime;
		unsigned __int16 iFastReloadMultiple6InterruptTime;
		unsigned __int16 iFastReloadMultiple7InterruptTime;
		unsigned __int16 iFastReloadMultiple8InterruptTime;
	}; assert_sizeof(WeaponAnimPackageStateTimers, 206);

	struct FootstepAnims
	{
		FootstepAnim footstep[9];
	}; assert_sizeof(FootstepAnims, 612);

	struct WeaponAnimPackage
	{
		const char PTR64 name;
		XAnimParts PTR64  PTR64 anims; // array: 260
		WeaponAnimPackageStateTimers PTR64 timers;
		int meleeAnimType;
		int meleeAnimPrimaryCount;
		int meleeAnimAltCount;
		int fireAnimTimesMs[4];
		int pad;
		FootstepAnims PTR64 footstep; // always same values
	}; assert_sizeof(WeaponAnimPackage, 0x40);
	assert_offsetof(WeaponAnimPackage, footstep, 56);

	struct WeaponSFXPackageSounds
	{
		const char PTR64 name;
		const char PTR64 pickupSound;
		const char PTR64 pickupSoundPlayer;
		const char PTR64 ammoPickupSound;
		const char PTR64 ammoPickupSoundPlayer;
		const char PTR64 projectileSound;
		const char PTR64 pullbackSound;
		const char PTR64 pullbackSoundPlayer;
		const char PTR64 pullbackSoundQuick;
		const char PTR64 pullbackSoundQuickPlayer;
		const char PTR64 fireSound;
		const char PTR64 fireSoundPlayer;
		const char PTR64 fireSoundPlayerAkimbo;
		const char PTR64 fireSoundPlayerAkimboRight;
		const char PTR64 fireStartSound;
		const char PTR64 fireStartSoundPlayer;
		const char PTR64 fireLoopSound;
		const char PTR64 fireLoopSoundPlayer;
		const char PTR64 fireStopSound;
		const char PTR64 fireStopSoundPlayer;
		const char PTR64 fireLastSound;
		const char PTR64 fireLastSoundPlayer;
		const char PTR64 fireLastSoundPlayerAkimbo;
		const char PTR64 fireLastSoundPlayerAkimboRight;
		const char PTR64 regenerateSound;
		const char PTR64 regenerateSoundPlayer;
		const char PTR64 emptyFireSound;
		const char PTR64 emptyFireSoundPlayer;
		const char PTR64 emptyRegenFireSound;
		const char PTR64 emptyRegenFireSoundPlayer;
		const char PTR64 rechamberSound;
		const char PTR64 rechamberSoundPlayer;
		const char PTR64 reloadSound;
		const char PTR64 reloadSoundPlayer;
		const char PTR64 reloadEmptySound;
		const char PTR64 reloadEmptySoundPlayer;
		const char PTR64 reloadStartSound;
		const char PTR64 reloadStartSoundPlayer;
		const char PTR64 reloadEndSound;
		const char PTR64 reloadEndSoundPlayer;
		const char PTR64 detonateSound;
		const char PTR64 detonateSoundPlayer;
		const char PTR64 nightVisionWearSound;
		const char PTR64 nightVisionWearSoundPlayer;
		const char PTR64 nightVisionRemoveSound;
		const char PTR64 nightVisionRemoveSoundPlayer;
		const char PTR64 altSwitchSound;
		const char PTR64 altSwitchSoundPlayer;
		const char PTR64 raiseSound;
		const char PTR64 raiseSoundPlayer;
		const char PTR64 firstRaiseSound;
		const char PTR64 firstRaiseSoundPlayer;
		const char PTR64 putawaySound;
		const char PTR64 putawaySoundPlayer;
		const char PTR64 enterAdsSoundPlayer;
		const char PTR64 leaveAdsSoundPlayer;
		const char PTR64 bulletRicochetImpact;
		const char PTR64 projExplosionSound;
		const char PTR64 projDudSound;
		const char PTR64 projIgnitionSound;
		const char PTR64 bounceSound;
		const char PTR64 rollingSound;
	}; assert_sizeof(WeaponSFXPackageSounds, 0x1F0);

	struct WeaponSFXPackage
	{
		const char PTR64 name;
		WeaponSFXPackageSounds PTR64 sounds;
		char rattleSoundType;
		const char PTR64 szAdsrBaseSetting;
		const char PTR64 szWeapSndReflectionClass;
		float weapSndFireVolumeShot1;
		float weapSndFireVolumeShot2;
		float weapSndFireVolumeShot3;
		float weapSndProneFireLFEVolume;
	}; assert_sizeof(WeaponSFXPackage, 0x38);

	struct WeaponVFXPackageDefs
	{
		FxCombinedDef viewFlashEffect;
		FxCombinedDef worldFlashEffect;
		FxCombinedDef viewFlashADSEffect;
		FxCombinedDef viewFlashOverchargeEffect;
		FxCombinedDef viewFlashOverchargeADSEffect;
		FxCombinedDef worldFlashOverchargeEffect;
		FxCombinedDef viewShellEjectEffect;
		FxCombinedDef worldShellEjectEffect;
		FxCombinedDef viewLastShotEjectEffect;
		FxCombinedDef worldLastShotEjectEffect;
		FxCombinedDef viewMagEjectEffect;
	}; assert_sizeof(WeaponVFXPackageDefs, 0xB0);

	struct WeaponVFXPackage
	{
		const char PTR64 name;
		WeaponVFXPackageDefs PTR64 vfx;
	};

	struct BehaviorTreeNode
	{
		const char PTR64 name;
		char __pad0[16];
	}; assert_sizeof(BehaviorTreeNode, 24);

	struct BehaviorTree
	{
		const char PTR64 name;
		unsigned short nodeCount;
		BehaviorTreeNode PTR64 nodes;
	}; assert_sizeof(BehaviorTree, 0x18);

	struct XAnimArcheType;

	enum XAnimUpVectorType
	{
		XANIM_UP_VECTOR_TYPE_WORLD_SPACE = 0x0,
		XANIM_UP_VECTOR_TYPE_BONE_RELATIVE = 0x1,
		XANIM_UP_VECTOR_TYPE_AIM_AT_BONE = 0x2,
	};

	struct XAnimAimConstraint
	{
		vec3_t aimTargetLocalOffset;
		vec3_t localAimVector;
		vec3_t localUpVector;
		vec3_t axisMask;
		vec3_t upVector;
		XAnimUpVectorType upVectorType;
	};

	struct XAnimRotationConstraint
	{
		vec4_t rotationOffsetQuat;
		vec3_t axisMask;
		float blendFraction;
	};

	struct XAnimPositionConstraint
	{
		float blendFraction;
		vec3_t minLocalTranslationLimit;
		vec3_t maxLocalTranslationLimit;
		vec3_t offset;
		vec3_t sourceBoneOffsets[2];
		vec3_t axisMask;
	};

	struct XAnimDistanceDrivenOffsetConstraint
	{
		vec4_t minLocalOffset;
		vec4_t maxLocalOffset;
		vec3_t sourceBoneOffsets[2];
		float distanceScale;
		float distanceBias;
		char curveType;
	};

	union XAnimConstraintUnion
	{
		XAnimPositionConstraint positionConstraint;
		XAnimRotationConstraint rotationConstraint;
		XAnimAimConstraint aimConstraint;
		XAnimDistanceDrivenOffsetConstraint distanceDrivenOffsetConstraint;
	};

	struct XAnimConstraint
	{
		char type;
		char localTargetBoneIndex;
		scr_string_t sourceBoneNames[2];
		XAnimConstraintUnion u;
	}; assert_sizeof(XAnimConstraint, 88);

	struct unk_1453E1E68
	{
		scr_string_t unk01;
		char __pad0[92];
		scr_string_t unk02;
		char __pad1[4];
		scr_string_t unk03;
		char __pad2[20];
	}; assert_sizeof(unk_1453E1E68, 0x80);

	struct unk_1453E1E30
	{
		scr_string_t unk01;
		char __pad0[8];
	}; assert_sizeof(unk_1453E1E30, 12);

	struct unk_1453E1EA8
	{
		char __pad0[32];
	}; assert_sizeof(unk_1453E1EA8, 32);

	struct XAnimProceduralBones
	{
		const char PTR64 name;
		XAnimConstraint PTR64 constraints;
		unsigned int numConstraints;
		unsigned int numTargetBones;
		scr_string_t PTR64 targetBoneNames;
		unsigned int unk01_count;
		unk_1453E1E68 PTR64 unk01;
		unsigned int unk02_count;
		unk_1453E1E30 PTR64 unk02;
		int unk_04;
		unsigned int unk03_count;
		unk_1453E1EA8 PTR64 unk03;
	}; assert_sizeof(XAnimProceduralBones, 0x50);

	struct ReticleDef
	{
		const char PTR64 name;
		const char PTR64 widgetName;
		bool lockReticleToTag;
		bool primaryAffectedByEMP;
		bool secondaryAffectedByEMP;
		bool scaleWithFOV;
		float naturalDistance;
		float minReticleScale;
		float maxReticleScale;
	}; assert_sizeof(ReticleDef, 0x20);

	struct GfxLightMap
	{
		const char PTR64 name;
		GfxImage PTR64 textures[3];
	};

	union XAssetHeader
	{
		void PTR64 data;
		PhysicsLibrary PTR64 physicsLibrary;
		PhysicsSFXEventAsset PTR64 physicsSFXEventAsset;
		PhysicsVFXEventAsset PTR64 physicsVFXEventAsset;
		PhysicsAsset PTR64 physicsAsset;
		PhysicsFXPipeline PTR64 physicsFXPipeline;
		PhysicsFXShape PTR64 physicsFXShape;
		XAnimParts PTR64 parts;
		XModelSurfs PTR64 modelSurfs;
		XModel PTR64 model;
		MayhemData PTR64 mayhem;
		Material PTR64 material;
		ComputeShader PTR64 computeShader;
		MaterialVertexShader PTR64 vertexShader;
		MaterialHullShader PTR64 hullShader;
		MaterialDomainShader PTR64 domainShader;
		MaterialPixelShader PTR64 pixelShader;
		MaterialVertexDeclaration PTR64 vertexDecl;
		MaterialTechniqueSet PTR64 techniqueSet;
		GfxImage PTR64 image;
		SndGlobals PTR64 soundGlobals;
		SndBank PTR64 soundBank;
		SndBankTransient PTR64 soundBankTransient;
		clipMap_t PTR64 clipMap;
		ComWorld PTR64 comWorld;
		GlassWorld PTR64 glassWorld;
		PathData PTR64 pathData;
		NavMeshData PTR64 navMeshData;
		MapEnts PTR64 mapEnts;
		FxWorld PTR64 fxWorld;
		GfxWorld PTR64 gfxWorld;
		GfxWorldTransientZone PTR64 gfxWorldTransientZone;
		//void PTR64 iesProfile;
		GfxLightDef PTR64 lightDef;
		//void PTR64 uiMap;
		AnimationClass PTR64 animClass;
		PlayerAnimScript PTR64 playerAnim;
		Gesture PTR64 gesture;
		LocalizeEntry PTR64 localize;
		WeaponAttachment PTR64 attachment;
		WeaponCompleteDef PTR64 weapon;
		ParticleSystemDef PTR64 vfx;
		FxEffectDef PTR64 fx;
		FxImpactTable PTR64 impactFx;
		SurfaceFxTable PTR64 surfaceFx;
		//void PTR64 aiType;
		//void PTR64 mpType;
		//void PTR64 character;
		//void PTR64 modelAlias;
		RawFile PTR64 rawfile;
		ScriptFile PTR64 scriptfile;
		StringTable PTR64 stringTable;
		LeaderboardDef PTR64 leaderboardDef;
		VirtualLeaderboardDef PTR64 virtualLeaderboardDef;
		StructuredDataDefSet PTR64 structuredDataDefSet;
		DDLFile PTR64 ddlFile;
		TracerDef PTR64 tracerDef;
		VehicleDef PTR64 vehDef;
		AddonMapEnts PTR64 addonMapEnts;
		NetConstStrings PTR64 netConstStrings;
		LuaFile PTR64 luaFile;
		ScriptableDef PTR64 scriptable;
		EquipmentSoundTable PTR64 equipSndTable;
		VectorField PTR64 vectorField;
		FxParticleSimAnimation PTR64 particleSimAnimation;
		StreamingInfo PTR64 streamingInfo;
		LaserDef PTR64 laserDef;
		TTFDef PTR64 ttfDef;
		SuitDef PTR64 suitDef;
		SuitAnimPackage PTR64 suitAnimPackage;
		SpaceshipTargetDef PTR64 spaceshipTargetDef;
		RumbleInfo PTR64 rumble;
		RumbleGraph PTR64 rumbleGraph;
		WeaponAnimPackage PTR64 weaponAnimPackage;
		WeaponSFXPackage PTR64 weaponSFXPackage;
		WeaponVFXPackage PTR64 weaponVFXPackage;
		BehaviorTree PTR64 behaviorTree;
		//XAnimArcheType PTR64 archeType;
		XAnimProceduralBones PTR64 proceduralBones;
		ReticleDef PTR64 reticleDef;
		GfxLightMap PTR64 lightMap;
	};

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct XAssetEntry
	{
		XAssetHeader header;
		int nextHash;
		int nextOverride; // or nextPoolEntry
		char inuseMask;
		unsigned char type;
		unsigned short zoneIndex;
	}; assert_sizeof(XAssetEntry, 0x18);

	struct ScriptStringList
	{
		int count;
		const char PTR64  PTR64 strings;
	};

	union GfxZoneTableEntry
	{
		char PTR64 dataPtr;
		void PTR64 voidPtr;
		ID3D11Buffer PTR64 buffer;
		ID3D11DepthStencilState PTR64 depthStencilState;
		ID3D11BlendState PTR64 blendState;
	};

	typedef std::uint32_t GfxBlendStateBits[4];

	struct XGfxGlobals
	{
		unsigned int depthStencilStateCount;
		unsigned int blendStateCount;
		std::uint64_t PTR64 depthStencilStateBits;
		GfxBlendStateBits PTR64 blendStateBits;
		GfxZoneTableEntry PTR64 depthStencilStates;
		GfxZoneTableEntry PTR64 blendStates;
		unsigned int perPrimConstantBufferCount;
		unsigned int perObjConstantBufferCount;
		unsigned int stableConstantBufferCount;
		unsigned int PTR64 perPrimConstantBufferSizes;
		unsigned int PTR64 perObjConstantBufferSizes;
		unsigned int PTR64 stableConstantBufferSizes;
		GfxZoneTableEntry PTR64 perPrimConstantBuffers;
		GfxZoneTableEntry PTR64 perObjConstantBuffers;
		GfxZoneTableEntry PTR64 stableConstantBuffers;
	};

	struct XGlobals
	{
		XGfxGlobals PTR64 gfxGlobals;
	};

	struct XAssetList
	{
		ScriptStringList stringList;
		int assetCount;
		XAsset PTR64 assets;
		XGlobals PTR64 globals;
	};

	enum DBSyncMode : std::int8_t
	{
		DB_LOAD_SYNC = 0x0,
		DB_LOAD_ASYNC = 0x1,
	};

	enum DBAllocFlags : std::int32_t
	{
		DB_ZONE_NONE = 0x0,
		DB_ZONE_COMMON = 0x1,
		DB_ZONE_GAME = 0x4, // maybe
		DB_ZONE_LOAD = 0x100,
		DB_ZONE_CUSTOM = 0x1000000 // added for custom zone loading
	};

	struct XZoneInfo
	{
		const char PTR64 name;
		int allocFlags;
	};

	struct DBFile
	{
		char name[64];
		void PTR64 handle;
		unsigned __int64 memoryBufferSize;
		unsigned char PTR64 memoryBuffer;
		void PTR64 handle_dcache;
		char __pad1[22];
		bool isSecure;
		char __pad2[49];
	}; assert_sizeof(DBFile, 0xA8);
	assert_offsetof(DBFile, isSecure, 118);

	struct db_internal_state
	{
		int dummy;
	};

	struct db_z_stream_s
	{
		unsigned char PTR64 next_in;
		unsigned int avail_in;
		unsigned int total_in;
		unsigned char PTR64 next_out;
		unsigned int avail_out;
		unsigned int total_out;
		char PTR64 msg;
		db_internal_state PTR64 state;
		unsigned __int8 PTR64 (__fastcall PTR64 zalloc)(unsigned __int8 PTR64 , unsigned int, unsigned int);
		void(__fastcall PTR64 zfree)(unsigned __int8 PTR64 , unsigned __int8 PTR64 );
		unsigned __int8 PTR64 opaque;
		int data_type;
		unsigned long adler;
		unsigned long reserved;
	};

	enum DB_CompressorType : std::uint8_t
	{
		DB_COMPRESSOR_INVALID = 0x0,
		DB_COMPRESSOR_PASSTHROUGH = 0x1,
		DB_COMPRESSOR_BLOCK = 0x2,
	};

	struct DB_ReadStream
	{
		unsigned char PTR64 next_in;
		unsigned __int64 avail_in;
		unsigned __int64 total_in;
		unsigned char PTR64 next_out;
		unsigned __int64 avail_out;
		unsigned __int64 total_out;
		DB_CompressorType compressor;
	};

	struct DB_LoadData
	{
		DBFile PTR64 file;
		void PTR64 unk1;
		unsigned char PTR64 fileBuffer;
		unsigned __int64 readSize;
		unsigned __int64 completedReadSize;
		unsigned __int64 offset;
		unsigned char PTR64 start_in;
		unsigned int readError;
		int readingResident;
		DB_ReadStream stream;
		__int64 read_size_;
		__int64 offset_;
		int unk4;
		int unk5;
		int unk6;
		int unk7;
		int unk8;
		int unk9;
		int unk10;
		int unk11;
	}; assert_sizeof(DB_LoadData, 0xA8);

	enum XFileBlock
	{
		XFILE_BLOCK_TEMP = 0x0,
		XFILE_BLOCK_UNK1 = 0x1,
		XFILE_BLOCK_UNK2 = 0x2,
		XFILE_BLOCK_IMAGE_STREAM = 0x3,
		XFILE_BLOCK_SHARED_STREAM = 0x4,
		XFILE_BLOCK_CALLBACK = 0x5,
		XFILE_BLOCK_RUNTIME = 0x6,
		XFILE_BLOCK_UNK7 = 0x7,
		XFILE_BLOCK_VIRTUAL = 0x8,
		XFILE_BLOCK_SCRIPT = 0x9,
		MAX_XFILE_COUNT = 0xA,
	};

	struct XBlock
	{
		char PTR64 alloc;
		unsigned __int64 size;
	};

	struct XStreamFile
	{
		std::uint64_t offset;
		std::uint64_t offsetEnd;
		std::uint16_t fileIndex;
		bool isLocalized;
	};

	struct XZoneMemory
	{
		XBlock blocks[MAX_XFILE_COUNT];
		char __pad0[112];
		void PTR64 shared_ff_data;
		unsigned int shared_ff_count;
		int padding1;
		void PTR64 unknown; // always 0
		XStreamFile PTR64 streamed_images;
		unsigned int streamed_image_count;
		int streamed_image_index;
		char __pad1[0x100]; // unk size
	};

	struct DB_AuthHash
	{
		unsigned char bytes[32];
	};

	struct DB_AuthSignature
	{
		unsigned char bytes[256];
	};

	struct DB_MasterBlock
	{
		DB_AuthHash chunkHashes[512];
	}; assert_sizeof(DB_MasterBlock, 0x4000);

	struct DB_AuthSubHeader
	{
		char fastfileName[32];
		unsigned int reserved;
		DB_AuthHash masterBlockHashes[192];
	};

	struct DB_AuthHeader // sub_1409E6100
	{
		char magic[8]; // IWffs100
		unsigned int reserved;
		DB_AuthHash subheaderHash;
		DB_AuthSignature signedSubheaderHash;
		DB_AuthSubHeader subheader;
		char padding[9904]; // not used
	}; assert_sizeof(DB_AuthHeader, 0x4000);

	struct XPakHeader
	{
		char magic[8];
		std::uint32_t version;
		char unknown[20]; // unused
		unsigned char iv[16];
		DB_AuthHash hash;
		DB_AuthSignature signedhash;
		// iv for each image
	};

	struct XFileStreamData
	{
		std::uint64_t size;
		std::uint64_t unk1;
		std::uint64_t unk2;
		std::uint64_t block_size[MAX_XFILE_COUNT];
		std::uint64_t unk_arr[8];
	}; assert_sizeof(XFileStreamData, 168);

	struct XFileHeader
	{
		char magic[8];
		std::uint32_t version;
		std::uint8_t unused; // (unused)
		std::uint8_t has_no_image_fastfile;
		std::uint8_t has_no_shared_fastfile;
		std::uint8_t unk1;
		std::uint32_t fileTimeHigh; // (unused)
		std::uint32_t fileTimeLow; // (unused)
		XFileStreamData stream_data;
		std::uint32_t shared_ff_hash; // some check
		std::uint32_t shared_ff_count; // streamed shared_asset count
		std::uint32_t image_ff_hash; // some check
		std::uint32_t image_ff_count; // streamed image count
		// image streams 24  PTR64 sharedcount
		// image streams 24  PTR64 imagecount
		std::uint64_t fileLen;
		std::uint64_t fileLenUnk1;
		std::uint64_t fileLenUnk2;
		// if signed: DB_AuthHeader info;
		// XFileCompressorHeader
	};

	struct XFileCompressorHeader
	{
		DB_CompressorType compressor;
		char magic[3];
	};

#pragma pack(push, 1)
	struct XBlockCompressionBlockHeader
	{
		unsigned int compressedSize;
		std::uint64_t uncompressedSize;
	};

	struct XBlockCompressionBlockSizeAndCompressionType
	{
		unsigned __int32 blockSize : 24;
		unsigned __int32 compressionType : 8;
	};

	struct XBlockCompressionDataHeader
	{
		std::uint64_t uncompressedSize;
		XBlockCompressionBlockSizeAndCompressionType blockSizeAndType;
	};
#pragma pack(pop)

	enum XBlockCompressionType
	{
		XBLOCK_COMPRESSION_INVALID = 0x0,
		XBLOCK_COMPRESSION_ZLIB_SIZE = 0x1,
		XBLOCK_COMPRESSION_ZLIB_SPEED = 0x2,
		XBLOCK_COMPRESSION_LZ4HC = 0x3,
		XBLOCK_COMPRESSION_LZ4 = 0x4,
		XBLOCK_COMPRESSION_NONE = 0x5,
	};

	struct XFileReadData
	{
		bool header_parsed;
		std::uint8_t has_no_image_fastfile;
		std::uint8_t has_no_shared_fastfile;
		std::uint8_t unk1;
		char __pad0[4];
		XFileStreamData stream_data;
		std::uint32_t version;
		std::uint32_t shared_ff_hash;
		std::uint32_t shared_ff_count;
		std::uint64_t fileLenUnk1;
		std::uint32_t image_ff_hash;
		std::uint32_t image_ff_count;
		std::uint64_t fileLen;
		std::uint64_t fileLenUnk2;
	}; assert_sizeof(XFileReadData, 224);

	// SoundAssetBank
	struct SndAssetBankHeader
	{
		unsigned int magic;
		unsigned int version;
		unsigned int entrySize;
		unsigned int checksumSize;
		unsigned int dependencySize;
		unsigned int entryCount;
		unsigned int dependencyCount;
		unsigned int buildVersion;
		std::uint64_t fileSize;
		std::uint64_t entryOffset;
		std::uint64_t checksumOffset;
		char checksumChecksum[16];
		char dependencies[512];
		std::uint64_t SourceChecksumOffset;
		std::uint64_t AssetNameOffset;
		char zoneName[64];
		char platform[8];
		char language[3];
		unsigned int convertedAssetVersion;
		unsigned int assetSectionSize;
		char padding[5];
	};

	struct SndAssetBankEntry
	{
		unsigned int id;
		unsigned int size;
		unsigned int seekTableSize;
		unsigned int frameCount;
		unsigned int hybridPcmSize;
		unsigned __int64 offset;
		int frameRate;
		char channelCount;
		char looping;
		char format;
		unsigned __int16 EnvelopeTime1;
		unsigned __int16 EnvelopeTime2;
		char EnvelopeLoudness0;
		char EnvelopeLoudness1;
		char EnvelopeLoudness2;
		char EnvelopeLoudness3;
		char BlocksizeKB;
	};
}

#pragma pop()