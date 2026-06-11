/*
================================================================================
Problem Name: Alien Dictionary (LeetCode 269 / GFG)
Difficulty: Hard
Category: Graph Theory / Topological Sort / Directed Acyclic Graph (DAG)
================================================================================

Problem Description:
Given a sorted dictionary of an alien language having N words and K starting 
alphabets of a standard dictionary. Find the order of characters in the alien 
language.

Note: 
- The dictionary is sorted in alphabetical order of the alien language.
- If no valid ordering exists, return "".
- If there are multiple valid orders, return any one of them.

--------------------------------------------------------------------------------
Example 1:
Input: 
N = 5, K = 4
dict = ["baa", "abcd", "abca", "cab", "cad"]

Output: "bdac"
Explanation: 
- From "baa" and "abcd", we can determine 'b' comes before 'a' ('b' -> 'a').
- From "abcd" and "abca", we can determine 'd' comes before 'a' ('d' -> 'a').
- From "abca" and "cab", we can determine 'a' comes before 'c' ('a' -> 'c').
- From "cab" and "cad", we can determine 'b' comes before 'd' ('b' -> 'd').
Combining these, a valid order is "bdac".

--------------------------------------------------------------------------------
Example 2:
Input: 
N = 3, K = 3
dict = ["caa", "aaa", "aab"]

Output: "cab"
Explanation: 
- From "caa" and "aaa", we can determine 'c' comes before 'a' ('c' -> 'a').
- From "aaa" and "aab", we can determine 'a' comes before 'b' ('a' -> 'b').
Combining these, a valid order is "cab".

--------------------------------------------------------------------------------
Constraints:
- 1 <= N <= 10^4
- 1 <= K <= 26
- 1 <= Length of words <= 100
- The characters in the words are lowercase English alphabets.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findOrder(string dict[], int N, int K) {
        vector<vector<int>> adj(K);
        vector<int> indegree(K, 0);

        for (int i = 0; i < N - 1; i++) {
            string w1 = dict[i];
            string w2 = dict[i + 1];
            int len = min(w1.length(), w2.length());
            bool hasMismatch = false;
            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j] - 'a'].push_back(w2[j] - 'a');
                    hasMismatch = true;
                    break;
                }
            }
            // If w2 is a prefix of w1 (e.g. "abc" and "ab"), the dictionary is invalid.
            if (!hasMismatch && w1.length() > w2.length()) {
                return "";
            }
        }

        for (int i = 0; i < K; i++) {
            for (int neighbor : adj[i]) {
                indegree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        string ans = "";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            ans += (char)(node + 'a');

            for (auto neighbor : adj[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // If topological sort does not contain all K vertices, it means a cycle exists.
        if (ans.length() < K) {
            return "";
        }

        return ans;
    }
};
