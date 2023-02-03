#include <iostream>
#include "Trie.h"
#include "Node.h"
#include <vector>
#include <string>
#include <cstdio>

int main()
{
    Trie newTrie;
    newTrie.addAWord("hello");
    newTrie.addAWord("ball");
    newTrie.addAWord("chicken");
    newTrie.addAWord("fries");
    newTrie.addAWord("dog");

    std::vector<std::string> allWords = newTrie.allWordsBeginningWithPrefix("d");

    for (std::vector<std::string>::iterator t = allWords.begin(); t != allWords.end(); ++t)
    {
        std::cout << *t << "\n";
    }
    return 0;
}