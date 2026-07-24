#include <vector>
#include <algorithm>
#include <bitset>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        
        std::vector<int> S = nums;
        std::sort(S.begin(), S.end());
        S.erase(std::unique(S.begin(), S.end()), S.end());

        int n = S.size();

       
        std::bitset<2048> pair_xor;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                pair_xor.set(S[i] ^ S[j]);
            }
        }

        
        std::vector<int> P;
        for (int x = 0; x < 2048; ++x) {
            if (pair_xor[x]) {
                P.push_back(x);
            }
        }

       
        std::bitset<2048> triplet_xor;
        for (int p : P) {
            for (int c : S) {
                triplet_xor.set(p ^ c);
            }
        }

        
        return triplet_xor.count();
    }
};