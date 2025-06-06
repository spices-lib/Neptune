/**
* @file ShaderCommon.h.
* @brief This Shader Header File Defines Shader Structure both Shader side and C++ side.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#ifndef SHADER_COMMON
#define SHADER_COMMON

#ifdef __cplusplus
#include <glm/glm.hpp>

namespace NeptuneShader
{
using vec2 = glm::vec2;     
using vec3 = glm::vec3;     
using vec4 = glm::vec4;     
using mat4 = glm::mat4;     
using uint = unsigned int; 

#else

#extension GL_EXT_scalar_block_layout                    : enable   /* @brief Enable shader vec3 type memory align.                         */
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require  /* @brief Enable uint64_t type in shader.                               */
#extension GL_EXT_buffer_reference2                      : require  /* @brief Enable Shader Buffer Address access.                          */
#extension GL_EXT_nonuniform_qualifier                   : enable   /* @brief Enable Bindless DescriptorSet dynamic index.                  */
#extension GL_EXT_debug_printf                           : require  /* @brief Enable shader debug info. (debugPrintfEXT("Hello: %d", num);) */

#endif

/**
* @brief Macros for Variable Constant.
*/
const uint BINDLESS_TEXTURE_MAXNUM        = 65535                     ;   /* @brief Maximum number of BindLess Texture Array.             */
const uint BINDLESS_TEXTURE_SET           = 1                         ;   /* @brief BindLess Texture Descriptor Set.                      */
const uint BINDLESS_TEXTURE_BINDING       = 0                         ;   /* @brief BindLess Texture Descriptor Set Binding.              */
const uint MESH_BUFFER_MAXNUM             = 100000                    ;   /* @brief Ray Tracing Renderer Maximum mesh desc buffer count.  */
const uint DIRECTIONALLIGHT_BUFFER_MAXNUM = 100                       ;   /* @brief Maximum number of Directional lights.                 */
const uint POINTLIGHT_BUFFER_MAXNUM       = 10000                     ;   /* @brief Maximum number of Point lights.                       */
const uint MESHLET_NVERTICES              = 64                        ;   /* @brief Maximum number of Meshlet's nVertices.                */
const uint MESHLET_NPRIMITIVES            = 124                       ;   /* @brief Maximum number of Meshlet's nPrimitives.              */
          
const uint NV_SUBGROUP_SIZE               = 32                        ;   /* @brief Nvidia Hardware only support 32 subgroup size.        */
const uint AMD_SUBGROUP_SIZE              = 64                        ;   /* @brief AMD    Hardware only support 64 subgroup size.        */
          
const uint SUBGROUP_SIZE                  = NV_SUBGROUP_SIZE          ;   /* @brief Use Nvidia Hardware.                                  */

const uint POST_BLOOM_MIPMAP              = 5                         ;   /* @brief PostRenderer Bloom mipmap count.                      */

/**
* @brief  Macros for Calculate Constant.
*/
const vec2 invAtan                        = vec2(0.1591, 0.3183)      ;     /* @brief inverse arctan.                                       */
const float PI                            = 3.141592654f              ;     /* @brief PI.                                                   */
const float BIAS                          = 0.01f                     ;     /* @brief small blas.                                           */
const float EPS                           = 1e-6f                     ;     /* @brief small eps.                                            */

/*****************************************************************************************/


/***************************************Vertex********************************************/

/**
* @brief This Struct defines Per Vertex Struct of Mesh.
*/
struct Vertex
{
	vec3 position;            /* @brief Vertex Position in local world. */
	vec3 normal;              /* @brief Vertex Normal.                  */
	vec3 color;               /* @brief Vertex Color.                   */
	vec2 texCoord;            /* @brief Vertex UV.                      */
};

/**
* @brief This Struct defines Per Half Edge Struct of Mesh.
*/
struct HalfEdge
{
	uint first;               /* @brief Half Edge first Vertex index.        */
	uint second;              /* @brief Half Edge second Vertex index.       */
};

/**
* @brief Using Pixel rather than Vertex in shader mey be easier to understand.
* It defines pixel data, not be original vertex data.
*/
#define Pixel Vertex

/**
* @brief GBuffer Data per pixel, for SceneCompose Renderer Fragment Shader use.
*/
struct GBufferPixel
{
	vec3  albedo;              /* @brief Albedo.     */
	vec3  normal;              /* @brief Normal.     */
	float roughness;           /* @brief Roughness.  */
	float metallic;            /* @brief Metallic.   */
	vec3  position;            /* @brief Position.   */
};

/*****************************************************************************************/


/**************************************Material*******************************************/

/**
* @brief This Struct defines PBR Material Attribute.
*/
struct MaterialAttributes
{
	vec3  albedo;              /* @brief Albedo, used for Reflection attenuation.                       */
	float roughness;           /* @brief Roughness, used for Reflection direction.                      */
	float metallic;            /* @brief Metallic, used for                                             */
	vec3  emissive;            /* @brief Emissive, used for Direct illumination.                        */
	vec3  normal;              /* @brief Normal, used for light effect.                                 */
	uint  maxRayDepth;         /* @brief Max Ray Tracing Depth, defined specific from material.         */
	uint  maxLightDepth;       /* @brief Max Ray Tracing Light Depth, defined specific from material.   */
	uint  maxShadowDepth;      /* @brief Max Ray Tracing Shadow Depth, defined specific from material.  */
};

/*****************************************************************************************/


/*************************************Pre Renderer Data***********************************/

