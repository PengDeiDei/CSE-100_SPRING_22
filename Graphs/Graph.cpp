/**
 * Name: Haonan Peng
 * Email: hap045@ucsd.edu
 * 
 * Source:
 * 1) Design note of PA2: I direct use the code of prasing CSV file
 *   
 * 2) https://gist.github.com/quickgrid/572aa9b3dfb8a71bb424005f9a810a84
 *    I took it as reference to build my graph
 *      
 * 
 * This file provides functions implementation of graph
 */

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

#include <utility>
#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

// Graph constructor
Graph::Graph(const string &edgelist_csv_fn) {
    num_Edges = 0; // initialize edges counter
    edgeList.clear(); // clear the edge list vector
    vertices.clear(); // clear the vertices vector
    ifstream infile(edgelist_csv_fn); // open edge list  
    string currLine; // string to store current line

    while(getline(infile, currLine)){
        istringstream istr(currLine);
        string label1, label2, weightStr;
        getline(istr, label1,',');
        getline(istr, label2, ',');
        getline(istr, weightStr, '\n');

        num_Edges++;
        int weight = stoi(weightStr);
        auto loc1 = find(vertices.begin(),vertices.end(),label1);

        if(loc1 == vertices.end()){
            vertices.push_back(label1);
            unordered_map<string, int> newMap;
            newMap.insert(make_pair(label2,weight));
            edgeList.push_back(newMap);
        }else{
            int idx = loc1 - vertices.begin();
            edgeList[idx].insert(make_pair(label2,weight));
        }
        
        auto loc2 = find(vertices.begin(),vertices.end(),label2);
        if(loc2 == vertices.end()){
            vertices.push_back(label2);
            unordered_map<string, int> newMap;
            newMap.insert(make_pair(label1,weight));
            edgeList.push_back(newMap);
        }else{
            int idx = loc2 - vertices.begin();
            edgeList[idx].insert(make_pair(label1,weight));
        }
    }
    infile.close();
}

// return the number of nodes
unsigned int Graph::num_nodes() {
    return vertices.size();
}

// store nodes from vector to unordered_set
// and return the set
unordered_set<string> Graph::nodes() {
    unordered_set<string> nodesSet;
    nodesSet.insert(vertices.begin(),vertices.end());
    return nodesSet;
}

unsigned int Graph::num_edges() {
    return num_Edges;
}

unsigned int Graph::num_neighbors(string const &node_label) {
    // TODO
    auto loc = find(vertices.begin(),vertices.end(),node_label);
    if(loc != vertices.end()){
        int idx = loc - vertices.begin();
        return edgeList[idx].size();
    }

    // return 0 if node doesn't exist
    return 0;
}

// get the index of u_label in the vertices vector
// use the index to find the specific unordered_map 
// in the edgelist vector, and get access to the weight
// between u_label and v_label
int Graph::edge_weight(string const &u_label, string const &v_label) {
    // check if both node labels are valid
    if(find(vertices.begin(),vertices.end(),u_label) == vertices.end()){
        return -1;
    }else if(find(vertices.begin(),vertices.end(),v_label)== vertices.end()){
        return -1;
    }else{
        int idx = find(vertices.begin(),vertices.end(),u_label) - vertices.begin();
        if(edgeList[idx].find(v_label) == edgeList[idx].end()){
            return -1;
        }else{
            return edgeList[idx][v_label];
        }
    }

    // return -1 if any node label is invalid
    return -1; 
}

unordered_set<string> Graph::neighbors(string const &node_label) {
    unordered_set<string> nodeNeighbors;

    // get the specific unordered_map from the nested edgelist vector
    // by looking up the index of the specific node
    auto loc = find(vertices.begin(),vertices.end(),node_label);
    if(loc != vertices.end()){
        int idx = loc - vertices.begin();
        for(auto it = edgeList[idx].begin();it!=edgeList[idx].end();it++){
            nodeNeighbors.insert(it->first);
        }
    }
    // return empty unordered_set if node doesn't exist
    return nodeNeighbors;
}

