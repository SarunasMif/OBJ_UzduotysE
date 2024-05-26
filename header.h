#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <algorithm> 
#include <regex>

struct Data{
    int number;
    std::set<int> lines;
};

int main();
void ReadFile(std::string filename, std::map<std::string, Data>& map);
std::vector<std::string> cleanline(std::string& line);
void ToLower(std::string& word);
void Printfile(std::map<std::string, Data>& map);
void BuildReff(std::map<std::string, Data>& map);
void ReadLink(std::string filename, std::map<int, std::string>& map);
void printLinks(std::map<int, std::string>& map);

#endif