class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> L(26, -1), R(26, -1);
        
        // Step 1: Find first and last occurrences of each character
        for (int i = 0; i < n; ++i) {
            if (L[s[i] - 'a'] == -1) L[s[i] - 'a'] = i;
            R[s[i] - 'a'] = i;
        }
        
        vector<string> ans;
        int last_end = -1;
        
        // Step 2 & 3: Find valid substrings and pick greedily
        for (int i = 0; i < n; ++i) {
            if (i != L[s[i] - 'a']) continue; // Only process at the start of a character's range
            
            int right = R[s[i] - 'a'];
            bool valid = true;
            
            for (int j = i; j <= right; ++j) {
                if (L[s[j] - 'a'] < i) { // Character's first index was before 'i'
                    valid = false;
                    break;
                }
                right = max(right, R[s[j] - 'a']); // Expand range to include all occurrences
            }
            
            if (valid) {
                // If this valid range is inside the previously added range, replace it
                if (i <= last_end) {
                    ans.back() = s.substr(i, right - i + 1);
                } else {
                    ans.push_back(s.substr(i, right - i + 1));
                }
                last_end = right;
            }
        }
        
        return ans;
    }
};