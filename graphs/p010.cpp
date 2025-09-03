#include <bits/stdc++.h>
using namespace std;

class DisjointSet{
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
    int makeConnected(int n, vector<vector<int>>& connections) {
        if ((int)connections.size() < n - 1) return -1;

        DisjointSet ds(n);
        int cntExtras = 0;

        for (auto &it : connections) {
            int u = it[0];
            int v = it[1];
            if (ds.findSet(u) == ds.findSet(v)) {
                cntExtras++; // extra edge
            } else {
                ds.unionSets(u, v);
            }
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (ds.findSet(i) == i) components++;
        }


        return (cntExtras >= components - 1 ? components - 1 : -1);
    }
};
