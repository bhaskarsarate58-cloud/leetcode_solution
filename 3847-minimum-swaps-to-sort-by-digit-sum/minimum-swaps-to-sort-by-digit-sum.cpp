#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    int getDigitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

public:
    int minSwaps(std::vector<int>& nums) {
        int n = nums.size();
        
        // Store elements with their digit sums and original indices
        // Structure: {digit_sum, value, original_index}
        std::vector<std::tuple<int, int, int>> items(n);
        for (int i = 0; i < n; ++i) {
            items[i] = {getDigitSum(nums[i]), nums[i], i};
        }
        
        // Sort according to problem criteria:
        // 1. Increasing order of digit sum
        // 2. If digit sums are equal, smaller number appears first
        std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
            if (std::get<0>(a) != std::get<0>(b)) {
                return std::get<0>(a) < std::get<0>(b);
            }
            if (std::get<1>(a) != std::get<1>(b)) {
                return std::get<1>(a) < std::get<1>(b);
            }
            return std::get<2>(a) < std::get<2>(b);
        });
        
        // Find minimum swaps using cycle decomposition
        std::vector<bool> visited(n, false);
        int swaps = 0;
        
        for (int i = 0; i < n; ++i) {
            // If already visited or already in the correct position
            if (visited[i] || std::get<2>(items[i]) == i) {
                continue;
            }
            
            // Traverse the cycle
            int cycle_size = 0;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                curr = std::get<2>(items[curr]);
                cycle_size++;
            }
            
            if (cycle_size > 1) {
                swaps += (cycle_size - 1);
            }
        }
        
        return swaps;
    }
};