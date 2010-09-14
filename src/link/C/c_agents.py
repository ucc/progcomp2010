# add your agents to this file by copying the definition and adjusting
# you then need to make sure there's an arena that imports your agent

from link.cAgent import cAgent

class c_angel (cAgent):
	def __init__ (self):
		cAgent.__init__(self, "./link/C/agents/c_angel")

class c_lucifer (cAgent):
	def __init__ (self):
		cAgent.__init__(self, "./link/C/agents/c_lucifer")

class c_streetfighter (cAgent):
	def __init__ (self):
		cAgent.__init__(self, "./link/C/agents/c_streetfighter")

class c_wash (cAgent):
	def __init__ (self):
		cAgent.__init__(self, "./link/C/agents/c_wash")
