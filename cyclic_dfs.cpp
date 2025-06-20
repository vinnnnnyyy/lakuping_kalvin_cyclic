
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_VERTICES = 100;

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
int vertices;
bool visited[MAX_VERTICES];
bool recStack[MAX_VERTICES];
int cycleVertices[MAX_VERTICES];
int cycleSize;

// Function to add edge
void addEdge(int u, int v) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        adjacencyMatrix[u][v] = 1;
    }
}


void displayMatrix() {
    cout << "Adjacency Matrix:" << endl;
    cout << "   ";
    for (int i = 0; i < vertices; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    for (int i = 0; i < vertices; i++) {
        cout << i << ": ";
        for (int j = 0; j < vertices; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void displayList() {
    cout << "\nAdjacency List:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << i << ": ";
        for (int j = 0; j < vertices; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

// DFS utility function for cycle detection
bool dfsUtil(int vertex, int path[], int pathSize) {
    visited[vertex] = true;
    recStack[vertex] = true;
    path[pathSize] = vertex;
    pathSize++;
    
    // Check all adjacent vertices
    for (int neighbor = 0; neighbor < vertices; neighbor++) {
        if (adjacencyMatrix[vertex][neighbor] == 1) {
            if (!visited[neighbor]) {
                if (dfsUtil(neighbor, path, pathSize)) {
                    return true;
                }
            } else if (recStack[neighbor]) {
                // Found back edge - cycle detected
                // Find cycle start in path
                int cycleStart = -1;
                for (int i = 0; i < pathSize; i++) {
                    if (path[i] == neighbor) {
                        cycleStart = i;
                        break;
                    }
                }
                
                // Store cycle vertices
                cycleSize = 0;
                for (int i = cycleStart; i < pathSize; i++) {
                    cycleVertices[cycleSize++] = path[i];
                }
                cycleVertices[cycleSize++] = neighbor; // Complete the cycle
                return true;
            }
        }
    }
    
    recStack[vertex] = false;
    return false;
}


bool detectCycleDFS() {
    // Initialize arrays
    memset(visited, false, sizeof(visited));
    memset(recStack, false, sizeof(recStack));
    cycleSize = 0;
    
    int path[MAX_VERTICES];
    
    // Check each vertex
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            if (dfsUtil(i, path, 0)) {
                return true;
            }
        }
    }
    return false;
}

// Function to print cycle vertices
void printCycle() {
    if (cycleSize > 0) {
        cout << "Cycle vertices: ";
        for (int i = 0; i < cycleSize; i++) {
            cout << cycleVertices[i] << " ";
        }
        cout << endl;
    }
}

// Initialize graph
void initGraph(int v) {
    vertices = v;
    // Initialize adjacency matrix to 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

int main() {
    cout << "=== Simple Cycle Detection using DFS ===" << endl << endl;
    
    // Test Case 1: Graph with cycle
    cout << "Test Case 1: Graph with cycle" << endl;
    initGraph(4);
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 1);  // Creates cycle: 1 -> 2 -> 3 -> 1
    
    displayMatrix();
    displayList();
    
    bool hasCycle1 = detectCycleDFS();
    cout << "\nIs cyclic: " << (hasCycle1 ? "true" : "false") << endl;
    if (hasCycle1) {
        printCycle();
    }
    cout << "----------------------------------------" << endl;
    
    // Test Case 2: Graph without cycle (DAG)
    cout << "\nTest Case 2: Directed Acyclic Graph (DAG)" << endl;
    initGraph(4);
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(0, 3);
    
    displayMatrix();
    displayList();
    
    bool hasCycle2 = detectCycleDFS();
    cout << "\nIs cyclic: " << (hasCycle2 ? "true" : "false") << endl;
    if (hasCycle2) {
        printCycle();
    } else {
        cout << "No cycle found - This is a DAG" << endl;
    }
    cout << "----------------------------------------" << endl;
    
    // Test Case 3: Self-loop
    cout << "\nTest Case 3: Graph with self-loop" << endl;
    initGraph(3);
    addEdge(0, 1);
    addEdge(1, 1);  // Self-loop
    addEdge(1, 2);
    
    displayMatrix();
    displayList();
    
    bool hasCycle3 = detectCycleDFS();
    cout << "\nIs cyclic: " << (hasCycle3 ? "true" : "false") << endl;
    if (hasCycle3) {
        printCycle();
    }
    
    return 0;
}