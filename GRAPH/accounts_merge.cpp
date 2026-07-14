/*
================================================================================
Problem Name: Accounts Merge (LeetCode 721)
Difficulty: Medium
Category: Graph Theory / Disjoint Set Union (DSU)
================================================================================

Problem Description:
Given a list of accounts where each element accounts[i] is a list of strings, 
where the first element accounts[i][0] is a name, and the rest of the elements 
are emails representing that account.

Now, we want to merge these accounts. Two accounts definitely belong to the same 
person if there is some common email to both accounts. Note that even if two 
accounts have the same name, they may belong to different people as people 
could have the same name. A person can have any number of accounts initially, 
but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the 
first element of each account is the name, and the rest of the elements are 
emails in sorted order. The accounts themselves can be returned in any order.

--------------------------------------------------------------------------------
Example 1:
Input: 
accounts = [
  ["John","johnsmith@mail.com","john_newyork@mail.com"],
  ["John","johnsmith@mail.com","john00@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]
Output: 
[
  ["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
  ["Mary","mary@mail.com"],
  ["John","johnnybravo@mail.com"]
]

Explanation:
The first and second John's accounts are merged since they share the email 
"johnsmith@mail.com". The third John's account and Mary's account are not merged 
since there is no shared email. The output list of accounts can be in any order, 
but the emails in each account must be sorted.

--------------------------------------------------------------------------------
Constraints:
- 1 <= accounts.length <= 1000
- 2 <= accounts[i].length <= 10
- 1 <= accounts[i][j].length <= 30
- accounts[i][0] consists of English letters.
- accounts[i][j] (for j > 0) is a valid email.

================================================================================
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Disjoint Set Union (DSU) structure using path compression and union by size.
class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DisjointSet ds(n);
        
        // Map to store mapping of email -> account/node index
        unordered_map<string, int> mapMailNode;
        
        // Step 1: Traverse the accounts and build the DSU representation
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string mail = accounts[i][j];
                // If the email is seen for the first time, map it to the current account index
                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                } else {
                    // If the email has been seen before, union the current account index
                    // with the previously mapped account index
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }

        // Step 2: Group all emails under their ultimate parent account index
        vector<vector<string>> mergedMail(n);
        for (auto& it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }

        // Step 3: Format the output - retrieve names, sort emails, and prepare result
        vector<vector<string>> ans;
        for (int i = 0; i < n; i++) {
            if (mergedMail[i].empty()) continue;
            
            // Sort the emails for the current merged account
            sort(mergedMail[i].begin(), mergedMail[i].end());
            
            vector<string> temp;
            temp.push_back(accounts[i][0]); // Add the name
            for (auto& mail : mergedMail[i]) {
                temp.push_back(mail);
            }
            ans.push_back(temp);
        }
        
        return ans;
    }
};
