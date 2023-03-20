#pragma once

template <typename T>
class vec2_t {
public:
	T x, y;
};

template <typename T>
class vec3_t {
public:
	T x, y, z;
};

template <typename T>
class vec4_t {
public:
	T x, y, z, w;
};

using vec2f_t = vec2_t<float>;
using vec3f_t = vec3_t<float>;
using vec4f_t = vec4_t<float>;

using vec2i_t = vec2_t<int>;
using vec3i_t = vec3_t<int>;
using vec4i_t = vec4_t<int>;
