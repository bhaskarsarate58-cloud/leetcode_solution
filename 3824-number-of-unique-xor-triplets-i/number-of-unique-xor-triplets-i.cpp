class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
      int n =nums.size();
        int ans;
      if(n>=3){
        int msb = log2(n);
        ans = pow(2,msb+1);
       
      }else{
        ans = n;
      } 
       return  ans;
    }
};