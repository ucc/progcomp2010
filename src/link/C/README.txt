Welcome to the C SDK and link library.

If you want to enter in C, you've come to the right place.

== Compiling and watching the sample bots in 2 easy steps ==

Run "make" in this directory. [NB: this document assumes you use Linux 
or Mac OS X. If you use Windows, see WINDOWS.txt for instructions.]

Go to the src/ directory and run "./simulate.py -v -a CSampleAgents".

== Making your own agent with C in 11 easy steps ==

0. Flick through the documentation.

1. Pick a name for your agent. Make sure the name is a valid identifier 
in both C and Python. Be original. Names do *not* have to be prefixed 
with "c_"

2. Flick through the sample agents in the agents directory.  Pick a 
sample agent to copy-paste (so you don't have to type out the function 
definitions).

3. Copy the sample agent code into a new file in the "agents" directory. 
Make sure the file name matches the new agent name. The makefile will 
automatically compile your new agent when you run "make".

4. Create a python wrapper for your agent, by copying one of the sample 
agent definitions in c_agents.py and using the name of your agent.

5. Create an arena in which your agent can battle:

   5.1. open arenas/MyArena.py

   5.2. add "from link.C.c_agents import <youragentname>"

   5.3. modify the "Agents =" line to include your agent, and take out 
any agents you don't want to battle.

   5.4. to see how to import the C sample agents, see CSampleAgents.py.

6. Watch your agent in action: ./simulate -v -a MyArena

7. Oh no, my agent dies very quickly: what's going on?

   7.1 insert debugmsg() statements in your C program.
        
        7.1.1 debugmsg() is like printf - see c_link.h for an example.

        7.1.2 in Initialise(), save the name that's passed to you so 
that you can uniquely identify your agent when you're printing debug 
statements.

   7.2 Run "./simulate -v -n 1 -a MyArena" to start with only 1 of each 
agent.

   7.3 Change the agents against which you're battling in MyArena.py so 
that you have a predictable opponent.

   7.4 Edit conf.py, and set DEBUG=True. Don't forget to reset it when 
you're done.

   7.5 Read doc/UNSUPPORTED.txt to see how to interact directly with 
your agent. You can then invoke your agent from the command line 
(for example "./link/C/agents/c_angel") and see how it responds.

8. Once your agent works to your satisfaction, try it both on short and 
long durations (100 and 1000 rounds: see MAX_ITERATIONS in conf.py)

9. If the rolling scoreboard has been opened on progcomp.ucc.asn.au/, 
submit it there! Otherwise, sit tight.

10. Watch its progress on the scoreboard and adjust your strategy 
accordingly.

=== C++ ===

See PLUSPLUS.txt.

=== OTHER IMPORTANT NOTES ===

 * Static storage *is* *considered* *cheating*. You must *not* attempt 
to communicate between instances of your agent in any way other than by 
sequences of moves.

 * Obfuscated code is bad. Don't do it.
