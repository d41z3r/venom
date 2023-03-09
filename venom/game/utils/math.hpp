#pragma once

template <typename T>
struct vec2_t {
	T x, y;
};

template <typename T>
struct vec3_t {
	T x, y, z;
};

template <typename T>
struct vec4_t {
	T x, y, z, w;
};

using vec2f_t = vec2_t<float>;
using vec3f_t = vec3_t<float>;
using vec4f_t = vec4_t<float>;

using vec2i_t = vec2_t<int>;
using vec3i_t = vec3_t<int>;
using vec4i_t = vec4_t<int>;
