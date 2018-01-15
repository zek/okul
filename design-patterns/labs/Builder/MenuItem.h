#pragma once

#include<string>
#include<iostream>

class MenuItem
{
public:
  void SetName (const std::string name) {m_name = name;}
  const std::string& Name() const {return m_name;}

  void SetPrice (const float price) {m_price = price;}
  const float Price() const {return m_price;}

  void SetTax (const float tax) {m_tax = tax;}
  const float Tax() const {return m_tax;}

  void SetIngredients (const std::string ingredients) {m_ingredients = ingredients;}
  std::string Ingredients () const {return m_ingredients;}

  void Print () const {std::cout<<m_name<<"\t"<<m_price<<"\t"<<m_tax<<"\t"<<m_ingredients<<"\n";}

protected:
  std::string m_name;
  float m_price;
  float m_tax;
  std::string m_ingredients;
};
