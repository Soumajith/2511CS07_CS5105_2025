#include <bits/stdc++.h>
using namespace std;
int main(){

    int n; cin>>n ;
    vector<long long>a(n);
    for(int i=0;i<n;++i) cin>>a[i];
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    if(a.size()<2){
        cout<<"-1 -1\n";
    } else {
        cout<<a[1]<<" "<<a[a.size()-2]<<"\n";
    }
    return 0;
}
