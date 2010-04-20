# Alternative (obsolete) algorithms for selecting agents for battle.
# They're all a bit crap and only here for comparison purposes.


# Selects an opponent and removes it from the list of remaining potential opponents.
       # This is just an example, but the fact that the first agent will miss out on having
       # a fight picked with it it, and that the last agent won't get to pick a fight, seems
       # to not matter very much. Can probably be left as-is.
       def ChoosePair (self):
               # This approach forces each agent to defend once and attack once per round.
               # Keep track of the remaining population.
               remaining = self.population[:]
               agentID = random.randint (0,len(remaining)-1)
               defender = remaining.pop (agentID) # Not really a defender (try to work it out)!
               while len (remaining) > 1:
                       if defender.GetPoints () < 1:   # If the agent died before it got a chance to attack
                               attackerID = random.randint (0,len(remaining)-1)
                               attacker = remaining.pop (attackerID)
                       else: attacker = defender
                       defenderID = random.randint (0,len(remaining)-1)
                       defender = remaining.pop (defenderID)
                       yield attacker, defender

