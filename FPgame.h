#ifndef	_FPgame_h
#define _FPgame_h

#include "object.h"

typedef struct Monster
{
	Object proto;
	int hit_points;
} Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

typedef struct Room
{
	Object proto;

	Monster *bad_guy;
	struct Room *north;
	struct Room *south;
	struct Room *west;
	struct Room *east;
} Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

typedef struct Map
{
	Object proto;
	Room *start;
	Room *location;
} Map;

void *Map_move(void* self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif
