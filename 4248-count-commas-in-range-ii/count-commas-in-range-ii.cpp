class Solution {
public:
    long long countCommas(long long n) {
    long long ans = 0;
    //  if(n<1000)return 0;
    //  else{
    //     ans = n-1000 +1;
    //  }

    //  return ans;
    long long size = 1000;
   
    long long anspast =0;
    while(1){
        if(size<=n){
            ans = n-size +1 + anspast;
            anspast =ans;
            size*=1000;
        }
        else{
            return ans;
        }
    } 
        
    }
};