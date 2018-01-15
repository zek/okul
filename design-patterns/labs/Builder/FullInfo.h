#pragma once

#include<string>
#include<list>

class FullInfo
{
public:
  std::string name;
  std::string origin;
  std::string receipe;
  float price;
  float tax;
  std::list<std::string> ingredients;
  float callories;
};
