#include <vector>
#ifndef NODE_H
#define NODE_H
class Node
{
public:

    bool isWord_;
    Node *children_[26];

    Node();
    ~Node();
    Node(const Node &other);
    Node &operator=(Node otherNode);
};
#endif