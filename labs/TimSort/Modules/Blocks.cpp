#include "Blocks.h"
bool Invariant(size_t size, std::vector<size_t>& mas){
    size_t X,Y,Z;
    if (size==3){
        X = mas[2];
        Y= mas[1];
        Z=mas[0];
    }
    else{
        X = mas[1];
        Y= mas[0];
    }
    if (size==3){
        if (Z > X + Y && Y > X) return true;
        else return false;
    }
    else{
        if (Y > X) return true;
        else return false;
    }
}

std::vector<int> Blocks(std::vector<std::vector<int>>& runs){
    size_t counter = 0;
    std::stack<std::vector<int>> blocks;
    std::vector<size_t> size_of_blocks;
    std::vector<int> Y;
    std::vector<int> X;
    for (std::vector<int>& i : runs){
        blocks.push(i);
        size_of_blocks.push_back(i.size());
        if (size_of_blocks.size() == 3){
            if (!Invariant(3, size_of_blocks)){
                if (size_of_blocks[0] < size_of_blocks[2]){ //Z<X
                    size_of_blocks[1] = size_of_blocks[0] + size_of_blocks[1];
                    X = blocks.top();
                    blocks.pop();
                    Y = blocks.top();
                    blocks.pop();
                    Merge(Y, blocks.top());
                    std::cout << "Merge " << counter << ":";
                    for (int num : Y){
                        std::cout << " " << num;
                    }
                    std::cout << "\n";
                    counter++;
                    blocks.pop();
                    blocks.push(Y);
                    blocks.push(X);
                    size_of_blocks.erase(size_of_blocks.begin());
                }
                else{
                    size_of_blocks[1] = size_of_blocks[2] + size_of_blocks[1];
                    X = blocks.top();
                    blocks.pop();
                    Y = blocks.top();
                    blocks.pop();
                    Merge(Y, X);
                    std::cout << "Merge " << counter << ":";
                    for (int num : Y){
                        std::cout << " " << num;
                    }
                    std::cout << "\n";
                    counter++;
                    blocks.push(Y);
                    size_of_blocks.erase(size_of_blocks.begin()+2); //delete x
                }
                if (!Invariant(2, size_of_blocks)){
                    X = blocks.top();
                    blocks.pop();
                    Y = blocks.top();
                    blocks.pop();
                    size_of_blocks[0] = size_of_blocks[0]+size_of_blocks[1];
                    Merge(Y, X);
                    std::cout << "Merge " << counter << ":";
                    for (int num : Y){
                        std::cout << " " << num;
                    }
                    std::cout << "\n";
                    counter++;
                    blocks.push(Y);
                    size_of_blocks.pop_back();
                }
            }
            else{ // next "the tree" in stack
                size_of_blocks.erase(size_of_blocks.begin());
            }
        }
        else if (size_of_blocks.size()==2){
            if (!Invariant(2, size_of_blocks)){
                X = blocks.top();
                blocks.pop();
                Y = blocks.top();
                blocks.pop();
                size_of_blocks[0] = size_of_blocks[0]+size_of_blocks[1];
                Merge(Y, X);
                std::cout << "Merge " << counter << ":";
                for (int num : Y){
                    std::cout << " " << num;
                }
                std::cout << "\n";
                counter++;
                blocks.push(Y);
                size_of_blocks.pop_back();
            }
        }
    }
    size_of_blocks.clear();
    X.clear(), Y.clear();
    std::vector<int> Z;
    while(blocks.size()>1){ // stack is not clear
        if (blocks.size()==2){
            X = blocks.top();
            blocks.pop();
            Y = blocks.top();
            blocks.pop();
            Merge(Y, X);
            std::cout << "Merge " << counter << ":";
            for (int num : Y){
                std::cout << " " << num;
            }
            std::cout << "\n";
            counter++;
            blocks.push(Y);
        }
        else{
            X = blocks.top();
            blocks.pop();
            Y = blocks.top();
            blocks.pop();
            if (blocks.top().size() < X.size()){ //Z<X
                Merge(Y, blocks.top());
                std::cout << "Merge " << counter << ":";
                for (int num : Y){
                    std::cout << " " << num;
                }
                std::cout << "\n";
                counter++;
                blocks.pop();
                blocks.push(Y);
                blocks.push(X);
            }
            else{
                Merge(Y, X);
                std::cout << "Merge " << counter << ":";
                for (int num : Y){
                    std::cout << " " << num;
                }
                std::cout << "\n";
                counter++;
                blocks.push(Y);
            }
        }
    }
    return blocks.top();
}