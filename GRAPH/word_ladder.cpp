/*
================================================================================
Problem Name: Word Ladder I & II (LeetCode 127 / 126 & GFG)
Difficulty: Hard
Category: Graph Theory / Breadth-First Search (BFS) / DFS Backtracking
================================================================================

Problem Description:

------------------------------------
Word Ladder I (Shortest Path Length)
------------------------------------
A transformation sequence from word `beginWord` to word `endWord` using a dictionary 
`wordList` is a sequence of words `beginWord -> s_1 -> s_2 -> ... -> s_k` such that:
- Every adjacent pair of words differs by a single letter.
- Every `s_i` (for 1 <= i <= k) is in `wordList`. Note that `beginWord` does not 
  need to be in `wordList`.
- `s_k == endWord`.

Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return the 
number of words in the shortest transformation sequence from `beginWord` to `endWord`, 
or 0 if no such sequence exists.

Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> "cog", 
which is 5 words long.

------------------------------------
Word Ladder II (All Shortest Paths)
------------------------------------
Given two words, `beginWord` and `endWord`, and a dictionary `wordList`, return all 
the shortest transformation sequences from `beginWord` to `endWord`. Each sequence 
should be returned as a list of the words [beginWord, s_1, s_2, ..., s_k].

Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]

================================================================================
Complexity Analysis:

Word Ladder I:
- Time Complexity: O(N * M * 26)
  Where N is the size of the wordList and M is the length of each word. For each 
  word, we try replacing each of its M positions with 26 alphabets.
- Space Complexity: O(N * M)
  For storing the words in an unordered set and the BFS queue.

Word Ladder II:
- Time Complexity: O(N * M * 26 + K * M)
  Where K is the number of shortest paths. We perform BFS to establish levels/distances 
  and then use DFS to reconstruct paths.
- Space Complexity: O(N * M)
  For the levels/steps hashmap, queue, and DFS recursion stack.
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// =============================================================================
// Word Ladder I: BFS Queue of pairs (word, steps)
// =============================================================================
class WordLadderI {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Transfer wordList to a hashset for O(1) lookups and deletions
        unordered_set<string> st(wordList.begin(), wordList.end());
        
        // If endWord is not in the set, a transformation sequence is impossible
        if (st.find(endWord) == st.end()) {
            return 0;
        }
        
        // Queue stores pairs of {current_word, steps_taken}
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        
        // If beginWord is in the set, erase it so we do not visit it again
        if (st.find(beginWord) != st.end()) {
            st.erase(beginWord);
        }
        
        while (!q.empty()) {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();
            
            // If target word is found, return the total steps
            if (word == endWord) {
                return steps;
            }
            
            // Generate all possible 1-character transformations
            for (int i = 0; i < word.size(); i++) {
                char originalChar = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    // If the modified word is in the set, it is a valid neighbor
                    if (st.find(word) != st.end()) {
                        st.erase(word); // Remove from set to mark as visited
                        q.push({word, steps + 1});
                    }
                }
                word[i] = originalChar; // Restore character
            }
        }
        
        return 0;
    }
};

// =============================================================================
// Word Ladder II: Optimal BFS + DFS Backtracking (Prevents Time Limit Exceeded)
// =============================================================================
class WordLadderII {
private:
    unordered_map<string, int> steps; // Stores the minimum steps from beginWord to each word
    vector<vector<string>> ans;
    string startWord;
    
    // DFS Backtracking starting from endWord back to beginWord to construct paths
    void dfs(string word, vector<string>& path) {
        if (word == startWord) {
            vector<string> temp = path;
            reverse(temp.begin(), temp.end());
            ans.push_back(temp);
            return;
        }
        
        int stepsTaken = steps[word];
        int sz = word.size();
        
        // Try all possible 1-character predecessors
        for (int i = 0; i < sz; i++) {
            char originalChar = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;
                // If predecessor is in our BFS shortest path map and has steps = stepsTaken - 1
                if (steps.find(word) != steps.end() && steps[word] == stepsTaken - 1) {
                    path.push_back(word);
                    dfs(word, path);
                    path.pop_back(); // Backtrack
                }
            }
            word[i] = originalChar; // Restore character
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(wordList.begin(), wordList.end());
        
        // Base BFS to calculate shortest step distance from beginWord to all words
        queue<string> q;
        q.push(beginWord);
        steps[beginWord] = 1;
        
        if (st.find(beginWord) != st.end()) {
            st.erase(beginWord);
        }
        
        while (!q.empty()) {
            string word = q.front();
            q.pop();
            int currStep = steps[word];
            
            if (word == endWord) break;
            
            for (int i = 0; i < word.size(); i++) {
                char originalChar = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if (st.find(word) != st.end()) {
                        // Word has been reached in shortest steps
                        steps[word] = currStep + 1;
                        q.push(word);
                        st.erase(word); // Erase from set so it is not visited again in BFS
                    }
                }
                word[i] = originalChar;
            }
        }
        
        // If endWord is not reached during BFS, return empty paths
        if (steps.find(endWord) != steps.end()) {
            startWord = beginWord;
            vector<string> path;
            path.push_back(endWord);
            dfs(endWord, path);
        }
        
        return ans;
    }
};
