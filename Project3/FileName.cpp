#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Stack class implementation
class Stack {
private:
    vector<string> data;

public:
    void push(const string& item) {
        data.push_back(item);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    const string& top() {
        return data.back();
    }

    bool empty() {
        return data.empty();
    }
};

// Queue class implementation
class Queue {
private:
    vector<string> data;
    int front;

public:
    Queue()  {
        front = 0;
    }

    void Enqueue(const string& item) {
        data.push_back(item);
    }

    void Dequeue() {
        if (front < data.size()) {
            ++front;
        }
    }

    const string& frontItem() {
        return data[front];
    }

    bool empty() {
        return front >= data.size();
    }
};

// Structure to represent a city
struct City {
    string name;
    vector<string> neighbors;

    City() = default;  // Default constructor

    City(const string& cityName, const vector<string>& cityNeighbors) {
        name = cityName;
        neighbors = cityNeighbors;   
    
    }
};


// Map of Romania cities and their connections
unordered_map<string, City> romaniaMap = {
    {"Arad", {"Arad", {"Zerind", "Sibiu", "Timisoara"}}},
    {"Zerind", {"Zerind", {"Arad", "Oradea"}}},
    {"Oradea", {"Oradea", {"Zerind", "Sibiu"}}},
    {"Sibiu", {"Sibiu", {"Arad", "Oradea", "Fagaras", "Rimnicu Vilcea"}}},
    {"Timisoara", {"Timisoara", {"Arad", "Lugoj"}}},
    {"Lugoj", {"Lugoj", {"Timisoara", "Mehadia"}}},
    {"Mehadia", {"Mehadia", {"Lugoj", "Drobeta"}}},
    {"Drobeta", {"Drobeta", {"Mehadia", "Craiova"}}},
    {"Craiova", {"Craiova", {"Drobeta", "Rimnicu Vilcea", "Pitesti"}}},
    {"Fagaras", {"Fagaras", {"Sibiu"}}},
    {"Rimnicu Vilcea", {"Rimnicu Vilcea", {"Sibiu", "Craiova", "Pitesti"}}},
    {"Pitesti", {"Pitesti", {"Rimnicu Vilcea", "Craiova", "Bucharest"}}},
    {"Bucharest", {"Bucharest", {"Pitesti"}}}
};

// Depth-First Search (DFS)
bool dfs(const string& start, const string& goal, unordered_map<string, bool>& visited, Stack& path) {
    visited[start] = true;
    path.push(start);

    if (start == goal) {
        return true;  // Goal reached
    }

    for (const string& neighbor : romaniaMap[start].neighbors) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, goal, visited, path)) {
                return true;
            }
        }
    }

    path.pop();
    return false;
}

 
// Breadth-First Search (BFS)
bool bfs(const string& start, const string& goal, vector<string>& path) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    Queue queue;

    queue.Enqueue(start);
    visited[start] = true;

    while (!queue.empty()) {
        string current = queue.frontItem();
        queue.Dequeue();

        if (current == goal) {
            // Build the path by backtracking through the parent map
            string node = goal;
            while (node != start) {
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(start);

            reverse(path.begin(), path.end());
            return true;  // Goal reached
        }

        for (const string& neighbor : romaniaMap[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue.Enqueue(neighbor);
            }
        }
    }

    return false;
}

int main() {
    string startCity, endCity;

    // Get user input for start and end cities
    cout << "Enter the starting city: ";
    cin >> startCity;
    cout << "Enter the ending city: ";
    cin >> endCity;
    cout << endl;

    // DFS
    cout << "DFS:" << endl;
    unordered_map<string, bool> dfsVisited;
    Stack dfsPath;
    dfs(startCity, endCity, dfsVisited, dfsPath);

    vector<string> reversedDFSPath;
    while (!dfsPath.empty()) {
        reversedDFSPath.push_back(dfsPath.top());
        dfsPath.pop();
    }

    for (int i = reversedDFSPath.size() - 1; i > 0; --i) {
        cout << reversedDFSPath[i] << " -> ";
    }
    cout << reversedDFSPath[0] << endl << endl;

    // BFS
    cout << "BFS:" << endl;
    vector<string> bfsPath;
    bfs(startCity, endCity, bfsPath);

    for (const string& city : bfsPath) {
        cout << city;
        if (city != endCity) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
