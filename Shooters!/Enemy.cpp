#include"Enemy.h"
#include"DxLib.h"
#include"Random.h"

Enemy::Enemy(Vec2 &pos, int graph_handle, int hp, float speed, int range, int anime_interval, enItemType item_type, int shot_speed)
	: range(range), anime_interval(anime_interval), shot_speed(shot_speed),
	draw_flag(true), erase_flag(false), pos(pos), hp(hp), speed(speed), counter(0),
	refresh_time(GetNowCount()), refresh_time_a(0), anime_switch_flag(true), graph_index(0),
	shoot_flag(false), graph_handle(graph_handle), item_type(item_type)
{

}

void Enemy::damage(const int damage) {
	hp -= damage;
	if (hp <= 0) {
		draw_flag = false;
	}
}