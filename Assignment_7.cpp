#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    void mst(vector<vector<int>> adj[], int v) {
        // Min-heap: {weight, {current_node, parent_node}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

        vector<int> vis(v, 0);
        vector<int> parent(v, -1);
        int sum = 0;

        pq.push({0, {0, -1}});  // start from node 0 with weight 0 and no parent

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int wt = top.first;
            int node = top.second.first;
            int par = top.second.second;

            if (vis[node]) continue;

            vis[node] = 1;
            sum += wt;
            parent[node] = par;

            for (auto& it : adj[node]) {
                int adjnode = it[0];
                int adjwt = it[1];
                if (!vis[adjnode]) {
                    pq.push({adjwt, {adjnode, node}});
                }
            }
        }

        cout << "Edges in MST:\n";
        for (int i = 0; i < v; i++) {
            if (parent[i] != -1)
                cout << parent[i] << " - " << i << endl;
        }
        cout << "Total weight of MST: " << sum << endl;
    }
};

int main() {
    int v, e;
    cin >> v >> e;
    vector<vector<int>> adj[v];

    for (int i = 0; i < e; i++) {
        int u, vv, w;
        cin >> u >> vv >> w;

        adj[u].push_back({vv, w});
        adj[vv].push_back({u, w});  // undirected graph
    }

    Graph g;
    g.mst(adj, v);

    return 0;
}
