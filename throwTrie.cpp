#include <iostream>
#include <vector>
#include <string>
#include <stack>

const int ALPHABET_SIZE = 26;

struct TrieNode {
  std::vector<TrieNode*> children;
  bool isEndOfWord;

  TrieNode() {
    children.resize(ALPHABET_SIZE, nullptr);
    isEndOfWord = false;
  }
};

class Trie {
 public:
  Trie() {
    root = new TrieNode();
  }

  void insert(const std::string& word) {
    TrieNode* pCrawl = root;
    for (int i = 0; i < word.length(); i++) {
      int index = word[i] - 'a';
      if (!pCrawl->children[index]) {
        pCrawl->children[index] = new TrieNode();
      }
      pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
  }

  std::vector<std::string> getWords() {
    std::vector<std::string> words;
    std::stack<std::pair<TrieNode*, std::string>> dfsStack;
    dfsStack.push({root, ""});
    while (!dfsStack.empty()) {
      TrieNode* node = dfsStack.top().first;
      std::string word = dfsStack.top().second;
      dfsStack.pop();
      for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
          std::string newWord = word + (char)('a' + i);
          if (node->children[i]->isEndOfWord) {
            words.push_back(newWord);
          }
          dfsStack.push({node->children[i], newWord});
        }
      }
    }
    return words;
  }

 private:
  TrieNode* root;
};

int main() {
  Trie trie;
  trie.insert("hello");
  trie.insert("world");
  trie.insert("hi");

  std::vector<std::string> words = trie.getWords();
  for (const std::string& word : words) {
    std::cout << word << std::endl;
  }

  // Output:
  // hello
  // hi
  // world
  return 0;
}