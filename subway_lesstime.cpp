#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<climits>
#include<string>
#include<sstream>
using namespace std;

void subway_lesstime(void){
    int n;
    char s,t;
    unordered_map<char,unordered_map<char,int>> graph;
    cin>>n;
    cin>>s>>t;
    string line;
    while(getline(cin,line)){
        if(line == "0000") break;
        istringstream iss(line);
        int val;
        char a,b;
        iss>>a>>b>>val;
        graph[a][b] = val;
        graph[b][a] = val;
    }
    unordered_map<char,int> dist;
    unordered_map<char,vector<char>> record;
    unordered_set<char> visited;
    for(auto i : graph){
        char a = i.first;
        dist[a] = INT_MAX;
        cout<<a<<endl;
        
    }
    dist[s] = 0;
    while(visited.find(t) == visited.end()){
        char minnode;
        int mindist = INT_MAX;
        for(auto[a,b] : dist){
            if(visited.find(a) == visited.end() && b < mindist){
                minnode = a;
                mindist = b;
            }
        }
        visited.insert(minnode);
        for(auto[a,b] : graph[minnode]){
            if(dist[minnode] + b  < dist[a]){
                dist[a] = dist[minnode] + b;
                record[a] = record[minnode];
                record[a].push_back(a);
            }
        }
        for(auto i: record[t]){
            cout<<i<<' ';
        }
    }
}
