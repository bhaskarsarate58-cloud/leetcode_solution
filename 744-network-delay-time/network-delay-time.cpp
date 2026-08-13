class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> adj(n+1);
    for(const auto& edge : times){
       int u= edge[0];
       int v= edge[1];
       int w= edge[2];
        adj[u].push_back({v,w});
    }
    vector<int> dist(n+1,INT_MAX);
    dist[k]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,k});
    while(!pq.empty()){
        auto[d,u] = pq.top();
        pq.pop();
        if(d > dist[u]){
            continue;
        }
        for(const auto& neighbor: adj[u]){
            int v = neighbor.first;
            int weight = neighbor.second;
            if(dist[u]+weight < dist[v]){
                dist[v] = dist[u]+weight;
                pq.push({dist[v],v});
            }
        }
    }
    int max_time = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1; 
            max_time = max(max_time, dist[i]);
        }

        return max_time;

    }
};