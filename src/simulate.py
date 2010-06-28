#!/usr/bin/python2.5
'''simulate.py - Runs a full simulation of the UCC Programming Competition with the provided agents.
Written by Luke Williams <shmookey@ucc.asn.au> for the UCC Programming Competition in 2008.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

# Import and add your agents here:
from link.C.c_agents import c_angel, c_lucifer, c_streetfighter, c_frenchie

from SampleAgents import Angel, Lucifer, Dummy, Frenchie, Streetfighter
Agents =  [c_angel,c_lucifer,c_streetfighter,c_frenchie]

####################################
# Developers only past this point! #
####################################

import sys
from uccProgComp import Supervisor

maxIterations = 150
startingPopulations = 10
verbose = False
trials = 1
usage = "Usage: rps [-v] [-i iterations=150] [-n starting_populations=10] [-t trials=1]"
for i in range (1,len(sys.argv)):
	if sys.argv[i] == "-i":
		try:
			maxIterations = int(sys.argv[i+1])
			i += 1
			continue
		except:
			print usage
			sys.exit(1)
	elif sys.argv[i] == "-n":
		try:
			startingPopulations = int(sys.argv[i+1])
			i += 1
			continue
		except:
			print usage
			sys.exit(1)
	elif sys.argv[i] == "-t":
		try:
			trials = int(sys.argv[i+1])
			i += 1
			continue
		except:
			print usage
			sys.exit(1)

	elif sys.argv[i] == "-v":
		verbose = True


iteration = 0
trial = 0
winners = {}
while trial < trials:
	sup = Supervisor ()
	for Agent in Agents: sup.RegisterAgent (Agent)
	sup.GeneratePopulation (startingPopulations)

	trial += 1
	iteration = 0
	while iteration < maxIterations and not sup.IsGameOver ():
		iteration += 1
		sup.Iterate ()
		if not verbose: continue
		print "Iteration %d:" % iteration
		for key, value in sup.GetStats ().iteritems():
			print "%s: Population=%d, Newborns=%d, Deaths=%d" % (key, value[0], value[1], value[2])
	winner = ("Error", -1)
	for key, value in sup.GetStats ().iteritems ():
		#print key, value
		if value[0] > winner[1]:
			winner = (key, value[0])
	if winner[0] in winners: winners[winner[0]] += 1
	else: winners[winner[0]] = 1
	#print "Winner: %s" % winner[0]

print "SCOREBOARD OVER %d TRIALS OF %d ROUNDS EACH" % (trials, maxIterations)
rawscoreboard = sorted ( [(score,player) for (player,score) in winners.items ()] , reverse=True )
scoreboard = []
for score, player in rawscoreboard:
	print "%s: %s" % (player, score)

