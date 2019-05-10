#include "Util.h"

#include <sstream>

float parseFloat(string str){
    stringstream ss(str);
    float x;
    ss >> x;
    return x;
}

int parseInt(string str){
    stringstream ss(str);
    int x;
    ss >> x;
    return x;
}

string parseString(int str){
    stringstream ss;
    ss << str;
    string x;
    ss >> x;
    return x;
}

std::vector<std::string> split(std::string s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
