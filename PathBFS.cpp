//
//  PathBFS.cpp
//  newGraph
//
//  Created by ComarPers 922 on 2017/4/2.
//  Copyright © 2017年 ComarPers 922. All rights reserved.
//

#include "PathBFS.hpp"
#include <cstring>
#include <queue>

PathBFS::PathBFS(myNewGraph& g,int f): graph(g),from(f)
{
    visited = new bool[g.getNumVer()];
    preVex = new int[g.getNumVer()];
    
    for(int i = 0; i<g.getNumVer();i++)
    {
        visited[i] = false;
        preVex[i] = SUPERNUM;
    }
    
    std::queue<int> q;
    q.push(from);
    visited[from] = true;
    int current;
    while(!q.empty())//Traversal
    {
        current = q.front();
        q.pop();
        typename myNewGraph::myNewGraphIterator it(graph,current);
        for(int temp = it.begin();!it.end();temp = it.next())
        {
            if(!visited[temp])
            {
                q.push(temp);
                preVex[temp] = current;
                visited[temp] =true;
            }
        }
    }
}
bool PathBFS::hasPath(int des)
{
    return visited[des];
}
void PathBFS::findPath(int des, std::vector<int>& nodes)
{
    if(hasPath(des))
    {
        std::stack<int> s;
        int current = des;
        s.push(des);
        while(preVex[current] != SUPERNUM)
        {
            s.push(preVex[current]);
            current = preVex[current];
        }
        while(!s.empty())
        {
            nodes.push_back(s.top());
            s.pop();
        }
    }
    else
    {
        // No way!
    }
}
void PathBFS::showPath(int des)
{
    std::vector<int> nodes;
    findPath(des, nodes);
    for (int i = 0; i<nodes.size(); i++)
    {
        std::cout<<nodes[i]<<(i+1==nodes.size()?"\n":"->");
    }
}
PathBFS::~PathBFS()
{
    delete [] visited;
    delete [] preVex;
}
