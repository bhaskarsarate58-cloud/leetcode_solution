class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        bool allZero = true;

        for (int num : nums) {
            totalXor ^= num;
            if (num != 0) {
                allZero = false;
            }
        }

        if (allZero) return 0;
        if (totalXor != 0) return nums.size();
        return nums.size() - 1;
    }
};