/**
* @brief Global View Struct.
*/
struct View 
{
	mat4  projection;          /* @brief Projection Matrix from major Camera Entity.                   */
	mat4  nprojection;         /* @brief Negative y axis Projection Matrix from major Camera Entity.   */
	mat4  view;                /* @brief View Matrix from major Camera Entity.                         */
	mat4  inView;              /* @brief Inverse View Matrix from major Camera Entity.                 */
	vec4  sceneTextureSize;    /* @brief Scene Texture Size.                                           */
	vec4  windowSize;          /* @brief Application Window Size.                                      */
	uint  stableFrames;        /* @brief Camera Stable Frames Number.                                  */
	float fov;                 /* @brief Camera Radians fov.                                           */
};

/**
* @brief Application Inout Struct.
*/
struct Input
{
	vec4  mousePos;            /* @brief Mouse Position and inverse position. */
	float gameTime;            /* @brief Application Run time since start.    */
	float frameTime;           /* @brief Duration time since last frame.      */
};

/*****************************************************************************************/


/******************************************Light Data*************************************/

/**
* @brief This struct defines DirectionalLight data.
*/
struct DirectionalLight
{
	mat4  rotationMatrix;      /* @brief Rotation of SunLight.   */
	vec3  color;               /* @brief Color of SunLight.      */
	float intensity;           /* @brief Intensity of SunLight.  */
};

/**
* @brief This struct defines PointLight data.
*/
struct PointLight
{
	vec3  position;            /* @brief World Position of PointLight. */
	vec3  color;               /* @brief Color of PointLight.          */
	float intensity;           /* @brief Intensity of PointLight.      */
	float constantf;           /* @brief Constantf of PointLight.      */
	float linear;              /* @brief Linear of PointLight.         */
	float quadratic;           /* @brief Quadratic of PointLight.      */
};

/*****************************************************************************************/


/*********************************RayTracing Renderer Data********************************/

/**
* @brief Mesh Description Struct.
*/
struct MeshDesc
{
	uint64_t modelAddress;                    /* @brief Address of the Model Matrix.                      */																									  
	uint64_t positionsAddress;                /* @brief Address of the Positions buffer.                  */
	uint64_t normalsAddress;                  /* @brief Address of the Normals buffer.                    */
	uint64_t colorsAddress;                   /* @brief Address of the Colors buffer.                     */
	uint64_t texCoordsAddress;                /* @brief Address of the TexCoords buffer.                  */
	uint64_t verticesAddress;                 /* @brief Address of the Vertices buffer.                   */
	uint64_t primitivePointsAddress;          /* @brief Address of the PrimitivePoints buffer.            */
	uint64_t primitiveVerticesAddress;        /* @brief Address of the PrimitiveVertices buffer.          */
	uint64_t primitiveLocationsAddress;       /* @brief Address of the PrimitiveLocationsAddress buffer.  */
	uint64_t materialParameterAddress;        /* @brief Address of the Material Parameter buffer.         */
	uint64_t meshletsAddress;                 /* @brief Address of the Meshlet Buffer.                    */
	uint     nMeshlets;                       /* @brief Meshlets Count.                                   */
	uint     entityID;                        /* @brief EntityId, cast from entt::entity.                 */
};

/**
* @brief Ray Tracing Shader Data Location 0. 
*/
struct HitPayLoad
{
	vec3  hitValue;                  /* @brief Current Hit Fragment Color.                                                */
	uint  seed;                      /* @brief Random Seed for BRDF Lambertian Light Reflection Direction Select.         */
	uint  rayDepth;                  /* @brief Ray Tracing Depth for diffuse.                                             */
	vec3  rayOrigin;                 /* @brief Next Ray Original World Position.                                          */
	vec3  rayDirection;              /* @brief Next Ray Direction in World Space.                                         */
	vec3  weight;                    /* @brief Current Fragment Color Weight.                                             */
	uint  maxRayDepth;               /* @brief Max Ray Tracing Depth, defined specific from material.                     */
	uint  entityID;                  /* @brief Entity ID from Closest Hit to Ray Gen Shader to RayEntityID Image.         */
	uint  triangleID;                /* @brief Triangle ID from Closest Hit to Ray Gen Shader to RayTriangleID Image.     */
	float depth;                     /* @brief Hit point depth to camera.                                                 */
};

/*****************************************************************************************/


/*********************************************Mesh***************************************/

/**
* @brief Sphere Struct.
*/
struct Sphere
{
	vec3  c;                                          /* @brief Center of Bound Sphere.                 */
	float r;                                          /* @brief Radius of Bound Sphere.                 */
};

/**
* @brief Bound AABB Struct.
*/
struct AABB
{
	vec3 min;                                         /* @brief Min of Bound AABB.                 */    
	vec3 max;                                         /* @brief Max of Bound AABB.                 */
};

/**
* @brief Meshlet Structure Data.
*/
struct Meshlet
{
	uint    vertexOffset;                        /* @brief Offset of Vertices this meshlet.        */
	uint    primitiveOffset;                     /* @brief Offset of primitives this meshlet.      */
	uint    nVertices;                           /* @brief Vertices Count this meshlet.( <= 64)    */
	uint    nPrimitives;                         /* @brief Primitives Count this meshlet.( <= 126) */
	uint    lod;                                 /* @brief Current meshlet lod level.              */
	Sphere  boundSphere;                         /* @brief Bounding Sphere in local world.         */
	Sphere  clusterBoundSphere;                  /* @brief Cluster Bounding Sphere in local world. */
	vec3    coneApex;                            /* @brief Normal Cone center.                     */
	vec3    coneAxis;                            /* @brief Normal Cone axis.                       */
	float   coneCutoff;                          /* @brief Normal Cone cutoff rate.                */
};

/*****************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif