# add your agents to this file by copying the definition and adjusting
# you then need to modify simulate.py

from link.externAgent import externAgent

class c_angel (externAgent):
	def __init__ (self):
		externAgent.__init__(self, "./link/C/agents/c_angel")

class c_lucifer (externAgent):
	def __init__ (self):
		externAgent.__init__(self, "./link/C/agents/c_lucifer")

class c_streetfighter (externAgent):
	def __init__ (self):
		externAgent.__init__(self, "./link/C/agents/c_streetfighter")

class c_frenchie (externAgent):
	def __init__ (self):
		externAgent.__init__(self, "./link/C/agents/c_frenchie")
