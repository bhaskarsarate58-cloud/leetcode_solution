class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
    sort(nums1.begin(),nums1.end());
    int n =nums1.size();
    // nums2[0] = nums1[0];
    int bit = nums1[0];
    for(int i =1;i<n;i++){
        if(nums1[i]%2 == bit){
            continue;
        }
        else{
            int j =0;
            for(int j=0;j<n;j++){
                if(nums1[i]==nums1[j]){continue;}
                if((nums1[i] - nums1[j])%2 != bit){break;}
            }
            if(j==n-1){return false;}
        }
    }return true;   
    }
};