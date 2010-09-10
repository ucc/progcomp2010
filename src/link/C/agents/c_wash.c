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

/* Implement the wash agent, that is by default nice but will 
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

/* data for each instance of my agent */
typedef struct {
	/* The name of the n-th foe who has beaten us */
	char (*defeatingFoes)[MAXFOENAMELEN];

	/* The length of the array, and how far we are along it */
	size_t foesLen;
	unsigned int foesCount;
} wash_data;


/* an internal function - have I lost to a given foe? */
int haveLostTo( wash_data * me, char * foeName ) {
    
	int foe;
    
    /* check every foe we know to have defeated us */
    for (foe=0; foe<me->foesCount; foe++) {
        if (strncmp( me->defeatingFoes[foe], foeName, MAXFOENAMELEN) == 0) {
            //debugmsg( "%d\thaveLostTo( %s ) -> Yes\n", me, foeName );
            return 1;
        }
    }
    
    /* this foe not found */
    return 0;
}

/* set up myself */
void * Initialise( char * myName ) {
	wash_data * me = malloc( sizeof( wash_data ) );
	
	me->defeatingFoes = calloc( NUMBEROFAGENTSGUESS, sizeof( MAXFOENAMELEN*sizeof(char) ) );
	me->foesLen = NUMBEROFAGENTSGUESS;
    me->foesCount = 0;
	
	return (void *) me;
}

/* Attack */
ATTACKTYPE Attack( void * this, char * foeName ) {
	wash_data * me = (wash_data *)this;
    
	ATTACKTYPE attack;
	
	attack.realAttack =  RandomAttack();
	
    /* have I lost to this foe? */
    if ( haveLostTo(me, foeName) ) {
        /* Assume they are lying  */
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

/* defend */
ITEMTYPE Defend( void * this, char * foeName, ITEMTYPE foePromisedAttack ) {
	wash_data * me = (wash_data *)this;
	
	ITEMTYPE defence;
	
    if (haveLostTo(me, foeName)) {
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
void Results( void * this, char * foeName, int isInstigatedByYou, 
			 RESULTTYPE winner, ITEMTYPE attItem, ITEMTYPE defItem, 
			 ITEMTYPE bluffItem, int pointDelta ) {
	
    wash_data * me = (wash_data *)this;
	
	int foe;
    
    /* figure out if we lost, which is the only thing we care about
       if we didn't, move on. */
    if ((winner == tie) || 
        (winner==attacker && isInstigatedByYou) ||
        (winner==defender && !isInstigatedByYou) ) return;
    
    //fprintf( stderr, "%d\tsaving loss from %s\n", me, foeName );
    
    /* if we've already lost the foe, don't store again */
    for (foe=0; foe<me->foesCount; foe++) {
        if (strncmp( me->defeatingFoes[foe], foeName, MAXFOENAMELEN ) == 0) {
            /* we've found it! */
            return;
        }
    }
    
    /* we haven't found the foe. add it, expanding the array if needed */
    if (me->foesCount==me->foesLen) {
        /* double the array size. This should error check, but doesn't */
        me->defeatingFoes = realloc( me->defeatingFoes, 
		                             me->foesLen*2*sizeof( MAXFOENAMELEN*sizeof(char) ) );
        me->foesLen *= 2;
    }
    
    strncpy( me->defeatingFoes[me->foesCount], foeName, MAXFOENAMELEN );
    me->foesCount++;
    
    return;
}

/* Cleanup */
void Cleanup( void * this ) {
	wash_data * me = (wash_data *) this;
	free(me->defeatingFoes);
	free(me);
}