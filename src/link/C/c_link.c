/*
 *  c_link.c
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 19/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include "c_link.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* You don't need to read this file.
   All you have to do is implement the bot functions defined in <c_link.h>
   This file sets up the I/O for you, as well as some utility functions and tables. 
 */

char ITEMNAMES[3][MAXITEMLEN] = {"Rock", "Paper", "Scissors"};

/* rock-rock     rock-paper     rock-scissors 
   paper-rock    paper-paper    paper-scissors
   scissors-rock scissors-paper scissors-scissors */  
   
RESULTTYPE RESULTOF[3][3] = { { tie, defender, attacker },
                              { attacker, tie, defender },
                              { defender, attacker, tie } };

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
	

RESULTTYPE stringToResult( char * str ) {
	if (strcasecmp( str, "Attacker" ) == 0) return attacker;
	if (strcasecmp( str, "Defender" ) == 0) return defender;
	if (strcasecmp( str, "Tie" ) == 0) return tie;
	/* If we reach this point, we've got real problems. */
	fprintf( stderr, "Attempt to convert invalid string \"%s\" into an ITEMTYPE! Aborting.\n", str );
	exit(EXIT_FAILURE);
	return -1;
}

int main( int argc, char * argv[] ) {
	srand( time( NULL ) );
	
	char command[MAXCOMMANDLEN];
	char foeName[MAXFOENAMELEN];
	char attItem[MAXITEMLEN], defItem[MAXITEMLEN], bluffItem[MAXITEMLEN];
	char didYouInstigate[MAXBOOLLEN];
	char winner[MAXRESULTLEN];
	int pointChange;
	void *thisInstance;

	ATTACKTYPE attack;
	ITEMTYPE defence;
	
	/* generate a random id for this bot. Hopefully it's unique
	   I can't use the UUID, because python doesn't pass it to me! */
	me = rand();
	
	// TODO: Get the UUID passed by python
	// Currently, just pass an empty string to the initialise function
	thisInstance = Initialise( "" );
	
	scanf( "%s", command );
	
	while (strcasecmp("BYE",command) != 0) {
		
		if (strcasecmp("ATTACK", command) == 0) {
			scanf( "%s", foeName );
			attack = Attack( thisInstance, foeName );
			printf("ATTACKING %s %s\n", ITEMNAMES[attack.realAttack], ITEMNAMES[attack.promisedAttack]);
		
		} else if (strcasecmp("DEFEND", command) == 0) {
			scanf( "%s %s", foeName, bluffItem );
			defence = Defend(thisInstance, foeName, stringToItem(bluffItem));
			printf("DEFENDING %s\n", ITEMNAMES[defence]);
		
		} else if (strcasecmp("RESULTS", command) == 0) {
			/* (foeName, isInstigatedByYou, winner, attItem, defItem, bluffItem, pointDelta) */
			scanf( "%s %s %s %s %s %s %d", foeName, didYouInstigate, winner, attItem, defItem, bluffItem, &pointChange );
			Results(thisInstance, foeName, (strcasecmp("True",didYouInstigate)==0), stringToResult(winner),
					stringToItem(attItem), stringToItem(defItem), stringToItem(bluffItem), pointChange);
			printf("OK\n");
		}
	
		fflush(stdout);
		fflush(stderr);
        
		// read the next command!
		scanf( "%s", command );
	}
	
	Cleanup(thisInstance);
	
	return 0;
}
