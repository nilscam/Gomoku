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

    void    addChildren(TreeNode<Data> *);
    void    deleteFrom(int);

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
void TreeNode<Data>::addChildren(TreeNode<Data> *data) {
    childrens.push_back(data);
}

template<typename Data>
std::vector<TreeNode<Data> *> &TreeNode<Data>::getChildrens() {
    return childrens;
}

template<typename Data>
void TreeNode<Data>::deleteFrom(int nb) {
    int to_delete = static_cast<int>(childrens.size() - nb);

    for (int i = 0; i < to_delete; i++) {
        TreeNode<Data> *delNode = childrens.back();
        delete delNode;
        childrens.pop_back();
    }
}


#endif //IA_TREENODE_HPP
