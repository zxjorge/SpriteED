#include <vector>

class Node
{
public:

    bool isWord_;
    Node **children_;

    Node();
    ~Node();
    Node(const Node &other);
    Node &operator=(Node otherNode);
};