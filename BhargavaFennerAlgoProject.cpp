
//EECE2560 Final Project, Fausta Fenner and Druhi Bhargava

//______________________________________________________________________________________
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <set>
#include <unordered_map> 
#include <vector>
#include <algorithm>
using namespace std;
//______________________________________________________________________________________


//string listofFactors[] = {" neighborhood", "grade","num_grocery_stores", "grocery_per_1000","num_grocery_7ft_surge","num_corner_stores","corner_per_1000","num_corner_in_floodplain","num_corner_7ft_surge","avg_distance_grocery","poverty_rate","snap_rate","avg_distance_snap","median_income"}; 

// global Hash map for storing factor weights
unordered_map<string, float> factorWeights;

//Vertex CLASS - each neighborhood is a vertex with a grade, number of soup kitchens, median income, list of connections to other nodes, etc
class Vertex {
public:
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
    list<Vertex*> connections; // List of connections to other nodes


    //constructor with all variables 
  Vertex(string name, char g, int num_grocery_stores, 
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


    // Method to calculate the total weight based on global factor weights
    float getWeight_gen() const {
        float totalWeight = 0.0;

            // Check if "poverty_rate" exists in factorWeights map
            if (factorWeights.count("poverty_rate") == 1) {
                //if it exists, add its value * the weight to the totalWeight
                totalWeight += factorWeights["poverty_rate"] * poverty_rate;
            }

            //repeat for all factors
            if (factorWeights.count("median_income") == 1) {
                totalWeight += factorWeights["median_income"] * median_income;
            }

            // Check if "corner_per_1000" exists in factorWeights map
            if (factorWeights.count("avg_distance_grocery") == 1) {
                totalWeight += factorWeights["avg_distance_grocery"] * avg_distance_grocery;
            }

            //return the final weight
            return totalWeight;
    } 
    
    
    // Method to calculate the total weight based on global factor weights during storm surge
    float getWeight_natural_disaster() const {
        float totalWeight = 0.0;

            //same strategy as above get weight, but for different factors
            if (factorWeights.count("num_grocery_7ft_surge") == 1) {
                totalWeight += factorWeights["num_grocery_7ft_surge"] * num_grocery_7ft_surge;
            }


            if (factorWeights.count("num_corner_in_floodplain") == 1) {
                totalWeight += factorWeights["num_corner_in_floodplain"] * num_corner_in_floodplain;
            }

            if (factorWeights.count("num_corner_7ft_surge") == 1) {
                totalWeight += factorWeights["num_corner_7ft_surge"] * num_corner_7ft_surge;
            }

    
            if (factorWeights.count("poverty_rate") == 1) {
                totalWeight += factorWeights["poverty_rate"] * poverty_rate;
            }
            return totalWeight;
    }


};



//GRAPH CLASS- connect neighborhoods in a graph
class Graph {

public:
    unordered_map<string, Vertex*> adjList; // Hasp map of neighborhood name to Node 

    //constructor 
    Graph(){}

    //function to add a neighborhood into the graph
    void addNeighborhood(Vertex* neighborhood) {            
        adjList[neighborhood->neighborhood] = neighborhood;    // look up table, searching adJList by name 
    }

    //function to add an edge between two neighborhoods given the source and desination neighborhood
    void addEdge(string src, string dest) {
        //if the connection does not already exist, add it 
        if (adjList.find(src) != adjList.end() && adjList.find(dest) != adjList.end()) {
            adjList[src]->connections.push_back(adjList[dest]);
            adjList[dest]->connections.push_back(adjList[src]); // Assuming undirected graph--> connections are made both both ways 
        }
    }

