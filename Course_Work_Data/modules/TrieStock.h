#ifndef CPPCOURSEWORK_TRIESTOCK_H
#define CPPCOURSEWORK_TRIESTOCK_H
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
struct TrieNode{
    std::vector<TrieNode*> children;
    float price = 0.0;
    bool is_word = false;
    size_t not_nullptr = 0;
    TrieNode(){
        children.assign(26, nullptr);
    }
    void Clear(){
        for (auto& i : children){
            delete i;
        }
        children.clear();
        price = 0.0;
        is_word = false;
        not_nullptr = 0;
    }
};
class Stocks{
private:
    TrieNode* head;
    size_t nums_stocks = 0;
    void PrintLikeTable(TrieNode* node, std::string& prefix);
    void ClearTrie(TrieNode* node);
    void DFS(TrieNode* node, std::string& prefix);
public:
    Stocks();
    void AddStock(std::string& ticker, float price);
    TrieNode* FindStock(std::string& ticker);
    void DeleteStock(std::string& ticker);
    void CompareStock(std::string & ticker, float current_price);
    void PrintStocks();
    void PrintAllPrefix();
    void ClearAllTrie();
    size_t GetNumsStocks();
    bool IsEmpty();
    ~Stocks();
};
#endif //CPPCOURSEWORK_TRIESTOCK_H
