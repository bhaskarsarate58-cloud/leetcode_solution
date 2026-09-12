#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
    struct Interval {
        int l, r, weight, id;
    };

    struct Result {
        long long weight = 0;
        vector<int> indices;

        bool operator<(const Result& other) const {
            if (weight != other.weight) {
                return weight < other.weight; // higher weight is better
            }
            // If weights are equal, lexicographically smaller index list is better
            return indices > other.indices; 
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> sorted_intervals(n);
        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        // Sort intervals by start time l
        sort(sorted_intervals.begin(), sorted_intervals.end(), [](const Interval& a, const Interval& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.r < b.r;
        });

        // Binary search helper: find first interval starting after r
        vector<int> start_times(n);
        for (int i = 0; i < n; ++i) {
            start_times[i] = sorted_intervals[i].l;
        }

        // DP state: memo[i][count]
        vector<vector<Result>> dp(n + 1, vector<Result>(5));

        for (int i = n - 1; i >= 0; --i) {
            // Find next non-overlapping interval index using binary search
            int next_idx = upper_bound(start_times.begin() + i + 1, start_times.end(), sorted_intervals[i].r) - start_times.begin();

            for (int count = 4; count >= 0; --count) {
                // Option 1: Skip current interval
                Result best = dp[i + 1][count];

                // Option 2: Take current interval (if count < 4)
                if (count < 4) {
                    Result take = dp[next_idx][count + 1];
                    take.weight += sorted_intervals[i].weight;
                    take.indices.push_back(sorted_intervals[i].id);
                    // Sort indices in ascending order for lexicographical evaluation
                    sort(take.indices.begin(), take.indices.end());

                    if (best < take) {
                        best = take;
                    }
                }

                dp[i][count] = best;
            }
        }

        return dp[0][0].indices;
    }
};