    //function to to print out a given neighborhoods data
    void SearchNeighborhood(string name){
         cout << "Neighborhood: "  << adjList[name]->neighborhood<< "\n" << 
                //cout each variable name and value
                "grade: " << adjList[name]->grade << "\n" <<
                "number of grcoery stores: " << adjList[name]->num_grocery_stores << "\n" <<
                "grocery stores per 1000: " << adjList[name] ->grocery_per_1000 << "\n" <<
                "number of grocery stores 7ft surge: " << adjList[name]-> num_grocery_7ft_surge << "\n" <<
                "number of corner stores: " << adjList[name] ->num_corner_stores << "\n" << 
                "number of corner stores per 1000: " <<  adjList[name]->corner_per_1000 << "\n" <<
                "number of corner in floodplain: " << adjList[name]-> num_corner_in_floodplain << "\n" <<  
                "number of corner in 7ft surge: " << adjList[name]-> num_corner_7ft_surge << "\n" <<
                "poverty rate: " << adjList[name]-> poverty_rate <<"\n" << 
                "snap rate: " << adjList[name]->snap_rate << "\n" << 
                "avg distance to snap: " << adjList[name]-> avg_distance_snap << "\n" <<
                "median_income: " << adjList[name]-> median_income << endl; 
    }



// BFS starting from a specific node, sorting neighbors by their weighted score
    void bfsWithWeightedOrder(string start, int choice) {
        unordered_map<string, bool> visited;
        queue<Vertex*> bfsQueue;

        // Start BFS with the start node
        bfsQueue.push(adjList[start]);
        visited[start] = true;


        while (!bfsQueue.empty()) {
            //get all the neighbors of the current node
            Vertex* currentNode = bfsQueue.front();
            bfsQueue.pop();

            //Print the current node (neighborhood)
            cout << "Visiting neighborhood: " << currentNode->neighborhood << endl;

            //sort the neighbors based on the weighted score (highest to lowest)
            vector<Vertex*> sortedNeighbors(currentNode->connections.begin(), currentNode->connections.end());
            
            sort(sortedNeighbors.begin(), sortedNeighbors.end(), [choice](Vertex* a, Vertex* b) {
                if (choice ==1){
                    return a->getWeight_gen() > b->getWeight_gen(); //Sort in descending order of weight
                }
                
                else if (choice ==2){
                    return a->getWeight_natural_disaster() > b->getWeight_natural_disaster(); //Sort in descending order of weight
                }
                return false;
                
            });

            //visit all sorted neighbors
            for (Vertex* neighbor : sortedNeighbors) {
                if (!visited[neighbor->neighborhood]) {
                    visited[neighbor->neighborhood] = true;
                    bfsQueue.push(neighbor);
                }
            }
        }
    }

};




//get user inputs for the weight value of each variable 
void getUserInputForWeights() {
    // Initialize all factor weights to zero
    factorWeights["poverty_rate"] = 0.0;
    factorWeights["median_income"] = 0.0;
    factorWeights["avg_distance_grocery"] = 0.0;

    // Prompt the user to input weights for each factor
    cout << "Enter the weight for poverty_rate (0.0 to 1.0): ";
    cin >> factorWeights["poverty_rate"];

    cout << "Enter the weight for median_income (0.0 to 1.0): ";
    cin >> factorWeights["median_income"];

    cout << "Enter the weight for avg_distance_grocery (the average distance to a grocery store) (0.0 to 1.0): ";
    cin >> factorWeights["avg_distance_grocery"];
}

//get user inputs for the weight value of each variable during a natural disaster
void getUserInputForWeights_Natural_Disaster() {
    // Initialize all factor weights to zero
    factorWeights["num_grocery_7ft_surge"] = 0.0;
    factorWeights["num_corner_in_floodplain"] = 0.0;
    factorWeights["num_corner_7ft_surge"] = 0.0;
    factorWeights["poverty_rate"] = 0.0;

    // Prompt the user to input weights for each factor
    cout << "Enter the weight for num_grocery_7ft_surge (Number of accessible grocery stores in a 7.5 foot storm surge) (0.0 to 1.0): ";
    cin >> factorWeights["num_grocery_7ft_surge"];

    cout << "Enter the weight for num_corner_in_floodplain (Number of corner stores in a floodplain) (0.0 to 1.0): ";
    cin >> factorWeights["num_corner_in_floodplain"];

    cout << "Enter the weight for num_corner_7ft_surge (Number of corner stores accessible during a 7.5 foot storm surge) (0.0 to 1.0): ";
    cin >> factorWeights["num_corner_7ft_surge"];

    cout << "Enter the weight for poverty_rate (0.0 to 1.0): ";
    cin >> factorWeights["poverty_rate"];
}



int main() {

    //initlizae all vertices
    Vertex* Allston = new Vertex("Allston", 'C', 3, 0.1, 0, 12, 0.41, 0, 1, 0.37, 17.7, 8.1, 0.16, 52.1, {"Green Line"});
    Vertex* Backbay = new Vertex("Backbay", 'C', 2, 0.1, 0, 5, 0.28, 0, 3, 0.23, 7.1, 4.1, 0.14, 97.8, {"Green Line"});
    Vertex* Beacon_Hill = new Vertex("Beacon Hill", 'A', 0, 0, 0, 3, 0.33, 0, 1, 0.24, 5.8, 2.5, 0.14, 102.2, {"Green Line"});
    Vertex* Brighton = new Vertex("Brighton", 'C', 2, 0.04, 1, 15, 0.33, 0, 0, 0.73, 13.3, 11.4, 0.19, 65.7, {"Green Line"});
    Vertex* Charlestown = new Vertex("CharlesTown", 'D', 1, 0.06, 0, 6, 0.36, 0, 3, 0.37, 19.4, 17, 0.1, 94.6, {"Green Line"});
    Vertex* Dorchester = new Vertex("Dorchester", 'C', 5, 0.04, 2, 47, 0.41, 0, 2, 0.58, 22.6, 29.3, 0.13, 60.05, {"Green Line"});
    Vertex* Downtown = new Vertex("Downtown", 'N', 0, 0, 0, 23, 2.05, 1, 8, 0.38, 20.3, 12.8, 0.1, 168.6, {"Green Line"});
    Vertex* East_Boston = new Vertex("East Boston", 'D', 1, 0.02, 1, 28, 0.69, 1, 12, 0.82, 16.5, 22.1, 0.11, 54.9, {"Green Line"});
    Vertex* Fenway = new Vertex("Fenway", 'C', 2, 0.06, 2, 14, 0.41, 0, 10, 0.28, 19.7, 11.8, 0.15, 37.9, {"Green Line"});
    Vertex* Hyde_Park = new Vertex("Hyde Park", 'C', 5, 0.16, 0, 9, 0.29, 0, 0, 0.48, 9.4, 15.2, 0.29, 64.9, {"Green Line"});
    Vertex* Jamaica_Plain = new Vertex("Jamaica Plain", 'A', 3, 0.08, 0, 9, 0.24, 0, 0, 0.45, 16.9, 13.8, 0.19, 84, {"Green Line"});
    Vertex* Longwood_Medical_Center = new Vertex("Longwood Medical Center", 'C', 0, 0, 0, 0, 0, 0, 0, 0.29, 7, 20.1, 0.27, 38.5, {"Green Line"});
    Vertex* Mattapan = new Vertex("Mattapan", 'C', 2, 0.09, 0, 8, 0.35, 0, 0, 0.6, 21.5, 28.8, 0.28, 43.5, {"Green Line"});
    Vertex* Mission_Hill = new Vertex("Mission Hill", 'D', 1, 0.06, 0, 2, 0.12, 0, 0, 0.29, 28.8, 22.5, 0.16, 37.3, {"Green Line"});
    Vertex* North_End = new Vertex("North End", 'D', 0, 0, 0, 7, 0.69, 0, 2, 0.64, 4.2, 1.6, 0.05, 98.5, {"Green Line"});
    Vertex* Roslindale = new Vertex("Roslindale", 'C', 2, 0.07, 0, 5, 0.17, 0, 0, 0.46, 11.4, 15.3, 0.18, 77.9, {"Green Line"});
    Vertex* Roxbury = new Vertex("Roxbury", 'D', 2, 0.04, 0, 20, 0.41, 0, 4, 0.37, 34.9, 40, 0.14, 32.3, {"Green Line"});
    Vertex* South_Boston = new Vertex("South Boston", 'D', 2, 0.06, 0, 10, 0.3, 0, 3, 0.35, 17.9, 13.4, 0.16, 89.1, {"Green Line"});
    Vertex* South_Boston_Waterfront = new Vertex("South Boston Waterfront", 'N', 0, 0, 0, 2, 1.06, 0, 1, 0.56, 3.7, 8.4, 0.55, 0, {"Green Line"});
    Vertex* South_End = new Vertex("South End", 'D', 4, 0.16, 3, 10, 0.41, 0, 9, 0.25, 19.6, 17.9, 0.08, 69.9, {"Green Line"});
    Vertex* West_End = new Vertex("West End", 'D', 1, 0.25, 0, 1, 0.25, 0, 0, 0.21, 10.3, 6.4, 0.18, 83.8, {"Green Line"});
    Vertex* West_Roxbury = new Vertex("West Roxbury", 'B', 2, 0.07, 0, 4, 0.13, 0, 0, 0.33, 5.8, 7.5, 0.33, 90.5, {"Green Line"});

    //initialize graph 
    Graph graph;

    //add vertices into graph
    graph.addNeighborhood(Allston);
    graph.addNeighborhood(Backbay);
    graph.addNeighborhood(Beacon_Hill);
    graph.addNeighborhood(Brighton);
    graph.addNeighborhood(Charlestown); 
    graph.addNeighborhood(Dorchester);
    graph.addNeighborhood(Downtown);
    graph.addNeighborhood(East_Boston);
    graph.addNeighborhood(Fenway); 
    graph.addNeighborhood(Hyde_Park);
    graph.addNeighborhood(Jamaica_Plain);
    graph.addNeighborhood(Longwood_Medical_Center);
    graph.addNeighborhood(Mattapan); 
    graph.addNeighborhood(Mission_Hill);
    graph.addNeighborhood(North_End);
    graph.addNeighborhood(Roslindale);
    graph.addNeighborhood(Roxbury); 
    graph.addNeighborhood(South_Boston);
    graph.addNeighborhood(South_Boston_Waterfront);
    graph.addNeighborhood(South_End); 
    graph.addNeighborhood(West_End);
    graph.addNeighborhood(West_Roxbury); 


    //add edges based on Boston data
    graph.addEdge("Allston", "Back Bay");
    graph.addEdge("Back Bay", "Beacon Hill");
    graph.addEdge("Beacon Hill", "Brighton");
    graph.addEdge("Brighton", "Charlestown");
    graph.addEdge("Charlestown", "Dorchester");
    graph.addEdge("Dorchester", "Downtown");
    graph.addEdge("Downtown", "East Boston");
    graph.addEdge("East Boston", "Fenway");
    graph.addEdge("Fenway", "Hyde Park");
    graph.addEdge("Hyde Park", "Jamaica Plain");
    graph.addEdge("Jamaica Plain", "Longwood Medical Center");
    graph.addEdge("Longwood Medical Center", "Mattapan");
    graph.addEdge("Mattapan", "Mission Hill");
    graph.addEdge("Mission Hill", "North End");
    graph.addEdge("North End", "Roslindale");
    graph.addEdge("Roslindale", "Roxbury");
    graph.addEdge("Roxbury", "South Boston");
    graph.addEdge("South Boston", "South Boston Waterfront");
    graph.addEdge("South Boston Waterfront", "South End");
    graph.addEdge("South End", "West End");
    graph.addEdge("West End", "West Roxbury");
    graph.addEdge("West Roxbury", "Allston");


    // Menu:

    bool system_running = true; 
    int selection;  
    string neighborhoodName; 

    //while loop that mantains the menu bar
    while(system_running)
    {
        //print menu
        cout << "Please select (1-4)\n" <<
                "1.Display a Neighborhoods Data \n" <<
                "2.General Mobile Market Route\n" <<
                "3.Mobile Market Route During a Natural Disaster\n" <<
                "4.End Program\n " << 
                
                "Number Entered: "; 



        cin >> selection; 

        //switch case for each selection
        switch(selection){

            //Case 1: User inputs  a neighborhood, program outputs data values for it
            case 1:
                cout << "Enter a Neighborhood: "; 
                cin >> neighborhoodName;
                //if valid neighborhood, call searchneighborhood
                if (graph.adjList.count(neighborhoodName) == 1) {
                    graph.SearchNeighborhood(neighborhoodName); 
                }
                //else return error
                else if (graph.adjList.count(neighborhoodName) == 0){
                    cout << "Not a Valid Neighborhood." <<endl;
                }

                break; 

            //Case 2: General Mobile Market Route
            case 2:
                cout << "Enter a Neighborhood to start the route at: "; 
                cin >> neighborhoodName;
                //if valid neighborhood, call bfs function
                if (graph.adjList.count(neighborhoodName) == 1) {
                    getUserInputForWeights();
                    graph.bfsWithWeightedOrder(neighborhoodName,1);
                }
                //else return error
                else if (graph.adjList.count(neighborhoodName) == 0){
                    cout << "Not a Valid Neighborhood." <<endl;
                }
                
                
        
                break; 

            //Case 3: Mobile Market Route During a Natural Disaster
            case 3: 
                cout << "Enter a Neighborhood to start the route at: "; 
                cin >> neighborhoodName;
                  if (graph.adjList.count(neighborhoodName) == 1) {
                    getUserInputForWeights_Natural_Disaster();
                    graph.bfsWithWeightedOrder(neighborhoodName,2);
                }
                else if (graph.adjList.count(neighborhoodName) == 0){
                    cout << "Not a Valid Neighborhood." <<endl;
                }
                
                break; 
            //Case 4: End program
            case 4:
                cout << "Ending Program" << endl; 
                system_running = false; 
                break; 

            default:
                cout << "Invalid Number."<< endl; 
                break; 
        } 

    }       


//delete pointers
    delete Allston;
    delete Backbay;
    delete Beacon_Hill;
    delete Brighton;
    delete Charlestown;
    delete Dorchester;
    delete Downtown;
    delete East_Boston;
    delete Fenway;
    delete Hyde_Park;
    delete Jamaica_Plain;
    delete Longwood_Medical_Center;
    delete Mattapan;
    delete Mission_Hill;
    delete North_End;
    delete Roslindale;
    delete Roxbury;
    delete South_Boston;
    delete South_Boston_Waterfront;
    delete South_End;
    delete West_End;
    delete West_Roxbury;


    return 0;
}
