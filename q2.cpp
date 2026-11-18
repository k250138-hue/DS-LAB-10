#include <iostream>
using namespace std;

const int MAXV = 10;
const int INF = 9999;

struct Graph {
    int V;
    char base;              // label of vertex 0: '0' or 'A'
    int w[MAXV][MAXV];

    Graph(int v, char b) {
        V = v; base = b;
        for (int i = 0; i < MAXV; i++)
            for (int j = 0; j < MAXV; j++) w[i][j] = INF;
    }

    void addEdge(char u, char v, int cost) {
        w[u - base][v - base] = cost;
        w[v - base][u - base] = cost;   // undirected for MST
    }

    void prim(char start) {
        int key[MAXV], parent[MAXV];
        bool inMST[MAXV];
        for (int i = 0; i < V; i++) {
            key[i] = INF; parent[i] = -1; inMST[i] = false;
        }
        key[start - base] = 0;
        int total = 0;

        cout << "Edge\tWeight\n";
        for (int count = 0; count < V; count++) {
            // pick the cheapest vertex not yet in the MST
            int u = -1;
            for (int i = 0; i < V; i++)
                if (!inMST[i] && (u == -1 || key[i] < key[u])) u = i;

            inMST[u] = true;
            if (parent[u] != -1) {
                cout << char(base + parent[u]) << " - " << char(base + u)
                     << "\t" << key[u] << endl;
                total += key[u];
            }

            // update keys of neighbours
            for (int v = 0; v < V; v++)
                if (w[u][v] != INF && !inMST[v] && w[u][v] < key[v]) {
                    key[v] = w[u][v];
                    parent[v] = u;
                }
        }
        cout << "Total MST weight = " << total << endl << endl;
    }
};

int main() {
    // Graph (a): vertices 0..4, start 0
    Graph ga(5, '0');
    ga.addEdge('0','1',3); ga.addEdge('0','3',7); ga.addEdge('0','4',8);
    ga.addEdge('1','2',1); ga.addEdge('1','3',4);
    ga.addEdge('2','3',2); ga.addEdge('3','4',3);
    cout << "Graph (a) - Prim from 0\n";
    ga.prim('0');

    // Graph (b): vertices A..G, start A
    Graph gb(7, 'A');
    gb.addEdge('A','B',1); gb.addEdge('A','D',5);
    gb.addEdge('B','D',3); gb.addEdge('B','C',4);
    gb.addEdge('D','G',4); gb.addEdge('D','E',1);
    gb.addEdge('C','E',7); gb.addEdge('E','G',2);
    gb.addEdge('E','F',1); gb.addEdge('G','F',10);
    cout << "Graph (b) - Prim from A\n";
    gb.prim('A');

    return 0;
}