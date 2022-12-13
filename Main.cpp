#include <iostream>
#include <chrono>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

/*
struct custom_hash {
    //http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html
    static uint64_t split_mix64(uint64_t seed) { seed += 0x9E3779B97F4A7C15; seed = (seed ^ (seed >> 30)) * 0xBF58476D1CE4E5B9; seed = (seed ^ (seed >> 27)) * 0x94D049BB133111EB; return seed ^ (seed >> 31); } size_t operator()(uint64_t seed) const { static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count(); return split_mix64(seed + FIXED_RANDOM); } };
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
    reverse(topological_order.begin(), topological_order.end());
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
            in_degree_node[dependent_node]++;
            dependent_node_size--;
        }
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
