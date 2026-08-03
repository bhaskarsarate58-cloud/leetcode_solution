#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        std::vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            int take = 0;
            dp[i] = INT_MIN;

            for (int k = 0; k < 3 && i + k < n; ++k) {
                take += stoneValue[i + k];
                dp[i] = std::max(dp[i], take - dp[i + k + 1]);
            }
        }

        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};