class Solution {
public:
    void dfs(int u,vector<vector<int>>& adj, vector<bool>& suspicious){
        suspicious[u] = true;
        for(int v: adj[u]){
            if(!suspicious[v])
            dfs(v,adj,suspicious);
        }
    }
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
      vector<vector<int>> adj(n);
      for(const auto& inv : invocations){
        adj[inv[0]].push_back(inv[1]);
      }  
      vector<bool> suspicious(n,false);
      dfs(k,adj,suspicious);

      for(const auto& inv:invocations){
        int u =inv[0];
        int v =inv[1];
        if(!suspicious[u] && suspicious[v]){
            vector<int> all(n);
            for(int i =0;i<n;i++){
                all[i]=i;
            }
            return all;
        }
      }
    vector<int> result;
    for(int i=0;i<n;i++){
        if(!suspicious[i]){
            result.push_back(i);
        }
    }
    return result;

    }
};