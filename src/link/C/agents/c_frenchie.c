/*
 *  c_frechie.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 22/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include <c_link.h>
#include <stdlib.h>
#include <string.h>

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

/* Our guess at the number of agents I'm going to fight in my lifetime
   (note that this is only a guess, not an upper limit. Do *not* take it as 
   gospel on the number of agents you're going to see. */
#define NUMBEROFAGENTSGUESS 100

/* The name of the n-th foe who has beaten us */
char (*defeatingFoes)[MAXFOENAMELEN] = NULL;

/* The length of the array, and how far we are along it */
size_t foesLen = 0;
unsigned int foesCount = 0;

/* an internal function - have I lost to a given foe? */
int haveLostTo( char * foeName ) {
    int foe;
    
    /* check every foe we know to have defeated us */
    for (foe=0; foe<foesCount; foe++) {
        if (strncmp( defeatingFoes[foe], foeName, MAXFOENAMELEN) == 0) {
            debugmsg( "%d\thaveLostTo( %s ) -> Yes\n", me, foeName );
            return 1;
        }
    }
    
    /* this foe not found */
    return 0;
}


ATTACKTYPE Attack( char * foeName ) {
	ATTACKTYPE attack;
    
	attack.realAttack =  RandomAttack();
	
    /* have I lost to this foe? */
    if ( haveLostTo(foeName) ) {
        /* Assume they are lying (FIXME: I'm not entirely sure why the python
           does what it does: I'm just duplicating.) */
        switch (attack.realAttack) {
            case rock:
                attack.promisedAttack = scissors;
                break;
            case paper:
                attack.promisedAttack = rock;
                break;
            default: /* attack = scissors */
                attack.promisedAttack = paper;
                break;
        }
    } else {
        /* be nice! */
        attack.promisedAttack = attack.realAttack;
    }

	
	return attack;
}


ITEMTYPE Defend( char * foeName, ITEMTYPE foePromisedAttack ) {
	ITEMTYPE defence;
	
    if (haveLostTo(foeName)) {
        /* They've screwed us in the past, assume they're lying and go for the
           kill. */
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
    } else {
        /* be nice! */
        defence = foePromisedAttack;
    }

    return defence;
}

/* This is so much less fun in C */
void Results( char * foeName, int isInstigatedByYou, ITEMTYPE yourItem, 
			 ITEMTYPE theirItem, ITEMTYPE promisedItem) {
	
    int foe;
    
    /* check to see if we've initialised our arrays */
	if (defeatingFoes == NULL) {
        defeatingFoes = calloc( NUMBEROFAGENTSGUESS, sizeof( MAXFOENAMELEN*sizeof(char) ) );
        foesLen = NUMBEROFAGENTSGUESS;
    }
    
    /* figure out if we lost, which is the only thing we care about
       if we didn't, move on. */
    if (RESULTOF[yourItem][theirItem] != lose) return;
    
    fprintf( stderr, "%d\tsaving loss from %s\n", me, foeName );
    
    /* if we've already lost the foe, don't store again */
    for (foe=0; foe<foesCount; foe++) {
        if (strncmp( defeatingFoes[foe], foeName, MAXFOENAMELEN ) == 0) {
            /* we've found it! */
            return;
        }
    }
    
    /* we haven't found the foe. add it, expanding the array if needed */
    if (foesCount==foesLen) {
        /* double the array size */
        defeatingFoes = realloc( defeatingFoes, foesLen*2*sizeof( MAXFOENAMELEN*sizeof(char) ) );
        foesLen *= 2;
    }
    
    strncpy( defeatingFoes[foesCount], foeName, MAXFOENAMELEN );
    foesCount++;
    
    return;
}

/* same for Cleanup() */

void Cleanup() {
	free(defeatingFoes);
}