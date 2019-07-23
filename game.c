#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "FPgame.h"
#include <assert.h>
#include "object.h"

Object MapProto = 
{
.init = Map_init,
.move = Map_move,
.attack = Map_attack
};
int process_input (Map *game)
{
	assert(game != 	NULL);
	printf("\n");

	char ch = getchar();
	getchar();	// eat ENTER
	
	int damage = rand() %4;
	
	switch(ch)
	{
		case -1:
			printf("Giving up? you suck.\n");
			return 0;
			break;
		case'n':
			game->_(move)(game,NORTH);
			break;
		case 's':
			game->_(move)(game,SOUTH);
			break;
		case 'e':
			game->_(move)(game,EAST);
			break;
		case 'w':
			game->_(move)(game,WEST);
			break;
		case 'a':
			game->_(attack)(game, damage);
			break;
		case 'l':
			printf("You can go:	");
			if(game->location->north)	printf("NORTH	");
			else;
			if(game->location->east)	printf("EAST	");
			else;
			if(game->location->west)	printf("WEAST	");
			else;
			if(game->location->south)	printf("SOUTH	");
			else;
			break;
		case 'o':
			game->_(destroy(game));
			return 0;
			break;
		default:
			printf("What?:	%d\n",ch);
			break;
	}
	return 1;
}

int main (int argc, char * argv[])
{
	//simple way to setup the randomness
	assert(time(NULL)>=0);
	srand(time(NULL));
	
	// make our map to work with
	Map *game = NEW(Map,"The Hall of Minotaur");
	
	printf("You enter the	");
	game->location->_(describe)(game->location);
	
	while(process_input(game))
	{
	}
	
	return 0;
}
