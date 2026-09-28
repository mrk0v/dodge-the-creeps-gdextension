// src/mob.h

#ifndef MOB_H
#define MOB_H
#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class Mob : public RigidBody2D {
	GDCLASS(Mob, RigidBody2D)
protected:
	static void _bind_methods();

private:
public:
	Mob();
	~Mob();
	void _ready() override;
	void _process(double delta) override;
	void _on_visible_on_screen_notifier_2d_screen_exited();
};

}; //namespace godot

#endif // !MOB_H
