class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n =nums.size();
        vector<int> nums2 = nums;
        sort(nums2.begin(),nums2.end());
        vector<int> nums3 = nums2;
        reverse(nums3.begin(),nums3.end());
        int k=0;
        if(nums == nums3){
            return k;
        }
        
        vector<int> list;
        for(int i=0;i<n;i++){
            if(nums2[i] != nums[i]){
               list.push_back(nums[i]);  
            }
        }
        if(list.empty()) return 0;
        k = list[0];
        for(int i = 1;i<list.size();i++){
            k = k & list[i]; 
        }
        return k;
        
    }
};