#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int maxLen = 0;
    int prefixLen = 0;
    int suffixLen = 0;
    char leftChar = 0;
    char rightChar = 0;
};

class Solution {
private:
    vector<Node> tree;
    string s;

    Node merge(const Node& left, const Node& right, int leftLen, int rightLen) {
        Node parent;
        parent.leftChar = left.leftChar;
        parent.rightChar = right.rightChar;

        parent.maxLen = max(left.maxLen, right.maxLen);
        parent.prefixLen = left.prefixLen;
        parent.suffixLen = right.suffixLen;

        // Check if adjacent characters at the split boundary match
        if (left.rightChar == right.leftChar) {
            parent.maxLen = max(parent.maxLen, left.suffixLen + right.prefixLen);

            if (left.prefixLen == leftLen) {
                parent.prefixLen = left.prefixLen + right.prefixLen;
            }
            if (right.suffixLen == rightLen) {
                parent.suffixLen = right.suffixLen + left.suffixLen;
            }
        }

        return parent;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start]};
            return;
        }

        int mid = start + (end - start) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch};
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }

        tree[node] = merge(tree[2 * node], tree[2 * node + 1], mid - start + 1, end - mid);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        this->s = s;
        int n = s.length();
        int k = queryIndices.size();

        tree.resize(4 * n);
        build(1, 0, n - 1);

        vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            result[i] = tree[1].maxLen;
        }

        return result;
    }
};