#include <string>
#include <algorithm>

class Solution {
public:
    int maxProduct(int n) {
        std::string s = std::to_string(n);
        
        
        std::sort(s.begin(), s.end());
        
        int len = s.length();
        
       
        if (len < 2) {
            return (s[0] - '0') * (s[0] - '0');
        }
        
        
        int d1 = s[len - 1] - '0';
        int d2 = s[len - 2] - '0';
        
        return d1 * d2;
    }
};