
//______________________________________________________________________________________
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <set>
using namespace std;
//______________________________________________________________________________________



//NODE CLASS - each neighborhood is a node with a grade, number of soup kitchens, median income, list of transport lines, and list of connections to other nodes
class Node {
public:
    //Node * next; 
    string neighborhood; //name of neighborhood
    char grade; // redlining grade
    int num_grocery_stores; //number of grocery stores
    float grocery_per_1000; //number of grocery stores per 1000
    int num_grocery_7ft_surge; //number of grocery stores in 7.5 foot storm surge
    int num_corner_stores; //number of corner stores
    float corner_per_1000; //number of corner stores per 1000
    int num_corner_in_floodplain; //number of corner stores in floodplain
    float num_corner_7ft_surge; //number of corner stores in 7.5 foot storm surge
    float avg_distance_grocery; //average distance to closest grocery store (in miles)
    float poverty_rate; //poverty rate (percent)
    float snap_rate; //snap rate
    float avg_distance_snap; //avg distance to snap outlet (mile)
    float median_income; //median income ($k)
    list<string> transport; // List of transport lines
    list<Node*> connections; // List of connections to other nodes



    //constructor with all variables 
  Node(string name, char g, int num_grocery_stores, 
     float grocery_per_1000, int num_grocery_7ft_surge, 
     int num_corner_stores, float corner_per_1000, 
     int num_corner_in_floodplain, float num_corner_7ft_surge, 
     float avg_distance_grocery, float poverty_rate, 
     float snap_rate, float avg_distance_snap, float median_income,
     list<string> trans) {

    neighborhood = name;
    grade = g;
    this->num_grocery_stores = num_grocery_stores; 
    this->grocery_per_1000 = grocery_per_1000;
    this->num_grocery_7ft_surge = num_grocery_7ft_surge;
    this->num_corner_stores = num_corner_stores;
    this->corner_per_1000 = corner_per_1000;
    this->num_corner_in_floodplain = num_corner_in_floodplain;
    this->num_corner_7ft_surge = num_corner_7ft_surge;
    this->avg_distance_grocery = avg_distance_grocery;
    this->poverty_rate = poverty_rate;
    this->snap_rate = snap_rate;
    this->avg_distance_snap = avg_distance_snap;
    this -> median_income = median_income;
    transport = trans;
}


};

//GRAPH CLASS- connect neighborhoods in a graph
class Graph {
private:
    int vertices; //number of neighborhoods
    Node** adjList; // array of nodes (neighborhoods) // notation ? 
public:
    Graph(int v);                                                              //create the graph
    void addEdge(string src, string dest);                                     //add a connection
    void addNeighborhood(string name, char g, int num_grocery_stores,          //add a neighborhood
     float grocery_per_1000, int num_grocery_7ft_surge, 
     int num_corner_stores, float corner_per_1000, 
     int num_corner_in_floodplain, float num_corner_7ft_surge, 
     float avg_distance_grocery, float poverty_rate, 
     float snap_rate, float avg_distance_snap, float median_income,
     list<string> trans);
    void displayGraph();                                                       //display all data for each neighborhood
    void breadthFirstSearch(string startNeighborhood);                         //BFS given starting neighborhood
    void generalSorting(list<Node*> connections); 
};


//constructor for graph
//______________________________________________________________________________________
Graph::Graph(int v) {
    vertices = v;
    adjList = new Node*[v];
    for (int i = 0; i < v; i++) {
        adjList[i] = nullptr;
    }
}
//______________________________________________________________________________________



//add a neighborhood to the graph
//______________________________________________________________________________________
void Graph::addNeighborhood(string name, char g, int num_grocery_stores, 
     float grocery_per_1000, int num_grocery_7ft_surge, 
     int num_corner_stores, float corner_per_1000, 
     int num_corner_in_floodplain, float num_corner_7ft_surge, 
     float avg_distance_grocery, float poverty_rate, 
     float snap_rate, float avg_distance_snap, float median_income,
     list<string> trans) {
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] == nullptr) {
            adjList[i] = new Node(name, g, num_grocery_stores, 
                                   grocery_per_1000, num_grocery_7ft_surge, 
                                   num_corner_stores, corner_per_1000, 
                                   num_corner_in_floodplain, num_corner_7ft_surge, 
                                   avg_distance_grocery, poverty_rate, 
                                   snap_rate, avg_distance_snap, median_income,trans);
            break;
        }
    }
}
//______________________________________________________________________________________





//add a connection (edge) between neighborhoods
//______________________________________________________________________________________
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
//______________________________________________________________________________________




