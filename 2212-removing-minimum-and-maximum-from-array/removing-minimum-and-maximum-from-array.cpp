class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n; 
        
        int mini = 0;
        int maxi = 0;
        
        
        for(int i = 1; i < n; ++i) {
            if(nums[i] < nums[mini]) {
                mini = i;
            }
            if(nums[i] > nums[maxi]) {
                maxi = i;
            }
        }
        
        
        int pt1 = min(mini, maxi);
        int pt2 = max(mini, maxi);
        
        
        int both_from_front = pt2 + 1;
        int both_from_back = n - pt1;
        int front_and_back = (pt1 + 1) + (n - pt2);
        
        
        return min({both_from_front, both_from_back, front_and_back});
    }
};