#include "Trie.h"
/*
 * George Benyeogor
 * CS3505
 * A3: A Trie and Rule-of-Three
 *
 */

/// @brief
Trie::Trie()
{
    root_ = new Node();
}

/// @brief
/// @param otherTrie
Trie::Trie(const Trie &otherTrie)
{
    root_ = otherTrie.root_;
    // left_ = right_ = nullptr;
    // if (otherTrie.left_)
    // {
    //     left_ = new Trie(*(otherTrie.left_));
    // }
    // if (otherTrie.right_)
    // {
    //     right_ = new Trie(*(otherTrie.right_));
    // }
}

/// @brief
Trie::~Trie()
{
    // delete left_;
    // delete right_;
    delete root_;
}

/// @brief
/// @param otherTrie
/// @return
Trie &Trie::operator=(Trie otherTrie)
{
    std::swap(root_, otherTrie.root_);
    // std::swap(left_, otherTrie.left_);
    // std::swap(right_, otherTrie.right_);
    // std::swap(isWord_, otherTrie.isWord_);
    return *this;
}

/// @brief
/// @param word
void Trie::addAWord(std::string word)
{
    Node *temp = root_;

    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (!temp->children_[index])
        {
            temp->children_[index] = new Node();
        }
        temp = temp->children_[index];
    }
    temp->isWord_ = true;
}

/// @brief
/// @param word
/// @return
bool Trie::isAWord(std::string word)
{
    Node *temp = root_;

    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (!temp->children_[index])
        {
            return false;
        }
        else
        {
            temp = temp->children_[index];
        }
    }
    return temp->isWord_;
}

/// @brief
/// @param word
/// @return
std::vector<std::string> Trie::allWordsBeginningWithPrefix(std::string prefix)
{
    Node *temp = root_;
    std::vector<std::string> words;

    for (int i = 0; i < prefix.length(); i++)
    {
        int index = prefix[i] - 'a';
        if (!temp->children_[index])
        {
            wordSearch(words, root_, "");
            return words;
        }
        else
        {
            temp = temp->children_[index];
        }
    }
    wordSearch(words, root_, prefix);
    return words;
}

std::vector<std::string> Trie::wordSearch(std::vector<std::string>& words, Node *root, std::string prefix)
{
    
}
