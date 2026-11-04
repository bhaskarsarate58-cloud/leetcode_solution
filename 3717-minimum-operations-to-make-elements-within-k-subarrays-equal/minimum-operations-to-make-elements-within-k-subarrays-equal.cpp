
class Solution {
public:

    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        // Two multisets to maintain the sliding window median.
        multiset<int> low, high;

        long long sumLow = 0;
        long long sumHigh = 0;

        // Balance the two multisets.
        auto balance = [&]() {

            while (low.size() > high.size() + 1) {

                int val = *low.rbegin();

                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while (low.size() < high.size()) {

                int val = *high.begin();

                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        // Insert an element into the window.
        auto add = [&](int val) {

            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            }
            else {
                high.insert(val);
                sumHigh += val;
            }

            balance();
        };

        // Remove an element from the window.
        auto remove = [&](int val) {

            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            }
            else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            balance();
        };

        // Calculate the minimum equalization cost.
        auto getCost = [&]() -> long long {

            long long median = *low.rbegin();

            return median * (long long)low.size() - sumLow
                 + sumHigh - median * (long long)high.size();
        };

        // cost[i] = cost of the window ending at prefix index i.
        vector<long long> cost(n + 1, 0);

        // Generate the cost of every window of size x.
        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i + 1] = getCost();
            }
        }

        // Dynamic Programming.
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        // Selecting zero subarrays costs zero.
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        // Choose exactly j non-overlapping subarrays.
        for (int j = 1; j <= k; j++) {

            for (int i = 1; i <= n; i++) {

                // Option 1: Skip the current element.
                dp[j][i] = dp[j][i - 1];

                // Option 2: Select a window ending at i-1.
                if (i >= x && dp[j - 1][i - x] != INF) {

                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
