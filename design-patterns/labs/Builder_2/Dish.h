#pragma once

#include<string>

class Dish
{
public:
  Dish (const std::string name, const float callories) :
    m_name(name),
    m_left(100),
    m_callories(callories)
  {}

  const std::string& Name() const  {return m_name;}
  float PercentLeft () const {return m_left;}
  float Callories() const {return m_callories;}

  void Bite (const float howMuch) {m_left -= howMuch;}

protected:
  std::string m_name;
  float m_left;
  float m_callories;
};

