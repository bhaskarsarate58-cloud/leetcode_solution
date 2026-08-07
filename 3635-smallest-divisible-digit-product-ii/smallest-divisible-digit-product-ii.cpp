#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
    long long gcd(long long a, long long b) {
        return std::gcd(a, b);
    }

    // Returns minimum length of non-zero digits needed to form factor t
    // Returns -1 if t cannot be formed using digits 1-9.
    int minDigitsNeeded(long long t) {
        int count = 0;
        for (int d = 9; d >= 2; --d) {
            while (t % d == 0) {
                t /= d;
                count++;
            }
        }
        return (t == 1) ? count : -1;
    }

    // Construct the smallest sequence of 'len' digits whose product is divisible by t
    string fillSmallest(int len, long long t) {
        string res = "";
        for (int d = 9; d >= 2; --d) {
            while (t % d == 0) {
                res += to_string(d);
                t /= d;
            }
        }
        while ((int)res.length() < len) {
            res += '1';
        }
        sort(res.begin(), res.end());
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        // Step 1: Check if t can be factored into single digits
        long long temp_t = t;
        for (int p : {2, 3, 5, 7}) {
            while (temp_t % p == 0) temp_t /= p;
        }
        if (temp_t > 1) return "-1";

        int n = num.length();

        // Check if num itself (or modified if it contains '0') works directly
        // Precompute prefix products modulo t requirements
        vector<long long> req(n + 1, t);
        bool zero_seen = false;
        int first_zero = -1;

        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                zero_seen = true;
                first_zero = i;
                break;
            }
            req[i + 1] = req[i] / gcd(req[i], num[i] - '0');
        }

        // If num is zero-free and already satisfies t
        if (!zero_seen && req[n] == 1) {
            return num;
        }

        // Search for highest prefix index i to modify digit num[i] to d > num[i]
        int max_prefix = zero_seen ? first_zero : n - 1;

        for (int i = max_prefix; i >= 0; --i) {
            long long current_req = req[i];
            int start_digit = (i < n) ? (num[i] - '0' + 1) : 1;

            for (int d = start_digit; d <= 9; ++d) {
                long long next_req = current_req / gcd(current_req, d);
                int rem_len = n - 1 - i;
                int needed = minDigitsNeeded(next_req);

                if (needed != -1 && needed <= rem_len) {
                    string result = num.substr(0, i) + to_string(d);
                    result += fillSmallest(rem_len, next_req);
                    return result;
                }
            }
        }

        // If no match found within original length n, increase length to n + 1
        int needed = minDigitsNeeded(t);
        int target_len = max(n + 1, needed);
        return fillSmallest(target_len, t);
    }
};