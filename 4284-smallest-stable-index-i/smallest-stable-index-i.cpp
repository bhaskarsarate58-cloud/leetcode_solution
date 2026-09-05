class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
    long long n =nums.size();
    for(int i =0;i<n;i++){
        int maxint = INT_MIN;
        for(int j =0;j<=i;j++){
            maxint = max(maxint,nums[j]);
        }
        int minint = INT_MAX;
        for(int j =i;j<n;j++){
            minint = min(minint,nums[j]);
        }
        if(maxint-minint <=k){
            return i;
            }
    } return -1;
    }
};