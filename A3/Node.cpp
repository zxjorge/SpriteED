#include "Node.h"

Node::Node()
{
    for (int i = 0; i < 26; i++)
    {
        children_[i] = nullptr;
    }
}

Node::~Node()
{
    for (int i = 0; i < 26; i++)
        delete children_[i];
}

Node::Node(const Node &other)
{
    *children_ = *other.children_;
    isWord_ = other.isWord_;
}

Node &Node::operator=(Node otherNode)
{
    std::swap(*children_, *otherNode.children_);
    // std::swap(left_, otherTrie.left_);
    // std::swap(right_, otherTrie.right_);
    std::swap(isWord_, otherNode.isWord_);
    return *this;
}