#pragma once
#include <game/manager/game_timer.hpp>
#include <game/manager/console.hpp>
#include <game/gui/rt_font.hpp>
#include <game/utils/boost.hpp>

#include <cstdint>

#pragma pack(push, 1)
struct base_app_t {
	void* vftable;
	boost_signal_t sig_input;
	boost_signal_t sig_input_move;
	boost_signal_t sig_os;
	boost_signal_t sig_update;
	boost_signal_t sig_render;
	boost_signal_t sig_pre_enterbackground;
	boost_signal_t sig_enterbackground;
	boost_signal_t sig_enterforeground;
	boost_signal_t sig_accel;
	boost_signal_t sig_trackball;
	boost_signal_t sig_arcade_input;
	boost_signal_t sig_raw_keyboard;
	boost_signal_t sig_hardware;
	boost_signal_t sig_on_screen_size_changed;
	boost_signal_t sig_unload_surfaces;
	boost_signal_t sig_load_surfaces;
	boost_signal_t sig_joypad_events;
	boost_signal_t sig_native_input_state_changed;
	bool console_visible;
	bool fps_visible;
	bool initted;
	std::uint8_t pad1[5];
	game_timer_t game_timer;
	console_t console;
	rt_font_t small_font;
	rt_font_t large_font;
	rt_font_t fixed_font;
	rt_font_t growmoji_font;

	//deque <OSMessage> m_OSMessages; 
	//bool m_bManualRotation;
	//ResourceManager m_resourceManager;
	//eInputMode m_inputMode;
	//int m_memUsed;
	//int m_texMemUsed;
	//eErrorType m_error;
	//bool m_bIsInBackground;
	//vector<string> m_commandLineParms;

	//CL_Mat4f m_projectionMatrix;
	//Entity m_entityRoot;
	//bool m_bCheatMode;
	//vector<TouchTrackInfo> m_touchTracker;
	//string m_version;
	//bool m_bDisableSubPixelBlits;
};
#pragma pack(pop)

