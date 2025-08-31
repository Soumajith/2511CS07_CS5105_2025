#include<bits/stdc++.h>
using namespace std;

vector<int> bfs(vector<vector<int> >& adj)  {
    int V = adj.size();
    
    int s = 0; 
    vector<int> res;

    queue<int> q;  
    
    vector<bool> visited(V, false);

    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);

        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }

    return res;
}

int main()  {
    // adj list
    vector<vector<int> > adj;
    int n, m;

    cout << "Enter the rows of adj list: " << endl;
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Enter the number of elements in the list";
        cin >> m;
        vector<int> temp;
        for(int j = 0; j < m; j++){
            int x;
            cin >> x;

            temp.push_back(x);
        }
        adj.push_back(temp);
    }

    
    vector<int> ans = bfs(adj);
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << endl;
}

// T.C. = O(V+E)
// S.C. = O(V)