# add your agents to this file by copying the definition and adjusting
# you then need to modify simulate.py

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

class c_frenchie (cAgent):
	def __init__ (self):
		cAgent.__init__(self, "./link/C/agents/c_frenchie")
