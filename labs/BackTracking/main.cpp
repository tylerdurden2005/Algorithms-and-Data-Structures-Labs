#include <iostream>
#include <vector>
#include <set>
#include <cmath>

class TableField{
    std::vector<std::vector<size_t>> field;
    std::set<std::pair<size_t, size_t>> coordinates;
    std::set<std::pair<size_t, size_t>> coordinatesReserve;
    void drawOnField(int size, size_t x0, size_t y0){
        //x0, y0 - куда ставим
        size_t x_F = x0 + size;
        size_t y_F = y0 + size;
        for (size_t row = y0, column = x0; row<y_F; ++row, ++column){
            field[row][x_F-1] = 1;
            field[row][x0] = 1;

            field[y_F-1][column] = 1;
            field[y0][column] = 1;
        }
        coordinates.erase({x0, y0});
        if (x_F<field.size() ){
            if (coordinates.count({x_F, y0}) > 0){
                coordinatesReserve.insert({x_F, y0});
            }
            coordinates.insert({x_F, y0});
        }
        if (y_F < field.size() ){
            if (coordinates.count({x0, y_F}) > 0){
                coordinatesReserve.insert({x0, y_F});
            }
            coordinates.insert({x0, y_F});
        }
    }
    bool check(int sideSize, size_t x0, size_t y0, int& offset){
        int table_side = field.size();
        if(x0 + sideSize -1 >= table_side){
            offset = x0+sideSize - table_side;
            return false;
        }
        if (y0+sideSize-1 >=field.size()){
            offset = y0+sideSize - table_side;
            return false;
        }
        for (size_t i = x0, j = y0; i<x0+sideSize; ++i, ++j){
            if (field[y0][i] == 1){
                offset = (int)(sideSize - (i - x0));
                return false;
            }
            if (field[j][x0] == 1){
                offset = (int)(sideSize - (j - y0));
                return false;
            }
        }
        return true;
    }
public:
    TableField(int& tableSide){
        field.assign(tableSide, std::vector<size_t>(tableSide, 0));
        coordinates.insert({0, 0});
    }
    bool add(int& sideSize, std::pair<size_t, size_t>& square_coord, int& offset){
        if (coordinates.empty()) return false;
        auto begin = coordinates.begin();
        size_t x0 = begin->first;
        size_t y0 = begin->second;
        while(field[y0][x0] == 1){
            coordinates.erase({x0, y0});
            if (coordinates.empty()) return false;
            begin = coordinates.begin();
            x0 = begin->first;
            y0 = begin->second;
        }
        if (!check(sideSize, x0, y0, offset)) return false;
        drawOnField(sideSize, x0, y0);
        square_coord.first = x0;
        square_coord.second = y0;
        return true;
    }
    void del(int& side_size, size_t& x0, size_t& y0){
        size_t x_F = x0 + side_size;
        size_t y_F = y0 + side_size;
        for (size_t row = y0, column = x0; row<y_F; ++row, ++column){
            field[row][x_F-1] = 0;
            field[row][x0] = 0;

            field[y_F-1][column] = 0;
            field[y0][column] = 0;
        }
        coordinates.insert({x0, y0});
        if (coordinatesReserve.count({x_F, y0})>0){
            coordinatesReserve.erase({x_F, y0});
        }
        else coordinates.erase({x_F, y0});
        if (coordinatesReserve.count({x0, y_F})>0){
            coordinatesReserve.erase({x0, y_F});
        }
        else coordinates.erase({x0, y_F});
    }
    int addPrime(int& tableSide){
        drawOnField(tableSide / 2 + 1, 0, 0);
        drawOnField(tableSide / 2, 0, tableSide / 2 + 1);
        drawOnField(tableSide / 2, tableSide / 2 + 1, 0);
        return (tableSide / 2 + 1)*(tableSide / 2 + 1) + (tableSide / 2)*(tableSide / 2)*2;
    }
    void addFirstSquare(int& side){
        drawOnField(side, 0, 0);
    }
    void info_coord(){
        std::cout << "COORD: \n";
        for (auto& i : coordinates){
            std::cout << i.first << " " << i.second << "\n";
        }
    }
    void print(){
        for (auto& i : field){
            for (auto& j : i){
                std::cout << j << " ";
            }
            std::cout << "\n";
        }
    }
};

