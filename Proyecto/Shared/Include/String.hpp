#pragma once

#include <string>

#include "Glm.hpp"
#include "Types.hpp"

using namespace std;

// STRING

inline vec1   str_to_f (const string& val_1) { return stof(val_1); }
inline vec2   str_to_f (const string& val_1, const string& val_2) { return vec2(stof(val_1), stof(val_2)); }
inline vec3   str_to_f (const string& val_1, const string& val_2, const string& val_3) { return vec3(stof(val_1), stof(val_2), stof(val_3)); }
inline vec4   str_to_f (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return vec4(stof(val_1), stof(val_2), stof(val_3), stof(val_4)); }

inline dvec1  str_to_d (const string& val_1) { return stod(val_1); }
inline dvec2  str_to_d (const string& val_1, const string& val_2) { return dvec2(stod(val_1), stod(val_2)); }
inline dvec3  str_to_d (const string& val_1, const string& val_2, const string& val_3) { return dvec3(stod(val_1), stod(val_2), stod(val_3)); }
inline dvec4  str_to_d (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return dvec4(stod(val_1), stod(val_2), stod(val_3), stod(val_4)); }

inline ulvec1 str_to_ul(const string& val_1) { return stoull(val_1); }
inline ulvec2 str_to_ul(const string& val_1, const string& val_2) { return ulvec2(stoull(val_1), stoull(val_2)); }
inline ulvec3 str_to_ul(const string& val_1, const string& val_2, const string& val_3) { return ulvec3(stoull(val_1), stoull(val_2), stoull(val_3)); }
inline ulvec4 str_to_ul(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return ulvec4(stoull(val_1), stoull(val_2), stoull(val_3), stoull(val_4)); }

inline uvec1  str_to_u (const string& val_1) { return stoul(val_1); }
inline uvec2  str_to_u (const string& val_1, const string& val_2) { return uvec2(stoul(val_1), stoul(val_2)); }
inline uvec3  str_to_u (const string& val_1, const string& val_2, const string& val_3) { return uvec3(stoul(val_1), stoul(val_2), stoul(val_3)); }
inline uvec4  str_to_u (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return dvec4(stoul(val_1), stoul(val_2), stoul(val_3), stoul(val_4)); }

inline uhvec1 str_to_uh(const string& val_1) { return u_to_uh(stoul(val_1)); }
inline uhvec2 str_to_uh(const string& val_1, const string& val_2) { return u_to_uh(uvec2(stoul(val_1), stoul(val_2))); }
inline uhvec3 str_to_uh(const string& val_1, const string& val_2, const string& val_3) { return u_to_uh(uvec3(stoul(val_1), stoul(val_2), stoul(val_3))); }
inline uhvec4 str_to_uh(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return u_to_uh(uvec4(stoul(val_1), stoul(val_2), stoul(val_3), stoul(val_4))); }

inline usvec1 str_to_us(const string& val_1) { return u_to_us(stoul(val_1)); }
inline usvec2 str_to_us(const string& val_1, const string& val_2) { return u_to_us(uvec2(stoul(val_1), stoul(val_2))); }
inline usvec3 str_to_us(const string& val_1, const string& val_2, const string& val_3) { return u_to_us(uvec3(stoul(val_1), stoul(val_2), stoul(val_3))); }
inline usvec4 str_to_us(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return u_to_us(uvec4(stoul(val_1), stoul(val_2), stoul(val_3), stoul(val_4))); }

inline ilvec1 str_to_il(const string& val_1) { return stoll(val_1); }
inline ilvec2 str_to_il(const string& val_1, const string& val_2) { return ilvec2(stoll(val_1), stoll(val_2)); }
inline ilvec3 str_to_il(const string& val_1, const string& val_2, const string& val_3) { return ilvec3(stoll(val_1), stoll(val_2), stoll(val_3)); }
inline ilvec4 str_to_il(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return ilvec4(stoll(val_1), stoll(val_2), stoll(val_3), stoll(val_4)); }

inline ivec1  str_to_i (const string& val_1) { return stoi(val_1); }
inline ivec2  str_to_i (const string& val_1, const string& val_2) { return ivec2(stoi(val_1), stoi(val_2)); }
inline ivec3  str_to_i (const string& val_1, const string& val_2, const string& val_3) { return ivec3(stoi(val_1), stoi(val_2), stoi(val_3)); }
inline ivec4  str_to_i (const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return ivec4(stoi(val_1), stoi(val_2), stoi(val_3), stoi(val_4)); }

inline ihvec1 str_to_ih(const string& val_1) { return i_to_ih(stoi(val_1)); }
inline ihvec2 str_to_ih(const string& val_1, const string& val_2) { return i_to_ih(ivec2(stoi(val_1), stoi(val_2))); }
inline ihvec3 str_to_ih(const string& val_1, const string& val_2, const string& val_3) { return i_to_ih(ivec3(stoi(val_1), stoi(val_2), stoi(val_3))); }
inline ihvec4 str_to_ih(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return i_to_ih(ivec4(stoi(val_1), stoi(val_2), stoi(val_3), stoi(val_4))); }

inline isvec1 str_to_is(const string& val_1) { return i_to_is(stoi(val_1)); }
inline isvec2 str_to_is(const string& val_1, const string& val_2) { return i_to_is(ivec2(stoi(val_1), stoi(val_2))); }
inline isvec3 str_to_is(const string& val_1, const string& val_2, const string& val_3) { return i_to_is(ivec3(stoi(val_1), stoi(val_2), stoi(val_3))); }
inline isvec4 str_to_is(const string& val_1, const string& val_2, const string& val_3, const string& val_4) { return i_to_is(ivec4(stoi(val_1), stoi(val_2), stoi(val_3), stoi(val_4))); }