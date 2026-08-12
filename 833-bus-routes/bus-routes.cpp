class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
     if(source == target) return 0;
     unordered_map<int, vector<int>> stoptobuses;
     for(int bus = 0;bus <routes.size(); ++bus){
        for(int stop : routes[bus]){
            stoptobuses[stop].push_back(bus);
        }
     }   
     queue<int> q;
     unordered_set<int> visitedstop;
     vector<bool> visitedbuses(routes.size(),false);
     q.push(source);
     visitedstop.insert(source);
     int buscount = 0;
     while(!q.empty()){
        int size = q.size();
        buscount++;
        for(int i =0;i<size;i++){
         int currstop = q.front();
         q.pop();
         for(int bus : stoptobuses[currstop]){
            if(visitedbuses[bus]) continue;
            visitedbuses[bus] = true;
            for(int nextstop : routes[bus]){
                if(nextstop == target) return buscount;
                if(!visitedstop.count(nextstop)){
                    visitedstop.insert(nextstop);
                    q.push(nextstop);
                }
            }
         }   
        }
     }
     return -1;
    }
};