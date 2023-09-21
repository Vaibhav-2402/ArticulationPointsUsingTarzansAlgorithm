
#include <iostream>
#include<unordered_map>
#include<vector>
#include<list>

using namespace std;

void dfs(int node, int parent, vector<int> &disc, vector<int> &low, unordered_map<int, bool> &vis, unordered_map<int, list<int> > &adj, vector<int> &ap, int timer) {
    vis[node] = true;
    disc[node] = low[node] = timer++;
    
    int child = 0;
    
    for(auto nbr : adj[node]) {
        if(nbr == parent) {
            continue;
        }
        else if(!vis[nbr]) {
            dfs(nbr, node, disc, low, vis, adj, ap, timer);
            
            low[node] = min(low[node], low[nbr]);
            
            if(low[nbr] >= disc[node] && parent != -1) {
                ap[node] = 1;
            }
            child++;
        }
        else {
            low[node] = min(low[node], disc[nbr]);
        }
    }
    
    if(parent == -1 && child > 1) {
        ap[node] = 1;
    }
}

int main() {
    
    int n = 5;
    int e = 5;
    
    vector<pair<int, int> > edges;
    
    edges.push_back({0,3});
    edges.push_back({0,4});
    edges.push_back({3,4});
    edges.push_back({0,1});
    edges.push_back({1,2});
    
    unordered_map<int, list<int> > adj;
    
    for(int i = 0; i < e; i++) {
        int u = edges[i].first;
        int v = edges[i].second;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    int parent = -1;
    
    unordered_map<int, bool> vis;
    
    int timer = 0;
    
    //creating vector for articulation points
    
    vector<int> ap(n, 0);
    
    //DFS call
    
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
        dfs(i, parent, disc, low, vis, adj, ap, timer);
    }
    }
    
    cout << " the Articulation points in the graph are : " << endl;
    
    for(int i = 0; i < n; i++) {
        if(ap[i] != 0) {
            cout << i << "  ";
        } 
    }cout << endl;
    
    return 0;
}