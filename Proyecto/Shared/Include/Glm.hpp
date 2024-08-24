#pragma once

#include "Types.hpp"

// FLOATING

inline dvec1  f_to_d (const vec1& val) { return static_cast<dvec1>  (val); }
inline dvec2  f_to_d (const vec2& val) { return static_cast<dvec2>  (val); }
inline dvec3  f_to_d (const vec3& val) { return static_cast<dvec3>  (val); }
inline dvec4  f_to_d (const vec4& val) { return static_cast<dvec4>  (val); }
inline dquat  f_to_d (const quat& val) { return static_cast<dquat>  (val); }
inline dmat2  f_to_d (const mat2& val) { return static_cast<dmat2>  (val); }
inline dmat3  f_to_d (const mat3& val) { return static_cast<dmat3>  (val); }
inline dmat4  f_to_d (const mat4& val) { return static_cast<dmat4>  (val); }

inline isvec1 f_to_is(const vec1& val) { return static_cast<isvec1> (val); }
inline isvec2 f_to_is(const vec2& val) { return static_cast<isvec2> (val); }
inline isvec3 f_to_is(const vec3& val) { return static_cast<isvec3> (val); }
inline isvec4 f_to_is(const vec4& val) { return static_cast<isvec4> (val); }
inline ihvec1 f_to_ih(const vec1& val) { return static_cast<ihvec1> (val); }
inline ihvec2 f_to_ih(const vec2& val) { return static_cast<ihvec2> (val); }
inline ihvec3 f_to_ih(const vec3& val) { return static_cast<ihvec3> (val); }
inline ihvec4 f_to_ih(const vec4& val) { return static_cast<ihvec4> (val); }
inline ivec1  f_to_i (const vec1& val) { return static_cast<ivec1>  (val); }
inline ivec2  f_to_i (const vec2& val) { return static_cast<ivec2>  (val); }
inline ivec3  f_to_i (const vec3& val) { return static_cast<ivec3>  (val); }
inline ivec4  f_to_i (const vec4& val) { return static_cast<ivec4>  (val); }
inline ilvec1 f_to_il(const vec1& val) { return static_cast<ilvec1> (val); }
inline ilvec2 f_to_il(const vec2& val) { return static_cast<ilvec2> (val); }
inline ilvec3 f_to_il(const vec3& val) { return static_cast<ilvec3> (val); }
inline ilvec4 f_to_il(const vec4& val) { return static_cast<ilvec4> (val); }

inline usvec1 f_to_us(const vec1& val) { return static_cast<usvec1> (val); }
inline usvec2 f_to_us(const vec2& val) { return static_cast<usvec2> (val); }
inline usvec3 f_to_us(const vec3& val) { return static_cast<usvec3> (val); }
inline usvec4 f_to_us(const vec4& val) { return static_cast<usvec4> (val); }
inline uhvec1 f_to_uh(const vec1& val) { return static_cast<uhvec1> (val); }
inline uhvec2 f_to_uh(const vec2& val) { return static_cast<uhvec2> (val); }
inline uhvec3 f_to_uh(const vec3& val) { return static_cast<uhvec3> (val); }
inline uhvec4 f_to_uh(const vec4& val) { return static_cast<uhvec4> (val); }
inline uvec1  f_to_u (const vec1& val) { return static_cast<uvec1>  (val); }
inline uvec2  f_to_u (const vec2& val) { return static_cast<uvec2>  (val); }
inline uvec3  f_to_u (const vec3& val) { return static_cast<uvec3>  (val); }
inline uvec4  f_to_u (const vec4& val) { return static_cast<uvec4>  (val); }
inline ulvec1 f_to_ul(const vec1& val) { return static_cast<ulvec1> (val); }
inline ulvec2 f_to_ul(const vec2& val) { return static_cast<ulvec2> (val); }
inline ulvec3 f_to_ul(const vec3& val) { return static_cast<ulvec3> (val); }
inline ulvec4 f_to_ul(const vec4& val) { return static_cast<ulvec4> (val); }

inline vec1   d_to_f (const dvec1& val) { return static_cast<vec1>  (val); }
inline vec2   d_to_f (const dvec2& val) { return static_cast<vec2>  (val); }
inline vec3   d_to_f (const dvec3& val) { return static_cast<vec3>  (val); }
inline vec4   d_to_f (const dvec4& val) { return static_cast<vec4>  (val); }
inline quat   d_to_f (const dquat& val) { return static_cast<quat>  (val); }
inline mat2   d_to_f (const dmat2& val) { return static_cast<mat2>  (val); }
inline mat3   d_to_f (const dmat3& val) { return static_cast<mat3>  (val); }
inline mat4   d_to_f (const dmat4& val) { return static_cast<mat4>  (val); }

