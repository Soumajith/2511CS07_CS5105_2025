#include <bits/stdc++.h>
using namespace std;
int main(){
   
    int n;
    cin >> n;
    vector<long long>a(n);

    for(int i=0;i<n;++i) 
        cin>>a[i];
    long long mx = a.empty()? 0 : a[0];
    
    for(long long v:a) if(v>mx) mx=v;
   
    cout<<mx<<"\n";
    
    return 0;
}
