#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<string>

using namespace std;

unordered_map<string,string> dm;  // 所有的关系节点
vector<string> vers; // 所有的可能答案
unordered_map<string,int> v2c;// 记录最大前序数
unordered_map<string,int> cnt;// 以及查找过的节点


vector<string> res;

int dfs(string &cur){
    if(cnt.find(cur) != cnt.end()) return cnt[cur]; // 查找过的直接返回
    if(dm.find(cur) == dm.end() || dm[cur] == "NA"){
        cnt[cur] = 0;
        return 0;
    }
    string pre = dm[cur];
    cnt[cur] = dfs(pre) + 1;
    return cnt[cur];
}
void version_update(void){
    int n;
    cin>>n;
    for(int i = 0; i < n;++i){
        string s1,s2;
        cin>>s1>>s2;
        dm[s1] = s2;
        vers.push_back(s1);
    }
    for(int i = 0; i < vers.size();++i) v2c[vers[i]] = dfs(vers[i]);
    int mx = 0;
    for(auto it: v2c) mx = max(mx,it.second);
    for(auto it:v2c){
        if(it.second == mx){
            res.push_back(it.first);
        }
    }
    sort(res.begin(),res.end());
    for(auto it : res){
        cout<< it<<' ';
    }
}