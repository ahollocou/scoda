# Minimal implementation of SCoDA

This version of the code is designed for practical use, whereas the benchmark version of the code is designed for performance evaluation.

## Compilation
Run the Make command:

		make
		
## Usage

The program uses Standard Input and Output to read the graph and write the results, and takes three parameters.

	./scoda MAX_NODE_ID DEGREE_THRESHOLD IGNORE_LINES < input_graph.txt > output_communities.txt

Parameters:

- **Standard Input**: list of tab-separated edges (each line: SRC_NODE \<tab\> DST_NODE)
- **Standard Output**: community detection result (each line: NODE \<tab\> COMMUNITY)
- **MAX_NODE_ID**: int32 larger than all node IDs in the graph
- **DEGREE_THRESHOLD**: parameter of the algorithm
- **IGNORE_LINES**: number of line to ignore at the beginning of the input file

Note: exactly `2 * MAX_NODE_ID * sizeof( int32_t )` bits are allocated by the program.
