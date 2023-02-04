#include <iostream>
#include <chrono>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

/*
struct custom_hash {
    static uint64_t split_mix64(uint64_t seed) { seed += 0x9e3779b97f4a7c15; seed = (seed ^ (seed >> 30)) * 0xbf58476d1ce4e5b9; seed = (seed ^ (seed >> 27)) * 0x94d049bb133111eb; return seed ^ (seed >> 31); } size_t operator()(uint64_t seed) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return split_mix64(seed + FIXED_RANDOM); } };
*/

bool kahn_topological_sort(unordered_map < string, vector < string > > &directed_acyclic_graph, unordered_map < string, int > &in_degree_node, vector < string > &topological_order)
{
    queue < string > independent_node_queue;
    for(auto node : directed_acyclic_graph)
        if(!in_degree_node[node.first])
            independent_node_queue.push(node.first);
    while(!independent_node_queue.empty())
    {
        string parent_node = independent_node_queue.front();
        topological_order.push_back(parent_node);
        independent_node_queue.pop();
        for(auto child_node : directed_acyclic_graph[parent_node])
        {
            in_degree_node[child_node]--;
            if(!in_degree_node[child_node])
                independent_node_queue.push(child_node);
        }
    }
    if((int)topological_order.size() != (int)directed_acyclic_graph.size())
        return false;
    return true;
}

int main() 
{
    #ifndef FILE_HANDLER
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int node_size;
    cin >> node_size;
    unordered_map < string, vector < string > > directed_acyclic_graph; 
    unordered_map < string, int > in_degree_node; 
    vector < string > topological_order;
    while(node_size)
    {
        string node;
        cin >> node;
        int dependent_node_size;
        cin >> dependent_node_size;
        directed_acyclic_graph[node];
        while(dependent_node_size){
            string dependent_node;
            cin >> dependent_node;
            directed_acyclic_graph[node].push_back(dependent_node);
            directed_acyclic_graph[dependent_node].push_back(node);
            dependent_node_size--;
        }
        in_degree_node[node] = directed_acyclic_graph[node].size();
        node_size--;
    }
    bool flag = kahn_topological_sort(directed_acyclic_graph, in_degree_node, topological_order);
    if(flag){
        cout << "A ( might have another way ) ordered prerequisite maintainance: ";
        for(int node = 0; node < (int)topological_order.size(); node++)
        {
            cout << topological_order[node];
            if(node != (int)topological_order.size() - 1)
                cout << " -> ";
        }
    }
    else
        cout << "It is impossible to maintain prerequisite";
    return 0;
}
