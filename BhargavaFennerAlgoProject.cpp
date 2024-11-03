#include <iostream>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <set>
using namespace std;

//NODE CLASS - each neighborhood is a node with a grade, number of soup kitchens, median income, list of transport lines, and list of connections to other nodes
class Node {
public:
    string neighborhood;
    char grade; // Grade
    int soup_kitchens; // Number of soup kitchens/Boston eats data
    double median_income; // Median income (in thousands)
    list<string> transport; // List of transport lines
    list<Node*> connections; // List of connections to other nodes

    Node(string name, char g, int soup, double income, list<string> trans) {
        neighborhood = name;
        grade = g;
        soup_kitchens = soup;
        median_income = income;
        transport = trans;
    }
};

//GRAPH CLASS- connections neighborhoods
class Graph {
private:
    int vertices; //number of neighborhoods
    Node** adjList; // array of nodes (neighborhoods)
public:
    Graph(int v);
    void addEdge(string src, string dest);
    void addNeighborhood(string name, char grade, int soup_kitchens, double median_income, list<string> transport);
    void displayGraph();
    void breadthFirstSearch(string startNeighborhood); 
};

//constructor 
Graph::Graph(int v) {
    vertices = v;
    adjList = new Node*[v];
    for (int i = 0; i < v; i++) {
        adjList[i] = nullptr;
    }
}

//add neighborhood given data
void Graph::addNeighborhood(string name, char grade, int soup_kitchens, double median_income, list<string> transport) {
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] == nullptr) {
            adjList[i] = new Node(name, grade, soup_kitchens, median_income, transport);
            break;
        }
    }
}

//add a connection
void Graph::addEdge(string src, string dest) {
    Node *srcNode = nullptr, *destNode = nullptr;
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] != nullptr && adjList[i]->neighborhood == src) {
            srcNode = adjList[i];
        }
        if (adjList[i] != nullptr && adjList[i]->neighborhood == dest) {
            destNode = adjList[i];
        }
    }

    //adds connection to list
    if (srcNode != nullptr && destNode != nullptr) {
        srcNode->connections.push_back(destNode);
    }
}

//display data
void Graph::displayGraph() {
    //iterate through list
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] != nullptr) {
            Node* temp = adjList[i];
            cout << "Neighborhood: " << temp->neighborhood << endl;
            cout << "Grade: " << temp->grade << endl;
            cout << "Soup Kitchens: " << temp->soup_kitchens << endl;
            cout << "Median Income: " << temp->median_income << "k" << endl;
            cout << "Transport Lines: ";
            for (auto line : temp->transport) {
                cout << line << " ";
            }
            cout << endl;
            cout << "Connected to: ";
            for (auto connection : temp->connections) {
                cout << connection->neighborhood << " ";
            }
            cout << endl << endl;
        }
    }
}

// BFS implementation ?
void Graph::breadthFirstSearch(string startNeighborhood) {  //add input to specify algorithm

    std::queue<Node*> nodeQueue; // Queue to hold nodes to be explored
    std::set<string> visited; // Set to keep track of visited neighborhoods

    // Find the starting node
    Node* startNode = nullptr;
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] != nullptr && adjList[i]->neighborhood == startNeighborhood) {
            startNode = adjList[i];
            break;
        }
    }

    if (startNode == nullptr) {
        cout << "Starting neighborhood not found." << endl;
        return;
    }

    // Start BFS
    nodeQueue.push(startNode);
    visited.insert(startNode->neighborhood);

    cout << "BFS Route starting from " << startNeighborhood << ": " << endl;

    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();
        
        // Print current node information
        cout << currentNode->neighborhood << " "<<endl;
        
        
        // Iterate through all the connected nodes
        for (Node* neighbor : currentNode->connections) {

            //Call sorting function, using switch case to specify which sorting algorithm to use
        

            //cout <<  currentNode -> neighborhood << " Edge:";
            if (visited.find(neighbor->neighborhood) == visited.end()) {
                //cout << neighbor -> neighborhood<<endl;
                visited.insert(neighbor->neighborhood);
                nodeQueue.push(neighbor);
            }
        }



    }

    cout << endl;
}



int main() {
    Graph graph(17);
    graph.addNeighborhood("East Boston", 'D', 8, 54.9, {"Blue"});
    graph.addNeighborhood("Boston", 'D', 1, 58.5, {"Red", "Green"});
    graph.addNeighborhood("South Boston", 'D', 3, 89.1, {"Red", "Blue"});
    graph.addNeighborhood("South End", 'D', 4, 69.9, {"Orange", "Green"});
    graph.addNeighborhood("CharlesTown", 'D', 1, 94.6, {"Orange"});
    graph.addNeighborhood("Allston", 'C', 0, 52.1, {"Green"});
    graph.addNeighborhood("Brighton", 'C', 0, 52.1, {"Green"});
    graph.addNeighborhood("Fenway/Kenmore", 'C', 3, 65.7, {"Green"});
    graph.addNeighborhood("Roxbury", 'D', 1, 32.5, {"Orange"});
    graph.addNeighborhood("Jamaica Plain", 'D', 5, 32.3, {"Orange"});
    graph.addNeighborhood("Dorchester", 'C', 1, 0, {"Red"}); // median income is split
    graph.addNeighborhood("Roslindale", 'C', 6, 77.9, {"Orange"});
    graph.addNeighborhood("West Roxbury", 'C', 4, 90.5, {"Orange"});
    graph.addNeighborhood("Mattapan", 'C', 8, 43.5, {"Red"});
    graph.addNeighborhood("Hyde Park", 'C', 1, 64.9, {"Red"});
    graph.addNeighborhood("North Dorchester", 'C', 3, 59.7, {"Red"});
    graph.addNeighborhood("South Dorchester", 'C', 4, 62.2, {"Red"});

    graph.addEdge("Roxbury", "Jamaica Plain");
    graph.addEdge("Roxbury", "Roslindale");
    graph.addEdge("Roxbury", "Mattapan");
    graph.addEdge("Roxbury", "Dorchester");

    graph.addEdge("Mattapan","South End");
    graph.addEdge("South End","Hyde Park");
    graph.addEdge("Roslindale","South End");
   
    graph.displayGraph();

    graph.breadthFirstSearch("Roxbury");

    return 0;
}
