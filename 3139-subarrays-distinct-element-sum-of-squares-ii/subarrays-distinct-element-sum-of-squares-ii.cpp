#include <vector>
#include <unordered_map>

class Solution {
    static const int MOD = 1e9 + 7;
    std::vector<long long> sum_sq, sum_lin, lazy;
    int n;

    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = (l + r) / 2;
            long long v = lazy[node];

            // Left child
            lazy[2 * node] = (lazy[2 * node] + v) % MOD;
            // (A + v)^2 = A^2 + 2*v*A + v^2 * length
            sum_sq[2 * node] = (sum_sq[2 * node] + 2 * v * sum_lin[2 * node] + v * v % MOD * (mid - l + 1)) % MOD;
            sum_lin[2 * node] = (sum_lin[2 * node] + v * (mid - l + 1)) % MOD;

            // Right child
            lazy[2 * node + 1] = (lazy[2 * node + 1] + v) % MOD;
            sum_sq[2 * node + 1] = (sum_sq[2 * node + 1] + 2 * v * sum_lin[2 * node + 1] + v * v % MOD * (r - mid)) % MOD;
            sum_lin[2 * node + 1] = (sum_lin[2 * node + 1] + v * (r - mid)) % MOD;

            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long v) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            lazy[node] = (lazy[node] + v) % MOD;
            sum_sq[node] = (sum_sq[node] + 2 * v * sum_lin[node] + v * v % MOD * (r - l + 1)) % MOD;
            sum_lin[node] = (sum_lin[node] + v * (r - l + 1)) % MOD;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, v);
        update(2 * node + 1, mid + 1, r, ql, qr, v);
        sum_sq[node] = (sum_sq[2 * node] + sum_sq[2 * node + 1]) % MOD;
        sum_lin[node] = (sum_lin[2 * node] + sum_lin[2 * node + 1]) % MOD;
    }

public:
    int sumCounts(std::vector<int>& nums) {
        n = nums.size();
        sum_sq.assign(4 * n, 0);
        sum_lin.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        std::unordered_map<int, int> last_pos;
        long long total_sum = 0;
        long long current_total_squares = 0;

        for (int j = 0; j < n; ++j) {
            int prev = -1;
            if (last_pos.find(nums[j]) != last_pos.end()) {
                prev = last_pos[nums[j]];
            }
            last_pos[nums[j]] = j;

            // Update range [prev + 1, j] by adding 1
            update(1, 0, n - 1, prev + 1, j, 1);

            // The root node (1, 0, n-1) holds the sum of squares of all subarrays ending at or before j
            total_sum = (total_sum + sum_sq[1]) % MOD;
        }

        return total_sum;
    }
};