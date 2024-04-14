# bellman_ford_HPC

## STEPS TO RUN THE PROGRAM FOR COMPARING:

1) Run the generate_matrix file to get a random matrix of 10,000 nodes. (The number of nodes can be changed in the code)
2) Run djikstras.cpp to get the run time of the djikstras algorithm on that graph, along with the distances to each node in the terminal.
3) Then run mpi_bellman_ford.cpp using mpic++ and mpiexec (Use the input_graph.txt input file that will be created as input and put that in the terminal). Output will be sent to the output.txt file. And run-time of the algorithm will be displayed on the terminal.
