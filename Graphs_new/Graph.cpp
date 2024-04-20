/**
 * TODO: add a file header here.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <queue>
#include <stack>
#include <algorithm> 
#include "Graph.h"

using namespace std;

Graph::Graph(const string &edgelist_csv_fn) {
    // TODO
    num_Edges = 0; // initialize edges counter
    
    ifstream infile(edgelist_csv_fn); // open edge list  
    string currLine; // string to store current line

    int index = 0;
    while(getline(infile, currLine)){
        istringstream istr(currLine);
        string label1, label2, weightStr;
        getline(istr, label1,',');
        getline(istr, label2, ',');
        getline(istr, weightStr, '\n');

        num_Edges++;
        unsigned int weight = (unsigned int) stoi(weightStr);

        if(edgesList.find(label1) == edgesList.end()){
            lbl2idx.insert(make_pair(label1,index));
            vertices.push_back(label1);
            index++;
        }
        edgesList[label1].insert(make_pair(label2,weight));

        if(edgesList.find(label2) == edgesList.end()){
            lbl2idx.insert(make_pair(label2,index));
            vertices.push_back(label2);
            index++;
        }

        edgesList[label2].insert(make_pair(label1,weight));
    }
    infile.close();
}

unsigned int Graph::num_nodes() {
    return vertices.size();
}

unordered_set<string> Graph::nodes() {
    unordered_set<string> Nodes;
    for(string elem :vertices){
        Nodes.insert(elem);
    }
    return Nodes;
}

// Return the number of edges in graph
unsigned int Graph::num_edges() {
    return num_Edges;
}

// Return the number of neighbors of a specific node
unsigned int Graph::num_neighbors(string const &node_label) {
    // Return 0 if the node doesn't exist
    if(edgesList.find(node_label) == edgesList.end()){
        return 0;
    }
    return edgesList[node_label].size();
}

// Return the weight between two specific nodes
int Graph::edge_weight(string const &u_label, string const &v_label) {
    // Return -1 if any node doesn't exist in graph
    if(edgesList.find(u_label) == edgesList.end() ||
    edgesList.find(v_label) == edgesList.end()){
        return -1;
    }

    // Return -1 if two nodes are not connected
    if(edgesList[u_label].find(v_label) == edgesList[u_label].end()){
        return -1;
    }

    // Return -1 for self-edging case
    if(u_label == v_label){
        return -1;
    }
    
    // Return weight between two nodes if they are valid
    return edgesList[u_label][v_label];
}

// Return an unordered set contained labels of neighbors around a
// specific node; return empty set if the node doesn't exist.
unordered_set<string> Graph::neighbors(string const &node_label) {
    unordered_set<string> node_neighbors;
    
    // Check if the node exists or not.
    if(edgesList.find(node_label) != edgesList.end()){
        // Insert labels or all neighbor nodes by loop.
        for(auto it = edgesList[node_label].begin(); 
        it != edgesList[node_label].end();
        it++){
            node_neighbors.insert(it->first);
        }
    }

    return node_neighbors;
}

vector<tuple<string, string, int>>
Graph::shortest_path_weighted(string const &start_label,
                              string const &end_label) {
    // Vector for storing path
    vector<tuple<string, string, int>> SPW;

    // return empty vector for self-edging case
    if(start_label==end_label)return SPW;

    // Check if start and end nodes exist in graph.
    // Otherwise, return an empty vector
    if(edgesList.find(start_label) == edgesList.end() ||
    edgesList.find(end_label) == edgesList.end()) return SPW;
    
    // Vector for tracking nodes visiting.
    vector<bool> done(vertices.size(),false);

    // Vector for storing previous nodes.
    vector<int> prevs(vertices.size(),-1);

    // Vector for tracking the maximun distance 
    // from start node.
    vector<unsigned int> dist(vertices.size(),UINT_MAX);

    // Prioty queue for Dijkstra's algorithm implementation 
    priority_queue<Gnode, vector<Gnode>,GnodeComp> pq;

    pq.push(make_pair(0,start_label));

    while(!pq.empty()){
        // Pop the top Gnode in the queue
        Gnode curr = pq.top(); pq.pop();
        int curr_idx = lbl2idx[curr.second];

        if(!done[curr_idx]){
            // Mark current node to done 
            done[curr_idx] = true;

            for(auto it = edgesList[curr.second].begin();
            it != edgesList[curr.second].end(); it++){
                int node_idx = lbl2idx[it->first];
                // Calculate the current distance from start node
                unsigned int curr_dist = curr.first + it->second;

                if(curr_dist < dist[node_idx]){
                    dist[node_idx] = curr_dist;
                    prevs[node_idx] = curr_idx;
                    pq.push(make_pair(curr_dist,it->first));
                }
            }
        }
    }

    // Store the shortest weighted path by 
    // searching "prevs" vector from the end node
    int curr_idx = lbl2idx[end_label];

    // Using stack to store path first, then 
    // transfer to vector
    stack<tuple<string,string,int>> SPW_rev;

    while(curr_idx != lbl2idx[start_label]){
        // Obtain index of previous node
        int prev_idx = prevs[curr_idx];

        // break if previous node and current node
        // are not connected in a graph, i.e., there
        // are more than one graph in the file.
        if(prev_idx == -1){
            return SPW;
        }
        // Obtain labels of current and previous nodes
        string prev_label = vertices[prev_idx];
        string curr_label = vertices[curr_idx];

        SPW_rev.push(make_tuple(prev_label,
            curr_label,
            edgesList[curr_label][prev_label]));
        // Update current index
        curr_idx = prev_idx;
    }

    // Transfer from stack to vector
    while(!SPW_rev.empty()){
        SPW.push_back(SPW_rev.top()); SPW_rev.pop();
    }

    return SPW;
}

int Graph::smallest_connecting_threshold(string const &start_label,
                                         string const &end_label) {
    
    // Check if start and end nodes exist in graph. 
    // And check if it is not a self-edging case.
    // Otherwise, return -1.
    if(edgesList.find(start_label) == edgesList.end() ||
    edgesList.find(end_label) == edgesList.end()) return -1;

    if(start_label == end_label) return 0;
    
    // Vector for tracking nodes visiting.
    vector<bool> done(vertices.size(),false);

    // Vector for storing previous nodes.
    vector<int> path(vertices.size(),-1);

    vector<int> thrs_all;

    int start_idx = lbl2idx[start_label];
    int end_idx = lbl2idx[end_label];
    int path_index = 0;
    int thrsh = 0;

    smt_recur(start_idx, end_idx, done, path, path_index, thrsh, thrs_all);
    sort(thrs_all.begin(),thrs_all.end());
    return thrs_all.front();
}

void Graph::smt_recur(int & u, int & v, vector<bool> & done, 
    vector<int> & path, int & path_index, int & thrsh, vector<int> & thrs_all){

    done[u] = true;
    path[path_index] = u;
    path_index++;

    if(u != v){
        // Recur for all the vertices adjacent to current vertex
        string u_label = vertices[u];
        for(auto it = edgesList[u_label].begin(); 
            it!=edgesList[u_label].end();it++){
            
            int node_idx = lbl2idx[it->first];
            if(!done[node_idx]){
                int weight = edgesList[u_label][it->first];
                if( weight > thrsh){
                    thrsh = weight;
                }
                smt_recur(node_idx,v,done,path,path_index,thrsh,thrs_all);
            }
        }
        if(thrs_all.empty()){
            thrs_all.push_back(-1);       
        }
    }else{
        thrs_all.push_back(thrsh);
        thrsh = 0;
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    done[u] = false;
}
