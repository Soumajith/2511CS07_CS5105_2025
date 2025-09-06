#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        unordered_set<string> st(wordList.begin(), wordList.end());

        while(!q.empty()){
            auto [w , h] = q.front();
            q.pop();

            if(w == endWord) return h;
            for(int i = 0; i < w.length(); i++){
                char letter = w[i];

                
                for(char ch = 'a' ; ch  <= 'z' ; ch++){
                    w[i] = ch;

                    if(st.find(w) != st.end()){
                        q.push({w, h+1});
                        st.erase(w);
                    }
                }

                w[i] = letter;
            }
        }


        return 0;

    }
};