class Solution {
private:
    void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited, int& vertexCount, int& edgeCount) {
        visited[node] = true;
        vertexCount++;
        edgeCount += adj[node].size(); 
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, vertexCount, edgeCount);
            }
        }
    }

public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int completeComponents = 0;
        
        
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int vertexCount = 0;
                int edgeCount = 0;
                
                
                dfs(i, adj, visited, vertexCount, edgeCount);
                
                
                int uniqueEdges = edgeCount / 2;
                
                
                if (uniqueEdges == (vertexCount * (vertexCount - 1)) / 2) {
                    completeComponents++;
                }
            }
        }
        
        return completeComponents;
    }
};