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
#define MAXRESULTLEN    10
#define MAXBOOLLEN		6
#define UUIDLEN	42	// 40 digits, 'L' and NULL

/********** Type definitions **********/

/* The type of item used in an attack or defence */
typedef enum {rock, paper, scissors} ITEMTYPE;

/* A result of a battle, in terms of who won */
typedef enum {attacker, defender, tie} RESULTTYPE;


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

/* Another useful table - who's the victor given an 
   attacker with first item vs defender with the second item? */
extern RESULTTYPE RESULTOF[3][3];

/********** Bot Function definitions **********/
/* You need to provide implementations for these to create a bot */

/* Initialise( yourName : string - name of this instance (you)
             ) : void * - A data pointer to represent this instance
 
 Called to create a new instance of this agent

 */
void *Initialise( char * yourName );

/* Defend( this : pointer - value returned from Initialise();
           foeName : string - the name of your foe;
           foePromisedAttack : ITEMTYPE - the item your foe promised to use
         ) : ITEMTYPE - the item you wish to use to defend;
 
 Called when your agent needs to defend itself.
 
 */
ITEMTYPE Defend( void * this, char * foeName, ITEMTYPE foePromisedAttack );


/* Attack( this: pointer - value returned from Initialise();
           foeName : string - the name of your foe
		 ) : ATTACKTYPE - the real and promised attack you wish to use

 Called when your agent needs to attack another agent.
 
 */
ATTACKTYPE Attack( void * this, char * foeName );


/* Results( this : pointer - value returned from Initialise();
            foeName : string - the name of your foe;
            isInstigatedByYou : 0=you defended/1=you attacked;
            winner : RESULTTYPE - who won
			attItem : ITEMTYPE - the item used to attack;
            defItem : ITEMTYPE - the item used to defend;
            bluffItem : ITEMTYPE - the item that was promised
            pointDelta : integer - how your points were affected.
          );

 Called after your agent battles another agent, to tell you how the battle goes.
 
 */
void Results( void * this, char * foeName, int isInstigatedByYou, RESULTTYPE winner,
              ITEMTYPE attItem, ITEMTYPE defItem, ITEMTYPE bluffItem,
              int pointDelta );

/* Cleanup( this: pointer - value returned from Initialise()
          );

   Called when your agent is no longer needed, either due to the round ending
   or due to your agent being eliminated.

 */
void Cleanup( void * this );
