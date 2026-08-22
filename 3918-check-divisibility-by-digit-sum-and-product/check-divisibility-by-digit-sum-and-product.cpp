class Solution {
public:
    bool checkDivisibility(int n) {
        int temp = n;
        long long digit_sum = 0;
        long long digit_product = 1;

        while (temp > 0) {
            int digit = temp % 10;
            digit_sum += digit;
            digit_product *= digit;
            temp /= 10;
        }

        long long total = digit_sum + digit_product;
        
        return n % total == 0;
    }
};