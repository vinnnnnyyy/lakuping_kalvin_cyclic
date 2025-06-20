#include <iostream>
#include <cstring>
using namespace std;

const int MAX_VERTICES = 100;

// Global variables
int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
int vertices;
int inDegree[MAX_VERTICES];
int queue[MAX_VERTICES];
int front, rear;
int topologicalOrder[MAX_VERTICES];
int topoSize;
int cycleVertices[MAX_VERTICES];
int cycleSize;

// Queue operations
void initQueue() {
    front = rear = -1;
}

bool isEmpty() {
    return front == -1;
}

void enqueue(int vertex) {
    if (front == -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    queue[rear] = vertex;
}

int dequeue() {
    int vertex = queue[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
    return vertex;
}

// Function to add edge
void addEdge(int u, int v) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
        adjacencyMatrix[u][v] = 1;
    } else {
        cout << "Invalid edge: (" << u << ", " << v << "). Vertices should be between 0 and " << vertices-1 << endl;
    }
}

// Function to display adjacency matrix
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

// Function to display adjacency list
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

// Calculate in-degree for all vertices
void calculateInDegree() {
    for (int i = 0; i < vertices; i++) {
        inDegree[i] = 0;
    }
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                inDegree[j]++;
            }
        }
    }
}

// Display in-degree information
void displayInDegree() {
    cout << "\nIn-degree of vertices:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << "Vertex " << i << ": " << inDegree[i] << endl;
    }
}

bool detectCycleBFS() {
    calculateInDegree();
    
    initQueue();
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(i);
        }
    }
    
    int processedCount = 0;
    topoSize = 0;
    
    while (!isEmpty()) {
        int vertex = dequeue();
        topologicalOrder[topoSize++] = vertex;
        processedCount++;
        
        for (int neighbor = 0; neighbor < vertices; neighbor++) {
            if (adjacencyMatrix[vertex][neighbor] == 1) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    enqueue(neighbor);
                }
            }
        }
    }
    
    bool hasCycle = (processedCount != vertices);
    
    cycleSize = 0;
    if (hasCycle) {
        for (int i = 0; i < vertices; i++) {
            if (inDegree[i] > 0) {
                cycleVertices[cycleSize++] = i;
            }
        }
    }
    
    return hasCycle;
}

void printTopologicalOrder() {
    if (topoSize > 0) {
        cout << "Topological order: ";
        for (int i = 0; i < topoSize; i++) {
            cout << topologicalOrder[i];
            if (i < topoSize - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

// Function to print cycle vertices
void printCycleVertices() {
    if (cycleSize > 0) {
        cout << "Vertices involved in cycle: ";
        for (int i = 0; i < cycleSize; i++) {
            cout << cycleVertices[i] << " ";
        }
        cout << endl;
    }
}

// Simple cycle path finder
void findCyclePath() {
    if (cycleSize == 0) return;
    
    cout << "Cycle path: ";
    // For simplicity, just show the cycle vertices
    // In a complete implementation, we'd trace the actual path
    for (int i = 0; i < cycleSize; i++) {
        cout << cycleVertices[i] << " ";
    }
    // Try to find a connection back to first vertex
    for (int i = 0; i < cycleSize; i++) {
        if (adjacencyMatrix[cycleVertices[i]][cycleVertices[0]] == 1) {
            cout << cycleVertices[0];
            break;
        }
    }
    cout << endl;
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
    cout << "=== Cycle Detection in Directed Graph using BFS (Kahn's Algorithm) ===" << endl << endl;
    
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
    
    // Calculate and display in-degrees
    calculateInDegree();
    displayInDegree();
    
    // Detect cycle using BFS (Kahn's Algorithm)
    cout << "\n=== Cycle Detection Result ===" << endl;
    bool hasCycle = detectCycleBFS();
    
    if (hasCycle) {
        cout << "Result: CYCLE DETECTED!" << endl;
        printCycleVertices();
        findCyclePath();
        cout << "Note: Topological ordering is not possible for cyclic graphs." << endl;
    } else {
        cout << "Result: NO CYCLE FOUND" << endl;
        cout << "This is a Directed Acyclic Graph (DAG)" << endl;
        printTopologicalOrder();
    }
    
    return 0;
}
