class Solution {
public:
    int minMoves(vector<int>& nums) {
    int mx = *max_element(nums.begin(),nums.end());
    int ans =0;
    for(int i : nums){
    ans += mx - i;
    }  
    return ans;
    }
};