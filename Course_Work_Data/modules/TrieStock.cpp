#include "TrieStock.h"

void Stocks::PrintLikeTable(TrieNode *node, std::string& prefix) {
    if (node == nullptr) return;
    if (node->is_word){
        std::cout << prefix << " -- " << node->price << "\n";
    }
    for (int i =0; i<26; ++i){
        prefix.push_back('A'+i);
        PrintLikeTable(node->children[i], prefix);
        prefix.pop_back();
    }
}

TrieNode *Stocks::FindStock(std::string &ticker) {
    TrieNode* ptr = head;
    size_t id;
    for (char i : ticker) {
        id = i - 'A';
        if (ptr->children[id] == nullptr){
            return nullptr;
        }
        ptr = ptr->children[id];
    }
    if (ptr->is_word) return ptr;
    else return nullptr;
}

void Stocks::ClearTrie(TrieNode *node) {
    if (node == nullptr) return;
    else{
        for (size_t i =0; i<26; ++i){
            ClearTrie(node->children[i]);
        }
        node->Clear();
    }
}

void Stocks::DFS(TrieNode *node, std::string& prefix) {
    if (node == nullptr) return;
    for (int i =0; i<26; ++i){
        if (node->children[i] != nullptr){
            prefix.push_back('A'+i);
            std::cout << prefix << std::endl;
            DFS(node->children[i], prefix);
            prefix.pop_back();
        }
    }
}

Stocks::Stocks() {
    head = new TrieNode();
}

void Stocks::AddStock(std::string &ticker, float price) {
    TrieNode* ptr = head;
    size_t id;
    for (char i : ticker){
        id = i - 'A';
        if (ptr->children[id] == nullptr){
            ptr->children[id] = new TrieNode();
            ptr->not_nullptr+=1;
        }
        ptr = ptr->children[id];
    }
    if (!ptr->is_word){
        nums_stocks++;
    }
    ptr->is_word = true;
    ptr->price = price;
}

void Stocks::DeleteStock(std::string &ticker) {
    int parent_symbol = -1;
    TrieNode* ptr = head;
    TrieNode* prefix_parent = head;
    size_t id;
    size_t counter_letter = 0;
    for (char i : ticker) {
        id = i - 'A';
        if (ptr->children[id] == nullptr) {
            std::cout << "\nThere is no such action!\n";
            return;
        }
        else{
            if (ptr->children[id]->not_nullptr > 1 ){
                prefix_parent = ptr->children[id];
                parent_symbol = counter_letter;
            }
            else if (ptr->children[id]->not_nullptr == 1 && ptr->children[id]->is_word){
                prefix_parent = ptr->children[id];
                parent_symbol = counter_letter;
            }
            ptr = ptr->children[id];
        }
        counter_letter++;
    }

    if (!ptr->is_word){
        std::cout << "\nThere is no such action!\n";
        return;
    }

    ptr->is_word = false;
    ptr->price =0.0;

    if (ptr->not_nullptr == 0){
        ptr = prefix_parent;
        TrieNode* previous = nullptr;
        size_t index_for_letter = parent_symbol+1;
        id = ticker[index_for_letter] - 'A';
        size_t post_prefix_id = id;
        while (ptr->children[id] != nullptr){
            ptr = ptr->children[id];
            delete previous;
            previous = ptr;
            index_for_letter++;
            if (index_for_letter < ticker.size()) id = ticker[index_for_letter] - 'A';
            else break;
        }
        delete previous;
        prefix_parent->children[post_prefix_id] = nullptr;
        prefix_parent->not_nullptr -=1;
    }
    nums_stocks--;
}


void Stocks::CompareStock(std::string &ticker, float current_price) {
    TrieNode* ptr = FindStock(ticker);
    if (ptr == nullptr){
        std::cout << "\nThere is no such action!\n";
        return;
    }
    if (current_price < ptr->price){
        std::cout << "\nBuy!!!\n";
    }
    else{
        std::cout << "\nCell!!!\n";
    }
}

void Stocks::PrintStocks() {
    std::string prefix;
    PrintLikeTable(head, prefix);
}

void Stocks::PrintAllPrefix() {
    std::string prefix;
    DFS(head, prefix);
}

void Stocks::ClearAllTrie() {
    ClearTrie(head);
}

size_t Stocks::GetNumsStocks() {
    return nums_stocks;
}

bool Stocks::IsEmpty() {
    return head->not_nullptr == 0;
}

Stocks::~Stocks() {
    ClearTrie(head);
}
