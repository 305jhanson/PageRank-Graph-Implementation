#include <iomanip>
#include <iostream>
#include<string>
#include<sstream>
#include <map>
#include <vector>
#include <iterator>
using namespace std;


class Graph
{
private:

    //maps to hold graph and match with outdegree,string,and rank
    map<int, vector<int>> myMap;
    map<int, int> outdegMap;
    map<string, int> stringMap;
    map<int, float> rankMap;
public:

    //helper methods
    void insertEdge(string from, string to);
    bool isEdge(string from, string to);
    vector<int> getAdjacent(int vertex);
    void calcR(int p);
    void initializeSum();
    void printGraph();
};

void Graph::insertEdge(string fro, string t) {

    //check if string is in map and if not add with number
    //for both the from and to
    if (stringMap.find(fro) == stringMap.end()) {
        int index = stringMap.size();
        stringMap[fro] = index;
    }
    if (stringMap.find(t) == stringMap.end()) {
        int index = stringMap.size();
        stringMap[t] = index;
    }


    //get number of to and from string
    int to = stringMap[t];
    int from = stringMap[fro];

    //add to to adjacent vector of from
    myMap[from].push_back(to);

    //add to out degree of from
    //this is for later function but keeps track of how many sites a node points to 
    //if not in map already then set to points to one site
    if (outdegMap.find(from) == outdegMap.end()) {
        outdegMap[from] = 1;
    }

    //if in map add one to outdegree
    else {
        outdegMap[from]++;
    }

    //initialize the to site in outdegree and my map
    if (outdegMap.find(to) == outdegMap.end()) {
        outdegMap[to] = 0;
    }
    if (myMap.find(to) == myMap.end())
        myMap[to] = {};
}


//leftover from a stepik question dont really need for this project
bool Graph::isEdge(string fro, string t) {
    int from = stringMap[fro];
    int to = stringMap[t];
    vector<int> vec = myMap[from];
    for (unsigned int i = 0; i < vec.size();i++) {
        if (to == vec.at(i)) {
            return true;
        }
    }
    return false;
}

//method sets the initialize rank of all the elements to 1/(number of nodes)
void Graph::initializeSum() {

    map<string, int>::iterator it;

    //go over all the vertices and set to 1/(# vertices)
    //O(V) V=vertices
    for (it = stringMap.begin(); it != stringMap.end(); it++) {
        rankMap[it->second] = 1.0 / (float)stringMap.size();

    }

}

//recursivly calculate rank based on value of p given in input
//store each rank in a map
//O(p) as it is called p times
void Graph::calcR(int p) {

    //base condition to exit
    if (p == 1) {
        return;
    }

    //new rank and iterator for map
    map<int, float> newRank;
    map<string, int>::iterator it;
    int index = 0;

    //go over the map O(vertices)
    for (it = stringMap.begin(); it != stringMap.end(); it++) {

        //get the adjacent vertices to this vertex
        vector<int> adj = getAdjacent(it->second);

        //go over each adjacent vertex and add to rank
        //O(edges)
        for (unsigned int i = 0; i < adj.size(); i++) {

            //intialize the new rank for vertex
            if (newRank.find(adj.at(i)) == newRank.end()) {
                newRank[adj.at(i)] = 0;
            }

            //add to rank of vertex that is being pointed to 
            newRank[adj.at(i)] += rankMap[it->second] * 1.0 / outdegMap[it->second];
        }
    }

    //update rank and call function with one less to counter
    rankMap = newRank;
    int ps = p - 1;
    calcR(ps);
}

//get adjacent
vector<int> Graph::getAdjacent(int vertex) {

    vector<int> ve = myMap[vertex];
    return ve;
}

//print each vertex with rank
void Graph::printGraph() {
    map<string, int>::iterator it;
    int index = 0;
    for (it = stringMap.begin(); it != stringMap.end(); it++) {

        //print with 2 decimals
        cout << it->first << " ";
        cout << std::fixed << std::showpoint;
        cout << std::setprecision(2);
        cout << rankMap[it->second];
        cout << endl;
        index++;
    }

}

int main()
{
    //graph object and take in inputs
    Graph g;
    int numIns;
    cin >> numIns;
    int p;
    cin >> p;

    //for number of edges take in input and insert into graph
    for (int i = 0; i < numIns; i++) {

        string one;
        string two;
        cin >> one;
        cin >> two;
        g.insertEdge(one, two);

    }

    //intialize the rank to 1/(# of vertices)
    g.initializeSum();

    //calculate rank 
    g.calcR(p);

    //print vertices with rank
    g.printGraph();


}