#include<iostream>
#include<list>
#include<queue>
#include<vector>

using namespace std;

struct GraphNode
{
    int vertix;
    // adjacent list
    list<GraphNode*> neighbors;
    // initialization list
    explicit GraphNode(int val):vertix(val) {}
};

class Graph
{
private:
    // size
    int size;
    // adjacent list
    vector<GraphNode*> adj;

public:
    explicit Graph(int curSize);
    ~Graph();
    void clear(vector<GraphNode*>& nodeSet);
    void addEdge(GraphNode* startV, GraphNode* endV);
    GraphNode intersect(bool* startVisited, bool* endVisited) const;
    void performBFS(bool* visited, queue<GraphNode*>& queue, vector<GraphNode*>& parentV);
    static void printPath(vector<GraphNode*>& startParentV,  vector<GraphNode*>& endParentV, GraphNode* intersectV) ;
    bool biDirectionSearch(GraphNode* startV, GraphNode* endV);
};

Graph::Graph(int curSize) {
    size = curSize;
    // initialize the list
    for (int i = 0; i < size; ++i) {
        // fill the size,
        adj.push_back(new GraphNode(0));
    }
}

Graph::~Graph() {
    clear(adj);
}

void Graph::clear(vector<GraphNode*>& nodeSet) {
    // free the memory allocated in the constructor function
    for (int i = 0; i < size; ++i) {
        // free the vector
        if (adj[i] != nullptr) {
            // free the list
            list<GraphNode*>::iterator it;
            for (it = adj[i]->neighbors.begin(); it != adj[i]->neighbors.end(); ++it) {
                if (*it != nullptr) {
                    GraphNode* trash = *it;
                    delete trash;
                }
            }
            // free the vector memory
            delete adj[i];
        }
    }
}

void Graph::addEdge(GraphNode* startV, GraphNode* endV) {
    adj[startV->vertix]->neighbors.push_back(endV);
    // undirected graph
    adj[endV->vertix]->neighbors.push_back(startV);
}

GraphNode Graph::intersect(bool* startVisited, bool* endVisited) const {
    GraphNode intersetNode(-1);
    for (int i = 0; i < size; ++i) {
        if (startVisited[i] && endVisited[i]) {
            intersetNode.vertix = i;
            return intersetNode;
        }
    }
    return intersetNode;
}

/**
 * process neighbors of one node in thr graph, add its neighbors to the node's adjacent list
 */
void Graph::performBFS(bool* visited, queue<GraphNode*>& queue, vector<GraphNode*>& parentV) {
    GraphNode* first = queue.front();
    // pop the current node from the queue
    queue.pop();
    visited[first->vertix] = true;
    list<GraphNode*>::iterator it;
    // check all the neighbors of the current node
    for (it = adj[first->vertix]->neighbors.begin(); it != adj[first->vertix]->neighbors.end(); ++it) {
        // it is an iterator, which is a pointer type, we should use "*" to ge the content of it, which
        // is also a pointer type
        // also, we should notice that we must put "()" in the code, since the priority reason
        if (!visited[(*it)->vertix]) {
            queue.push(*it);
            parentV[(*it)->vertix] = first;
        }
    }
}

bool Graph::biDirectionSearch(GraphNode* startV, GraphNode* endV) {
    bool startVisited[size];
    bool endVisited[size];

    vector<GraphNode*> startParent(size);
    vector<GraphNode*> endParent(size);

    queue<GraphNode*> startQueue;
    queue<GraphNode*> endQueue;
    // initialize the visit flag list
    for (int i = 0; i < size; ++i) {
        startVisited[i] = false;
        endVisited[i] = false;
    }
    // initialize the start point queue
    startQueue.push(startV);
    startVisited[startV->vertix] = true;
    // allocate new memory to store node data
    startParent[startV->vertix] = new GraphNode(-1);
    // initialize the end point queue
    endQueue.push(endV);
    endVisited[endV->vertix] = true;
    endParent[endV->vertix] = new GraphNode(-1);

    while (!startQueue.empty() && !endQueue.empty()) {
        performBFS(startVisited, startQueue, startParent);
        performBFS(endVisited, endQueue, endParent);

        GraphNode intersectNode = intersect(startVisited, endVisited);
        if (intersectNode.vertix != -1) {
            printPath(startParent, endParent, &intersectNode);
            // free the parent allocated memory
            clear(startParent);
            clear(endParent);
            return true;
        }
    }
    // free the parent allocated memory
    clear(startParent);
    clear(endParent);
    return false;
}

void Graph::printPath(vector<GraphNode*>& startParentV,  vector<GraphNode*>& endParentV, GraphNode* intersectV) {
                    vector<GraphNode*> path;
                    path.push_back(intersectV);
                    int i = intersectV->vertix;
                    while (startParentV[i]->vertix != -1) {
//                        cout << "loop" << endl;
                        path.insert(path.begin(), startParentV[i]);
//                        cout << "i: " << i << endl;
                        i = startParentV[i]->vertix;
                    }
                    i = intersectV->vertix;
                    while (endParentV[i]->vertix != -1) {
//                        cout << "loop" << endl;
                        path.push_back(endParentV[i]);
                        i = endParentV[i]->vertix;
                    }
                    vector<GraphNode*>::iterator it;
                    for (it = path.begin(); it != path.end(); ++it) {
                        cout << (*it)->vertix << endl;
                    }
                }

int main() {
    // number of vertices
    int n=15;

    // source vertex
    auto* start = new GraphNode(0);

    // target vertex
    auto* end = new GraphNode(14);

    // create a graph given in above diagram
    auto* node1 = new GraphNode(1);
    auto* node2 = new GraphNode(2);
    auto* node3 = new GraphNode(3);
    auto* node4 = new GraphNode(4);
    auto* node5 = new GraphNode(5);
    auto* node6 = new GraphNode(6);
    auto* node7 = new GraphNode(7);
    auto* node8 = new GraphNode(8);
    auto* node9 = new GraphNode(9);
    auto* node10 = new GraphNode(10);
    auto* node11 = new GraphNode(11);
    auto* node12 = new GraphNode(12);
    auto* node13 = new GraphNode(13);

    Graph g(n);
    g.addEdge(start, node4);
    g.addEdge(node1, node4);
    g.addEdge(node2, node5);
    g.addEdge(node3, node5);
    g.addEdge(node4, node6);
    g.addEdge(node5, node6);
    g.addEdge(node6, node7);
    g.addEdge(node7, node8);
    g.addEdge(node8, node9);
    g.addEdge(node8, node10);
    g.addEdge(node9, node11);
    g.addEdge(node9, node12);
    g.addEdge(node10, node13);
    g.addEdge(node10, end);

    if(!g.biDirectionSearch(start, end)) {
        cout << "cannot find a path between the given two nodes." << endl;
    }

    return 0;

}
