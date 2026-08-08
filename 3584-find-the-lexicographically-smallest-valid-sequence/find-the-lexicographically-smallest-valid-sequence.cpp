#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();
        
        // last_pos[j] stores the maximum index in word1 to match word2[j...m-1] exactly
        std::vector<int> last_pos(m, -1);
        int p = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }
            last_pos[j] = p;
            if (p >= 0) {
                p--;
            }
        }
        
        std::vector<int> res;
        bool changed = false;
        int i = 0;
        
        // Greedily match characters of word2
        for (int j = 0; j < m; ++j) {
            while (i < n) {
                if (word1[i] == word2[j]) {
                    // Match character without change
                    if (changed) {
                        if (j == m - 1 || last_pos[j + 1] > i) {
                            res.push_back(i);
                            i++;
                            break;
                        }
                    } else {
                        res.push_back(i);
                        i++;
                        break;
                    }
                } else {
                    // Try using the 1 allowed character change here
                    if (!changed && (j == m - 1 || last_pos[j + 1] > i)) {
                        res.push_back(i);
                        changed = true;
                        i++;
                        break;
                    }
                }
                i++; // Advance pointer in word1 if current index cannot be used
            }
        }
        
        if (res.size() == m) {
            return res;
        }
        return {};
    }
};