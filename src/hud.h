// hud.h
#ifndef HUD_H
#define HUD_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

namespace godot {

class HUD : public CanvasLayer {
	GDCLASS(HUD, CanvasLayer);

private:
	Label *score_node = nullptr;
	Label *message_node = nullptr;
	Button *start_button = nullptr;
	Timer *message_timer = nullptr;

	void _on_game_over_message_timeout();
	void _on_game_over_restart_timeout();
	void _on_message_timer_timeout();
	void _on_start_button_pressed();

protected:
	static void _bind_methods();

public:
	HUD();
	~HUD();
	void _ready() override;

	void start_game_event_handeler();
	void update_score(int score);
	void show_message(const String &text);
	void show_gameover();
};
}; //namespace godot

#endif //!HUD_H
