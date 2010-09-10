/*
 *  c_streetfighter.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 20/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */


#include <c_link.h>

/* Implement the streetfighter bot, which thinks everyone has it in for him. */

void * Initialise( char * myName ) {
	return NULL;
}

ATTACKTYPE Attack( void * this, char * foe_name ) {
	ATTACKTYPE attack;
	
	attack.realAttack =  RandomAttack();
	
	/* Here we choose the thing that will hurt them if they go for the kill */
	switch (attack.realAttack) {
		case rock:
			attack.promisedAttack = paper;
			break;
		case paper:
			attack.promisedAttack = scissors;
			break;
		default: /* attack = scissors */
			attack.promisedAttack = rock;
			break;
	}
	return attack;
}

/* Here we assume they are lying, trying to kill us. And we try to kill them. */
ITEMTYPE Defend( void * this, char * foeName, ITEMTYPE foePromisedAttack ) {
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
    return defence;
}

/* You need to define a results function, even if it isn't used
 (otherwise the linker will complain) */
void Results( void * this, char * foeName, int isInstigatedByYou, RESULTTYPE winner,
             ITEMTYPE attItem, ITEMTYPE defItem, ITEMTYPE bluffItem,
             int pointDelta ) {
	
	return;	/* Ignore whatever just happened. */
}

/* same for Cleanup() */

void Cleanup( void * this ) {
	return;
}
