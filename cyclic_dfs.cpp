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
    } else {
        cout << "Invalid edge: (" << u << ", " << v << "). Vertices should be between 0 and " << vertices-1 << endl;
    }
}

void displayMatrix() {
    cout << "\nAdjacency Matrix:" << endl;
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
        bool hasEdges = false;
        for (int j = 0; j < vertices; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                cout << j << " ";
                hasEdges = true;
            }
        }
        if (!hasEdges) {
            cout << "(no outgoing edges)";
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
        cout << "Cycle found: ";
        for (int i = 0; i < cycleSize; i++) {
            cout << cycleVertices[i];
            if (i < cycleSize - 1) {
                cout << " -> ";
            }
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
    cout << "=== Cycle Detection in Directed Graph using DFS ===" << endl << endl;
    
    // Get number of vertices from user
    cout << "Enter the number of vertices (1-" << MAX_VERTICES << "): ";
    cin >> vertices;
    
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        cout << "Invalid number of vertices. Exiting." << endl;
        return 1;
    }
    
    initGraph(vertices);
    
    // Get number of edges from user
    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;
    
    if (numEdges < 0) {
        cout << "Invalid number of edges. Exiting." << endl;
        return 1;
    }
    
    // Get edges from user
    cout << "\nEnter edges (format: source destination):" << endl;
    cout << "Vertices are numbered from 0 to " << vertices-1 << endl;
    
    for (int i = 0; i < numEdges; i++) {
        int source, destination;
        cout << "Edge " << i+1 << ": ";
        cin >> source >> destination;
        addEdge(source, destination);
    }
    
    // Display the graph
    cout << "\n=== Graph Representation ===" << endl;
    displayMatrix();
    displayList();
    
    // Detect cycle
    cout << "\n=== Cycle Detection Result ===" << endl;
    bool hasCycle = detectCycleDFS();
    
    if (hasCycle) {
        cout << "Result: CYCLE DETECTED!" << endl;
        printCycle();
    } else {
        cout << "Result: NO CYCLE FOUND" << endl;
        cout << "This is a Directed Acyclic Graph (DAG)" << endl;
    }
    
    return 0;
}
