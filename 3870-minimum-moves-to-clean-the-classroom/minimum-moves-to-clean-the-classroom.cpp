#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startR = -1, startC = -1;
        vector<pair<int, int>> litters;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startR = i;
                    startC = j;
                } else if (classroom[i][j] == 'L') {
                    litters.push_back({i, j});
                }
            }
        }
        
        int k = litters.size();
        int targetMask = (1 << k) - 1;
        
        // Map litter coordinates to bit index
        auto getLitterIndex = [&](int r, int c) {
            for (int i = 0; i < k; ++i) {
                if (litters[i].first == r && litters[i].second == c) {
                    return i;
                }
            }
            return -1;
        };

        // dist[r][c][mask] stores the maximum remaining energy for that state
        // -1 means unvisited
        vector<vector<vector<int>>> maxEnergy(
            m, vector<vector<int>>(n, vector<int>(1 << k, -1))
        );

        // Queue stores {r, c, mask, energy}
        queue<tuple<int, int, int, int>> q;
        
        // Initial state
        int initialMask = 0;
        int idx = getLitterIndex(startR, startC);
        if (idx != -1) {
            initialMask |= (1 << idx);
        }
        
        q.push({startR, startC, initialMask, energy});
        maxEnergy[startR][startC][initialMask] = energy;

        int moves = 0;
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == targetMask) {
                    return moves;
                }

                for (auto& dir : dirs) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int nextE = e - 1;
                        if (nextE < 0) continue;

                        char cell = classroom[nr][nc];
                        if (cell == 'R') {
                            nextE = energy; // Reset energy to full
                        }

                        int nextMask = mask;
                        if (cell == 'L') {
                            int lIdx = getLitterIndex(nr, nc);
                            if (lIdx != -1) {
                                nextMask |= (1 << lIdx);
                            }
                        }

                        // If reaching this state with strictly more energy, push to queue
                        if (nextE > maxEnergy[nr][nc][nextMask]) {
                            maxEnergy[nr][nc][nextMask] = nextE;
                            q.push({nr, nc, nextMask, nextE});
                        }
                    }
                }
            }
            moves++;
        }

        return -1;
    }
};