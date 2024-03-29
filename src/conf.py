''' Configuration settings for the RPS simulator. '''

from rpsconst import *

# Enable for verbose output. (or use -v)
VERBOSE = False

# Enable for even more verbose output.
DEBUG = False

# How many iterations to run before quitting.
# This is 100 for the short version and 1000 for the long version
MAX_ITERATIONS = 100

# How many of each agent to create initially. (or use -n)
STARTING_POPULATION = 10

# Number of times the simulation is run. (or use -t)
TRIALS = 1

# How much health to give each agent on birth.
DEFAULT_HEALTH = 50

# How much health at which an agent can reproduce.
REPRODUCE_HEALTH = 100

# How much health at which an agent dies.
DIE_HEALTH = 0

# The age at which to kill any agent.
# This is 100 for the short version and 1000 for the long version
MAX_AGE = 100

# Cap the number of agents (set to 0 to disable)
# you may also need to run ulimit -n <some big number like 1000>
MAX_TOTAL_AGENTS = 255

# Game dynamics:
#                WINNER          TRUTH          ATTPoints, DEFPoints
pointsTable     [Attacker]      [False] =       (3, -3)
pointsTable     [Attacker]      [True]  =       (2, -2)
pointsTable     [Defender]      [False] =       (-2, 2)
pointsTable     [Defender]      [True]  =       (-3, 3)
pointsTable     [Tie]           [False] =       (0, 0)
pointsTable     [Tie]           [True]  =       (1, 1)
