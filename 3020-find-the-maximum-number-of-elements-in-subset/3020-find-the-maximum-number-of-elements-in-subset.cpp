#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> counts;
        for (int num : nums) {
            counts[num]++;
        }

        int maxLen = 1;

        // Handle the special case for 1
        if (counts.count(1)) {
            int ones = counts[1];
            if (ones % 2 == 0) ones--;
            maxLen = max(maxLen, ones);
        }

        // Handle cases for x > 1
        for (auto const& [val, count] : counts) {
            if (val == 1) continue;

            long long curr = val;
            int currentLen = 0;

            // Continue while we have at least 2 of the current number
            while (counts.count(curr) && counts[curr] >= 2) {
                currentLen += 2;
                curr *= curr;
            }

            // Include the peak element (appears at least once)
            if (counts.count(curr)) {
                currentLen += 1;
            } else {
                // If the peak isn't there, we backtrack
                currentLen -= 1;
            }

            maxLen = max(maxLen, currentLen);
        }

        return maxLen;
    }
};