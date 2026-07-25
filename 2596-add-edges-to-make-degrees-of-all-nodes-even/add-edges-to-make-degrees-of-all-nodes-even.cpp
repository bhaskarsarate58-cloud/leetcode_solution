#include <vector>
#include <unordered_set>

class Solution {
public:
    bool isPossible(int n, std::vector<std::vector<int>>& edges) {
        std::vector<int> degree(n + 1, 0);
        
        
        std::vector<std::unordered_set<int>> adj(n + 1);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            degree[u]++;
            degree[v]++;
            adj[u].insert(v);
            adj[v].insert(u);
        }

       
        std::vector<int> odd;
        for (int i = 1; i <= n; ++i) {
            if (degree[i] % 2 != 0) {
                odd.push_back(i);
            }
        }

       
        auto hasEdge = [&](int u, int v) {
            return adj[u].count(v) > 0;
        };

        
        if (odd.empty()) return true;
        if (odd.size() != 2 && odd.size() != 4) return false;

        
        if (odd.size() == 2) {
            int a = odd[0], b = odd[1];

            
            if (!hasEdge(a, b)) return true;

            
            for (int i = 1; i <= n; ++i) {
                if (i != a && i != b && !hasEdge(a, i) && !hasEdge(b, i)) {
                    return true;
                }
            }
            return false;
        }

       
        if (odd.size() == 4) {
            int a = odd[0], b = odd[1], c = odd[2], d = odd[3];

            if (!hasEdge(a, b) && !hasEdge(c, d)) return true;
            if (!hasEdge(a, c) && !hasEdge(b, d)) return true;
            if (!hasEdge(a, d) && !hasEdge(b, c)) return true;
        }

        return false;
    }
};