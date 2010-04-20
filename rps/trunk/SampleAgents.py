'''SampleAgents.py - A collection of sample agents for playing Rock Paper Scissors.
Written by Luke Williams <shmookey@ucc.asn.au> for the UCC Programming Competition in 2008.
Requires Python 2.5.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

from uccProgComp import BaseAgent, LearningAgent, RandomAttack
from rpsconst import *

# Angel is a very simple bot that always tells the truth and expects others to do the same.
class Dummy (BaseAgent):
	def Attack (self, foe):
		return Paper, Paper
	def Defend (self, foe, bluff):
		return bluff

class Angel (BaseAgent):
	def Attack (self, foe):
		attack = RandomAttack ()	# Chooses randomly from Rock, Paper, Scissors
		return attack, attack		# Tells the truth for its bluff.
	def Defend (self, foe, bluff):
		return bluff			# Trusts them to be going for a tie.

# Lucifer here is the opposite. He always lies expecting people to be good and always goes for the kill.
class Lucifer (BaseAgent):
	def Attack (self, foe):
		attack = RandomAttack ()
		if attack == Rock: bluff = Scissors	# Here we choose the thing
		elif attack == Paper: bluff = Rock	# that will hurt them
		else: bluff = Paper			# if they go for a tie.
		return attack, bluff
	def Defend (self, foe, bluff):
		if bluff == Rock: attack = Paper	# Here we trust that they
		elif bluff == Paper: attack = Scissors	# are telling the truth.
		else: attack = Rock			# And we try to kill them.
		return attack
#	def Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta):
#		BaseAgent.Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta)
#		print "I just scored " + str(pointDelta) + " points!"


# Streetfighter assumes everyone has it in for him.
class Streetfighter (BaseAgent):
	def Attack (self, foe):
		attack = RandomAttack ()
		if attack == Rock: bluff = Paper	# Here we choose the thing
		elif attack == Paper: bluff = Scissors	# that will hurt them
		else: bluff = Rock			# if they try to kill us.
		return attack, bluff
	def Defend (self, foe, bluff):
		if bluff == Rock: attack = Scissors	# Here we assume that they
		elif bluff == Paper: attack = Rock	# are lying, trying to kill us.
		else: attack = Paper			# And we try to kill them.
		return attack

# This is our first bot with any sort of learning capability, based on the LearningAgent base.
# Experienced programmers might opt to write their own learning code based on BaseAgent, but it's up to you.
# Frenchie is a simple bot that is by default nice but will permanently turn against any agent that betrays it.
class Frenchie (LearningAgent):
	def Attack (self, foe):
		attack = RandomAttack ()
		if Loss in LearningAgent.GetWinHistory (self, foe):
			if attack == Rock: bluff = Scissors
			elif attack == Paper: bluff = Rock
			else: bluff = Paper
		else:
			bluff = attack
		return attack, bluff
	def Defend (self, foe, bluff):
		if Loss in LearningAgent.GetWinHistory (self, foe):
			if bluff == Rock: attack = Scissors	# They've fucked us in the past,
			elif bluff == Paper: attack = Rock	# so we assume they're lying and
			else: attack = Paper			# hoping we go for a kill.
		else:
			attack = bluff
		return attack


# If you want to implement your own Results () callback, you have to call the parent class's first:
class Blank (BaseAgent):
	def Attack (self, foe):
		return Paper, Paper
	def Defend (self, foe, bluff):
		return bluff
	def Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta):
		BaseAgent.Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta)
		# Now you can do your own thing

