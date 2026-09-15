class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        int count = 0;
        int last_end = -1;

        for (int i = 0; i < n; ++i) {
            // Check if a palindrome of length k or k + 1 ends at index i
            for (int len : {k, k + 1}) {
                int left = i - len + 1;
                
                // Ensure left boundary is valid and past the last selected palindrome
                if (left > last_end && isPalindrome(s, left, i)) {
                    count++;
                    last_end = i;
                    break; // Greedily end at the earliest possible index
                }
            }
        }

        return count;
    }

private:
    bool isPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }
};