#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge {
    int dest;
    int weight;
};

class Graph {
public:
    Graph(int num_nodes) : num_nodes(num_nodes), adj_list(num_nodes) {}

    void add_edge(int u, int v, int weight) {
        adj_list[u].push_back({v, weight});
    }

    vector<int> dijkstra(int start) {
        vector<int> distance(num_nodes, numeric_limits<int>::max());
        distance[start] = 0;
        vector<bool> visited(num_nodes, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});

        while (!pq.empty()) {
            int dist_u = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;
            visited[u] = true;

            for (const auto& edge : adj_list[u]) {
                int v = edge.dest;
                int weight = edge.weight;
                if (!visited[v] && dist_u + weight < distance[v]) {
                    distance[v] = dist_u + weight;
                    pq.push({distance[v], v});
                }
            }
        }

        return distance;
    }

private:
    int num_nodes;
    vector<vector<Edge>> adj_list;
};

Graph read_graph_from_file(const string& filename) {
    ifstream file(filename);
    int num_nodes;
    file >> num_nodes;
    Graph graph(num_nodes);

    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            int weight;
            file >> weight;
            if (weight != 999999999) {
                graph.add_edge(i, j, weight);
            }
        }
    }

    return graph;
}

int main() {
    string filename = "input_graph.txt";  // Change this to the path of your input file
    Graph graph = read_graph_from_file(filename);

    int start_node = 0;  // Change this to the starting node

    // Measure the execution time
    auto start_time = high_resolution_clock::now();
    vector<int> distances = graph.dijkstra(start_node);
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    cout << "Shortest distances from node " << start_node << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }

    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}