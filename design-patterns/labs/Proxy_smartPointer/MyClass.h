#pragma once

#include<iostream>

class MyClass
{
public:
  MyClass (std::string name) : m_name (name)  {std::cout<<"Constructing object "<<m_name<<"\n";}
  ~MyClass() {std::cout<<"Destroying object "<<m_name<<"\n";}

  void print () {std::cout<<"This is "<<m_name<<"\n";}

  
  std::string m_name;
};
