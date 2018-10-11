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
    ~TreeNode();

    Data &getData();

    void setData(Data);
    std::vector<TreeNode<Data> *> &getChildrens();

    void    addChildren(Data);
    void    print();

    float   value;
private:
    Data    _data;
    std::vector<TreeNode *> childrens;
};

template<typename Data>
TreeNode<Data>::TreeNode(Data data) : _data(data) {}

template<typename Data>
TreeNode<Data>::~TreeNode() {
    for (auto i : childrens)
        delete i;
}

template<typename Data>
Data &TreeNode<Data>::getData() {
    return _data;
}

template<typename Data>
void TreeNode<Data>::setData(Data data) {
    _data = data;
}

template<typename Data>
void TreeNode<Data>::addChildren(Data data) {
    childrens.push_back(new TreeNode(data));
}

template<typename Data>
void TreeNode<Data>::print() {
    for (int i = 0; i < childrens.size(); i++)
        std::cout << childrens[i]->getData() << std::endl;
}

template<typename Data>
std::vector<TreeNode<Data> *> &TreeNode<Data>::getChildrens() {
    return childrens;
}


#endif //IA_TREENODE_HPP
