#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class SparseTable {
    vector<vector<int>> st;
public:
    void build(const vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return;
        int maxLog = log2(n) + 1;
        st.assign(maxLog, vector<int>(n));
        st[0] = arr;
        for (int j = 1; j < maxLog; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int L, int R) {
        if (L > R) return 0;
        int j = log2(R - L + 1);
        return max(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }

        struct Group {
            int start, end, len;
        };
        
        // Find all zero groups in s
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(n, -1);

        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (zeroGroups.empty() || s[i - 1] == '1') {
                    zeroGroups.push_back({i, i, 1});
                } else {
                    zeroGroups.back().end = i;
                    zeroGroups.back().len++;
                }
                zeroGroupIndex[i] = zeroGroups.size() - 1;
            }
        }

        int m = zeroGroups.size();

        // adjSum[i] = len(zeroGroup[i]) + len(zeroGroup[i+1])
        vector<int> adjSum(max(0, m - 1));
        for (int i = 0; i < m - 1; ++i) {
            adjSum[i] = zeroGroups[i].len + zeroGroups[i + 1].len;
        }

        SparseTable st;
        if (!adjSum.empty()) {
            st.build(adjSum);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            // Find the index of the first zero-group that intersects [l, r]
            int gL = -1;
            for (int i = l; i <= r; ++i) {
                if (zeroGroupIndex[i] != -1) {
                    gL = zeroGroupIndex[i];
                    break;
                }
            }

            // Find the index of the last zero-group that intersects [l, r]
            int gR = -1;
            for (int i = r; i >= l; --i) {
                if (zeroGroupIndex[i] != -1) {
                    gR = zeroGroupIndex[i];
                    break;
                }
            }

            // CRITICAL CHECK: Less than 2 zero-groups inside [l, r] -> NO TRADE POSSIBLE!
            if (gL == -1 || gL == gR) {
                ans.push_back(totalOnes);
                continue;
            }

            // Clipped zero-group lengths at boundaries l and r
            int leftLen = min(zeroGroups[gL].end, r) - max(zeroGroups[gL].start, l) + 1;
            int rightLen = min(zeroGroups[gR].end, r) - max(zeroGroups[gR].start, l) + 1;

            int maxGain = 0;

            if (gL + 1 == gR) {
                // Exactly 2 zero groups intersect [l, r]
                maxGain = leftLen + rightLen;
            } else {
                // Merge gL & gL+1
                maxGain = max(maxGain, leftLen + zeroGroups[gL + 1].len);

                // Merge gR-1 & gR
                maxGain = max(maxGain, zeroGroups[gR - 1].len + rightLen);

                // Range query for any fully contained adjacent zero group pair between gL+1 and gR-1
                if (gL + 1 <= gR - 2) {
                    maxGain = max(maxGain, st.query(gL + 1, gR - 2));
                }
            }

            ans.push_back(totalOnes + maxGain);
        }

        return ans;
    }
};