#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <climits>
using namespace std;




void dfs(vector<bool> &visited,int src,int level, vector<vector<int>> graph, int x, unordered_map<int, int> &prev_map,
unordered_map<int, int> &curr_map, bool flag)
{
    if(flag)
    {
        curr_map.insert({src, 1});
        visited[src]=true;
        for (int i = 0; i < graph.size(); i++)
        {
            if(i==src)
            {
                continue;
            }
            if(graph[src][i]==1)
            {
                if(!visited[i])
                {
                    
                    if(level<x)
                    {
                        
                        dfs(visited, i, level+1, graph, x, prev_map, curr_map, flag);
                    }
                }
                
               
            }
        }
    }
    else
    {
        if (prev_map.find(src)!=prev_map.end())
        {
            curr_map.insert({src, 1});

        }
        visited[src]=true;
        for (int i = 0; i < graph.size(); i++)
        {
            if(i==src)  
            {
                continue;
            }
            if(graph[src][i]==1)
            {
                if(!visited[i])
                {
                    if(level<x)
                    {
                        
                        dfs(visited, i, level+1, graph, x, prev_map, curr_map, flag);
                    }
                }
                
               
            }
        }
    }
    return;
}


int solve(vector<vector<int>> graph, vector<int> hotspots, int city, int e, int x)
{
    if (hotspots.size()==0)
    {
        return 0;
    }
    unordered_map<int, int> prev_map;
    unordered_map<int, int> curr_map;
    
    bool flag = false;
    for(int i=0; i<hotspots.size(); i++)
    {
        vector<bool> visited(graph.size(), false);
        if(i==0)
        {
            flag=true;
        }
        else
        {
            flag=false;
        }
        int level=0;
        dfs(visited,hotspots[i], level, graph, x, prev_map, curr_map, flag);
        prev_map=curr_map;
        curr_map.clear();
    }

    return prev_map.size();
}

int main()
{
    int n, e, h, x;
    cout<<"Enter number of cities, number of hotspot cities & distance through which virus can travel: "<<endl;
    cin>>n>>h>>x;
    cout<<"Enter hotspot cities"<<endl;
    vector<int> hotspots;
    for(int i=0; i<h; i++)
    {
        int city;
        cin>>city;
        
        hotspots.push_back(city);
        
    }
    e=n-1;
    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
    cout<<"Enter city you want to conncect (with spaces):"<<endl;
    for(int i=0; i<e; i++)
    {
        int src, dest;
        cin>>src>>dest;
        graph[src][dest]=1;
        graph[dest][src]=1;
        
    }

    int ans=solve(graph, hotspots, n+1, e, x);
    cout<<"The number of epicentre is: "<<ans<<endl;

    return 0;
}