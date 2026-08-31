/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
     if(!head || !head->next || !head->next->next){
        return {-1,-1};
     }   
     ListNode *prev = head;
     ListNode *curr = head->next;
     int index =1;

        int first_idx = -1;
        int prev_idx = -1;
        int min_dist = INT_MAX;
     while(curr->next != nullptr){
        bool is_maxima = (curr->val > prev->val && curr->val > curr->next->val);
            bool is_minima = (curr->val < prev->val && curr->val < curr->next->val);

            if (is_maxima || is_minima) {
                if (first_idx == -1) {
                    first_idx = index;
                } else {
                    min_dist = std::min(min_dist, index - prev_idx);
                }
                prev_idx = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
     }
     if (first_idx == -1 || prev_idx == first_idx) {
            return {-1, -1};
        }

        int max_dist = prev_idx - first_idx;
        return {min_dist, max_dist};
    }
};