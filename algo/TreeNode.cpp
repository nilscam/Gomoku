//
// Created by nils on 10/10/18.
//

#include "TreeNode.hpp"

template<typename Data>
TreeNode<Data>::TreeNode() = default;


template<typename Data>
Data TreeNode<Data>::getData() const {
    return _data;
}

template<typename Data>
void TreeNode<Data>::setData(Data data) {
    _data = data;
}


template<typename Data>
std::vector<std::unique_ptr<TreeNode<Data>>> &TreeNode<Data>::getChildrens() {
    return childrens;
}

template<typename Data>
void TreeNode<Data>::addChildren(TreeNode &node) {
    childrens.push(std::make_unique(new TreeNode(node)));
}

template<typename Data>
TreeNode<Data>::TreeNode(Data data) : _data(data) {
}
