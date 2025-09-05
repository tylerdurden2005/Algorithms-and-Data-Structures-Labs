#include "Cut.h"

size_t MinRunLen(size_t n){
    size_t flag =0;
    while (n>=16){
        flag |= n & 1;
        n >>= 1;
    }
    return n+flag;
}
void InsertSort(std::vector<int>& mas){
    for (size_t i = 1; i<mas.size(); ++i){
        size_t j =i;
        while(abs(mas[j-1]) < abs(mas[j]) && j > 0){
            int p = mas[j-1];
            mas[j-1] = mas[j];
            mas[j] = p;
            j-=1;
        }
    }
}
void Cut(std::vector<int>& mas, size_t min_run, size_t index, std::vector<std::vector<int>>& parts){
    if (index >= mas.size()) return;
    std::vector<int> run;
    if (index+1 == mas.size()) {
        run.push_back(mas[index]);
        parts.push_back(run);
        return;
    }
    size_t len = 1;
    int flag;
    if (abs(mas[index]) <  abs(mas[index+1])) flag = 1;//increasing
    else flag =0;
    run.push_back(mas[index]);
    size_t i = index+1;
    if (flag==0){ //decreasing
        while (abs(mas[i]) <= abs(mas[i-1]) && i <mas.size()){
            run.push_back(mas[i]);
            len++;
            i++;
        }
    }
    else{ //increasing
        while (abs(mas[i]) > abs(mas[i-1]) && i <mas.size()){
            run.push_back(mas[i]);
            len++;
            i++;
        }
    }
    while(i < mas.size() && len < min_run){
        run.push_back(mas[i]);
        len++;
        i++;
    }
    if (len != mas.size() || len<=min_run){
        InsertSort(run);
    }
    parts.push_back(run);
    run.clear();
    Cut(mas, min_run, index+len, parts);
}
