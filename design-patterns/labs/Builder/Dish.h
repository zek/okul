#pragma once

#include<string>
#include<iostream>
#include<list>

class Dish
{
public:
  Dish () : m_left(100) {}

  float PercentLeft () const {return m_left;}

  void SetName (const std::string name) {m_name = name;}
  const std::string& Name() const  {return m_name;}

  void SetCallories (const float cal) {m_callories = cal;}
  float Callories () const {return m_callories;}
  float CalloriesLeft() const {return m_callories*m_left/100;}

  void SetOrigin (const std::string origin) {m_origin = origin;}
  std::string Origin () const {return m_origin;}

  void SetReceipe (const std::string receipe) {m_receipe = receipe;}
  std::string Receipe () const {return m_receipe;}

  void SetIngredients (const std::list<std::string> ingredients) {m_ingredients = ingredients;}
  std::list<std::string> Ingredients () const {return m_ingredients;}

  void Bite (const float howMuch) {m_left -= howMuch;}

  void Print () const {std::cout<<m_name<<"\t"<<m_origin<<"\t"<<m_left<<"\t"<<m_callories<<"\t"<<m_receipe<<"\n";
    for (const std::string& str : m_ingredients )
      std::cout<<str<<" ";
    std::cout<<"\n";}

protected:
  std::string m_name;
  float m_left;
  float m_callories;
  std::string m_origin;
  std::string m_receipe;
  std::list<std::string> m_ingredients;
};

