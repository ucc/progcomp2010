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

ITEMTYPE RandomAttack() {
	return (ITEMTYPE)rand()%3;
}


int main( int argc, char * argv[] ) {
	srand( time( NULL ) );
	return 0;
}