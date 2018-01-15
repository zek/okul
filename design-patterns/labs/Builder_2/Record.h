#pragma once

#include<string>


class Record
{
public:
  Record (const std::string name, const float price, const float tax) :
    m_name (name),
    m_price (price),
    m_tax (tax)
  {
  }

  const std::string& Name() const {return m_name;}
  const float Price() const {return m_price;}
  const float Tax() const {return m_tax;}

protected:
  std::string m_name;
  float m_price;
  float m_tax;
};
