/*
 *  c-link.h
 *  c-link-lib
 *
 *  Created by Daniel Axtens on 19/04/10.
 *  Licensed under an MIT-style license: see the LICENSE file for details.
 *
 */

/********** Type definitions **********/

/* The type of item used in an attack or defence */
typedef enum {rock, paper, scissors} ITEMTYPE;


/* An attack, consisting of the real attack and the attack promised */
typedef struct {
	ITEMTYPE realAttack;
	ITEMTYPE promisedAttack;
} ATTACKTYPE;

/********** Utility Function definitions **********/

/* Returns a random item */

ITEMTYPE RandomAttack();

/********** Bot Function definitions **********/

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