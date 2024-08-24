#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/spline.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

typedef std::byte      Byte;
typedef vector<Byte>   Byte_Array;
typedef vector<string> Tokens;
typedef vector<Tokens> Token_Array;

// FLOATING

typedef double     dvec1; // 64-bits | min: 2.2250738585072014e-308 | max: 1.7976931348623158e+308
typedef glm::dvec2 dvec2; // 128-bits
typedef glm::dvec3 dvec3; // 196-bits
typedef glm::dvec4 dvec4; // 256-bits
typedef glm::dquat dquat; // 256-bits
typedef glm::dmat2 dmat2; // 256-bits
typedef glm::dmat3 dmat3; // 576-bits
typedef glm::dmat4 dmat4; // 1024-bits

typedef float     vec1; // 32-bits | min: 1.175494351e-38f | max: 3.402823466e+38f
typedef glm::vec2 vec2; // 64-bits
typedef glm::vec3 vec3; // 96-bits
typedef glm::vec4 vec4; // 128-bits
typedef glm::quat quat; // 128-bits
typedef glm::mat2 mat2; // 128-bits
typedef glm::mat3 mat3; // 288-bits
typedef glm::mat4 mat4; // 512-bits

// INT

typedef int8_t              int8; // min: -128 | max: 127
typedef int16_t            int16; // min: -32'768 | max: 32'767
typedef int32_t            int32; // min: -2'147'483'648 | max: 2'147'483'647
typedef int64_t            int64; // min: -9'223'372'036'854'775'808 | max: 9'223'372'036'854'775'807

typedef int8              isvec1; // 8-bits
typedef glm::tvec2<int8>  isvec2; // 16-bits
typedef glm::tvec3<int8>  isvec3; // 24-bits
typedef glm::tvec4<int8>  isvec4; // 32-bits

typedef int16             ihvec1; // 16-bits
typedef glm::tvec2<int16> ihvec2; // 32-bits
typedef glm::tvec3<int16> ihvec3; // 48-bits
typedef glm::tvec4<int16> ihvec4; // 64-bits

typedef int32              ivec1; // 32-bits
typedef glm::ivec2         ivec2; // 64-bits
typedef glm::ivec3         ivec3; // 96-bits
typedef glm::ivec4         ivec4; // 128-bits

typedef int64             ilvec1; // 64-bits
typedef glm::tvec2<int64> ilvec2; // 128-bits
typedef glm::tvec3<int64> ilvec3; // 192-bits
typedef glm::tvec4<int64> ilvec4; // 256-bits

// UINT

typedef uint32_t             uint; //max: 4'294'967'295
typedef uint8_t             uint8; //max: 255
typedef uint16_t           uint16; //max: 65'535
typedef uint32_t           uint32; //max: 4'294'967'295
typedef uint64_t           uint64; //max: 18'446'744'073'709'551'615

typedef uint8              usvec1; // 8-bits
typedef glm::tvec2<uint8>  usvec2; // 16-bits
typedef glm::tvec3<uint8>  usvec3; // 24-bits
typedef glm::tvec4<uint8>  usvec4; // 32-bits

typedef uint16             uhvec1; // 16-bits
typedef glm::tvec2<uint16> uhvec2; // 32-bits
typedef glm::tvec3<uint16> uhvec3; // 48-bits
typedef glm::tvec4<uint16> uhvec4; // 64-bits

typedef uint32              uvec1; // 32-bits
typedef glm::uvec2          uvec2; // 64-bits
typedef glm::uvec3          uvec3; // 96-bits
typedef glm::uvec4          uvec4; // 128-bits

typedef uint64             ulvec1; // 64-bits
typedef glm::tvec2<uint64> ulvec2; // 128-bits
typedef glm::tvec3<uint64> ulvec3; // 192-bits
typedef glm::tvec4<uint64> ulvec4; // 256-bits