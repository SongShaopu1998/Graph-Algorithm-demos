//
// Created by shaopu on 2021/10/27.
// aimed at undirected, unweighted graph
//
#include<iostream>
#include<list>
#include<queue>
#include<vector>

using namespace std;

class Graph{
    // graphNode
private:
    // if the given edge is not represented as an integer,
    // we should use a hashtable, or a map to reflect them
    // into integers
    list<int>* adj;
    // if it is a weighted graph, then we should use pair:

    // list<pair<int, int>>* adj;

    // size of the nodes
    int size;
public:
    explicit Graph(int v);
    ~Graph();
    void addEdge(int start, int neighbor);
    void performBFS(bool* visited, queue<int>& nodeQueue, vector<int>& parent);
    static void printPath(vector<int>& startParent, vector<int>& endParent, int intersectV);
    bool biDirectionSearch(int start, int end);
    int intersect(const bool* startVisited, const bool* endVisited) const;
};

Graph::Graph(int v) {
    size = v;
    // allocate the memory for the adj list
    adj = new list<int>[size];
}

Graph::~Graph() {
    // free the adj allocated memory
    delete [] adj;
}

void Graph::addEdge(int start, int neighbor) {
    // undirected graph
    adj[start].push_back(neighbor);
    adj[neighbor].push_back(start);
}

void Graph::performBFS(bool *visited, queue<int> &nodeQueue, vector<int> &parent) {
    // first element in the current queue
    int first = nodeQueue.front();
    // pop it
    nodeQueue.pop();
    // add its neighbors to the queue
    list<int>::iterator it;
    for (it = adj[first].begin(); it != adj[first].end(); ++it) {
        // not visited
        if (!visited[*it]) {
            // add to the queue
            nodeQueue.push(*it);
            // set the parent of *it to first
            parent[*it] = first;
            // mark it visited
            visited[*it] = true;
        }
    }
}

bool Graph::biDirectionSearch(int start, int end) {
    bool startVisited[size];
    bool endVisited[size];

    // initialize the visited list
    for (int i = 0; i < size; ++i) {
        startVisited[i] = false;
        endVisited[i] = false;
    }

    vector<int> startParent(size);
    vector<int> endParent(size);

    queue<int> startQueue;
    queue<int> endQueue;

    // initialize the first node

    // start
    startQueue.push(start);
    startVisited[start] = true;
    startParent[start] = -1;

    // end
    endQueue.push(end);
    endVisited[end] = true;
    endParent[end] = -1;

    // start to traverse/explore
    while (!startQueue.empty() && !endQueue.empty()) {
        performBFS(startVisited, startQueue, startParent);
        performBFS(endVisited, endQueue, endParent);

        // if intersecting
        int intersectNode = intersect(startVisited, endVisited);
        if (intersectNode != -1) {
            // print the path and end
            printPath(startParent, endParent, intersectNode);
            return true;
        }
    }
    return false;
}

int Graph::intersect(const bool *startVisited, const bool *endVisited) const {
    for (int i = 0; i < size; ++i) {
        if (startVisited[i] && endVisited[i]) {
            return i;
        }
    }
    return -1;
}

void Graph::printPath(vector<int> &startParent, vector<int> &endParent, int intersectV) {
    vector<int> path;
    path.push_back(intersectV);
    int i = intersectV;
    while (startParent[i] != -1) {
        path.insert(path.begin(), startParent[i]);
        i = startParent[i];
    }
    i = intersectV;
    while (endParent[i] != -1) {
        path.push_back(endParent[i]);
        i = endParent[i];
    }
    // output the path
    for (int j : path) {
        cout << j << endl;
    }
}

int main() {

    int n = 15;
    int start = 0;
    int end = 14;

    Graph test(n);
    test.addEdge(start, 4);
    test.addEdge(1, 4);
    test.addEdge(2, 5);
    test.addEdge(3, 5);
    test.addEdge(4, 6);
    test.addEdge(5, 6);
    test.addEdge(6, 7);
    test.addEdge(7, 8);
    test.addEdge(8, 9);
    test.addEdge(8, 10);
    test.addEdge(9, 11);
    test.addEdge(9, 12);
    test.addEdge(10, 13);
    test.addEdge(10, end);

    if (test.biDirectionSearch(start, end)) {
        cout << "OK!" << endl;
    }

    return 0;
}

