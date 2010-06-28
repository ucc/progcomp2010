/*
 *  c_link.h
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 19/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

#include <stdio.h>

#define MAXCOMMANDLEN	15
#define MAXFOENAMELEN	50
#define MAXITEMLEN		10
#define MAXBOOLLEN		6

/********** Type definitions **********/

/* The type of item used in an attack or defence */
typedef enum {rock, paper, scissors} ITEMTYPE;

/* A result of a battle */
typedef enum {win, lose, tie} RESULTTYPE;


/* An attack, consisting of the real attack and the attack promised */
typedef struct {
	ITEMTYPE realAttack;
	ITEMTYPE promisedAttack;
} ATTACKTYPE;


/********** Utility Function definitions **********/
/* These are implemented in c-link.c, and automagically linked in */

/* prints a debug message. Same arguments as printf().
   (you can't use printf because it is used to talk between
    the agent and supervisor) 
 */

#define debugmsg(x...) fprintf(stderr, x)

/* A (hopefully) unique identifier for this particular instance of your agent,
   to help with debugging */
int me;


/* Returns a random item */

ITEMTYPE RandomAttack();

/* A useful translation table
   eg debugmsg( "I use %s.\n", ITEMNAMES[rock] ); */

extern char ITEMNAMES[3][MAXITEMLEN];

/* Another useful table - what's the result of the 
   first item vs the second item? */
extern RESULTTYPE RESULTOF[3][3];

/********** Bot Function definitions **********/
/* You need to provide implementations for these to create a bot */

/* Defend( foeName : string - the name of your foe;
           foePromisedAttack : ITEMTYPE - the item your foe promised to use
         ) : ITEMTYPE - the item you wish to use to defend;
 
 Called when your agent needs to defend itself.
 
 */
ITEMTYPE Defend( char * foeName, ITEMTYPE foePromisedAttack );


/* Attack( foeName : string - the name of your foe
		 ) : ATTACKTYPE - the real and promised attack you wish to use

 Called when your agent needs to attack another agent.
 
 */
ATTACKTYPE Attack( char * foeName );


/* Results( foeName : string - the name of your foe;
            isInstigatedByYou : 0=you defended/1=you attacked;
			yourItem : ITEMTYPE - the item you used;
            theirItem : ITEMTYPE - the item they used;
            promisedItem : ITEMTYPE - the item that was promised
          );

 Called after your agent battles another agent, to tell you how the battle goes.
 
 */
void Results( char * foeName, int isInstigatedByYou, ITEMTYPE yourItem, 
			  ITEMTYPE theirItem, ITEMTYPE promisedItem);

/* Cleanup();

   Called when your agent is no longer needed, either due to the round ending
   or due to your agent being eliminated.

 */
void Cleanup();