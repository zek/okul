#pragma once

#include<string>
#include<fstream>
#include<vector>
#include <map>
#include <iostream>

using namespace std;


class FileDictionary{
 public:
    static std::vector<std::string>& get_fly(std::string dictionaryPath)
    {

        if (s_pool.find(dictionaryPath) == s_pool.end()){
          std::ifstream file(dictionaryPath);
          std::string word;
          while (file >> word)
            s_pool[dictionaryPath].push_back(word);

        }
        return s_pool.at(dictionaryPath);
    }

  private:
    static std::map<std::string, std::vector<std::string>> s_pool;
};

std::map<std::string, std::vector<std::string>> FileDictionary::s_pool = {};


class Dictionary
{
 public:
  Dictionary (std::string dictionaryPath, unsigned long long index) {
    m_index = index;
    m_dictionaryPath = dictionaryPath;
  }

  const std::string& Word() const {

    return FileDictionary::get_fly(m_dictionaryPath)[m_index];
}

  int Index() const {return m_index;}
  void SetIndex (int index) {m_index = index;}

 protected:
  unsigned long long m_index;
  std::string m_dictionaryPath;
};