inline isvec1 d_to_is(const dvec1& val) { return static_cast<isvec1>(val); }
inline isvec2 d_to_is(const dvec2& val) { return static_cast<isvec2>(val); }
inline isvec3 d_to_is(const dvec3& val) { return static_cast<isvec3>(val); }
inline isvec4 d_to_is(const dvec4& val) { return static_cast<isvec4>(val); }
inline ihvec1 d_to_ih(const dvec1& val) { return static_cast<ihvec1>(val); }
inline ihvec2 d_to_ih(const dvec2& val) { return static_cast<ihvec2>(val); }
inline ihvec3 d_to_ih(const dvec3& val) { return static_cast<ihvec3>(val); }
inline ihvec4 d_to_ih(const dvec4& val) { return static_cast<ihvec4>(val); }
inline ivec1  d_to_i (const dvec1& val) { return static_cast<ivec1> (val); }
inline ivec2  d_to_i (const dvec2& val) { return static_cast<ivec2> (val); }
inline ivec3  d_to_i (const dvec3& val) { return static_cast<ivec3> (val); }
inline ivec4  d_to_i (const dvec4& val) { return static_cast<ivec4> (val); }
inline ilvec1 d_to_il(const dvec1& val) { return static_cast<ilvec1>(val); }
inline ilvec2 d_to_il(const dvec2& val) { return static_cast<ilvec2>(val); }
inline ilvec3 d_to_il(const dvec3& val) { return static_cast<ilvec3>(val); }
inline ilvec4 d_to_il(const dvec4& val) { return static_cast<ilvec4>(val); }

inline usvec1 d_to_us(const dvec1& val) { return static_cast<usvec1>(val); }
inline usvec2 d_to_us(const dvec2& val) { return static_cast<usvec2>(val); }
inline usvec3 d_to_us(const dvec3& val) { return static_cast<usvec3>(val); }
inline usvec4 d_to_us(const dvec4& val) { return static_cast<usvec4>(val); }
inline uhvec1 d_to_uh(const dvec1& val) { return static_cast<uhvec1>(val); }
inline uhvec2 d_to_uh(const dvec2& val) { return static_cast<uhvec2>(val); }
inline uhvec3 d_to_uh(const dvec3& val) { return static_cast<uhvec3>(val); }
inline uhvec4 d_to_uh(const dvec4& val) { return static_cast<uhvec4>(val); }
inline uvec1  d_to_u (const dvec1& val) { return static_cast<uvec1> (val); }
inline uvec2  d_to_u (const dvec2& val) { return static_cast<uvec2> (val); }
inline uvec3  d_to_u (const dvec3& val) { return static_cast<uvec3> (val); }
inline uvec4  d_to_u (const dvec4& val) { return static_cast<uvec4> (val); }
inline ulvec1 d_to_ul(const dvec1& val) { return static_cast<ulvec1>(val); }
inline ulvec2 d_to_ul(const dvec2& val) { return static_cast<ulvec2>(val); }
inline ulvec3 d_to_ul(const dvec3& val) { return static_cast<ulvec3>(val); }
inline ulvec4 d_to_ul(const dvec4& val) { return static_cast<ulvec4>(val); }

// INT

inline ivec1  il_to_i (const ilvec1& val) { return static_cast<ivec1> (val); }
inline ihvec1 il_to_ih(const ilvec1& val) { return static_cast<ihvec1>(val); }
inline isvec1 il_to_is(const ilvec1& val) { return static_cast<isvec1>(val); }
inline ivec2  il_to_i (const ilvec2& val) { return static_cast<ivec2> (val); }
inline ihvec2 il_to_ih(const ilvec2& val) { return static_cast<ihvec2>(val); }
inline isvec2 il_to_is(const ilvec2& val) { return static_cast<isvec2>(val); }
inline ivec3  il_to_i (const ilvec3& val) { return static_cast<ivec3> (val); }
inline ihvec3 il_to_ih(const ilvec3& val) { return static_cast<ihvec3>(val); }
inline isvec3 il_to_is(const ilvec3& val) { return static_cast<isvec3>(val); }
inline ivec4  il_to_i (const ilvec4& val) { return static_cast<ivec4> (val); }
inline ihvec4 il_to_ih(const ilvec4& val) { return static_cast<ihvec4>(val); }
inline isvec4 il_to_is(const ilvec4& val) { return static_cast<isvec4>(val); }

