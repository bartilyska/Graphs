#   G r a p h s 
The task is to load graphs and determine the following parameters:
the degree sequence;
the number of components;
bipartiteness;
the eccentricity of vertices (within the components)
vertices colours (consecutive natural numbers from 1) obtained using algorithms:
greedy (the vertex order according to its number)
LF method (ties are solved by the vertex number)
SLF method (ties are solved by highest vertex degree, and if there is still a tie choose the vertex with the lowest number)
the number of different C4 subgraphs
the number of the graph complement's edges
Input
In the first line there's a number k of graphs.
The following lines contain k graph data sets.
A single data set contains a number n - the graph order - and n lists of neighbours for each vertex. A list contains the number of neighbours (s) and s neighbours IDs.
Neighbours IDs are numbers from 1 to n.
Output
You should print k sets of responses. Each set should contain the designated parameters in the order in which the parameters are listed. For point
1, 4, 6a, 6b, 6c you should print sequence of n numbers;
7, 8 you should print a number;
2, 3 you should print a character T or F (true/false).



 
