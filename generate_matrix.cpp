#include <iostream>
#include <fstream>
#include <random>
#include <limits>

// Generate a random adjacency matrix of size n and write it to a file
void generate_random_adjacency_matrix(int n, const std::string& filename) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_weight(1, 100); // Random weight between 1 and 100
    std::uniform_int_distribution<int> dis_edge(0, 1); // 0 or 1 for edge existence

    // Write the size of the matrix to the file
    outfile << n << std::endl;

    // Generate the adjacency matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Ensure no self-loops
            if (i == j) {
                outfile << "0 ";
            } else {
                // Randomly determine if there is an edge between nodes i and j
                int edge = dis_edge(gen);
                if (edge) {
                    // If an edge exists, assign a random weight
                    int weight = dis_weight(gen);
                    outfile << weight << " ";
                } else {
                    // If no edge exists, signify it with a large value
                    outfile << "9999999 ";
                }
            }
        }
        outfile << std::endl;
    }

    outfile.close();
}

int main() {
    int n = 10000; // Number of nodes
    std::string filename = "input_graph.txt";
    
    generate_random_adjacency_matrix(n, filename);

    std::cout << "Random weighted adjacency matrix of " << n << " nodes has been generated and written to " << filename << "." << std::endl;

    return 0;
}