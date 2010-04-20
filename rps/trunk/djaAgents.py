from uccProgComp import BaseAgent, LearningAgent, RandomAttack
from rpsconst import *

# BOFH is something of a cross between Frechie and Lucifer

class BOFH (LearningAgent):
	def Attack (self, foe):
		attack = RandomAttack ()
		
		return attack, bluff
	def Defend (self, foe, bluff):
		if bluff == Rock: attack = Scissors	# Here we assume that they
		elif bluff == Paper: attack = Rock	# are lying, trying to kill us.
		else: attack = Paper			# And we try to kill them.
		return attack

	def Attack (self, foe):
		attack = RandomAttack ()
		if len(LearningAgent.GetWinHistory (self, foe)) > 0:
			if attack == Rock: bluff = Paper	# Here we choose the thing
			elif attack == Paper: bluff = Scissors	# that will hurt them
			else: bluff = Rock			# if they try to kill us.
		else:
			if attack == Rock: bluff = Scissors	# Here we choose the thing
			elif attack == Paper: bluff = Rock	# that will hurt them
			else: bluff = Paper			# if they go for a tie.
		return attack, bluff
		
	def Defend (self, foe, bluff):
		if len(LearningAgent.GetWinHistory (self, foe)) > 0:
			if bluff == Rock: attack = Scissors	# They've fucked us in the past,
			elif bluff == Paper: attack = Rock	# so we assume they're lying and
			else: attack = Paper			# hoping we go for a kill.
		else:
			if bluff == Rock: attack = Paper	# Here we trust that they
			elif bluff == Paper: attack = Scissors	# are telling the truth.
			else: attack = Rock			# And we try to kill them.
		return attack

#Fish is somewhat intelligent; it builds up trust and then stabs you in the back.
# If Fish detects that a bot is being predictably nice (tie 2+ times in a row), it will attack.
# If Fish detects that a bot has betrayed it (Loss), it will attack.
# Otherwise, Fish is nice.

class Fish (LearningAgent):
	def Attack (self, foe):
		#print "Attacking" , foe
		#print LearningAgent.GetWinHistory (self, foe)
		attack = RandomAttack ()
		
		history = LearningAgent.GetWinHistory (self, foe)
		
		#no history; be nice
		if len(history) == 0:
			bluff = attack
		
		#if we just lost to them, try to destroy them.
		elif Loss == history[-1] or (len(history)>1 and [Tie,Tie] == history[-2:-1]):
			if attack == Rock: bluff = Scissors
			elif attack == Paper: bluff = Rock
			else: bluff = Paper
		else:
			bluff = attack
		return attack, bluff
		
		
	def Defend (self, foe, bluff):
		
		history = LearningAgent.GetWinHistory (self, foe)
		
		if len(history) > 0 and Loss == history[-1]:
			if bluff == Rock: attack = Scissors	# They've fucked us in the past,
			elif bluff == Paper: attack = Rock	# so we assume they're lying and
			else: attack = Paper			# hoping we go for a kill.
		else:
			attack = bluff
		return attack