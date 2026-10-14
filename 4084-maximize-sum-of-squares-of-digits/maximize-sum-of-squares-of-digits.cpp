class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if ((long long)num * 9 < sum) {
            return "";
        }

        string result = "";

        while (sum >= 9 && result.length() < num) {
            result += '9';
            sum -= 9;
        }

        if (sum > 0 && result.length() < num) {
            result += to_string(sum);
            sum = 0;
        }

        while (result.length() < num) {
            result += '0';
        }

        return result;
    }
};