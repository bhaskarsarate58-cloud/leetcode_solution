class Solution {
public:
    int countCommas(int n) {
        int ans;
     if(n<1000)return 0;
     else{
        ans = n-1000 +1;
     }
     return ans;   
    }
};