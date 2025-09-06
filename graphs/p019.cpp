class Solution {
private:
    unordered_map<string, int> map;
    string begin;
    vector<vector<string>> ans;
    void dfs(string word, vector<string>&seq){
        if(word == begin){
            reverse(seq.begin(), seq.end());
            ans.push_back(seq);
            reverse(seq.begin(), seq.end());
            return;
        }
        int steps = map[word];
        int sz = begin.size();

        for(int i = 0; i < sz; i++){
            char original = word[i];
            for(char ch = 'a'; ch <= 'z'; ch++){
                word[i] = ch;
                if(map.find(word) != map.end() && map[word] + 1 == steps){
                    seq.push_back(word);
                    dfs(word, seq);
                    seq.pop_back();
                }
            }
            word[i] = original;
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        queue<string>q;
        q.push({beginWord});
        unordered_set<string>st(wordList.begin(), wordList.end());
        begin = beginWord;
        int sz = begin.size();
        map[begin] = 1;
        st.erase(beginWord);

        while(!q.empty()){
            string word = q.front();
            int ind = map[word];
            if(word == endWord) break;
            q.pop();

            for(int i = 0; i < sz; i++){
                char original = word[i];
                for(char ch = 'a'; ch <= 'z'; ch++){
                    word[i] = ch;
                    if(st.count(word)){
                        map[word] = ind + 1;
                        q.push(word);
                        st.erase(word);
                    }
                }
                word[i] = original;
            }
        }

        if(map.find(endWord) != map.end()){
            vector<string>seq;
            seq.push_back(endWord);
            dfs(endWord, seq);
        }

        return ans;
    }
};