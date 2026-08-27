#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Try to match target up to prefix of length i (0 <= i < n)
        // and make index i strictly larger than target[i].
        for (int i = n - 1; i >= 0; i--) {
            // Check if target[0 ... i-1] can be matched
            vector<int> temp_freq = freq;
            bool can_match_prefix = true;
            for (int j = 0; j < i; j++) {
                int char_idx = target[j] - 'a';
                if (temp_freq[char_idx] <= 0) {
                    can_match_prefix = false;
                    break;
                }
                temp_freq[char_idx]--;
            }

            if (!can_match_prefix) continue;

            // Try to find a character strictly greater than target[i]
            for (int c = target[i] - 'a' + 1; c < 26; c++) {
                if (temp_freq[c] > 0) {
                    // Valid prefix found! Build the result.
                    string res = target.substr(0, i);
                    res += (char)('a' + c);
                    temp_freq[c]--;

                    // Fill the rest with smallest available characters
                    for (int k = 0; k < 26; k++) {
                        while (temp_freq[k] > 0) {
                            res += (char)('a' + k);
                            temp_freq[k]--;
                        }
                    }
                    return res;
                }
            }
        }

        return "";
    }
};