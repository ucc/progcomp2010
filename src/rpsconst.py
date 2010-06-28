'''rpsconst.py - A precarious collection of constants for RPS simulation.
Written by Luke Williams <shmookey@ucc.asn.au> for the UCC Programming Competition in 2008.

Licensed under an MIT-style license: see the LICENSE file for details.
'''

Rock = 0
Paper = 1
Scissors = 2

rpsStrings=["Rock","Paper","Scissors"]

Attacker = 0
Defender = 1
Tie = 2

adtStrings=["Attacker","Defender","Tie"]

Bluff = 0
Truth = 1
Win = 3
Loss = 4
# EOF. Stop reading now, kid, you'll only hurt yourself.
resultTable = [[Tie,Defender,Attacker],[Attacker,Tie,Defender],[Defender, Attacker, Tie]]
pointsTable = [[0,0],[0,0],[0,0]]
