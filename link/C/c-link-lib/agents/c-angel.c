/*
 *  c-angel.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 20/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include <c_link.h>

/* Implement the angel bot, which always tells the truth
   and expects others to do the same */

ATTACKTYPE Attack( char * foe_name ) {
	ATTACKTYPE attack;
	
	attack.realAttack =  RandomAttack();		/* Chooses randomly from Rock, Paper, Scissors */ 
	attack.promisedAttack = attack.realAttack;	/* Tells the truth for its bluff */

	return attack;
}

ITEMTYPE Defend( char * foeName, ITEMTYPE foePromisedAttack ) {
	return foePromisedAttack;	/* Trusts them to be going for a tie */
}

/* You need to define a results function, even if it isn't used
   (otherwise the linker will complain) */
void Results( char * foeName, int isInstigatedByYou, ITEMTYPE yourItem, 
			 ITEMTYPE theirItem, ITEMTYPE promisedItem) {
	
	return;	/* Ignore whatever just happened. */
}