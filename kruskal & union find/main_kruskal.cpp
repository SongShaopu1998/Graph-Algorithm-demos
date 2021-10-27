//
// Created by shaopu on 2021/10/27.
//

#include<iostream>
#include<vector>
#include<list>
#include <queue>

using namespace std;

class forest {
private:
    int* parent;
    int nodeNum;
public:
    // use friend class
    friend class Graph;
    explicit forest(int n);
    ~forest();
    int _find(int u);
    void _union(int root1, int root2);
};

forest::forest(int n) {
    nodeNum = n;
    parent = new int[nodeNum];
    // initialize
    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
    }
}

forest::~forest() {
    delete [] parent;
}

int forest::_find(int u) {
    // it is a root
    if (parent[u] < 0) {
        // return the root index
        return u;
    }
    else {
        // find the final root
        int root = _find(parent[u]);
        // path compression
        parent[u] = root;
        return root;
    }
}

void forest::_union(int root1, int root2) {
    int newSize = parent[root1] + parent[root2];
    // smart union
    if (parent[root1] < parent[root2]) {
        parent[root2] = root1;
        parent[root1] = newSize;
    }
    else {
        parent[root1] = root2;
        parent[root2] = newSize;
    }
}

class Graph {
private:
    int size;
    // we need a weight dimension
    list<pair<int, int>>* adj;
public:
    explicit Graph(int n);
    ~Graph();
    void addEdge(int start, int end, int weight);
    int performKruskal();
};

Graph::Graph(int n) {
    size = n;
    adj = new list<pair<int, int>>[size];
}

Graph::~Graph() {
    delete [] adj;
}

void Graph::addEdge(int start, int end, int weight) {
    pair<int ,int> temPairStart = {weight, start};
    pair<int ,int> temPairEnd = {weight, end};
    adj[start].push_back(temPairEnd);
    adj[end].push_back(temPairStart);
}

int Graph::performKruskal() {
    int sumWeight = 0;
    forest disJointSet(size);
    typedef pair<int, pair<int, int>> edgePair;
    priority_queue<edgePair, vector<edgePair>, greater<>> graphQueue;
    // add all edges to the queue
    for (int i = 0; i < size; ++i) {
        list<pair<int, int>>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); ++it) {
            // weight-start-end
            pair<int, int> edge = {i, (*it).second};
            graphQueue.push({(*it).first, edge});
        }
    }
    int edgeNum = 0;
    while (edgeNum < size - 1) {
        int weight = graphQueue.top().first;
        pair<int, int> edge = graphQueue.top().second;
        // pop the element
        graphQueue.pop();
        if (disJointSet._find(edge.first) != disJointSet._find(edge.second)) {
            edgeNum++;
            cout << edge.first << "->" << edge.second << endl;
            sumWeight += weight;
            disJointSet._union(disJointSet._find(edge.first), disJointSet._find(edge.second));
        }
    }
    return sumWeight;
}

int main() {
    Graph kruskal(9);
    kruskal.addEdge(0, 1, 4);
    kruskal.addEdge(0, 7, 8);
    kruskal.addEdge(1, 2, 8);
    kruskal.addEdge(1, 7, 11);
    kruskal.addEdge(2, 3, 7);
    kruskal.addEdge(2, 8, 2);
    kruskal.addEdge(2, 5, 4);
    kruskal.addEdge(3, 4, 9);
    kruskal.addEdge(3, 5, 14);
    kruskal.addEdge(4, 5, 10);
    kruskal.addEdge(5, 6, 2);
    kruskal.addEdge(6, 7, 1);
    kruskal.addEdge(6, 8, 6);
    kruskal.addEdge(7, 8, 7);
    int mstWeight = kruskal.performKruskal();
    cout << "total cost: " << mstWeight << endl;
    return 0;
}

