#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FPgame.h"
#include <assert.h>


//Description: monster receives damages from main character
//		and will be dead or alive
//	Input: Object pointer (monster), damage
//	Output: 1 monster is dead
//		0 monster is still alive 
//	Effect: show how many damages monster is taken and health it remains
int Monster_attack(void *self, int damage)
{
	assert((self != NULL) ||(damage >=0));
	Monster *monster = self;
	//monster->_(description) is a macro = monster->proto.description
	printf("You attack %s!\n",monster->_(description));
	
	// calculate damages from character
	monster->hit_points -=damage;
	if(monster->hit_points >0)
	{
		printf("It is still alive with %d HP.\n",monster->hit_points);
		return 0;
	}
	else
	{
		printf("It is dead!\n");
		return 1;
	}
}
//Description: initialze monter's variables
//	Input:	monster pointer (object)
//	Output: 1 if the function is working well
//		else return 0
//	Effect: nothing
int Monster_init(void *self)
{
	assert(self != NULL);
	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

// Set the value of Monster->proto->init/attack
Object MonsterProto = 
{
	.init = Monster_init,
	.attack = Monster_attack
};


//Description: room spaces for character's movement
//	Input: direction and room pointer
//	Ouput: a room pointers with new posision of character
//	Effect: Nothing
void *Room_move(void *self,Direction direction)
{
	assert((self!= NULL)||
		((direction != NORTH)&&(direction!=SOUTH)
		&&(direction!=EAST)&&(direction!=WEST)));
	Room *room = self;
	Room *next = NULL;
	
	if(direction == NORTH && room->north)
	{
		printf("You go north, into: \n");
		next= room->north;
	}
	else if(direction == SOUTH && room->south)
	{
		printf("You go south,into: \n");
		next= room->south;
	}
	else if(direction == EAST && room->east)
	{
		printf("You go east,into: \n");
		next= room->east;
	}
	else if(direction == WEST && room->west)
	{
		printf("You go to west, into: \n");
		next= room->west;
	}
	else
	{
		printf("You can't go that direction");
		next= NULL;
	}
	if(next)
	{
		next->_(describe)(next); // it's a macro
	}
	else
	{
		// Do nothing
	}
	return next;
}

//Description: determine whether monster and character collides
//	Input: Room pointer, an int damage
//	Output:	1: there is a collision between main char and monster
//		0: you miss it
int Room_attack(void *self, int damage)
{
	assert((self != NULL)||(damage >= 0));
	Room *room = self;
	Monster *monster = room->bad_guy;
	
	if(monster)
	{
		monster->_(attack)(monster,damage);
		return 1;
	}
	else
	{
		printf("You flail in the air at nothing. Idiot.\n");
		return 0;
	}
}

Object RoomProto =
{
	.move = Room_move,
	.attack = Room_attack
};
//Description: map is a space that contain many spaces. this function is used to
//		make user enter the rooms
//	Input: Map pointer, direction
//	Output: Map pointer with a new position
//	Effect: nothing
void *Map_move(void *self, Direction direction)
{
	assert((self!= NULL)||((direction != NORTH)&&(direction!=SOUTH)&&(direction!=EAST)&&	(direction!=WEST)));	
	Map * map = self;
	Room *location = map->location;
	Room *next = NULL;
	
	next = location->_(move)(location,direction);

	if(next)
	{
		map->location = next;
	}
	else
	{
		// do nothing
	}
	return next;
}
//Description: allow user attacks monter when outside the room
//	Input: Map pointer
//	Output: 1 : attack well done
//		0 : miss
//	Effect: nothing 
int Map_attack(void *self,int damage)
{
	assert((self != NULL)||(damage >= 0));
	Map* map = self;
	Room *location = map->location;
	
	return location->_(attack)(location,damage);
}

int Map_init(void *self)
{
	assert(self != NULL);
	Map *map = self;
	
	// make some rooms for a small map
	Room *hall = NEW(Room,"The Great Hall");
	Room *throne = NEW(Room,"The throne room");
	Room *arena = NEW(Room,"The arean, with the minotaur");
	Room *kitchen = NEW(Room,"Kitchen you have the knife now");
	Room *garden = NEW(Room,"It's the garden, with Deadpool");

	// put the bad guy in the arean
	arena->bad_guy = NEW(Monster,"The evil minotour");
	garden->bad_guy = NEW(Monster,"The superhero Deadpool");

	// setup the map rooms
	hall->north = throne;
	hall->west = garden;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;
	
	arena->east = throne;
	kitchen->west = throne;

	// start the map and the character off in the hall
	map->start = hall;
	map->location = hall;

	return 1;
}

