//
// Created by nils on 10/10/18.
//

#ifndef IA_TREENODE_HPP
#define IA_TREENODE_HPP


#include <vector>
#include <memory>

template <typename Data>
class TreeNode {
public:
    TreeNode();
    explicit TreeNode(Data);
    ~TreeNode() = default;

    Data getData() const;
    void setData(Data);

    void    addChildren(TreeNode &);
    std::vector<std::unique_ptr<TreeNode>>  &getChildrens();

private:
    Data    _data;

    std::vector<std::unique_ptr<TreeNode>> childrens;
};

#endif //IA_TREENODE_HPP
