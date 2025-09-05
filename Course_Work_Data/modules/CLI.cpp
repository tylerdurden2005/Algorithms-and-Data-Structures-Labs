#include "CLI.h"
#include "TrieStock.h"

bool CheckName(std::string& str){
    if (str.size() > 4) return false;
    bool flag = true;
    for (char i : str){
        if (!std::isupper(i)){
            flag =  false;
            break;
        }
    }
    return flag;
}
bool CheckPrice(std::string& str, float& our_price){
    float price = std::stof(str);
    if (price < 0){
        std::cout << "Error: Price can`t be < 0!\n";
        return false;
    }
    our_price = price;
    return true;
}
void HandleInputError() {
    std::cout << "Enter again: ";
    std::cin.clear();
    std::cin.sync();
}
void CloseProgram(Stocks* StockMarket){
    std::cout << "\nProgram close....\n";
    delete StockMarket;
}

void AfterLook(Stocks* stocks_data){
    std::string input;
    std::cout << "Now you can analyze or change recommended prices or close all program!\n"
                 "If you want to change recommended prices - enter \"Update\" \n"
                 "If you want to close program - enter \"Analyze\" \n"
                 "If you want to close program - enter \"Close\" \n";
    std::getline(std::cin, input);
    while (input != "Update" &&  input != "Analyze" && input != "Close"){
        std::cout << "You entered an unknown command: ";
        std::cout << input  << "\n";
        std::cout << "Try again!\n";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    if (input == "Close"){
        CloseProgram(stocks_data);
    }
    else if (input=="Update"){
        InputData(stocks_data, TypeInput::RecommendedInput);
    }
    else{
        InputData(stocks_data, TypeInput::CompareInput);
    }
}
void AfterRecommended(Stocks* stocks_data){
    std::string input;
    std::cout << "Now you can look at all stocks or start analyzing!\n"
                 "If you want to see stocks - enter \"Look\" \n"
                 "If you want to close program - enter \"Analyze\" \n";
    std::getline(std::cin, input);
    while (input != "Look" &&  input != "Analyze"){
        std::cout << "You entered an unknown command: ";
        std::cout << input  << "\n";
        std::cout << "Try again!\n";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    if (input == "Look"){
        stocks_data->PrintStocks();
        AfterLook(stocks_data);
    }
    else InputData(stocks_data, TypeInput::CompareInput);
}
void AfterAnalyze(Stocks* stocks_data){
    std::string input;
    std::cout << "Now you can look at all stocks or change recommended prices or close all program!\n"
                 "If you want to see stocks - enter \"Look\" \n"
                 "If you want to change recommended prices from terminal - enter \"Update1\" \n"
                 "If you want to change recommended prices from file - enter \"Update2\" \n"
                 "If you want to close program - enter \"Close\" \n";
    std::getline(std::cin, input);
    while (input != "Look" &&  input != "Close" && input != "Update1" && input != "Update2"){
        std::cout << "You entered an unknown command: ";
        std::cout << input  << "\n";
        std::cout << "Try again!\n";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    if (input == "Look"){
        stocks_data->PrintStocks();
        AfterLook(stocks_data);
    }
    else if (input == "Close"){
        CloseProgram(stocks_data);
    }
    else if (input == "Update1"){
        InputData(stocks_data, TypeInput::RecommendedInput);
    }
    else{
        InputFromFile(stocks_data);
        AfterRecommended(stocks_data);
    }
}
void InputData(Stocks* stocks_data, TypeInput flag){
    if (flag == TypeInput::RecommendedInput){
        std::cout << "\nEntry recommended prices\n";
    }
    else std::cout << "\nAnalyze\n";
    std::cout << "Enter \"NAME price\" \n";
    std::cout << "If you want to finish entering prices - enter \"Stop\" \n";
    std::string input;
    std::getline(std::cin, input);
    std::string word;
    float price;
    while (input != "Stop"){
        while (true){
            try{
                size_t id = input.find(' ');
                if (id != std::string::npos){
                    word = input.substr(0, id);
                    if (!CheckName(word)){
                        std::cout << "Error: wrong ticker!\n";
                        throw std::invalid_argument("");
                    }
                    std::string price_str = input.substr(id+1);
                    if (!CheckPrice(price_str, price)){
                        throw std::invalid_argument("");
                    }
                    if (flag == TypeInput::RecommendedInput){
                        stocks_data->AddStock(word, price);
                    }
                    else if (flag == TypeInput::CompareInput){
                        stocks_data->CompareStock(word, price);
                    }
                    break;
                }
                else{
                    std::cout << "Error: wrong string!\n";
                    throw std::invalid_argument("");
                }
            }
            catch (const std::invalid_argument& e ) {
                HandleInputError();
                std::getline(std::cin, input);
            }
            catch (const std::out_of_range& e){
                HandleInputError();
                std::getline(std::cin, input);
            }
        }
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    if (flag == TypeInput::RecommendedInput){
        AfterRecommended(stocks_data);
    }
    else{ // compare
        AfterAnalyze(stocks_data);
    }
}

void InputFromFile(Stocks* stocks_data){
    std::string file_name = "/home/nikita/stocks.txt";
    std::ifstream file(file_name);
    std::string line;
    std::string word;
    float price;
    while (std::getline(file, line)) {
        size_t id = line.find(' ');
        word = line.substr(0, id);
        price = std::stof(line.substr(id));
        stocks_data->AddStock(word, price);
    }
    file.close();
}