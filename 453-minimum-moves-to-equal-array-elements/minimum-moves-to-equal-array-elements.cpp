
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int min_value = *min_element(nums.begin(), nums.end());

        int moves = 0;

        for (int x : nums) {
            moves += x - min_value;
        }

        return moves;
    }
};
