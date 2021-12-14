#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

enum caveType {START, MINOR, MAJOR, END};

class Node {
    public:
    string name;
    Node* parent;
    vector<Node*> children;

    Node(string n){
        name = n;
        children = {};
    }
    
    static caveType getType(string &n){
        if (n == "start"){
            return START;
        } else if (n== "end"){
            return END;
        } else if (n[0] - 91 > 0){
            return MINOR;
        } else {
            return MAJOR;
        }
    }

    ~Node(){
        for (auto p : children){
            delete p;
        }
    }
};

void buildAdjacencies(vector<pair<string, string>> &in_data, unordered_map<string,vector<string>> &adjacencies){
    for (auto &p : in_data){
        if (adjacencies.find(p.first) == adjacencies.end()){
            adjacencies.emplace(p.first, vector<string>{p.second});
        }
        else {
            adjacencies[p.first].push_back(p.second);
        }
        if (adjacencies.find(p.second) == adjacencies.end()){
            adjacencies.emplace(p.second, vector<string>{p.first});
        }
        else {
            adjacencies[p.second].push_back(p.first);
        }
    }
    return;
}

void buildTree(Node* root, unordered_map<string, vector<string>> &adjacencies, vector<string> visited){
    for (auto &adjacent : adjacencies[root->name]){
            //visited this particular adjacent cave already in this branch
            if (std::find(visited.begin(), visited.end(), adjacent) != visited.end()){
                caveType t = Node::getType(adjacent);
                if (t == END){
                    return;
                } if (t == MINOR || t == START){
                    continue;
                }
            } 
            Node* child = new Node(adjacent);
            root->children.push_back(child);
            vector<string> newVisited = visited;
            newVisited.push_back(root->name);
            buildTree(child, adjacencies, newVisited);
    }
}

void parseInput(string line, pair<string,string> &input){
    stringstream s_stream(line);
    string substr;
    getline(s_stream, substr, '-');
    input.first = substr;
    getline(s_stream, substr);
    input.second = substr;
}

void countPaths(Node* root, int &sum){
    for (auto &child : root->children){
        if (child->name == "end"){
            sum++;
        }
        countPaths(child, sum);
    }
}

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    vector<pair<string, string>> in_data;

    {
    ifstream in(filename);

    string line;
    int i = 0;
    while (in.good()){
        in_data.push_back({});
        getline(in, line);
        parseInput(line, in_data[i]);
        i++;
    }
    in.close();
    }

    unordered_map<string, vector<string>> adjacencies;

    buildAdjacencies(in_data, adjacencies);

    Node* start = new Node(string("start"));

    buildTree(start, adjacencies, vector<string>());

    Node* curr = start;
    int numPaths = 0;
    countPaths(curr, numPaths);
    cout << endl << "Number of paths: " << numPaths << endl;

    return 0;
}

void buildTree2(Node* root, unordered_map<string, vector<string>> &adjacencies, vector<string> visited, string special){
    string newSpecial;
    for (auto &adjacent : adjacencies[root->name]){
            newSpecial = special;
            //visited this particular adjacent cave already in this branch
            if (std::find(visited.begin(), visited.end(), adjacent) != visited.end()){
                caveType t = Node::getType(adjacent);
                if (t == MINOR && special.empty()){
                    newSpecial = adjacent;
                }
                else if (t == END){
                    return;
                } else if (t == MINOR || t == START){
                    continue;
                }
            } 
            Node* child = new Node(adjacent);
            root->children.push_back(child);
            vector<string> newVisited = visited;
            newVisited.push_back(root->name);
            buildTree2(child, adjacencies, newVisited, newSpecial);
    }
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    vector<pair<string, string>> in_data;

    {
    ifstream in(filename);

    string line;
    int i = 0;
    while (in.good()){
        in_data.push_back({});
        getline(in, line);
        parseInput(line, in_data[i]);
        i++;
    }
    in.close();
    }

    unordered_map<string, vector<string>> adjacencies;

    buildAdjacencies(in_data, adjacencies);

    Node* start = new Node(string("start"));

    buildTree2(start, adjacencies, vector<string>(), "");

    Node* curr = start;
    int numPaths = 0;
    countPaths(curr, numPaths);
    cout << "Number of paths: " << numPaths << endl;

    return 0;
}



int main()
{
    //part1();
    part2();
}