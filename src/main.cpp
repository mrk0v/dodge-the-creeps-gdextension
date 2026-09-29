// main.cpp

#include "godot_cpp/classes/audio_stream_player2d.hpp"
#include "godot_cpp/classes/marker2d.hpp"
#include "godot_cpp/classes/path_follow2d.hpp"
#include "mob.h"
#include "player.h"
#include <hud.h>
#include <main.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

void Main::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_mob_timer_timeout"), &Main::_on_mob_timer_timeout);
	ClassDB::bind_method(D_METHOD("_on_score_timer_timeout"), &Main::_on_score_timer_timeout);
	ClassDB::bind_method(D_METHOD("_on_start_timer_timeout"), &Main::_on_start_timer_timeout);
	ClassDB::bind_method(D_METHOD("new_game"), &Main::new_game);
	ClassDB::bind_method(D_METHOD("game_over"), &Main::game_over);
	ClassDB::bind_method(D_METHOD("set_mob_scene", "scene"), &Main::set_mob_scene);
	ClassDB::bind_method(D_METHOD("get_mob_scene"), &Main::get_mob_scene);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mob_scene",
						 PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"),
			"set_mob_scene", "get_mob_scene");
}
void Main::new_game() {
	get_node<AudioStreamPlayer2D>("Music")->play();
	_score = 0;
	get_tree()->call_group("mobs", "queue_free");

	HUD *hud = get_node<HUD>("HUD");
	hud->update_score(_score);
	hud->show_message("Get Ready!");

	Player *player = get_node<Player>("Player");
	Marker2D *start_position = get_node<Marker2D>("StartPosition");
	player->start(start_position->get_position());
	get_node<Timer>("StartTimer")->start();
}

void Main::game_over() {
	get_node<AudioStreamPlayer2D>("Music")->stop();
	get_node<AudioStreamPlayer2D>("DeathSound")->play();
	get_node<HUD>("HUD")->show_gameover();
	get_node<Timer>("MobTimer")->stop();
	get_node<Timer>("ScoreTimer")->stop();
}

void Main::_on_score_timer_timeout() {
	_score++;
	get_node<HUD>("HUD")->update_score(_score);
}

void Main::_on_start_timer_timeout() {
	get_node<Timer>("MobTimer")->start();
	get_node<Timer>("ScoreTimer")->start();
}

void Main::_on_mob_timer_timeout() {
	Mob *mob = Object::cast_to<Mob>(mob_scene->instantiate());
	PathFollow2D *mob_spawn_location = get_node<PathFollow2D>("MobPath/MobSpawnLocation");
	mob_spawn_location->set_progress_ratio(UtilityFunctions::randf());
	float direction = mob_spawn_location->get_rotation() + Math_PI / 2;
	mob->set_position(mob_spawn_location->get_position());
	direction += UtilityFunctions::randf_range(-Math_PI / 4, Math_PI / 4);
	mob->set_rotation(direction);
	Vector2 velocity(UtilityFunctions::randf_range(150.0, 250.0), 0);
	mob->set_linear_velocity(velocity.rotated(direction));
	add_child(mob);
}

void Main::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
}
