class Solution {
public:
    string smallestPalindrome(string s) {
        int n = s.length();
        string subs = s.substr(0,n/2);
        sort(subs.begin(),subs.end());
        string rsubs =subs;
        reverse(rsubs.begin(),rsubs.end());
        if(n%2 != 0){
            return subs+s[n/2]+rsubs;
        }else{
            return subs+rsubs;
        }
    }
};