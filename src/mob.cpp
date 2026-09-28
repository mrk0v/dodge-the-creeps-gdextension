// mob.cpp

#include "mob.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;

Mob::Mob() {}
Mob::~Mob() {}

void Mob::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	AnimatedSprite2D *animated_sprite_2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (!animated_sprite_2d) {
		return;
	}
	PackedStringArray mob_types = animated_sprite_2d->get_sprite_frames()->get_animation_names();
	animated_sprite_2d->play(mob_types[UtilityFunctions::randi() % mob_types.size()]);
}

void Mob::_process(double delta) {}

void Mob::_on_visible_on_screen_notifier_2d_screen_exited() {
	queue_free();
}

void Mob::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_visible_on_screen_notifier_2d_screen_exited"), &Mob::_on_visible_on_screen_notifier_2d_screen_exited);
}
