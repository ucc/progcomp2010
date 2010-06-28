'''externAgent.py - a bot shell for talking to external I/O bots.
Written by Daniel Axtens <dja@ucc.asn.au> for the UCC Programming Competition in 2010.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

from uccProgComp import BaseAgent, LearningAgent, RandomAttack
from rpsconst import *
from pexpect import pexpect

class externAgent (BaseAgent):
    
    def __init__ (self, externName):
        BaseAgent.__init__(self)
        self.process = pexpect.spawn(externName)
        self.process.delaybeforesend=0
        
        
    def stringToItem( self, str ):
        if str == "Rock":
            return Rock
        elif str == "Paper":
            return Paper
        elif str == "Scissors":
            return Scissors
        else:
            # Something has gone wrong!
            print "Error: tried to convert \"%s\" into an item!" % str
            return None

    def itemToString( self, item ):
        if item == Rock:
            return "Rock"
        elif item == Paper:
            return "Paper"
        elif item == Scissors:
            return "Scissors"
        else:
            # Something has gone wrong!
            print "Error: tried to convert '%d' to Rock/Paper/Scissors string!" % item
        
    def Attack (self, foe):
        self.process.sendline( "ATTACK %s" % foe )
        self.process.expect( "ATTACKING (.+) (.+)\r\n" )
        attack, bluff = self.process.match.groups()
        attack, bluff = attack.strip(), bluff.strip()
        return self.stringToItem(attack), self.stringToItem(bluff)
        
    def Defend( self, foe, bluff ):
        #print "DEFEND %s %s" % (foe, self.itemToString(bluff))
        self.process.sendline( "DEFEND %s %s" % (foe, self.itemToString(bluff) ) )
        self.process.expect( "DEFENDING (.+)\r\n" )
        #print '------------------ ', self.process.match.groups()[0].strip()
        defence = self.process.match.groups()[0].strip()
        return self.stringToItem(defence)
        
    def __del__(self):
        self.process.close(True)
