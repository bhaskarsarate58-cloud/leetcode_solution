class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        long long totalSum = 0;

        // Iterate through all possible divisors k of n
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool possible = true;
            int prev_max = -1;

            for (int i = 0; i < n; i += k) {
                int drops = 0, drop_idx = -1;
                for (int j = 0; j < k; ++j) {
                    if (nums[i + j] > nums[i + (j + 1) % k]) {
                        drops++;
                        drop_idx = i + (j + 1) % k;
                    }
                }

                if (drops > 1) {
                    possible = false;
                    break;
                }

                int curr_min, curr_max;
                if (drops == 0) {
                    curr_min = nums[i];
                    curr_max = nums[i + k - 1];
                } else {
                    // Check if the rotated order is valid
                    bool valid_rotation = true;
                    for (int j = 0; j < k - 1; ++j) {
                        int idx1 = i + (drop_idx - i + j) % k;
                        int idx2 = i + (drop_idx - i + j + 1) % k;
                        if (nums[idx1] > nums[idx2]) {
                            valid_rotation = false;
                            break;
                        }
                    }
                    if (!valid_rotation) {
                        possible = false;
                        break;
                    }
                    curr_min = nums[drop_idx];
                    curr_max = nums[i + (drop_idx - 1 - i + k) % k];
                }

                if (prev_max != -1 && prev_max > curr_min) {
                    possible = false;
                    break;
                }
                prev_max = curr_max;
            }

            if (possible) {
                totalSum += k;
            }
        }

        return totalSum;
    }
};