**Graph Analysis README**

### Overview
This project processes multiple graph datasets to compute various properties and characteristics of each graph. The program reads graph data, builds graph structures, and determines several key parameters, including degree sequence, connectivity, bipartiteness, eccentricities, vertex coloring, C4 subgraphs, and complement edges.

### Features
- Computes **degree sequence** of the graph.
- Determines the **number of components** in the graph.
- Checks if the graph is **bipartite**.
- Calculates **eccentricity** values for each vertex.
- Implements three **vertex coloring algorithms**:
  - Greedy coloring (by vertex order)
  - Largest First (LF) method
- Counts the number of **C4 subgraphs** (4-cycle subgraphs).
- Computes the **number of edges in the graph complement**.

### Input Format
1. The first line contains an integer **k**, the number of graphs.
2. The following lines contain **k graph datasets**.
3. Each dataset starts with an integer **n**, the number of vertices.
4. The next **n lines** describe the adjacency list of each vertex:
   - Each line starts with an integer **s**, the number of neighbors.
   - Followed by **s space-separated integers**, which are the IDs of the neighboring vertices.

### Output Format
For each graph, the program prints:
1. **Degree Sequence**: A sequence of n numbers.
2. **Number of Components**: A single integer.
3. **Bipartiteness**: 'T' (True) or 'F' (False).
4. **Eccentricities**: A sequence of n numbers.
5. **Greedy Coloring**: A sequence of n numbers representing vertex colors.
6. **C4 Subgraph Count**: A single integer.
7. **Complement Edges Count**: A single integer.

### Example Input
```
1
5
2 2 3
2 1 3
2 1 2
1 5
1 4
```

### Example Output
```
Degree Sequence: 2 2 2 1 1
Number of Components: 2
Bipartite: T
Eccentricities: 1 1 1 2 2
Greedy Coloring: 1 2 3 1 2
C4 Subgraphs Count: 0
Complement Edges: 7
```

### Usage
Compile the program using a C++ compiler and run it with graph data as input to obtain the required graph properties in a formatted output.

#### Compilation Example
```sh
g++ -o graph_analysis graph_analysis.cpp
```

#### Running the Program
```sh
./graph_analysis < input.txt
```

