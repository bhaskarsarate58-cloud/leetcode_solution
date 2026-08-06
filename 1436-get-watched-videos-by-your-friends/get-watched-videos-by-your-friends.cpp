#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    std::vector<std::string> watchedVideosByFriends(
        std::vector<std::vector<std::string>>& watchedVideos, 
        std::vector<std::vector<int>>& friends, 
        int id, 
        int level
    ) {
        int n = friends.size();
        std::vector<bool> visited(n, false);
        std::queue<int> q;

        // Step 1: Start BFS from the target user
        q.push(id);
        visited[id] = true;

        int current_level = 0;

        // Traverse level by level until we reach the target 'level'
        while (!q.empty() && current_level < level) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int person = q.front();
                q.pop();

                for (int friend_id : friends[person]) {
                    if (!visited[friend_id]) {
                        visited[friend_id] = true;
                        q.push(friend_id);
                    }
                }
            }
            current_level++;
        }

        // Step 2: Queue now contains ONLY people at the exact 'level'
        std::unordered_map<std::string, int> freq;
        while (!q.empty()) {
            int friend_id = q.front();
            q.pop();

            for (const std::string& video : watchedVideos[friend_id]) {
                freq[video]++;
            }
        }

        // Step 3: Store frequencies in a vector of pairs for custom sorting
        std::vector<std::pair<int, std::string>> video_list;
        for (const auto& entry : freq) {
            video_list.push_back({entry.second, entry.first});
        }

        // Step 4: Sort primarily by frequency (ascending), secondarily by name (alphabetical)
        std::sort(video_list.begin(), video_list.end());

        // Step 5: Extract ordered video names
        std::vector<std::string> result;
        for (const auto& item : video_list) {
            result.push_back(item.second);
        }

        return result;
    }
};