
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        // Build adjacency list
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
        }

        // dist[node][cnt]
        const int INF = 1e9;

        vector<vector<int>> dist(n, vector<int>(k + 1, INF));

        // {distance, node, consecutive count}
        priority_queue<
            tuple<int,int,int>,
            vector<tuple<int,int,int>>,
            greater<tuple<int,int,int>>
        > pq;

        // Starting node has one occurrence of its label
        dist[0][1] = 0;

        pq.push({0, 0, 1});

        while (!pq.empty()) {

            auto [d, u, cnt] = pq.top();
            pq.pop();

            // Ignore outdated states
            if (d != dist[u][cnt])
                continue;

            // Explore outgoing edges
            for (auto [v, w] : adj[u]) {

                int newCnt;

                if (labels[u] == labels[v]) {
                    newCnt = cnt + 1;
                }
                else {
                    newCnt = 1;
                }

                // Constraint violated
                if (newCnt > k)
                    continue;

                int newDist = d + w;

                if (newDist < dist[v][newCnt]) {

                    dist[v][newCnt] = newDist;

                    pq.push({newDist, v, newCnt});
                }
            }
        }

        // Minimum distance to destination
        int ans = INF;

        for (int cnt = 1; cnt <= k; cnt++) {
            ans = min(ans, dist[n - 1][cnt]);
        }

        return ans == INF ? -1 : ans;
    }
};
