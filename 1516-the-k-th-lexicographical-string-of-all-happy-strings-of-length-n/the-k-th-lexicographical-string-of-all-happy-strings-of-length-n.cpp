#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void backtrack(int n, int k, string current, int& count, string& result) {
       
        if (!result.empty()) return;

      
        if (current.length() == n) {
            count++;
            if (count == k) {
                result = current;
            }
            return;
        }

        
        for (char ch : {'a', 'b', 'c'}) {
           
            if (current.empty() || current.back() != ch) {
                backtrack(n, k, current + ch, count, result);
            }
        }
    }

    string getHappyString(int n, int k) {
        string result = "";
        int count = 0;
        backtrack(n, k, "", count, result);
        return result;
    }
};