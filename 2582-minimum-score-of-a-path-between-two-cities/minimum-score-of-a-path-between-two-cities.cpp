#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    void dfs(int u, vector<vector<pair<int, int>>>& adj, vector<bool>& visited, int& minScore) {
        visited[u] = true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

       
            minScore = min(minScore, weight);

            if (!visited[v]) {
                dfs(v, adj, visited, minScore);
            }
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
 
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            int u = road[0], v = road[1], w = road[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> visited(n + 1, false);
        int minScore = INT_MAX;

   
        dfs(1, adj, visited, minScore);

        return minScore;
    }
};