inline ilvec1 i_to_il (const ivec1& val)  { return static_cast<ilvec1>(val); }
inline ihvec1 i_to_ih (const ivec1& val)  { return static_cast<ihvec1>(val); }
inline isvec1 i_to_is (const ivec1& val)  { return static_cast<isvec1>(val); }
inline ilvec2 i_to_il (const ivec2& val)  { return static_cast<ilvec2>(val); }
inline ihvec2 i_to_ih (const ivec2& val)  { return static_cast<ihvec2>(val); }
inline isvec2 i_to_is (const ivec2& val)  { return static_cast<isvec2>(val); }
inline ilvec3 i_to_il (const ivec3& val)  { return static_cast<ilvec3>(val); }
inline ihvec3 i_to_ih (const ivec3& val)  { return static_cast<ihvec3>(val); }
inline isvec3 i_to_is (const ivec3& val)  { return static_cast<isvec3>(val); }
inline ilvec4 i_to_il (const ivec4& val)  { return static_cast<ilvec4>(val); }
inline ihvec4 i_to_ih (const ivec4& val)  { return static_cast<ihvec4>(val); }
inline isvec4 i_to_is (const ivec4& val)  { return static_cast<isvec4>(val); }

inline ilvec1 ih_to_il(const ihvec1& val) { return static_cast<ilvec1>(val); }
inline ivec1  ih_to_i (const ihvec1& val) { return static_cast<ivec1> (val); }
inline isvec1 ih_to_is(const ihvec1& val) { return static_cast<isvec1>(val); }
inline ilvec2 ih_to_il(const ihvec2& val) { return static_cast<ilvec2>(val); }
inline ivec2  ih_to_i (const ihvec2& val) { return static_cast<ivec2> (val); }
inline isvec2 ih_to_is(const ihvec2& val) { return static_cast<isvec2>(val); }
inline ilvec3 ih_to_il(const ihvec3& val) { return static_cast<ilvec3>(val); }
inline ivec3  ih_to_i (const ihvec3& val) { return static_cast<ivec3> (val); }
inline isvec3 ih_to_is(const ihvec3& val) { return static_cast<isvec3>(val); }
inline ilvec4 ih_to_il(const ihvec4& val) { return static_cast<ilvec4>(val); }
inline ivec4  ih_to_i (const ihvec4& val) { return static_cast<ivec4> (val); }
inline isvec4 ih_to_is(const ihvec4& val) { return static_cast<isvec4>(val); }

inline ilvec1 is_to_il(const isvec1& val) { return static_cast<ilvec1>(val); }
inline ivec1  is_to_i (const isvec1& val) { return static_cast<ivec1> (val); }
inline ihvec1 is_to_ih(const isvec1& val) { return static_cast<ihvec1>(val); }
inline ilvec2 is_to_il(const isvec2& val) { return static_cast<ilvec2>(val); }
inline ivec2  is_to_i (const isvec2& val) { return static_cast<ivec2> (val); }
inline ihvec2 is_to_ih(const isvec2& val) { return static_cast<ihvec2>(val); }
inline ilvec3 is_to_il(const isvec3& val) { return static_cast<ilvec3>(val); }
inline ivec3  is_to_i (const isvec3& val) { return static_cast<ivec3> (val); }
inline ihvec3 is_to_ih(const isvec3& val) { return static_cast<ihvec3>(val); }
inline ilvec4 is_to_il(const isvec4& val) { return static_cast<ilvec4>(val); }
inline ivec4  is_to_i (const isvec4& val) { return static_cast<ivec4> (val); }
inline ihvec4 is_to_ih(const isvec4& val) { return static_cast<ihvec4>(val); }

