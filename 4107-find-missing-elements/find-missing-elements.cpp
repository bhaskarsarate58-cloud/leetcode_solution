class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int s = nums[0];
        int l = nums.back();
        int current =s;
      vector<int> ans;
      for(int i =0;i<nums.size();i++){
        if(s!=nums[i]){
            while(s!=nums[i]){
                ans.push_back(s);
                s++;
            }
        }
        s++;
      }
      return ans;
    }
};