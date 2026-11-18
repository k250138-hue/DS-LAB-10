#include <iostream>
using namespace std;

class KruskalGraph {
    int V, E;
    char nodes[10];
    char u[20], v[20];
    int w[20];
    int parent[10];

public:
    KruskalGraph(int vertices, char nodeNames[]) {
        V = vertices;
        E = 0;
        for (int i = 0; i < V; i++) {
            nodes[i] = nodeNames[i];
        }
    }

    int getIndex(char name) {
        for (int i = 0; i < V; i++) {
            if (nodes[i] == name) return i;
        }
        return -1;
    }

    void addEdge(char start, char end, int weight) {
        u[E] = start;
        v[E] = end;
        w[E] = weight;
        E++;
    }

    int findParent(int i) {
        while (parent[i] != i) {
            i = parent[i];
        }
        return i;
    }

    void findMST() {
        // 1. Sort edges by weight (Bubble Sort)
        for (int i = 0; i < E - 1; i++) {
            for (int j = 0; j < E - i - 1; j++) {
                if (w[j] > w[j + 1]) {
                    // Swap weights
                    int tempW = w[j]; w[j] = w[j + 1]; w[j + 1] = tempW;
                    // Swap start nodes
                    char tempU = u[j]; u[j] = u[j + 1]; u[j + 1] = tempU;
                    // Swap end nodes
                    char tempV = v[j]; v[j] = v[j + 1]; v[j + 1] = tempV;
                }
            }
        }

        // 2. Initialize parent array for cycle detection
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        int totalCost = 0;
        int edgesAdded = 0;

        cout << "Edge \tWeight\n";
        for (int i = 0; i < E; i++) {
            int rootU = findParent(getIndex(u[i]));
            int rootV = findParent(getIndex(v[i]));

            // If adding this edge doesn't form a cycle
            if (rootU != rootV) {
                cout << u[i] << " - " << v[i] << "\t" << w[i] << endl;
                totalCost += w[i];
                parent[rootU] = rootV; // Union the two sets
                edgesAdded++;
            }

            if (edgesAdded == V - 1) break;
        }

        cout << "Total MST Cost: " << totalCost << "\n-------------------------\n";
    }
};

int main() {
    // Graph 3(a) - Vertices: a, b, c, d, e
    cout << "Kruskal's MST for Graph (a):\n";
    char nodesA[] = {'a', 'b', 'c', 'd', 'e'};
    KruskalGraph ga(5, nodesA);
    ga.addEdge('a', 'c', 10);
    ga.addEdge('e', 'd', 19);
    ga.addEdge('c', 'a', 21);
    ga.addEdge('a', 'd', 22);
    ga.addEdge('c', 'e', 33);
    ga.addEdge('b', 'e', 45);
    ga.addEdge('b', 'c', 53);
    ga.findMST();

    // Graph 3(b) - Vertices: A, B, C, D, E, F
    cout << "Kruskal's MST for Graph (b):\n";
    char nodesB[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    KruskalGraph gb(6, nodesB);
    gb.addEdge('A', 'B', 3);
    gb.addEdge('A', 'C', 5);
    gb.addEdge('A', 'D', 9);
    gb.addEdge('B', 'C', 3);
    gb.addEdge('B', 'D', 4);
    gb.addEdge('B', 'E', 7);
    gb.addEdge('C', 'D', 2);
    gb.addEdge('C', 'E', 6);
    gb.addEdge('C', 'F', 8);
    gb.addEdge('D', 'E', 2);
    gb.addEdge('D', 'F', 2);
    gb.addEdge('E', 'F', 5);
    gb.findMST();

    return 0;
}
