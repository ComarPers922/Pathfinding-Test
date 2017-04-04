//
//  PathBFS.hpp
//  newGraph
//
//  Created by ComarPers 922 on 2017/4/2.
//  Copyright © 2017年 ComarPers 922. All rights reserved.
//

#ifndef PathBFS_hpp
#define PathBFS_hpp

#include <iostream>
#include <vector>
#include <stack>
#include "myNewGraph.hpp"

class PathBFS
{
private:
    myNewGraph &graph;
    bool * visited;
    int from;
    int* preVex;
public:
    PathBFS(myNewGraph& g,int f);
    ~PathBFS();
    bool hasPath(int des);
    void findPath(int des, std::vector<int>& nodes);
    void showPath(int des);
};
#endif /* PathBFS_hpp */
