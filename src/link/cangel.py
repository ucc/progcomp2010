from uccProgComp import BaseAgent, LearningAgent, RandomAttack
from externAgent import externAgent
from rpsconst import *

class CAngel (externAgent):
	def __init__ (self):
		externAgent.__init__(self, "./link/C/c-link-lib/agents/c-angel")
		
