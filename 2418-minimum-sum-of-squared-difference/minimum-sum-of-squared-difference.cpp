
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        long long k = 1LL * k1 + k2;
        vector<int> diff;
        long long total = 0;
        int mx = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            total += d;
            mx = max(mx, d);
        }

        if (k >= total) return 0;

        int low = 0, high = mx;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int d : diff) {
                need += max(0, d - mid);
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long used = 0;
        long long ans = 0;
        long long count = 0;

        for (int d : diff) {
            if (d > level) {
                used += d - level;
                d = level;
            }

            if (d == level) count++;
            ans += 1LL * d * d;
        }

        long long remaining = k - used;
        ans -= count * (2LL * level - 1) * 0; // no-op

        // Reduce 'remaining' elements from level to level - 1.
        ans -= remaining * (2LL * level - 1);

        return ans;
    }
};
