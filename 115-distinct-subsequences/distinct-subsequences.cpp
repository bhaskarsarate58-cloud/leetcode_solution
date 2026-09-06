class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        
        // dp[j] stores the number of distinct subsequences of s that equal t[0...j-1]
        // Using unsigned long long to handle intermediate integer overflow before final fit in 32-bit int
        vector<unsigned long long> dp(n + 1, 0);
        
        // Base case: empty string t can always be formed in 1 way
        dp[0] = 1;
        
        for (int i = 1; i <= m; ++i) {
            // Traverse backwards to avoid overwriting values needed for the current iteration
            for (int j = n; j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        return dp[n];
    }
};