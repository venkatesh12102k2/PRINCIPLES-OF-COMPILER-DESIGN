# PRINCIPLES-OF-COMPILER-DESIGN
<h3>1 . NFA to DFA</h3>
<h4>Algorithm:</h4>
<pre>
Step-1	: Prompt the user for the number of states, number of input symbols, initial and final states and the transition table of NFA.
Step-2	: The initial state and the input symbols in the resultant DFA will be the same as it is in the given NFA.
Step-3	: Push the initial state into a queue.
Step-4	: Store the front element of the queue in a variable and pop that element from the queue.
Step-5	: If the element is already visited then go to Step-9. 
Step-6	: For each state in the element, apply the input and find out the resultant transition states. Combine the obtained set of states and take it as a new state in DFA. Store this transition in the transition table of DFA.
Step-7	: Push the obtained set of states into the queue.
Step-8	: Repeat Step-6 and Step-7 for all the input symbols.
Step-9	: If the queue is not empty then go to Step-4.
Step-10	: If one of the states in any combined state is final state then mark that combined state as a final state.
Step-11	: Display the transition table of the resultant DFA along with its initial and final states.
</pre>
<br>
<h3>2 . NFA WITH EPSILON MOVES TO NFA</h3>
<h4>Algorithm:</h4>
<pre>
Step-1	: Prompt the user for the number of states, number of input symbols, initial and final states and the transition table of the NFA with epsilon moves.
Step-2	: Find epsilon closure of each states given and store it in a variable.
Step-3	: For each given state and for each given input find its transition in NFA without epsilon moves using the below formula.
Transition_In_NFA_Without_Epsilon_Moves(q,a)=
epsilon closure(TransitionInNFAWithEpsilonMoves(epsilon closure(q), a))
Step-4	: The number of states, the states and the initial state will be the same.
Step-5	: The Input Symbols will also be the same excluding the epsilon.
Step-6	: If the epsilon closure of a state contains a final state then mark that state as a final state.
Step-7	: Display the transition table of NFA and display the initial and final states of it.
</pre>
<br>
<h3>3 . MINIMIZATION OF DFA</h3>
<h4>Algorithm:</h4>
<pre>
Step-1	: Prompt the number of state(say n), number of input symbols, the initial and the final states and the transition table of the DFA.
Step-2	: Create a boolean table of size n*n and initialise all the values as true. This table is used to identify whether two states are equivalent or not.
Step-3	: Traverse the table, if one state is a final state and other state is a non final state then mark their combination as distinguishable by storing false in the boolean table.
Step-4	: Store the count of distinguishable states in a variable(say temp).
Step-5	: Traverse each row(i) and column(j) of the table.
Step-6	: Find the transition of i and j on a given input. Say the transition states are x and y respectively.
Step-7	: If table[x][y] is false then set table[i][j] and table[j][i] as false as well.
Step-8	: Track the count of distinguishable states.
Step-9	: Repeat Steps 6-8 for all the input symbols.
Step-10	: If the variable “temp” value is not equal to the count of distinguishable states, then go to Step-4.
Step-11	: Display the distinguishable table.
Step-12	: Combine the states which are identified as equivalent by the distinguishable table and make them as a single state in minimized DFA.
Step-13	: Keep the states that are not equivalent as individual states in the minimized DFA.
Step-15	: Determine the transitions for the states of the minimized DFA.
Step-16	: Display the transition table of the minimized DFA along with its initial and final states. 
</pre>
<br>
<h3>4 . REGULAR EXPRESSION TO NFA WITH EPSILON MOVES</h3>
<h4>Algorithm:</h4>
<pre>
Step-1	: Prompt the user for the Regular Expression.
Step-2	: Extract all the sub-expressions from the given Regular Expression.
Step-3	: Create a new state in NFA with epsilon moves whenever it is required.
Step-4	: For all the extracted sub-expressions, store their equivalent transitions in the NFA with epsilon moves.
Step-5	: Evaluate the union operation and store its equivalent transition in the NFA with epsilon moves.
Step-6	: Evaluate the closure operation and store its equivalent transition in the NFA with epsilon moves.
Step-7	: Concatenate all the sub-expressions and store the transitions for the concatenation operation.
Steo-8	: Resultant NFA with epsilon moves will have same input symbols as in the given Regular Expression along with epsilon.
Step-9	: Mark the start state as initial state and the end state as final state.
Step-10	: Display the transition table of the resultant NFA with epsilon moves along with it’s initial and final state.
</pre>
<br>

