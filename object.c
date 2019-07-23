#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>


// In this script, we will interprete functions that are decleared in the object.h file
/*-------------------------------------------------------------------------------------*/
//Description: initializing everything in Object
//		Input: Object pointer
//		Output:	1
//		Effect: object is initialized
int Object_init(void *self)
{
	assert(self!=NULL);
	// dothing
	// just return everything into 1
	return 1;
}

//Description: free object when it finishes its job
//		Input: object pointer
//		Output: nothing
//		Effect:	there is no leak memory related to 
void Object_destroy(void *self)
{
	assert(self!=NULL);
	Object *obj = self;
	if(obj)
	{
		if (obj->description)	free(obj->description);
		else;
		free(obj);
	}
	else;
}

//Description: print out the description of the object
//		Input: object pointer
//		Ouput: nothing
//		Effect: the description is printed out
void Object_describe(void *self)
{
	assert(self!=NULL);
	Object *obj = self;
	printf("%s.\n",obj->description);
}
void *Object_move (void *self,Direction direction)
{
	assert(self!=NULL);
	printf("You can't go that direction.\n");
	return NULL;
}
int Object_attack(void *self, int damage)
{
	assert((self!=NULL)||(damage >= 0));
	printf("You can't attack that.\n");
	return 0;
}

//Desciption: return a new object that is ready for the game
//		Input:the size of Object pointer, description about object
//				the protocol of Object object
//		Output: a new Object that ready for the game
//		Effect: nothing 
void *Object_new (size_t size, Object proto, char *description)
{
	assert((size<=0)||(description!= NULL));	
	//setup the default functions in case they aren't set
	if(!proto.init)	proto.init = Object_init;
	else;
	if(!proto.describe) proto.describe = Object_describe;
	else;
	if(!proto.destroy) proto.destroy = Object_destroy;
	else;
	if(!proto.move)	proto.move = Object_move;
	else;
	if(!proto.attack) proto.attack = Object_attack;
	else;
	
	//now, start to create an object with the size of size, protocol proto, and description
	//	as parameters
	Object *el = calloc(1,size);	
	*el = proto;
	
	//copy the description over
	el->description = strdup(description);

	// initialize it with whatever init we were given
	if(!el->init(el))
	{
	//something happened that makes el not to be initialized (el->init(el) shoud be 1)
		el->destroy(el);
		return NULL;
	}
	else
	{
	//finish
		assert(el != NULL);
		return el;
	}
}
