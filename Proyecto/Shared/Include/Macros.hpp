#pragma once

#include "Types.hpp"

#undef min
#undef max

#define MIN_VEC1  numeric_limits<vec1 >::min()
#define MAX_VEC1  numeric_limits<vec1 >::max()
#define MIN_DVEC1 numeric_limits<dvec1>::min()
#define MAX_DVEC1 numeric_limits<dvec1>::max()

#define MIN_INT8  numeric_limits<int8 >::min()
#define MAX_INT8  numeric_limits<int8 >::max()
#define MIN_INT16 numeric_limits<int16>::min()
#define MAX_INT16 numeric_limits<int16>::max()
#define MIN_INT32 numeric_limits<int32>::min()
#define MAX_INT32 numeric_limits<int32>::max()
#define MIN_INT64 numeric_limits<int64>::min()
#define MAX_INT64 numeric_limits<int64>::max()

#define MAX_UINT8  numeric_limits<uint8 >::max()
#define MAX_UINT16 numeric_limits<uint16>::max()
#define MAX_UINT32 numeric_limits<uint32>::max()
#define MAX_UINT64 numeric_limits<uint64>::max()

#define PI          3.141592653589793
#define TWO_PI      6.283185307179586
#define INVERTED_PI 0.318309886183791
#define DEG_RAD     0.017453292519943
#define RAD_DEG     57.29577951308232
#define EULER       2.718281828459045
#define PHI         1.618033988749895
#define FPS_60      0.016666666666667
#define MAX_DIST    10000.0
#define EPSILON     0.00001