#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    const int MAX_K = 1e6 + 1;

    
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n - r) r = n - r;
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - i + 1) / i;
            if (res >= MAX_K) return MAX_K;
        }
        return res;
    }

   
    long long countArrangements(const vector<int>& count) {
        int total = 0;
        for (int c : count) total += c;
        
        long long res = 1;
        for (int freq : count) {
            res *= nCr(total, freq);
            if (res >= MAX_K) return MAX_K;
            total -= freq;
        }
        return res;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> halfCount(26, 0);
        string midChar = "";

        for (int i = 0; i < 26; ++i) {
            halfCount[i] = freq[i] / 2;
            if (freq[i] % 2 != 0) {
                midChar = string(1, (char)('a' + i));
            }
        }

        
        long long totalPermutations = countArrangements(halfCount);
        if (k > totalPermutations) return "";

        int halfLen = s.length() / 2;
        string leftHalf = "";

        
        for (int pos = 0; pos < halfLen; ++pos) {
            for (int i = 0; i < 26; ++i) {
                if (halfCount[i] == 0) continue;

                halfCount[i]--; 
                long long arrangements = countArrangements(halfCount);

                if (arrangements >= k) {
                    leftHalf += (char)('a' + i);
                    break; 
                } else {
                    k -= arrangements;
                    halfCount[i]++; 
                }
            }
        }

        string rightHalf = leftHalf;
        reverse(rightHalf.begin(), rightHalf.end());

        return leftHalf + midChar + rightHalf;
    }
};