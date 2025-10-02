#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> tCount;
        for (char c : t) {
            tCount[c]++;
        }
        int required = tCount.size();

        // Sliding window pointers
        int left = 0, right = 0;
        int formed = 0;
        unordered_map<char, int> windowCount;

        // Result -> length, left, right
        int minLen = INT_MAX;
        int minLeft = 0;

        while (right < s.size()) {
            char c = s[right];
            windowCount[c]++;

            if (tCount.find(c) != tCount.end() && windowCount[c] == tCount[c]) {
                formed++;
            }

            // Try to shrink from left
            while (left <= right && formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }

                char leftChar = s[left];
                windowCount[leftChar]--;
                if (tCount.find(leftChar) != tCount.end() && windowCount[leftChar] < tCount[leftChar]) {
                    formed--;
                }
                left++;
            }

            right++;
        }

        return (minLen == INT_MAX) ? "" : s.substr(minLeft, minLen);
    }
};

int main() {
    Solution sol;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    cout << sol.minWindow(s, t) << endl; // Output: BANC
    return 0;
}
