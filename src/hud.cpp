// hud.cpp

#include "hud.h"
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/scene_tree_timer.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

using namespace godot;

HUD::HUD() {
}

HUD::~HUD() {
}

void HUD::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_message_timer_timeout"), &HUD::_on_message_timer_timeout);
	ClassDB::bind_method(D_METHOD("_on_start_button_pressed"), &HUD::_on_start_button_pressed);
	ClassDB::bind_method(D_METHOD("show_gameover"), &HUD::show_gameover);
	ClassDB::bind_method(D_METHOD("update_score", "score"), &HUD::update_score);

	ADD_SIGNAL(MethodInfo("start_game"));
}

void HUD::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}

	score_node = get_node<Label>("ScoreLabel");
	message_node = get_node<Label>("Message");
	start_button = get_node<Button>("StartButton");
	message_timer = get_node<Timer>("MessageTimer");
}

void HUD::show_gameover() {
	show_message("Game Over");

	message_timer->connect("timeout",
			callable_mp(this, &HUD::_on_game_over_message_timeout),
			CONNECT_ONE_SHOT);
}

void HUD::show_message(const String &text) {
	message_node->set_text(text);
	message_node->show();
	message_timer->start();
}

void HUD::_on_game_over_message_timeout() {
	Label *message = get_node<Label>("Message");
	message->set_text("Dodge the Creeps!");
	message->show();

	get_tree()->create_timer(1.0)->connect("timeout",
			callable_mp(this, &HUD::_on_game_over_restart_timeout),
			CONNECT_ONE_SHOT);
}

void HUD::_on_game_over_restart_timeout() {
	get_node<Button>("StartButton")->show();
}

void HUD::update_score(int score) {
	score_node->set_text(String::num_int64(score));
}

void HUD::_on_start_button_pressed() {
	start_button->hide();
	emit_signal("start_game");
}

void HUD::_on_message_timer_timeout() {
	message_node->hide();
}