//display all data for each node
//______________________________________________________________________________________
void Graph::displayGraph() {
    //iterate through list, printing each data point for each neighborhood
    for (int i = 0; i < vertices; i++) {
        if (adjList[i] != nullptr) {
            Node* temp = adjList[i];


            cout << "Neighborhood: " << temp->neighborhood << endl;
            cout << "Grade: " << temp->grade << endl;
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
//______________________________________________________________________________________



// BFS implementation
//______________________________________________________________________________________
void Graph::breadthFirstSearch(string startNeighborhood) {  //add input to specify algorithm

    queue<Node*> nodeQueue; // Queue to hold nodes to be explored
    set<string> visited; // Set to keep track of visited neighborhoods
    
    queue<Node*> tempQueue;
    queue<Node*> SortedQueue;

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
    nodeQueue.push(startNode); // i am confused how a queue is using push and pop 
    visited.insert(startNode->neighborhood);

    cout << "BFS Route starting from " << startNeighborhood << ": " << endl;

    generalSorting(startNode-> connections);

    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        
        


        // Print current node information
        //cout << currentNode->neighborhood << " "; // Printing individual nodes 
        //cout << currentNode-> poverty_rate << endl; 

        
        
        // Iterate through all the connected nodes
        for (Node* neighbor : currentNode->connections) {

            //Call sorting function, using switch case to specify which sorting algorithm to use
           // cout << "current Node:" << currentNode ->neighborhood << endl;  // all Roxbury 
            


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
//______________________________________________________________________________________

// class DoubleLInkedList{
//     Node data; 


// }; 
//_______________________________________________________________
// bool comparator ???
bool comparePovertyRate(Node* a, Node* b) {
    return a->poverty_rate < b->poverty_rate;  // Sort in ascending order of poverty_rate
}

//______________________________________________________________________________________
// can acess by passing in starting node 
void Graph::generalSorting(list<Node*> connections) {

    list<Node*> sorted = connections; 
    sorted.sort(comparePovertyRate);

    cout << "Sorted by poverty rate: " << endl;
    for (Node* neighbor : sorted) {
        cout << neighbor->neighborhood << " ";
        cout << neighbor->poverty_rate << " ";
        cout << endl;
    }

//   for (Node* neighbor : connections) {
//     // Do something with each Node pointer (neighbor)
//     cout << neighbor->neighborhood << " ";  // Accessing a member of the Node class 
//     cout << neighbor-> poverty_rate <<" "; 

   
  }

   
   
//    for (int i = 0; i < vertices; i++) {
//         if (adjList[i] != nullptr) {
//             Node* temp = adjList[i];
//             cout << "Neighborhood name: "  << temp -> neighborhood << endl; 
//         } 
//    } 
    // charcteristic of a weight --> private property 
    
 // list of all Neighborhoods
//     //int n = adjList.size(); 

//     //for( int i = 0, i < ) 




/*Graphing Algo 1 - Natural Disaster 

- Number Grocery Stores per 1000 (.7)
- Number of Corner Stores per 1000 (.3)
- Poverty Rate (.6)

// sorting algorithm: insert sort

*/


/*Graphing Algo 2 - General Sorting Algo 

- Poverty Rate (0.5)
- Median Income (0.5) 
- Grade (0.3)
- Miles to Grocery Store 
- Miles to Snap 

*/



int main() {
    Graph graph(17);

    graph.addNeighborhood("Allston", 'C', 3, 0.1, 0, 12, 0.41, 0, 1, 0.37, 17.7, 8.1, 0.16, 52.1, {"Green Line"});
    graph.addNeighborhood("Backbay", 'C', 2, 0.1, 0, 5, 0.28, 0, 3, 0.23, 7.1, 4.1, 0.14, 97.8, {"Green Line"});
    graph.addNeighborhood("Beacon Hill", 'A', 0, 0, 0, 3, 0.33, 0, 1, 0.24, 5.8, 2.5, 0.14, 102.2, {"Green Line"});
    graph.addNeighborhood("Brighton", 'C', 2, 0.04, 1, 15, 0.33, 0, 0, 0.73, 13.3, 11.4, 0.19, 65.7, {"Green Line"});
    graph.addNeighborhood("CharlesTown", 'D', 1, 0.06, 0, 6, 0.36, 0, 3, 0.37, 19.4, 17, 0.1, 94.6, {"Green Line"});
    graph.addNeighborhood("Dorchester", 'C', 5, 0.04, 2, 47, 0.41, 0, 2, 0.58, 22.6, 29.3, 0.13, 60.05, {"Green Line"});
    graph.addNeighborhood("Downtown", 'N', 0, 0, 0, 23, 2.05, 1, 8, 0.38, 20.3, 12.8, 0.1, 168.6, {"Green Line"});
    graph.addNeighborhood("East Boston", 'D', 1, 0.02, 1, 28, 0.69, 1, 12, 0.82, 16.5, 22.1, 0.11, 54.9, {"Green Line"});
    graph.addNeighborhood("Fenway", 'C', 2, 0.06, 2, 14, 0.41, 0, 10, 0.28, 19.7, 11.8, 0.15, 37.9, {"Green Line"});
    graph.addNeighborhood("Hyde Park", 'C', 5, 0.16, 0, 9, 0.29, 0, 0, 0.48, 9.4, 15.2, 0.29, 64.9, {"Green Line"});
    graph.addNeighborhood("Jamaica Plain", 'A', 3, 0.08, 0, 9, 0.24, 0, 0, 0.45, 16.9, 13.8, 0.19, 84, {"Green Line"});
    graph.addNeighborhood("Longwood Medical Center", 'C', 0, 0, 0, 0, 0, 0, 0, 0.29, 7, 20.1, 0.27, 38.5, {"Green Line"});
    graph.addNeighborhood("Mattapan", 'C', 2, 0.09, 0, 8, 0.35, 0, 0, 0.6, 21.5, 28.8, 0.28, 43.5, {"Green Line"});
    graph.addNeighborhood("Mission Hill", 'D', 1, 0.06, 0, 2, 0.12, 0, 0, 0.29, 28.8, 22.5, 0.16, 37.3, {"Green Line"});
    graph.addNeighborhood("North End", 'D', 0, 0, 0, 7, 0.69, 0, 2, 0.64, 4.2, 1.6, 0.05, 98.5, {"Green Line"});
    graph.addNeighborhood("Roslindale", 'C', 2, 0.07, 0, 5, 0.17, 0, 0, 0.46, 11.4, 15.3, 0.18, 77.9, {"Green Line"});
    graph.addNeighborhood("Roxbury", 'D', 2, 0.04, 0, 20, 0.41, 0, 4, 0.37, 34.9, 40, 0.14, 32.3, {"Green Line"});
    graph.addNeighborhood("South Boston", 'D', 2, 0.06, 0, 10, 0.3, 0, 3, 0.35, 17.9, 13.4, 0.16, 89.1, {"Green Line"});
    graph.addNeighborhood("South Boston Waterfront", 'N', 0, 0, 0, 2, 1.06, 0, 1, 0.56, 3.7, 8.4, 0.55, 0, {"Green Line"});
    graph.addNeighborhood("South End", 'D', 4, 0.16, 3, 10, 0.41, 0, 9, 0.25, 19.6, 17.9, 0.08, 69.9, {"Green Line"});
    graph.addNeighborhood("West End", 'D', 1, 0.25, 0, 1, 0.25, 0, 0, 0.21, 10.3, 6.4, 0.18, 83.8, {"Green Line"});
    graph.addNeighborhood("West Roxbury", 'B', 2, 0.07, 0, 4, 0.13, 0, 0, 0.33, 5.8, 7.5, 0.33, 90.5, {"Green Line"});



    graph.addEdge("Roxbury", "Jamaica Plain");
    graph.addEdge("Roxbury", "Roslindale");
    graph.addEdge("Roxbury", "Mattapan");
    graph.addEdge("Roxbury", "Dorchester");
    graph.addEdge("Mattapan","South End");
    graph.addEdge("South End","Hyde Park");
    graph.addEdge("Roslindale","South End");
   

    //graph.displayGraph();

    graph.breadthFirstSearch("Roxbury");
    //string grade = "grade"; 
    //graph.generalSorting(grade); 


    // // Menu:
    // bool system_running = true; 
    // int selection;  
    
    // while(system_running)
    // {
    //     cout << "Please select (1-4)\n" <<
    //             "1. Display all Neighborhoods \n" << endl; 
    //     cin >> selection; 

    //     switch(selection){
    //         case 1:
    //             //cout << "Display all neighborhoods" << endl; 
    //             graph.displayGraph();
    //             break; 
    //         case 2:
    //             break; 
    //         case 3: 
    //             break; 
    //         case 4:
    //             break; 

    //         default:
    //             cout << "default case "<< endl; 
    //             break; 
    //     } 

    // }       



    

    return 0;
}
