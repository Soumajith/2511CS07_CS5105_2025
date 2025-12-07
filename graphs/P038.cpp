#include <bits/stdc++.h>
using namespace std;
struct DSU{ vector<int> p; DSU(int n):p(n){ iota(p.begin(),p.end(),0);} int find(int x){ return p[x]==x?x:p[x]=find(p[x]); } void unite(int a,int b){ a=find(a); b=find(b); if(a!=b) p[b]=a; } };
class Solution {
public:
    void solve() {
        int N; cin>>N;
        vector<vector<string>> accounts(N);
        for(int i=0;i<N;i++){
            int k; cin>>k; // number of strings in account
            accounts[i].resize(k);
            for(int j=0;j<k;j++) cin>>accounts[i][j];
        }
        unordered_map<string,int> emailId;
        int id=0;
        for(int i=0;i<N;i++){
            for(int j=1;j<(int)accounts[i].size();j++){
                string e=accounts[i][j];
                if(!emailId.count(e)) emailId[e]=id++;
            }
        }
        DSU d(id);
        for(int i=0;i<N;i++){
            for(int j=2;j<(int)accounts[i].size();j++){
                d.unite(emailId[accounts[i][1]], emailId[accounts[i][j]]);
            }
        }
        vector<vector<string>> groups(id);
        vector<string> nameOf(id);
        for(int i=0;i<N;i++){
            string name = accounts[i][0];
            for(int j=1;j<(int)accounts[i].size();j++){
                string e=accounts[i][j];
                int rid = d.find(emailId[e]);
                nameOf[rid]=name;
                groups[rid].push_back(e);
            }
        }
        for(int i=0;i<id;i++){
            if(groups[i].empty()) continue;
            sort(groups[i].begin(), groups[i].end());
            groups[i].erase(unique(groups[i].begin(), groups[i].end()), groups[i].end());
            cout<<nameOf[i];
            for(auto &e:groups[i]) cout<<" "<<e;
            cout<<"\n";
        }
    }
};
