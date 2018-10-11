//
// Created by nils on 10/10/18.
//

#ifndef IA_TREENODE_HPP
#define IA_TREENODE_HPP

#include <iostream>
#include <vector>
#include <memory>

template <typename Data>
class TreeNode {
public:
    TreeNode() = default;
    explicit TreeNode(Data);
    ~TreeNode() = default;

    Data getData() const;
    void setData(Data);
    std::vector<std::shared_ptr<TreeNode<Data>>> &getChildrens();

    void    addChildren(Data);
    void    print();

    float   value = 0.0;

private:
    Data    _data;
    std::vector<std::shared_ptr<TreeNode>> childrens;
};

template<typename Data>
TreeNode<Data>::TreeNode(Data data) : _data(data) {}

template<typename Data>
Data TreeNode<Data>::getData() const {
    return _data;
}

template<typename Data>
void TreeNode<Data>::setData(Data data) {
    _data = data;
}

template<typename Data>
void TreeNode<Data>::addChildren(Data data) {
    childrens.push_back(std::make_shared<TreeNode>(data));
}

template<typename Data>
void TreeNode<Data>::print() {
    for (int i = 0; i < childrens.size(); i++)
        std::cout << childrens[i]->getData() << std::endl;
}

template<typename Data>
std::vector<std::shared_ptr<TreeNode<Data>>> &TreeNode<Data>::getChildrens() {
    return childrens;
}

#endif //IA_TREENODE_HPP
