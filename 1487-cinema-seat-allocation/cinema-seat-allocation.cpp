#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // Map row number -> bitmask of reserved seats
        unordered_map<int, int> reservedRows;

        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Only track seats 2 through 9
            if (col == 2 || col == 3) {
                reservedRows[row] |= (1 << 0);
            } else if (col == 4 || col == 5) {
                reservedRows[row] |= (1 << 1);
            } else if (col == 6 || col == 7) {
                reservedRows[row] |= (1 << 2);
            } else if (col == 8 || col == 9) {
                reservedRows[row] |= (1 << 3);
            }
        }

        int maxFamilies = 0;

        // Process only the rows that have reservations
        for (const auto& [row, mask] : reservedRows) {
            bool leftPossible = !(mask & 0b0011);   // Bits 0 and 1 are free
            bool rightPossible = !(mask & 0b1100);  // Bits 2 and 3 are free
            bool middlePossible = !(mask & 0b0110); // Bits 1 and 2 are free

            if (leftPossible && rightPossible) {
                maxFamilies += 2;
            } else if (leftPossible || rightPossible || middlePossible) {
                maxFamilies += 1;
            }
        }

        // Add 2 families for each completely empty row
        int emptyRows = n - reservedRows.size();
        maxFamilies += emptyRows * 2;

        return maxFamilies;
    }
};