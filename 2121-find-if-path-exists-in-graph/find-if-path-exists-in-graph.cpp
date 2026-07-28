class Solution {
    private:
    bool dfs(int u,int destination,vector<vector<int>>& adj,vector<bool>& visit){
        if(u == destination) return true;
        visit[u]=true;
        for(int nej : adj[u]){
            if(!visit[nej]){
                if(dfs(nej,destination,adj,visit))
                return true;
            }
        }
        return false;


    }


public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        if(source == destination) return true;
      vector<vector<int>> adj(n);
      for( const auto& e : edges){
        int u = e[0];
        int v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
      }  
      vector<bool> visit(n,false);
       return dfs(source,destination,adj,visit);
    }
};