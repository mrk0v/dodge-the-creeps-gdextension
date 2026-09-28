// src/player.cpp
#include "player.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Player::Player() {
	speed = 400.0;
}
Player::~Player() {
}

void Player::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	Vector2 velocity;

	if (Input::get_singleton()->is_action_pressed("move_right")) {
		velocity.x += 1;
	}

	if (Input::get_singleton()->is_action_pressed("move_left")) {
		velocity.x -= 1;
	}

	if (Input::get_singleton()->is_action_pressed("move_down")) {
		velocity.y += 1;
	}

	if (Input::get_singleton()->is_action_pressed("move_up")) {
		velocity.y -= 1;
	}
	AnimatedSprite2D *animated_sprite_2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (!animated_sprite_2d) {
		return;
	}
	if (velocity.x != 0) {
		animated_sprite_2d->set_animation("walk");
		animated_sprite_2d->set_flip_v(false);
		animated_sprite_2d->set_flip_h(velocity.x < 0);
	} else if (velocity.y != 0) {
		animated_sprite_2d->set_animation("up");
		animated_sprite_2d->set_flip_h(velocity.y > 0);
	}
	if (velocity.length() > 0) {
		velocity = velocity.normalized() * speed;
		animated_sprite_2d->play();
	} else {
		animated_sprite_2d->stop();
	}
	Vector2 pos = get_position();
	pos += velocity * (real_t)delta;
	pos.x = Math::clamp(pos.x, (real_t)0.0, screen_size.x);
	pos.y = Math::clamp(pos.y, (real_t)0.0, screen_size.y);
	set_position(pos);
}

void Player::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		return;
	}
	hide();
	Rect2 viewport_rect = get_viewport_rect();
	screen_size = viewport_rect.get_size();
}

void Player::_bind_methods() {
	ADD_SIGNAL(MethodInfo("hit"));
	ClassDB::bind_method(D_METHOD("on_body_entered", "body"), &Player::on_body_entered);
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
	ClassDB::add_property("Player",
			PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

void Player::start(const Vector2 &p_position) {
	set_position(p_position);
	show();
	CollisionShape2D *collision_shape = get_node<CollisionShape2D>("CollisionShape2D");
	collision_shape->set_deferred("disabled", false);
}

void Player::on_body_entered(Node2D *body) {
	hide();
	emit_signal("hit");
	CollisionShape2D *collision_shape = get_node<CollisionShape2D>("CollisionShape2D");
	collision_shape->set_deferred("disabled", true);
}

void Player::set_speed(double p_speed) {
	speed = p_speed;
}

double Player::get_speed() const {
	return speed;
}
