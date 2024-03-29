'''uccProgComp.py - A supervisor candidate for Rock Paper Scissors.
Written by Luke Williams <shmookey@ucc.asn.au> for the UCC Programming Competition in 2008.
Requires Python 2.5.

Licensed under an MIT-style license: see the LICENSE file for details.
'''


import random, uuid
random.seed ()

from rpsconst import *
from conf import *

def Debug (f):
	def g (*args):
		if DEBUG:
			print f.__name__, args[1].__class__.__name__, args[1].GetID ()
		return f (*args)
	return g

class BaseAgent:
	def __init__ (self):
		self.id = uuid.uuid4().int
		self.__points = DEFAULT_HEALTH
		# The index will be changing all the time. It can go stale as soon as something dies.
		# So use it cautiously.
		self.__currentIndex = 0
		self.__reproduced = False
		self.__age = 0

	def GetCurrentIndex (self):
		return self.__currentIndex
	
	def SetCurrentIndex (self, index):
		self.__currentIndex = index

	def GetID (self):
		return self.id
	
	def GetPoints (self):
		return self.__points

	def SetPoints (self, points):
		self.__points = points

	def Defend (self, foe, bluff):
		return Rock
	
	def Attack (self, foe):
		return Rock

	def IsDead (self):
		return self.__points <= DIE_HEALTH

	def Reproduced (self):
		self.__points = DEFAULT_HEALTH
		self.__reproduced = True

	def HasReproduced (self):
		return self.__reproduced

	def SetReproduced (self, repro):
		self.__reproduced = repro

	def Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta):
		self.__points += pointDelta
		self.__age += 1
		if self.__age > MAX_AGE: self.__points = DIE_HEALTH

class LearningAgent (BaseAgent):
	def __init__ (self):
		BaseAgent.__init__ (self)
		self.winHistory = {}
	
	def Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta):
		BaseAgent.Results (self, foeName, wasAttacker, winner, attItem, defItem, bluffItem, pointDelta)
		if wasAttacker:
			if winner == Attacker: result = Win
			elif winner == Tie: result = Tie
			else: result = Loss
		else:
			if winner == Attacker: result = Loss
			elif winner == Tie: result = Tie
			else: result = Win
			
		if foeName in self.winHistory: self.winHistory [foeName].append (result)
		else: self.winHistory [foeName] = [result]

	def GetWinHistory (self, foeName):
		if foeName in self.winHistory: return self.winHistory [foeName]
		else: return []

class Supervisor:
	def __init__ (self):
		# The full list of living agents
		self.population = []
		# A list of classes for each agent type
		self.agentTypes = []
		# The current iteration
		self.iteration = 0
		self.agentStats = {}
		self.pendingDeaths = []

	def RegisterAgent (self, agent):
		self.agentTypes.append (agent)

	def GeneratePopulation (self, nAgentsPerClass):
		for Agent in self.agentTypes:
			for i in range (0,nAgentsPerClass): self.population.append (Agent ())
			self.agentStats [str(Agent)] = [nAgentsPerClass,0,0]
			if DEBUG: print "Created " + str(nAgentsPerClass) + " instances of " + Agent.__name__

	def Iterate (self):
		self.ClearStats ()
		self.UpdateIndexes ()
		self.iteration += 1
		for attacker, defender in self.Select ():
			attack, bluff = attacker.Attack (defender.GetID ())
			defense = defender.Defend (attacker.GetID (), bluff)
			winner = resultTable [attack] [defense]
			attPoints, defPoints = pointsTable [winner][attack == bluff]
			attacker.Results (defender.GetID (), True, winner, attack, defense, bluff, attPoints)
			defender.Results (attacker.GetID (), False, winner, attack, defense, bluff, defPoints)
			if attacker.IsDead (): self.KillAgent (attacker)
			elif attacker.GetPoints () >= REPRODUCE_HEALTH: self.SpawnAgent (attacker)
			if defender.IsDead (): self.KillAgent (defender)
			elif defender.GetPoints () >= REPRODUCE_HEALTH: self.SpawnAgent (defender)

	def IsGameOver (self):
		if self.population == []: return True
		liveAgents = [id for id,stats in self.agentStats.iteritems () if stats[0] > 0]
		print liveAgents
		if len(liveAgents) < 2: return True
		return False
	
	# This is needed because when we pick the players we also need a way of identifying them in the
	# population list without manually searching each time. O(n) each iteration is better than O(n)
	# each death. It also resets the check for if the agent has reproduced this round.
	def UpdateIndexes (self):
		for agentID in reversed(sorted(self.pendingDeaths)): del self.population [agentID]
		for index, agent in enumerate(self.population): 
			agent.SetCurrentIndex (index)
			agent.SetReproduced (False)
		self.pendingDeaths = []

	@Debug
	def KillAgent (self, agent):
		self.pendingDeaths.append (agent.GetCurrentIndex ())
		stat = self.agentStats [str(agent.__class__)]
		stat [0] -= 1
		stat [2] += 1

	@Debug
	def SpawnAgent (self, agent):
		if MAX_TOTAL_AGENTS > 0 and len(self.population) - len(self.pendingDeaths) < MAX_TOTAL_AGENTS:
			child = agent.__class__ ()
			self.population.append (child)
			agent.Reproduced ()
			stat = self.agentStats [str(agent.__class__)]
			stat [0] += 1
			stat [1] += 1

	def Select (self):
		# This approach causes agents to keep fighting until they've either died or reproduced.
		remaining = self.population[:]
		attackerID = defenderID = random.randint (0,len(remaining)-1)
		attacker = defender = remaining [attackerID]
		while len (remaining) >= 2:
			# Check to see if the attacker from last round needs to be dropped.
			if attacker.IsDead () or attacker.HasReproduced ():
				remaining.pop (attackerID)
				if not len(remaining) >= 2: continue
				if defenderID > attackerID: defenderID -= 1
			# Check to see if the defender from last round is up for some attacking.
			if defender.IsDead () or defender.HasReproduced ():
				remaining.pop (defenderID)
				if not len(remaining) >= 2: continue
				attackerID = random.randint (0,len(remaining)-1)
				attacker = remaining [attackerID]
			else:
				attacker = defender
				attackerID = defenderID
			defender = None
			defenderID = random.randint (0,len(remaining)-2)
			if defenderID >= attackerID: defenderID += 1
			defender = remaining [defenderID]

			yield attacker, defender

	def GetStats (self):
		return self.agentStats

	def ClearStats (self):
		for agent in self.agentTypes: self.agentStats [str(agent)] = self.agentStats [str(agent)] [:1] + [0,0]

def RandomAttack ():
	return random.randint (0,2)
