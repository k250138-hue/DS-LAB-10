#include <iostream>
using namespace std;

const int INF = 999999; // Represents infinity (no direct connection)

class DijkstraGraph {
    int matrix[6][6];
    char names[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

public:
    DijkstraGraph() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                matrix[i][j] = 0;
            }
        }

        // Same edges as Question 4 diagram
        addEdge('A', 'B', 4);
        addEdge('A', 'C', 2);
        addEdge('B', 'C', 5);
        addEdge('B', 'D', 10);
        addEdge('C', 'E', 3);
        addEdge('E', 'D', 4);
        addEdge('D', 'F', 11);
    }

    int getIndex(char name) {
        for (int i = 0; i < 6; i++) {
            if (names[i] == name) return i;
        }
        return -1;
    }

    void addEdge(char u, char v, int cost) {
        matrix[getIndex(u)][getIndex(v)] = cost;
    }

    // Recursive helper to print path from start to current node
    void printPath(int parent[], int j) {
        if (parent[j] == -1) {
            cout << names[j];
            return;
        }
        printPath(parent, parent[j]);
        cout << " -> " << names[j];
    }

    void dijkstra(char startName) {
        int start = getIndex(startName);
        int dist[6];
        bool visited[6];
        int parent[6];

        // 1. Initialize distances, visited flags, and parents
        for (int i = 0; i < 6; i++) {
            dist[i] = INF;
            visited[i] = false;
            parent[i] = -1;
        }
        dist[start] = 0;

        // 2. Find shortest path for all vertices
        for (int count = 0; count < 5; count++) {
            int minDist = INF, u = -1;

            // Pick unvisited vertex with smallest distance
            for (int i = 0; i < 6; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1) break; // Remaining vertices are unreachable
            visited[u] = true;

            // Update distances of neighbors of u
            for (int v = 0; v < 6; v++) {
                if (!visited[v] && matrix[u][v] != 0 && dist[u] != INF) {
                    if (dist[u] + matrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + matrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // 3. Display results
        cout << "Shortest Paths from Department " << startName << ":\n";
        cout << "--------------------------------------------------\n";
        bool anyUnreachable = false;

        for (int i = 0; i < 6; i++) {
            cout << "To " << names[i] << " : ";
            if (dist[i] == INF) {
                cout << "Unreachable (Cost: INF)\n";
                anyUnreachable = true;
            } else {
                cout << "Cost = " << dist[i] << "\t| Path: ";
                printPath(parent, i);
                cout << endl;
            }
        }

        cout << "--------------------------------------------------\n";
        cout << "Unreachable Vertices: ";
        if (!anyUnreachable) {
            cout << "None (All vertices are reachable from " << startName << ")\n";
        } else {
            for (int i = 0; i < 6; i++) {
                if (dist[i] == INF) cout << names[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    DijkstraGraph g;
    g.dijkstra('A');
    return 0;
}
