#pragma once

#pragma pack(push, 1)
struct lock_float_t {
	inline float get() const noexcept {
		return encrypted1 - weight * 0.5f;
	}

	// alternative way to get value
	//inline float get() const noexcept {
	//    return encrypted2 - weight;
	//}

	inline void set(float value) noexcept {
		encrypted1 = value + (weight * 0.5f);
		encrypted2 = value + weight;
	}

	float encrypted1;
	float unk1;
	float encrypted2;
	float weight;
};
#pragma pack(pop)
