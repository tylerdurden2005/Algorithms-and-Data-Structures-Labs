#include "modules/CLI.h"

int main() {
    std::cout << "Now Stock Market is closed! List of stocks empty.\n"
                 "If you want to add Recommended prices from terminal - enter \"Terminal\" \n"
                 "If you want to add Recommended prices from file - enter \"File\" \n"
                 "If you want to close program - enter \"Close\" \n";
    std::string input;
    std::getline(std::cin, input);
    while (input != "Terminal" &&  input != "Close" && input != "File"){
        std::cout << "You entered an unknown command: ";
        std::cout << input  << "\n";
        std::cout << "Try again!\n";
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, input);
    }
    auto* stocks_data = new Stocks;
    if (input == "Terminal"){
        InputData(stocks_data, TypeInput::RecommendedInput);
    }
    else if (input == "File"){
        InputFromFile(stocks_data);
        AfterRecommended(stocks_data);
    }
    else CloseProgram(stocks_data);
    return 0;
}

