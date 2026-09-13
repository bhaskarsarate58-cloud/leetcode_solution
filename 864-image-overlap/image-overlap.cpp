class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
    int n = img1.size();
    vector<pair<int,int>> v1,v2;
    for(int i =0;i<n;i++){
        for(int j =0;j<n;j++){
            if(img1[i][j] == 1) v1.push_back({i,j});
            if(img2[i][j] == 1) v2.push_back({i,j});
        }
    }     
    map<pair<int,int>,int> count;
    int max_overlap =0;
    for(auto& p1 :v1){
        for(auto& p2 :v2){
            pair<int,int> offset = {p1.first - p2.first,p1.second - p2.second};
            count[offset]++;
            max_overlap = max(max_overlap,count[offset]);
        }
    }
    return max_overlap;

    }
};