vector<tuple<string, string, int>>
Graph::shortest_path_weighted(string const &start_label,
                              string const &end_label) {
    stack<tuple<string, string, int>> undirSPW;

    // check if both labels are existed and different
    auto loc_start = find(vertices.begin(),vertices.end(),start_label);
    auto loc_end = find(vertices.begin(),vertices.end(),end_label);

    // implement Dijkstra's Algorithm to find the shortest
    // path with weights

    // get indices of start and end labels
    int idx_start = loc_start - vertices.begin();
    int idx_end = loc_end - vertices.begin();

    // track previous visited nodes with default -1
    vector<int> prev(vertices.size(),-1);
    prev[idx_start] = idx_start;
    prev[idx_end] = idx_end; 

    // maximun distance from start label
    vector<unsigned int> dist (vertices.size(),UINT_MAX);
    // bool vector to track nodes visiting
    vector<bool> done(vertices.size(),false);

    priority_queue<GNode, vector<GNode>,GNodeComp> pq;
    pq.push(make_pair(0,start_label));
    while(!pq.empty()){
        // pop the top node 
        GNode curr = pq.top(); pq.pop();
        // get the index of current label
        int curr_idx = find(vertices.begin(),vertices.end(),
        curr.second) - vertices.begin();

        // check if current node is visited or not
        if(done[curr_idx]==false){
            done[curr_idx] = true; // Mark visited node

            for(auto it = edgeList[curr_idx].begin();
            it!=edgeList[curr_idx].end();it++){
                // calculate the current distance
                unsigned int curr_dist = (unsigned int)(curr.first + it->second);
                // get the index of label of connected node
                int next_idx = find(vertices.begin(),vertices.end(),
                it->first) - vertices.begin();
                // update if current distance is less than
                // the distance of connected node
                if(curr_dist < dist[next_idx]){
                    dist[next_idx] = curr_dist;
                    prev[next_idx] = curr_idx;
                    pq.push(make_pair(curr_dist,it->first));
                }
            }
        }
    }
    // store the path to vector
    int curr_idx = idx_end;
    while(curr_idx != idx_start){
        int prev_idx = prev[curr_idx];
        string curr_label = vertices[curr_idx];
        string prev_label = vertices[prev_idx];
            
        int weight = edgeList[curr_idx].find(prev_label)->second;
        undirSPW.push(make_tuple(prev_label,curr_label,weight));
        curr_idx = prev_idx;
    }
    
    vector<tuple<string,string,int>> SPW;
    while(!undirSPW.empty()){
        SPW.push_back(undirSPW.top());
        undirSPW.pop();
    }
    return SPW;
}

int Graph::smallest_connecting_threshold(string const &start_label,
                                         string const &end_label) {
    // check if both labels are existed and different
    auto loc_start = find(vertices.begin(),vertices.end(),start_label);
    auto loc_end = find(vertices.begin(),vertices.end(),end_label);

    if(loc_start==vertices.end() || loc_end==vertices.end() ||
    loc_start==loc_end){
        return -1;
    }
    // implement Prim's Algorithm
    // get indices of start and end labels
    // int idx_start = loc_start - vertices.begin();
    int idx_end = loc_end - vertices.begin();

    // maximun distance from start label
    // int dist = INT_MAX;
    // index of next node, default 0
    vector<int> parent(vertices.size(),-1);

    // maximun distance from start label
    vector<unsigned int> key (vertices.size(),UINT_MAX);
    // bool vector to track nodes inside MST or not
    vector<bool> in (vertices.size(),false);

    priority_queue<GNode, vector<GNode>,GNodeComp> pq;
    pq.push(make_pair(0,start_label));
    while(!pq.empty()){
        // pop the top node 
        GNode curr = pq.top(); pq.pop();
        // get the index of current label
        int curr_idx = find(vertices.begin(),vertices.end(),
        curr.second) - vertices.begin();

        in[curr_idx] = true; // included node into MST

        for(auto it = edgeList[curr_idx].begin();
            it!=edgeList[curr_idx].end();it++){
            // get current weight
            int next_idx = find(vertices.begin(),vertices.end(),
                it->first) - vertices.begin();

            unsigned int next_weight = (unsigned int)it->second;
            if(in[next_idx] == false && key[next_idx] > next_weight){
                key[next_idx] = next_weight;
                pq.push(make_pair(next_weight,vertices[next_idx]));
                parent[next_idx] = curr_idx;
            }
        }
    }

    int thrsh = 0;
    int curr_idx = idx_end;
    while(curr_idx != -1){
        curr_idx= parent[curr_idx];
        if(curr_idx != -1){
            thrsh++;
        }
    }
    return thrsh;
}

