'''CSampleAgents.py
An areana that runs the sample bots in C.
Written by Daniel Axtens <dja@ucc.asn.au> for the UCC Programming Competition in 2010.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

from link.C.c_agents import c_angel, c_lucifer, c_streetfighter, c_frenchie

class arena:
	Agents =  [c_angel,c_lucifer,c_streetfighter,c_frenchie]