inline ulvec1 il_to_ul(const ilvec1& val) { return static_cast<ulvec1>(val); }
inline uvec1  il_to_u (const ilvec1& val) { return static_cast<uvec1> (val); }
inline uhvec1 il_to_uh(const ilvec1& val) { return static_cast<uhvec1>(val); }
inline usvec1 il_to_us(const ilvec1& val) { return static_cast<usvec1>(val); }
inline uvec2  il_to_u (const ilvec2& val) { return static_cast<uvec2> (val); }
inline uhvec2 il_to_uh(const ilvec2& val) { return static_cast<uhvec2>(val); }
inline usvec2 il_to_us(const ilvec2& val) { return static_cast<usvec2>(val); }
inline ulvec2 il_to_ul(const ilvec2& val) { return static_cast<ulvec2>(val); }
inline uvec3  il_to_u (const ilvec3& val) { return static_cast<uvec3> (val); }
inline uhvec3 il_to_uh(const ilvec3& val) { return static_cast<uhvec3>(val); }
inline usvec3 il_to_us(const ilvec3& val) { return static_cast<usvec3>(val); }
inline ulvec3 il_to_ul(const ilvec3& val) { return static_cast<ulvec3>(val); }
inline uvec4  il_to_u (const ilvec4& val) { return static_cast<uvec4> (val); }
inline uhvec4 il_to_uh(const ilvec4& val) { return static_cast<uhvec4>(val); }
inline usvec4 il_to_us(const ilvec4& val) { return static_cast<usvec4>(val); }
inline ulvec4 il_to_ul(const ilvec4& val) { return static_cast<ulvec4>(val); }

inline ulvec1 i_to_ul (const ivec1& val)  { return static_cast<ulvec1>(val); }
inline uvec1  i_to_u  (const ivec1& val)  { return static_cast<uvec1> (val); }
inline uhvec1 i_to_uh (const ivec1& val)  { return static_cast<uhvec1>(val); }
inline usvec1 i_to_us (const ivec1& val)  { return static_cast<usvec1>(val); }
inline ulvec2 i_to_ul (const ivec2& val)  { return static_cast<ulvec2>(val); }
inline uvec2  i_to_u  (const ivec2& val)  { return static_cast<uvec2> (val); }
inline uhvec2 i_to_uh (const ivec2& val)  { return static_cast<uhvec2>(val); }
inline usvec2 i_to_us (const ivec2& val)  { return static_cast<usvec2>(val); }
inline ulvec3 i_to_ul (const ivec3& val)  { return static_cast<ulvec3>(val); }
inline uvec3  i_to_u  (const ivec3& val)  { return static_cast<uvec3> (val); }
inline uhvec3 i_to_uh (const ivec3& val)  { return static_cast<uhvec3>(val); }
inline usvec3 i_to_us (const ivec3& val)  { return static_cast<usvec3>(val); }
inline ulvec4 i_to_ul (const ivec4& val)  { return static_cast<ulvec4>(val); }
inline uvec4  i_to_u  (const ivec4& val)  { return static_cast<uvec4> (val); }
inline uhvec4 i_to_uh (const ivec4& val)  { return static_cast<uhvec4>(val); }
inline usvec4 i_to_us (const ivec4& val)  { return static_cast<usvec4>(val); }

inline ulvec1 ih_to_ul(const ihvec1& val) { return static_cast<ulvec1>(val); }
inline uvec1  ih_to_u (const ihvec1& val) { return static_cast<uvec1> (val); }
inline uhvec1 ih_to_uh(const ihvec1& val) { return static_cast<uhvec1>(val); }
inline usvec1 ih_to_us(const ihvec1& val) { return static_cast<usvec1>(val); }
inline ulvec2 ih_to_ul(const ihvec2& val) { return static_cast<ulvec2>(val); }
inline uvec2  ih_to_u (const ihvec2& val) { return static_cast<uvec2> (val); }
inline uhvec2 ih_to_uh(const ihvec2& val) { return static_cast<uhvec2>(val); }
inline usvec2 ih_to_us(const ihvec2& val) { return static_cast<usvec2>(val); }
inline ulvec3 ih_to_ul(const ihvec3& val) { return static_cast<ulvec3>(val); }
inline uvec3  ih_to_u (const ihvec3& val) { return static_cast<uvec3> (val); }
inline uhvec3 ih_to_uh(const ihvec3& val) { return static_cast<uhvec3>(val); }
inline usvec3 ih_to_us(const ihvec3& val) { return static_cast<usvec3>(val); }
inline ulvec4 ih_to_ul(const ihvec4& val) { return static_cast<ulvec4>(val); }
inline uvec4  ih_to_u (const ihvec4& val) { return static_cast<uvec4> (val); }
inline uhvec4 ih_to_uh(const ihvec4& val) { return static_cast<uhvec4>(val); }
inline usvec4 ih_to_us(const ihvec4& val) { return static_cast<usvec4>(val); }

