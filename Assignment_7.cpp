
#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
    int v;
    vector<vector<int> > adj;
    Graph(int v){
        this-> v=  v;
        adj.assign(v, vector<int> (v,0));
    }
    void addedge(int u,int v, int wt){
        adj[u][v] = wt;
        adj[v][u]  = wt;

    }
    int minkey(vector<int>& key, vector<bool>& mstset){
        int min = INT_MAX, minind =-1;
        for(int i =0; i < v; i++){
            if(!mstset[i] && key[i] < min){
                min = key[i];
                minind = i;

            }

        }
        return minind;

    }

    void mst(){
        vector<int> parent(v,-1),  key(v,INT_MAX);
        vector<bool> mstset(v,false);
        key[0] = 0;
        for(int i = 0 ; i < v-1; i++){
            int u = minkey(key,  mstset);

            mstset[u] = true;
            for(int j =0; j < v ;j++  ){
                    if(adj[u][j] && !mstset[j] && adj[u][j] < key[j]){
                        parent[j] = u;
                        key[j] = adj[u][j];

                    }
            }
        }

        int cost = 0;
        for(int i = 1; i< v; i++){
            cout<< parent[i] << "wt" << adj[parent[i]][i];
            cost+= adj[i][parent[i]];
        }
        cout<<cost<<endl;
    }

};
int main(){
    int v,e;
    cin>>v>>e;
    Graph g(v);

    for(int i =0;i < e; i++){
        int u,v,w;
        cin>>u>>v>>w;
        g.addedge(u,v,w);
    }
    g.mst();
}