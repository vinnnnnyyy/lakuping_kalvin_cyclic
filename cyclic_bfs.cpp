
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
    }
}

// Function to display adjacency matrix
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

// Function to display adjacency list
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
    cout << "Topological order: ";
    for (int i = 0; i < topoSize; i++) {
        cout << topologicalOrder[i] << " ";
    }
    cout << endl;
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
    cout << "=== Simple Cycle Detection using BFS  ===" << endl << endl;
    
    // Test Case 1: Graph with cycle
    cout << "Test Case 1: Graph with cycle" << endl;
    initGraph(4);
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 1);  // Creates cycle: 1 -> 2 -> 3 -> 1
    
    displayMatrix();
    displayList();
    
    bool hasCycle1 = detectCycleBFS();
    cout << "\nIs cyclic: " << (hasCycle1 ? "true" : "false") << endl;
    if (hasCycle1) {
        printCycleVertices();
        findCyclePath();
    }
    printTopologicalOrder();
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
    
    bool hasCycle2 = detectCycleBFS();
    cout << "\nIs cyclic: " << (hasCycle2 ? "true" : "false") << endl;
    if (hasCycle2) {
        printCycleVertices();
    } else {
        cout << "No cycle found - This is a DAG" << endl;
    }
    printTopologicalOrder();
    cout << "----------------------------------------" << endl;
    
    // Test Case 3: Self-loop
    cout << "\nTest Case 3: Graph with self-loop" << endl;
    initGraph(3);
    addEdge(0, 1);
    addEdge(1, 1);  // Self-loop
    addEdge(1, 2);
    
    displayMatrix();
    displayList();
    
    bool hasCycle3 = detectCycleBFS();
    cout << "\nIs cyclic: " << (hasCycle3 ? "true" : "false") << endl;
    if (hasCycle3) {
        printCycleVertices();
        findCyclePath();
    }
    printTopologicalOrder();
    
    return 0;
}