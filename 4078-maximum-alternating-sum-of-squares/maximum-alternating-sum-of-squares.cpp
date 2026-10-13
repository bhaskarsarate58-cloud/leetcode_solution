class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
     int n =nums.size();
     vector<int> square;
     for(int i=0;i<n;i++){
        square.push_back(abs(nums[i]));
     }
     sort(square.begin(),square.end()); 
     long long ans=0;  
     for(int i=0;i<n;i++){
        if(i < (n)/2 ){
            ans-=square[i]*square[i];
        }else{
             ans+=square[i]*square[i];
        }
     }
     return ans;
    }
};