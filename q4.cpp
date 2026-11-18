#include <iostream>
using namespace std;

class DepartmentGraph {
    int matrix[6][6];
    char names[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

public:
    DepartmentGraph() {
        // Initialize all weights to 0 (no connection)
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                matrix[i][j] = 0;
            }
        }

        // Pre-load edges from the Question 4 diagram
        insertEdge('A', 'B', 4);
        insertEdge('A', 'C', 2);
        insertEdge('B', 'C', 5);
        insertEdge('B', 'D', 10);
        insertEdge('C', 'E', 3);
        insertEdge('E', 'D', 4);
        insertEdge('D', 'F', 11);
    }

    int getIndex(char name) {
        if (name >= 'a' && name <= 'f') name -= 32; // Handle lowercase input
        for (int i = 0; i < 6; i++) {
            if (names[i] == name) return i;
        }
        return -1;
    }

    void insertEdge(char u, char v, int cost) {
        int i = getIndex(u);
        int j = getIndex(v);
        if (i != -1 && j != -1) {
            matrix[i][j] = cost;
        } else {
            cout << "Invalid department name!\n";
        }
    }

    void deleteEdge(char u, char v) {
        int i = getIndex(u);
        int j = getIndex(v);
        if (i != -1 && j != -1) {
            matrix[i][j] = 0;
            cout << "Edge " << names[i] << " -> " << names[j] << " deleted.\n";
        } else {
            cout << "Invalid department name!\n";
        }
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix (Communication Costs):\n   ";
        for (int i = 0; i < 6; i++) cout << names[i] << "\t";
        cout << "\n--------------------------------------------------\n";

        for (int i = 0; i < 6; i++) {
            cout << names[i] << " | ";
            for (int j = 0; j < 6; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void showEdges() {
        cout << "\nIncoming and Outgoing Edges for Each Department:\n";
        for (int i = 0; i < 6; i++) {
            cout << "Department " << names[i] << ":\n";

            // Outgoing edges (row i)
            cout << "  Outgoing: ";
            bool hasOut = false;
            for (int j = 0; j < 6; j++) {
                if (matrix[i][j] != 0) {
                    cout << names[i] << "->" << names[j] << "(" << matrix[i][j] << ")  ";
                    hasOut = true;
                }
            }
            if (!hasOut) cout << "None";

            // Incoming edges (column i)
            cout << "\n  Incoming: ";
            bool hasIn = false;
            for (int j = 0; j < 6; j++) {
                if (matrix[j][i] != 0) {
                    cout << names[j] << "->" << names[i] << "(" << matrix[j][i] << ")  ";
                    hasIn = true;
                }
            }
            if (!hasIn) cout << "None";
            cout << "\n";
        }
    }
};

int main() {
    DepartmentGraph g;
    int choice, cost;
    char u, v;

    do {
        cout << "\n--- Department Network Menu ---\n";
        cout << "1. Display Adjacency Matrix\n";
        cout << "2. Insert Edge\n";
        cout << "3. Delete Edge\n";
        cout << "4. Find Incoming & Outgoing Edges\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.displayMatrix();
                break;
            case 2:
                cout << "Enter source (A-F), destination (A-F), and cost: ";
                cin >> u >> v >> cost;
                g.insertEdge(u, v, cost);
                cout << "Edge inserted.\n";
                break;
            case 3:
                cout << "Enter source (A-F) and destination (A-F) to delete: ";
                cin >> u >> v;
                g.deleteEdge(u, v);
                break;
            case 4:
                g.showEdges();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
