#include <iostream>
using namespace std;

class CourseSchedule {
    int V;
    int adj[10][10];
    int indegree[10];

public:
    CourseSchedule(int courses) {
        V = courses;
        for (int i = 0; i < V; i++) {
            indegree[i] = 0;
            for (int j = 0; j < V; j++) {
                adj[i][j] = 0;
            }
        }
    }

    void addPrerequisite(int u, int v) {
        adj[u][v] = 1; // Course u must be completed before course v
    }

    void topologicalSort() {
        // 1. Calculate indegrees of all vertices
        for (int i = 0; i < V; i++) {
            indegree[i] = 0;
        }
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1) {
                    indegree[v]++;
                }
            }
        }

        // Display initial indegrees
        cout << "Initial Indegrees (Prerequisites count):\n";
        for (int i = 0; i < V; i++) {
            cout << "Course " << i << " : " << indegree[i] << endl;
        }

        // 2. Push all vertices with indegree 0 into a simple array queue
        int q[10], front = 0, rear = 0;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q[rear++] = i;
            }
        }

        // 3. Process the queue
        int topoOrder[10];
        int count = 0;

        while (front < rear) {
            int curr = q[front++];
            topoOrder[count++] = curr;

            // Reduce indegree of neighbors
            for (int next = 0; next < V; next++) {
                if (adj[curr][next] == 1) {
                    indegree[next]--;
                    if (indegree[next] == 0) {
                        q[rear++] = next;
                    }
                }
            }
        }

        // 4. Check for cycles and print result
        cout << "\n------------------------------------------\n";
        if (count != V) {
            cout << "Cycle detected! No valid course completion order exists.\n";
        } else {
            cout << "Valid Course Completion Order: ";
            for (int i = 0; i < count; i++) {
                cout << topoOrder[i];
                if (i < count - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
};

int main() {
    CourseSchedule cs(6);

    // Edges from Question 6 diagram:
    // 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 4, 2 -> 5, 3 -> 5
    cs.addPrerequisite(0, 1);
    cs.addPrerequisite(0, 2);
    cs.addPrerequisite(1, 3);
    cs.addPrerequisite(2, 4);
    cs.addPrerequisite(2, 5);
    cs.addPrerequisite(3, 5);

    cs.topologicalSort();

    return 0;
}