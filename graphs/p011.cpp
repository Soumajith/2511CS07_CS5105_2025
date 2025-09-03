#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    unordered_map<int, int> parent;

    DisjointSet(int n) {
        for (int i = 0; i < n; i++) {
            makeSet(i);
        }
    }

    void makeSet(int v) {
        parent[v] = v;
    }

    int findSet(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = findSet(parent[v]); 
    }

    void unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b)
            parent[b] = a; 
    }
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        int maxRow = 0;
        int maxCol = 0;

        for(auto it : stones){
            maxRow = max(maxRow, it[0]);
            maxCol = max(maxCol, it[1]);
        }

        DisjointSet ds(maxRow+maxCol+1);
        unordered_map<int,int> stoneNodes; // to get the node pos
        for(auto it : stones){
            int row = it[0];
            int col = it[1] + maxRow + 1;
            ds.unionSets(row, col);
            stoneNodes[row]= 1;
            stoneNodes[col] = 1;
        }

        int cnt = 0;
        for(auto it : stoneNodes){
            if(ds.findSet(it.first) == it.first){
                cnt++;
            }
        }

        return n - cnt;
    }
};