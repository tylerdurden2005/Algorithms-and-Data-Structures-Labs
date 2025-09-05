#ifndef CPPCOURSEWORK_CLI_H
#define CPPCOURSEWORK_CLI_H
#include "TrieStock.h"
enum class TypeInput{
    RecommendedInput,
    CompareInput
};
bool CheckName(std::string& str);
bool CheckPrice(std::string& str, float& our_price);
void HandleInputError();
void CloseProgram(Stocks* StockMarket);
void InputData(Stocks* stocks_data, TypeInput flag);
void AfterAnalyze(Stocks* stocks_data);
void AfterRecommended(Stocks* stocks_data);
void AfterLook(Stocks* stocks_data);
void InputFromFile(Stocks* stocks_data);
#endif //CPPCOURSEWORK_CLI_H
