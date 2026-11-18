#include <iostream>
using namespace std;

const int N = 8;

struct Graph {
    char base;            // 'a', 'A' or '0' -> label of node 0
    int adj[N][N];
    bool vis[N];

    Graph(char b) {
        base = b;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) adj[i][j] = 0;
    }

    void addEdge(char u, char v, bool directed = true) {
        adj[u - base][v - base] = 1;
        if (!directed) adj[v - base][u - base] = 1;
    }

    void resetVisited() {
        for (int i = 0; i < N; i++) vis[i] = false;
    }

    void BFS(char start) {
        resetVisited();
        int q[N], front = 0, rear = 0;
        int s = start - base;
        vis[s] = true;
        q[rear++] = s;
        while (front < rear) {
            int u = q[front++];
            cout << char(base + u) << " ";
            for (int v = 0; v < N; v++)
                if (adj[u][v] && !vis[v]) {
                    vis[v] = true;
                    q[rear++] = v;
                }
        }
        cout << endl;
    }

    void dfsUtil(int u) {
        vis[u] = true;
        cout << char(base + u) << " ";
        for (int v = 0; v < N; v++)
            if (adj[u][v] && !vis[v]) dfsUtil(v);
    }

    void DFS(char start) {
        resetVisited();
        dfsUtil(start - base);
        cout << endl;
    }
};

void run(const char* name, Graph &g, char start) {
    cout << "Graph " << name << " (start " << start << ")\n";
    cout << "  BFS: "; g.BFS(start);
    cout << "  DFS: "; g.DFS(start);
    cout << endl;
}

int main() {
    // (a) directed, start 'a'
    Graph ga('a');
    ga.addEdge('a','b'); ga.addEdge('a','c'); ga.addEdge('a','d'); ga.addEdge('a','e');
    ga.addEdge('b','d'); ga.addEdge('c','d'); ga.addEdge('c','e'); ga.addEdge('d','e');
    run("a", ga, 'a');

    // (b) directed, start 1
    Graph gb('0');
    gb.addEdge('1','2'); gb.addEdge('1','4'); gb.addEdge('2','3'); gb.addEdge('2','5');
    gb.addEdge('3','7'); gb.addEdge('4','6'); gb.addEdge('5','7');
    gb.addEdge('6','5'); gb.addEdge('6','7');
    run("b", gb, '1');

    // (c) and (d) are the same graph, start 'A'
    Graph gc('A');
    gc.addEdge('A','B'); gc.addEdge('A','C'); gc.addEdge('C','B'); gc.addEdge('C','D');
    gc.addEdge('C','E'); gc.addEdge('D','E'); gc.addEdge('B','F'); gc.addEdge('E','F');
    run("c", gc, 'A');
    run("d", gc, 'A');

    // (e) directed, start 'A'
    Graph ge('A');
    ge.addEdge('H','A'); ge.addEdge('G','H'); ge.addEdge('C','H');
    ge.addEdge('A','B'); ge.addEdge('B','C'); ge.addEdge('C','G');
    ge.addEdge('D','A'); ge.addEdge('D','F'); ge.addEdge('F','A'); ge.addEdge('F','B');
    ge.addEdge('E','B'); ge.addEdge('C','E'); ge.addEdge('G','E'); ge.addEdge('E','F');
    run("e", ge, 'A');

    // (f) directed, start 0
    Graph gf('0');
    gf.addEdge('0','1'); gf.addEdge('0','2'); gf.addEdge('0','3'); gf.addEdge('1','3');
    gf.addEdge('2','4'); gf.addEdge('3','5'); gf.addEdge('3','6');
    gf.addEdge('4','5'); gf.addEdge('4','7'); gf.addEdge('5','2');
    run("f", gf, '0');

    // (g) 0<->1, 0<->3 are bidirectional, start 0
    Graph gg('0');
    gg.addEdge('0','1', false); gg.addEdge('0','3', false); gg.addEdge('0','7');
    gg.addEdge('1','4'); gg.addEdge('7','4'); gg.addEdge('7','5');
    gg.addEdge('3','5'); gg.addEdge('4','6'); gg.addEdge('5','6');
    run("g", gg, '0');

    // (h) undirected, start 'A'
    Graph gh('A');
    gh.addEdge('H','A',false); gh.addEdge('H','C',false); gh.addEdge('H','G',false);
    gh.addEdge('A','B',false); gh.addEdge('B','C',false); gh.addEdge('C','G',false);
    gh.addEdge('A','D',false); gh.addEdge('A','F',false); gh.addEdge('B','F',false);
    gh.addEdge('B','E',false); gh.addEdge('C','E',false); gh.addEdge('E','G',false);
    gh.addEdge('D','F',false); gh.addEdge('F','E',false);
    run("h", gh, 'A');

    return 0;
}