inline ulvec1 is_to_ul(const isvec1& val) { return static_cast<ulvec1>(val); }
inline uvec1  is_to_u (const isvec1& val) { return static_cast<uvec1> (val); }
inline uhvec1 is_to_uh(const isvec1& val) { return static_cast<uhvec1>(val); }
inline usvec1 is_to_us(const isvec1& val) { return static_cast<usvec1>(val); }
inline ulvec2 is_to_ul(const isvec2& val) { return static_cast<ulvec2>(val); }
inline uvec2  is_to_u (const isvec2& val) { return static_cast<uvec2> (val); }
inline uhvec2 is_to_uh(const isvec2& val) { return static_cast<uhvec2>(val); }
inline usvec2 is_to_us(const isvec2& val) { return static_cast<usvec2>(val); }
inline ulvec3 is_to_ul(const isvec3& val) { return static_cast<ulvec3>(val); }
inline uvec3  is_to_u (const isvec3& val) { return static_cast<uvec3> (val); }
inline uhvec3 is_to_uh(const isvec3& val) { return static_cast<uhvec3>(val); }
inline usvec3 is_to_us(const isvec3& val) { return static_cast<usvec3>(val); }
inline ulvec4 is_to_ul(const isvec4& val) { return static_cast<ulvec4>(val); }
inline uvec4  is_to_u (const isvec4& val) { return static_cast<uvec4> (val); }
inline uhvec4 is_to_uh(const isvec4& val) { return static_cast<uhvec4>(val); }
inline usvec4 is_to_us(const isvec4& val) { return static_cast<usvec4>(val); }

inline vec1  il_to_f(const ilvec1& val) { return static_cast<vec1> (val); }
inline vec2  il_to_f(const ilvec2& val) { return static_cast<vec2> (val); }
inline vec3  il_to_f(const ilvec3& val) { return static_cast<vec3> (val); }
inline vec4  il_to_f(const ilvec4& val) { return static_cast<vec4> (val); }

