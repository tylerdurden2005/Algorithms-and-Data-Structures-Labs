#include "Merge.h"
int counter_gallops = 0;
size_t Search(size_t size, int value, const std::vector<int>& mas, size_t index){
    size_t l = index;
    size_t r = size;
    int res = -1;
    while (l<r){
        size_t m = (l+r-1) / 2;
        if (abs(mas[m]) < abs(value)) {
            res = static_cast<int>(m);
            r=m;
        }
        else if (abs(mas[m]) >= abs(value)){
            l=m+1;
        }
    }
    if (res==-1) return size;
    else return res;
}
void Merge(std::vector<int>& mas1, const std::vector<int>& mas2){ //mas1 change
    std::vector<int> res;
    size_t i = 0, j = 0;
    size_t c1 = 0, c2 = 0, gallops = 0;
    size_t id; // index after gallop
    while (i < mas1.size() && j < mas2.size()) {
        if (abs(mas1[i]) >= abs(mas2[j])) {
            c2=0;
            res.push_back(mas1[i++]);
            c1++;
            if (c1==3){
                gallops++;
                id = Search(mas1.size(), mas2[j], mas1, i);
                c1 =0;
                for (size_t r =i; r<id; ++r){
                    res.push_back(mas1[r]);
                }
                i =id;
            }
        }
        else {
            c1=0;
            res.push_back(mas2[j++]);
            c2++;
            if (c2==3){
                gallops++;
                id = Search(mas2.size(), mas1[i], mas2, j);
                c2 =0;
                for (size_t r =j; r<id; ++r) res.push_back(mas2[r]);
                j =id;
            }
        }
    }
    if (j<mas2.size()){
        while(j < mas2.size()) res.push_back(mas2[j++]);
    }
    else if (i<mas1.size()){
        while(i<mas1.size()) res.push_back(mas1[i++]);
    }
    std::cout << "Gallops " << counter_gallops++ << ": "<< gallops << "\n";
    mas1 = res;
}
