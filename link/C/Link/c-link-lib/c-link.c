/*
 *  c-link.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 19/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include "c-link.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* If you just want to write a bot, you don't need to read this file.
   This merely sets up the I/O for you, so all you have to do is define the bot
   functions defined in <c-link.h>
 
   The only reason you would care about this info is if you want to use pointChange
   and/or childSpawned parameters from the RESULTS call, which are otherwise discarded.
 */

char ITEMNAMES[3][MAXITEMLEN] = {"Rock", "Paper", "Scissors"};


ITEMTYPE RandomAttack() {
	return (ITEMTYPE)rand()%3;
}

ITEMTYPE stringToItem( char * str ) {
	if (strcasecmp( str, "Rock" ) == 0) return rock;
	if (strcasecmp( str, "Paper" ) == 0) return paper;
	if (strcasecmp( str, "Scissors" ) == 0) return scissors;
	/* If we reach this point, we've got real problems. */
	fprintf( stderr, "Attempt to convert invalid string \"%s\" into an ITEMTYPE! Aborting.\n", str );
	exit(EXIT_FAILURE);
	return -1;
}
	

int main( int argc, char * argv[] ) {
	srand( time( NULL ) );
	
	char command[MAXCOMMANDLEN];
	char foeName[MAXFOENAMELEN];
	char yourItem[MAXITEMLEN], theirItem[MAXITEMLEN], promisedItem[MAXITEMLEN];
	char didYouInstigate[MAXBOOLLEN], childSpawned[MAXBOOLLEN];
	int pointChange;
	
	ATTACKTYPE attack;
	ITEMTYPE defence;
	
	scanf( "%s", command );
	
	while (strcasecmp("BYE",command) != 0) {
		
		if (strcasecmp("ATTACK", command) == 0) {
			scanf( "%s", foeName );
			attack = Attack( foeName );
			printf("ATTACKING %s %s\n", ITEMNAMES[attack.realAttack], ITEMNAMES[attack.promisedAttack]);
		
		} else if (strcasecmp("DEFEND", command) == 0) {
			scanf( "%s %s", foeName, promisedItem );
			defence = Defend(foeName, stringToItem(promisedItem));
			printf("DEFENDING %s\n", ITEMNAMES[defence]);
		
		} else if (strcasecmp("RESULTS", command) == 0) {
			scanf( "%s %s %s %s %s %d %s", foeName, didYouInstigate, yourItem, theirItem, promisedItem, &pointChange, childSpawned );
			Results(foeName, (strcasecmp("False",didYouInstigate)==0),
					stringToItem(yourItem), stringToItem(theirItem), stringToItem(promisedItem));
			printf("OK\n");
		}
	
		// read the next command!
		scanf( "%s", command );
	}
	
	return 0;
}