bool backTrack(int& tableSide, size_t& nums,  std::vector<std::pair<std::pair<size_t, size_t>, int>> result, size_t count, TableField& field, std::vector<std::pair<std::pair<size_t, size_t>, int>>& answer, int area, int maxSide, int& tableArea, int& numOfOperation){
    if (count > nums) return false;
    if (count == nums && area==tableArea){
        answer = result;
        return true;
    }
    else if (count == nums) return false;
    maxSide = (int)sqrt(maxSide);
    std::pair<size_t, size_t> coord;
    bool flag;
    int offset;
    for (int sideSize = maxSide; sideSize>=1;){
        numOfOperation++;
        offset = 0;
        flag = field.add(sideSize, coord, offset);
        //field.print();
        //std::cout << "\n----------------------------------------------\n";
        if (flag){

            result.push_back({coord, sideSize});
            ++count;
            area += sideSize*sideSize;
            if (backTrack(tableSide, nums, result, count, field, answer, area, tableArea-area, tableArea, numOfOperation)){
                return true;
            }
            area -= sideSize*sideSize;
            --count;
            field.del(sideSize, coord.first, coord.second);
            result.pop_back();
            --sideSize;
        }
        else{
            if (offset == 0){
                break;
            }
            sideSize -= offset;
        }
    }
    return false;
}

void printAnswer(std::vector<std::pair<std::pair<size_t, size_t>, int>>& result){
    std::cout << result.size() << "\n";
    for (auto& i : result){
        std::cout << i.first.first+1 << " " << i.first.second+1 << " " << i.second << "\n";
    }
}
bool isPrimal(int& num, int& divider){
    bool flag = true;
    for (int i = 2; i <= (int)sqrt(num); ++i){
        if (num % i == 0 ){
            if (num/i > divider) divider = num / i;
            flag = false;
        }
    }
    return flag;
}
/*void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    std::cout << "Memory usage: " << pmc.WorkingSetSize / 1024 << " KB" << std::endl;
}*/
void parity(int& table_side){
    std::cout << 4 << "\n";
    int half_side = table_side / 2;
    std::cout << "1 " <<  "1 " << half_side << "\n";
    std::cout << "1 " << half_side + 1 << " " << half_side << "\n";
    std::cout << half_side+1 <<  " 1 " << half_side << "\n";
    std::cout << half_side+1  <<  " " << half_side+1 << " " << half_side;
}
void nonParity(int& tableSide){
    size_t maxNumberOfSquares = tableSide * 2;
    std::vector<std::pair<std::pair<size_t, size_t>, int>> squaresAnswer;
    TableField table(tableSide);
    int count, area;
    int divider = 1;
    size_t startNums = 6;
    if (isPrimal(tableSide, divider)){
        area = table.addPrime(tableSide);
        count = 3;
        squaresAnswer.push_back({{0, 0}, tableSide / 2 +1});
        squaresAnswer.push_back({{0, tableSide / 2 +1}, tableSide / 2 });
        squaresAnswer.push_back({{tableSide / 2 +1, 0}, tableSide / 2 });
    }
    else{
        table.addFirstSquare(divider);
        count = 1;
        area = divider * divider;
        squaresAnswer.push_back({{0, 0}, divider});
    }
    //std::cout << "START TABLE:\n";
    //table.print();
    //table.info_coord();
    int numOfOperation = 0;
    int tableArea = tableSide*tableSide;
    for (size_t nums = startNums; nums<=maxNumberOfSquares; ++nums){
        //std::cout << "\n\n CURRENT NUMS: " << nums << "\n";
        if (backTrack(tableSide, nums, squaresAnswer, count, table, squaresAnswer, area, tableArea-area, tableArea, numOfOperation)){
            break;
        }
    }
    printAnswer(squaresAnswer);
    std::cout<< "Number of operations: " << numOfOperation << "\n";
}

int main() {
    int inputN;
    std::cin >> inputN;
    //auto start = std::chrono::high_resolution_clock::now();
    if (inputN % 2==0){
        parity(inputN);
        return 0;
    }
    nonParity(inputN);
    //printMemoryUsage();
    /*auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "time: " << duration.count() << " seconds" << std::endl;*/
}


