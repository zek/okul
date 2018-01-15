#pragma once

#include"FullInfo.h"

#include<string>
#include<iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <algorithm>
#include <sstream>

class FileReader
{
public:
  FileReader (const std::string fileName) : m_fileName (fileName) {}

  const FullInfo& Data() {return m_data;}

  void Read ()
  {
    using namespace std;

    ifstream file (m_fileName.data());
    std::string line;

    getline(file, line);
    m_data.name = line;

    getline(file, line);
    m_data.receipe = line;

    getline(file, line);
    m_data.origin = line;

    getline(file, line);
    m_data.price = stof(line);

    getline(file, line);
    m_data.tax = stof(line);

    getline(file, line);
    m_data.callories = stof(line);

    getline(file, line);
    std::istringstream lineSS (line);
    list<string> ingredients {istream_iterator<string>{lineSS}, istream_iterator<string>{}};
    m_data.ingredients = ingredients;
  }

protected:
  std::string m_fileName;
  FullInfo m_data;
};
