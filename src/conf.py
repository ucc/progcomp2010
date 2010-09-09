''' Configuration settings for the RPS simulator. '''

from rpsconst import *

# Enable for verbose output. (or use -v)
VERBOSE = False

# Enable for even more verbose output.
DEBUG = False

# How many iterations to run before quitting.
MAX_ITERATIONS = 1000

# How many of each agent to create initially.
STARTING_POPULATION = 10

# ???
TRIALS = 1

# How much health to give each agent on birth.
DEFAULT_HEALTH = 50

# How much health at which an agent can reproduce.
REPRODUCE_HEALTH = 100

# How much health at which an agent dies.
DIE_HEALTH = 0

# The age at which to kill any agent.
MAX_AGE = 100


# Cap the number of agents:
MAX_TOTAL_AGENTS = 255

# Game dynamics:
#                WINNER          TRUTH          ATTPoints, DEFPoints
pointsTable     [Attacker]      [False] =       (3, -3)
pointsTable     [Attacker]      [True]  =       (2, -2)
pointsTable     [Defender]      [False] =       (-2, 2)
pointsTable     [Defender]      [True]  =       (-3, 3)
pointsTable     [Tie]           [False] =       (0, 0)
pointsTable     [Tie]           [True]  =       (1, 1)
