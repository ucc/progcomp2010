'''externAgent.py - a bot shell for talking to external I/O bots.
Written by Daniel Axtens <dja@ucc.asn.au> for the UCC Programming Competition in 2010.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

from uccProgComp import BaseAgent, LearningAgent, RandomAttack
from rpsconst import *
#from pexpect import pexpect

import sys, subprocess

class externAgent (BaseAgent):

    def __init__ (self, externName):
        BaseAgent.__init__(self)
        try:
            self.process = subprocess.Popen(externName, stdin=subprocess.PIPE, 
                                            stdout=subprocess.PIPE,
                                            universal_newlines=True)
        except Exception, e:
            print ("Error spawning \"%s\": " % externName), e
           
        self.process.stdin.write ( ' '.join( ["HI", repr(self.GetID()), "\r\n"] ) )

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
            raise ValueError( "tried to convert \"%s\" into an item!" % str );
            return None

    def itemToString( self, item ):
        return rpsStrings[item]
        
        #if item == Rock:
        #    return "Rock"
        #elif item == Paper:
        #    return "Paper"
        #elif item == Scissors:
        #    return "Scissors"
        #else:
        #    # Something has gone wrong!
        #    print "Error: tried to convert '%d' to Rock/Paper/Scissors string!" % item
        #    # raise an exception
        #    raise ValueError("tried to convert '%d' to Rock/Paper/Scissors string!" % item)
        
    def resultToString( self, result ):
        return adtStrings[result]
    
        #if result == Attacker:
        #    return "Attacker"
        #elif result == Defender:
        #    return "Defender"
        #elif result == Tie:
        #    return "Tie"
        #else:
        #    # Something has gone wrong!
        #    print "Error: tried to convert '%d' to Attacker/Defender/Tie string!" % result
        #    # raise an exception
        #    raise ValueError("tried to convert '%d' to Attacker/Defender/Tie string!" % result)
        
    def Attack (self, foe):
        self.process.stdin.write ( ' '.join( ["ATTACK", repr(foe), "\r\n"] ) )
        #print >>sys.stderr, self.process.stderr.readlines()
        result = self.process.stdout.readline().split()
        try:
            attack, bluff = self.stringToItem( result[1] ), self.stringToItem( result[2] )
            return attack, bluff
        except:
            #agent is insane
            print "Agent is insane:", self, self.GetID()
            pass
        
    def Defend (self, foe, bluff ):
        self.process.stdin.write ( ' '.join( ["DEFEND", repr(foe), self.itemToString( bluff ), "\r\n"] ) )
        #print >>sys.stderr, self.process.stderr.readlines()
        result = self.process.stdout.readline().split()
        try:
            defence = self.stringToItem( result[1] )
            return defence
        except:
            #agent is insane
            print "Agent is insane:", self, self.GetID()
            pass

    def Results (self, foe, isInstigatedByYou, winner, attItem, defItem, bluffItem, pointDelta):
        
        BaseAgent.Results (self, foe, isInstigatedByYou, winner, attItem, 
                           defItem, bluffItem, pointDelta)
        
        string = ' '.join( [ "RESULTS", repr(foe), repr(isInstigatedByYou), 
                             self.resultToString(winner), 
                             self.itemToString( attItem ), 
                             self.itemToString( defItem ),
                             self.itemToString( bluffItem ), repr(pointDelta),
                             "\r\n" ] )
        
        #string = "RESULTS %s %s %s %s %s %s %d\r\n" % (foe, isInstigatedByYou, 
        #                     self.resultToString(winner), 
        #                     self.itemToString( attItem ), 
        #                     self.itemToString( defItem ),
        #                     self.itemToString( bluffItem ), pointDelta)
        #print string
        
        self.process.stdin.write ( string )
        self.process.stdout.readline() # read and discard (should be "OK")
        
        # we kill off the process here because otherwise the class doesn't get
        # destroyed until the end of the iteration. This causes us to hold more
        # than MAX_TOTAL_AGENTS open for a period of time, which is a bad thing.
        if self.IsDead():
            try:
                self.process.communicate( "BYE\r\n" )
            except Exception, e:
                print "Error in BYE:", self, ":", e
            
            try:
                self.process.kill()
            except:
                None


    def __del__(self):
        #unless we're being deleted unexpectedly, this is a no-op.
        if self.process.poll() == None:
            try:
                self.process.communicate( "BYE\r\n" )
            except Exception, e:
                print "Error in BYE:", self, ":", e
            
            try:
                self.process.kill()
            except:
                None