inline dvec1 il_to_d(const ilvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 il_to_d(const ilvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 il_to_d(const ilvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 il_to_d(const ilvec4& val) { return static_cast<dvec4>(val); }

inline vec1  i_to_f (const ivec1& val)  { return static_cast<vec1> (val); }
inline vec2  i_to_f (const ivec2& val)  { return static_cast<vec2> (val); }
inline vec3  i_to_f (const ivec3& val)  { return static_cast<vec3> (val); }
inline vec4  i_to_f (const ivec4& val)  { return static_cast<vec4> (val); }

inline dvec1 i_to_d (const ivec1& val)  { return static_cast<dvec1>(val); }
inline dvec2 i_to_d (const ivec2& val)  { return static_cast<dvec2>(val); }
inline dvec3 i_to_d (const ivec3& val)  { return static_cast<dvec3>(val); }
inline dvec4 i_to_d (const ivec4& val)  { return static_cast<dvec4>(val); }

inline vec1  ih_to_f(const ihvec1& val) { return static_cast<vec1> (val); }
inline vec2  ih_to_f(const ihvec2& val) { return static_cast<vec2> (val); }
inline vec3  ih_to_f(const ihvec3& val) { return static_cast<vec3> (val); }
inline vec4  ih_to_f(const ihvec4& val) { return static_cast<vec4> (val); }

inline dvec1 ih_to_d(const ihvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 ih_to_d(const ihvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 ih_to_d(const ihvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 ih_to_d(const ihvec4& val) { return static_cast<dvec4>(val); }

inline vec1  is_to_f(const isvec1& val) { return static_cast<vec1> (val); }
inline vec2  is_to_f(const isvec2& val) { return static_cast<vec2> (val); }
inline vec3  is_to_f(const isvec3& val) { return static_cast<vec3> (val); }
inline vec4  is_to_f(const isvec4& val) { return static_cast<vec4> (val); }

inline dvec1 is_to_d(const isvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 is_to_d(const isvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 is_to_d(const isvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 is_to_d(const isvec4& val) { return static_cast<dvec4>(val); }

// UINT

inline uvec1  ul_to_u (const ulvec1& val) { return static_cast<uvec1> (val); }
inline uhvec1 ul_to_uh(const ulvec1& val) { return static_cast<uhvec1>(val); }
inline usvec1 ul_to_us(const ulvec1& val) { return static_cast<usvec1>(val); }
inline uvec2  ul_to_u (const ulvec2& val) { return static_cast<uvec2> (val); }
inline uhvec2 ul_to_uh(const ulvec2& val) { return static_cast<uhvec2>(val); }
inline usvec2 ul_to_us(const ulvec2& val) { return static_cast<usvec2>(val); }
inline uvec3  ul_to_u (const ulvec3& val) { return static_cast<uvec3> (val); }
inline uhvec3 ul_to_uh(const ulvec3& val) { return static_cast<uhvec3>(val); }
inline usvec3 ul_to_us(const ulvec3& val) { return static_cast<usvec3>(val); }
inline uvec4  ul_to_u (const ulvec4& val) { return static_cast<uvec4> (val); }
inline uhvec4 ul_to_uh(const ulvec4& val) { return static_cast<uhvec4>(val); }
inline usvec4 ul_to_us(const ulvec4& val) { return static_cast<usvec4>(val); }

inline ulvec1 u_to_ul (const uvec1& val)  { return static_cast<ulvec1>(val); }
inline uhvec1 u_to_uh (const uvec1& val)  { return static_cast<uhvec1>(val); }
inline usvec1 u_to_us (const uvec1& val)  { return static_cast<usvec1>(val); }
inline ulvec2 u_to_ul (const uvec2& val)  { return static_cast<ulvec2>(val); }
inline uhvec2 u_to_uh (const uvec2& val)  { return static_cast<uhvec2>(val); }
inline usvec2 u_to_us (const uvec2& val)  { return static_cast<usvec2>(val); }
inline ulvec3 u_to_ul (const uvec3& val)  { return static_cast<ulvec3>(val); }
inline uhvec3 u_to_uh (const uvec3& val)  { return static_cast<uhvec3>(val); }
inline usvec3 u_to_us (const uvec3& val)  { return static_cast<usvec3>(val); }
inline ulvec4 u_to_ul (const uvec4& val)  { return static_cast<ulvec4>(val); }
inline uhvec4 u_to_uh (const uvec4& val)  { return static_cast<uhvec4>(val); }
inline usvec4 u_to_us (const uvec4& val)  { return static_cast<usvec4>(val); }

inline ulvec1 uh_to_ul(const uhvec1& val) { return static_cast<ulvec1>(val); }
inline uvec1  uh_to_u (const uhvec1& val) { return static_cast<uvec1> (val); }
inline usvec1 uh_to_us(const uhvec1& val) { return static_cast<usvec1>(val); }
inline ulvec2 uh_to_ul(const uhvec2& val) { return static_cast<ulvec2>(val); }
inline uvec2  uh_to_u (const uhvec2& val) { return static_cast<uvec2> (val); }
inline usvec2 uh_to_us(const uhvec2& val) { return static_cast<usvec2>(val); }
inline ulvec3 uh_to_ul(const uhvec3& val) { return static_cast<ulvec3>(val); }
inline uvec3  uh_to_u (const uhvec3& val) { return static_cast<uvec3> (val); }
inline usvec3 uh_to_us(const uhvec3& val) { return static_cast<usvec3>(val); }
inline ulvec4 uh_to_ul(const uhvec4& val) { return static_cast<ulvec4>(val); }
inline uvec4  uh_to_u (const uhvec4& val) { return static_cast<uvec4> (val); }
inline usvec4 uh_to_us(const uhvec4& val) { return static_cast<usvec4>(val); }

inline ulvec1 us_to_ul(const usvec1& val) { return static_cast<ulvec1>(val); }
inline uvec1  us_to_u (const usvec1& val) { return static_cast<uvec1> (val); }
inline uhvec1 us_to_uh(const usvec1& val) { return static_cast<uhvec1>(val); }
inline ulvec2 us_to_ul(const usvec2& val) { return static_cast<ulvec2>(val); }
inline uvec2  us_to_u (const usvec2& val) { return static_cast<uvec2> (val); }
inline uhvec2 us_to_uh(const usvec2& val) { return static_cast<uhvec2>(val); }
inline ulvec3 us_to_ul(const usvec3& val) { return static_cast<ulvec3>(val); }
inline uvec3  us_to_u (const usvec3& val) { return static_cast<uvec3> (val); }
inline uhvec3 us_to_uh(const usvec3& val) { return static_cast<uhvec3>(val); }
inline ulvec4 us_to_ul(const usvec4& val) { return static_cast<ulvec4>(val); }
inline uvec4  us_to_u (const usvec4& val) { return static_cast<uvec4> (val); }
inline uhvec4 us_to_uh(const usvec4& val) { return static_cast<uhvec4>(val); }

inline ilvec1 ul_to_il(const ulvec1& val) { return static_cast<ilvec1>(val); }
inline ivec1  ul_to_i (const ulvec1& val) { return static_cast<ivec1> (val); }
inline ihvec1 ul_to_ih(const ulvec1& val) { return static_cast<ihvec1>(val); }
inline isvec1 ul_to_is(const ulvec1& val) { return static_cast<isvec1>(val); }
inline ivec2  ul_to_i (const ulvec2& val) { return static_cast<ivec2> (val); }
inline ihvec2 ul_to_ih(const ulvec2& val) { return static_cast<ihvec2>(val); }
inline isvec2 ul_to_is(const ulvec2& val) { return static_cast<isvec2>(val); }
inline ilvec2 ul_to_il(const ulvec2& val) { return static_cast<ilvec2>(val); }
inline ivec3  ul_to_i (const ulvec3& val) { return static_cast<ivec3> (val); }
inline ihvec3 ul_to_ih(const ulvec3& val) { return static_cast<ihvec3>(val); }
inline isvec3 ul_to_is(const ulvec3& val) { return static_cast<isvec3>(val); }
inline ilvec3 ul_to_il(const ulvec3& val) { return static_cast<ilvec3>(val); }
inline ivec4  ul_to_i (const ulvec4& val) { return static_cast<ivec4> (val); }
inline ihvec4 ul_to_ih(const ulvec4& val) { return static_cast<ihvec4>(val); }
inline isvec4 ul_to_is(const ulvec4& val) { return static_cast<isvec4>(val); }
inline ilvec4 ul_to_il(const ulvec4& val) { return static_cast<ilvec4>(val); }

inline ilvec1 u_to_il (const uvec1& val)  { return static_cast<ilvec1>(val); }
inline ivec1  u_to_i  (const uvec1& val)  { return static_cast<ivec1> (val); }
inline ihvec1 u_to_ih (const uvec1& val)  { return static_cast<ihvec1>(val); }
inline isvec1 u_to_is (const uvec1& val)  { return static_cast<isvec1>(val); }
inline ilvec2 u_to_il (const uvec2& val)  { return static_cast<ilvec2>(val); }
inline ivec2  u_to_i  (const uvec2& val)  { return static_cast<ivec2> (val); }
inline ihvec2 u_to_ih (const uvec2& val)  { return static_cast<ihvec2>(val); }
inline isvec2 u_to_is (const uvec2& val)  { return static_cast<isvec2>(val); }
inline ilvec3 u_to_il (const uvec3& val)  { return static_cast<ilvec3>(val); }
inline ivec3  u_to_i  (const uvec3& val)  { return static_cast<ivec3> (val); }
inline ihvec3 u_to_ih (const uvec3& val)  { return static_cast<ihvec3>(val); }
inline isvec3 u_to_is (const uvec3& val)  { return static_cast<isvec3>(val); }
inline ilvec4 u_to_il (const uvec4& val)  { return static_cast<ilvec4>(val); }
inline ivec4  u_to_i  (const uvec4& val)  { return static_cast<ivec4> (val); }
inline ihvec4 u_to_ih (const uvec4& val)  { return static_cast<ihvec4>(val); }
inline isvec4 u_to_is (const uvec4& val)  { return static_cast<isvec4>(val); }

inline ilvec1 uh_to_il(const uhvec1& val) { return static_cast<ilvec1>(val); }
inline ivec1  uh_to_i (const uhvec1& val) { return static_cast<ivec1> (val); }
inline ihvec1 uh_to_ih(const uhvec1& val) { return static_cast<ihvec1>(val); }
inline isvec1 uh_to_is(const uhvec1& val) { return static_cast<isvec1>(val); }
inline ilvec2 uh_to_il(const uhvec2& val) { return static_cast<ilvec2>(val); }
inline ivec2  uh_to_i (const uhvec2& val) { return static_cast<ivec2> (val); }
inline ihvec2 uh_to_ih(const uhvec2& val) { return static_cast<ihvec2>(val); }
inline isvec2 uh_to_is(const uhvec2& val) { return static_cast<isvec2>(val); }
inline ilvec3 uh_to_il(const uhvec3& val) { return static_cast<ilvec3>(val); }
inline ivec3  uh_to_i (const uhvec3& val) { return static_cast<ivec3> (val); }
inline ihvec3 uh_to_ih(const uhvec3& val) { return static_cast<ihvec3>(val); }
inline isvec3 uh_to_is(const uhvec3& val) { return static_cast<isvec3>(val); }
inline ilvec4 uh_to_il(const uhvec4& val) { return static_cast<ilvec4>(val); }
inline ivec4  uh_to_i (const uhvec4& val) { return static_cast<ivec4> (val); }
inline ihvec4 uh_to_ih(const uhvec4& val) { return static_cast<ihvec4>(val); }
inline isvec4 uh_to_is(const uhvec4& val) { return static_cast<isvec4>(val); }

inline ilvec1 us_to_il(const usvec1& val) { return static_cast<ilvec1>(val); }
inline ivec1  us_to_i (const usvec1& val) { return static_cast<ivec1> (val); }
inline ihvec1 us_to_ih(const usvec1& val) { return static_cast<ihvec1>(val); }
inline isvec1 us_to_is(const usvec1& val) { return static_cast<isvec1>(val); }
inline ilvec2 us_to_il(const usvec2& val) { return static_cast<ilvec2>(val); }
inline ivec2  us_to_i (const usvec2& val) { return static_cast<ivec2> (val); }
inline ihvec2 us_to_ih(const usvec2& val) { return static_cast<ihvec2>(val); }
inline isvec2 us_to_is(const usvec2& val) { return static_cast<isvec2>(val); }
inline ilvec3 us_to_il(const usvec3& val) { return static_cast<ilvec3>(val); }
inline ivec3  us_to_i (const usvec3& val) { return static_cast<ivec3> (val); }
inline ihvec3 us_to_ih(const usvec3& val) { return static_cast<ihvec3>(val); }
inline isvec3 us_to_is(const usvec3& val) { return static_cast<isvec3>(val); }
inline ilvec4 us_to_il(const usvec4& val) { return static_cast<ilvec4>(val); }
inline ivec4  us_to_i (const usvec4& val) { return static_cast<ivec4> (val); }
inline ihvec4 us_to_ih(const usvec4& val) { return static_cast<ihvec4>(val); }
inline isvec4 us_to_is(const usvec4& val) { return static_cast<isvec4>(val); }

inline vec1  ul_to_f(const ulvec1& val) { return static_cast<vec1> (val); }
inline vec2  ul_to_f(const ulvec2& val) { return static_cast<vec2> (val); }
inline vec3  ul_to_f(const ulvec3& val) { return static_cast<vec3> (val); }
inline vec4  ul_to_f(const ulvec4& val) { return static_cast<vec4> (val); }

inline dvec1 ul_to_d(const ulvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 ul_to_d(const ulvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 ul_to_d(const ulvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 ul_to_d(const ulvec4& val) { return static_cast<dvec4>(val); }

inline vec1  u_to_f (const uvec1& val)  { return static_cast<vec1> (val); }
inline vec2  u_to_f (const uvec2& val)  { return static_cast<vec2> (val); }
inline vec3  u_to_f (const uvec3& val)  { return static_cast<vec3> (val); }
inline vec4  u_to_f (const uvec4& val)  { return static_cast<vec4> (val); }

inline dvec1 u_to_d (const uvec1& val)  { return static_cast<dvec1>(val); }
inline dvec2 u_to_d (const uvec2& val)  { return static_cast<dvec2>(val); }
inline dvec3 u_to_d (const uvec3& val)  { return static_cast<dvec3>(val); }
inline dvec4 u_to_d (const uvec4& val)  { return static_cast<dvec4>(val); }

inline vec1  uh_to_f(const uhvec1& val) { return static_cast<vec1> (val); }
inline vec2  uh_to_f(const uhvec2& val) { return static_cast<vec2> (val); }
inline vec3  uh_to_f(const uhvec3& val) { return static_cast<vec3> (val); }
inline vec4  uh_to_f(const uhvec4& val) { return static_cast<vec4> (val); }

inline dvec1 uh_to_d(const uhvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 uh_to_d(const uhvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 uh_to_d(const uhvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 uh_to_d(const uhvec4& val) { return static_cast<dvec4>(val); }

inline vec1  us_to_f(const usvec1& val) { return static_cast<vec1> (val); }
inline vec2  us_to_f(const usvec2& val) { return static_cast<vec2> (val); }
inline vec3  us_to_f(const usvec3& val) { return static_cast<vec3> (val); }
inline vec4  us_to_f(const usvec4& val) { return static_cast<vec4> (val); }

inline dvec1 us_to_d(const usvec1& val) { return static_cast<dvec1>(val); }
inline dvec2 us_to_d(const usvec2& val) { return static_cast<dvec2>(val); }
inline dvec3 us_to_d(const usvec3& val) { return static_cast<dvec3>(val); }
inline dvec4 us_to_d(const usvec4& val) { return static_cast<dvec4>(val); }