// main.h
#ifndef MAIN_H
#define MAIN_H

#include "mob.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

namespace godot {

class Main : public Node {
	GDCLASS(Main, Node)
protected:
	static void _bind_methods();

private:
	int _score;
	Ref<PackedScene> mob_scene;

public:
	void set_mob_scene(const Ref<PackedScene> &p_scene) { mob_scene = p_scene; }
	Ref<PackedScene> get_mob_scene() const { return mob_scene; }

	void _ready() override;
	void _on_mob_timer_timeout();
	void _on_score_timer_timeout();
	void _on_start_timer_timeout();
	void new_game();
	void game_over();
};

} // namespace godot

#endif
