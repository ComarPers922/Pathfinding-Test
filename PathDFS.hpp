//
//  PathDFS.hpp
//  newGraph
//
//  Created by ComarPers 922 on 2017/4/2.
//  Copyright © 2017年 ComarPers 922. All rights reserved.
//

#ifndef PathDFS_hpp
#define PathDFS_hpp

#include <iostream>
#include <vector>
#include <stack>
#include "myNewGraph.hpp"

class PathDFS
{
private:
    myNewGraph &graph;
    bool * visited;
    int from;
    int* preVex;
    void dfs(int v);
public:
    PathDFS(myNewGraph& g,int f);
    ~PathDFS();
    bool hasPath(int des);
    void findPath(int des, std::vector<int>& nodes);
    void showPath(int des);
};
#endif /* PathDFS_hpp */







