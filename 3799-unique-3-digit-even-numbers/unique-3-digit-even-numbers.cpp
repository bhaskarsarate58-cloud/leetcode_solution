#include <vector>
#include <unordered_map>

class Solution {
public:
    int totalNumbers(std::vector<int>& digits) {
        std::unordered_map<int, int> count;
        for (int d : digits) {
            count[d]++;
        }

        int validCount = 0;
        for (int num = 100; num <= 998; num += 2) {
            int d1 = num / 100;        
            int d2 = (num / 10) % 10;  
            int d3 = num % 10;         

            std::unordered_map<int, int> tempCount;
            tempCount[d1]++;
            tempCount[d2]++;
            tempCount[d3]++;
            if (tempCount[d1] <= count[d1] &&
                tempCount[d2] <= count[d2] &&
                tempCount[d3] <= count[d3]) {
                validCount++;
            }
        }

        return validCount;
    }
};