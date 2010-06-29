'''cAgent.py - a bot shell for talking to C bots.
Written by Daniel Axtens <dja@ucc.asn.au> for the UCC Programming Competition in 2010.

This is a separate class to externAgent so that changes can be made
without requiring C agents to have their wrapper scripts rewritten.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

from link.externAgent import externAgent

class cAgent (externAgent):
    """A class for handling agents in C. 
    A subclass of externAgent so that changes can be made to how all external
    agents are handled, or how all C agents are handled, without requiring C 
    agents to have their wrapper scripts rewritten. Use this in preference to 
    externAgent for C agents."""