#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& adj) {
        int V = adj.size();

        vector<int>color(V, -1);

        stack<int>st;

        for(int i = 0; i < V; i++){
            if(color[i] == -1){
                color[i] = 0; 
                st.push(i);

                while(!st.empty()){
                    int u = st.top();
                    st.pop();

                    for(auto v : adj[u]){
                        if(color[v] == -1){
                            color[v] = 1 - color[u];
                            st.push(v);
                        }

                        else if(color[u] == color[v]) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};