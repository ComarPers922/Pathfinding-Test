//
//  myNewGraph.cpp
//  newGraph
//
//  Created by ComarPers 922 on 2017/4/2.
//  Copyright © 2017年 ComarPers 922. All rights reserved.
//

#include "myNewGraph.hpp"
#include <iostream>
myNewGraph::myNewGraph(int v)
{
    this->numVer = v;
    for(int i =0; i<v; i++)
    {
        g.push_back(std::vector<int>());
    }
}
void myNewGraph::addEdge(int from, int to)
{
    if(from == to)
    {
        return;
    }
    if(this->hasEdge(from, to))
    {
        return;
    }
    g[from].push_back(to);
    g[to].push_back(from);
}

bool myNewGraph::hasEdge(int from, int to)
{
    for(int i = 0 ;i < g[from].size();i++)
    {
        if(g[from][i] == to)
        {
            return true;
        }
    }
    return false;
}
//use this iterator to find adjacent nodes
myNewGraph::myNewGraphIterator::myNewGraphIterator(myNewGraph &Graph, int vex):graph(Graph), v(vex)
{
    index = 0;
}

int myNewGraph::myNewGraphIterator::begin()
{
    index = 0;
    if(graph.g[v].size())
    {
        return graph.g[v][index];
    }
    return SUPERNUM;
}

int myNewGraph::myNewGraphIterator::next()
{
    if(index<graph.g[v].size())
    {
        return graph.g[v][++index];
    }
    return SUPERNUM;
}

bool myNewGraph::myNewGraphIterator::end()
{
    return index >= graph.g[v].size();
}

int myNewGraph::getNumEdge()
{
    return this->numEdge;
}

int myNewGraph::getNumVer()
{
    return this->numVer;
}

