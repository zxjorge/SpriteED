#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "Node.h"

class Trie
{

public:
    Node *root_;

    Trie();
    Trie(const Trie &other);
    ~Trie();
    Trie &operator=(Trie otherTrie);

    void addAWord(std::string word);
    bool isAWord(std::string word);
    std::vector<std::string> allWordsBeginningWithPrefix(std::string word);

private:
    std::vector<std::string> wordSearch(std::vector<std::string>& words, Node *root, std::string prefix);
};