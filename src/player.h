// scr/player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Player : public Area2D {
	GDCLASS(Player, Area2D)
protected:
	static void _bind_methods();

private:
	double speed;
	Vector2 screen_size;

public:
	Player();
	~Player();

	void _ready() override;
	void _process(double delta) override;

	void start(const Vector2 &p_position);
	void on_body_entered(Node2D *body);

	void set_speed(double p_speed);
	double get_speed() const;
};
}; //namespace godot

#endif // !PLAYER_H
