#include <iostream>
#include <unistd.h>

#include "algo/TreeNode.tpp"
#include "algo/Board.hpp"
#include "PiskvorkInterface.hpp"
#include "algo/MinMax.hpp"

int main() {
    /*
    PiskvorkInterface   program;

    program.mainLoop();
    */

    /*
    TreeNode<int>    node(5);

    for (int i = 0; i < 10; i++)
        node.addChildren(i);

    node.print();
    */

    MinMax  m;

    std::cout << "Minmax " << sizeof(MinMax) << std::endl;
    std::cout << "Board " << sizeof(Board) << std::endl;
    std::cout << "TreeNode " << sizeof(TreeNode<char>) << std::endl;



    m.propagation();
    return 0;
}