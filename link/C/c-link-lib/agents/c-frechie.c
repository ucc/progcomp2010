/*
 *  c-frechie.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 22/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include <c_link.h>
#include <stdlib.h>

/* Implement the frenchie bot, that is by default nice but will 
   permanently turn against any agent that betrays it.
   This is trickier in C than in any other language, for a number of reasons:
     - there's no classes in C, so we can't just write a generic learning agent
       and subclass it.
     - your agent has no idea how many agents it's going to battle, or how many
       battles it is going to fight, so you've got to do dynamic memory allocation.
        (anyone who tries to read the source of the supervisor to find out is liable
         to have their program break unexpectedly)
 */

/* To simplify things, we just look at whether we have lost to a particular agent.
   Unlike in the Python version, we don't keep a generic list
   This is also done in a inefficient (O(bot-cout)) way.
   Implementing a faster version is left as an exercise to the DSA student. */

/* Our guess at the number of agents I'm going to fight in my lifetime */
#define NUMBEROFAGENTSGUESS 100

/* The name of the n-th foe we've seen, as well as a 0/1 have we lost to them */
char foesNames[][MAXFOENAMELEN] = NULL;
int haveLostToFoe[] = NULL;

/* The length of the array, and how far we are along it */
size_t foesLen = 0;
unsigned int foesCount = 0;


ATTACKTYPE Attack( char * foe_name ) {
	ATTACKTYPE attack;
	
	attack.realAttack =  RandomAttack();
	
	/* Here we choose the thing that will hurt them if they go for the kill */
	switch (attack.realAttack) {
		case rock:
			result.promisedAttack = paper;
			break;
		case paper:
			result.promisedAttack = scissors;
			break;
		default: /* attack = scissors */
			result.promisedAttack = rock;
			break;
	}
	return attack;
}

/* Here we assume they are lying, trying to kill us. And we try to kill them. */
ITEMTYPE Defend( char * foeName, ITEMTYPE foePromisedAttack ) {
	ITEMTYPE defence;
	switch (foePromisedAttack) {
		case rock:
			defence = scissors;
			break;
		case paper:
			defence = rock;
			break;
		default:
			defence = paper;
			break;
	}
}

/* This is so much less fun in C */
void Results( char * foeName, int isInstigatedByYou, ITEMTYPE yourItem, 
			 ITEMTYPE theirItem, ITEMTYPE promisedItem) {
	
    int foe;
    
    /* check to see if we've initialised our arrays */
	if (foesNames == NULL) {
        foesNames = calloc( NUMBEROFAGENTSGUESS, sizeof( foesNames[0] ) );
        haveLostToFoe = calloc( NUMBEROFAGENTSGUESS, sizeof( haveLostToFoe[0] ) );
        foesLen = NUMBEROFAGENTSGUESS;
    }
    
    /* figure out if we lost, which is the only thing we care about
       if we didn't, move on. */
    if (RESULTOF[yourItem][theirItem] != lose) return;
    
    /* try and find existing foe */
    
    return;
}

/* same for Cleanup() */

void Cleanup() {
	free(foesNames);
    free(haveLostToFoe);
}