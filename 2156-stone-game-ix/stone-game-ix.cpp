#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> cnt(3, 0);
        for (int stone : stones) {
            cnt[stone % 3]++;
        }

        // If c0 is even, Alice wins if both c1 and c2 have at least 1 stone
        if (cnt[0] % 2 == 0) {
            return cnt[1] >= 1 && cnt[2] >= 1;
        } 
        // If c0 is odd, Alice wins if absolute difference between c1 and c2 is > 2
        else {
            return abs(cnt[1] - cnt[2]) > 2;
        }
    }
};