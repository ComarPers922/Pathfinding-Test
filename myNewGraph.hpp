//
//  myNewGraph.hpp
//  newGraph
//
//  Created by ComarPers 922 on 2017/4/2.
//  Copyright © 2017年 ComarPers 922. All rights reserved.
//
#ifndef myNewGraph_hpp
#define myNewGraph_hpp

#define SUPERNUM -123321 //Means Invalid item

#include <stdio.h>
#include <vector>
class myNewGraph
{
private:
    std::vector<std::vector<int>> g;//To record nodes
    int numEdge,numVer;
public:
    myNewGraph(int v);
    void addEdge(int from , int to);
    bool hasEdge (int from, int to);
    int getNumEdge();
    int getNumVer();
    
    class myNewGraphIterator
    {
    private:
        myNewGraph &graph;
        int v;
        int index;
    public:
        myNewGraphIterator(myNewGraph &Graph, int vex);
        int begin();
        int next();
        bool end();
    };
};

#endif /* myNewGraph_hpp */
