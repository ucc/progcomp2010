/*
 *  c_lucifer.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 20/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */


#include <c_link.h>

/* Implement the lucifer bot, which always lies expecting people to be good
   and always goes for the kill */

ATTACKTYPE Attack( char * foe_name ) {
	ATTACKTYPE attack;
	
	attack.realAttack =  RandomAttack();
	
	/* Here we choose the thing that will hurt them if they go for a tie */
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
	
	return attack;
}

/* Here we trust that they are telling the truth. And we try to kill them. */
ITEMTYPE Defend( char * foeName, ITEMTYPE foePromisedAttack ) {
	ITEMTYPE defence;
	switch (foePromisedAttack) {
		case rock:
			defence = paper;
			break;
		case paper:
			defence = scissors;
			break;
		default:
			defence = rock;
			break;
	}
    return defence;
}

/* You need to define a results function, even if it isn't used
 (otherwise the linker will complain) */
void Results( char * foeName, int isInstigatedByYou, ITEMTYPE yourItem, 
			 ITEMTYPE theirItem, ITEMTYPE promisedItem) {
	
	return;	/* Ignore whatever just happened. */
}

/* same for Cleanup() */

void Cleanup() {
	return;
}