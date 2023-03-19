#pragma once
#include <cstdint>
#include <deque>

#pragma pack(push, 1)
struct game_timer_t {
	void* vftable;
	std::uint32_t last_time_ms;
	std::uint32_t time_ms;
	std::uint32_t fps_timer;
	std::uint32_t game_timer;
	std::uint32_t shadow_offset;
	std::int32_t fps;
	std::int32_t fps_temp;
	bool game_timer_paused;
	std::int32_t delta_ms;
	float delta_float;
	std::deque<float> tick_history;
	std::uint32_t shadow_game_tick;
	std::uint8_t pad1[7];
};
#pragma pack(pop)

constexpr int aaaaaa = sizeof(game_timer_t);
