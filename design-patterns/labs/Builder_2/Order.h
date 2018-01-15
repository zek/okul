#pragma once

#include"Record.h"
#include<list>
#include<iostream>

class Order
{
public:
  ~Order () {    
    for (Record* rec : m_records)
      delete rec;
  }

  void Print () const {
    for (const Record* rec : m_records)
      std::cout<<rec->Name()<<"\t"<<rec->Price()<<"\t"<<rec->Tax()<<"\n";
  }

  float TotalPrice () const {
    float sum = 0;
    for (const Record* rec : m_records)
      sum += rec->Price();
    return sum;
  }
  
  float TotalTax () const {
    float sum = 0;
    for (const Record* rec : m_records)
      sum += rec->Tax();
    return sum;
  }

  void AddRecord(Record* rec) {
    m_records.push_back(rec);
  }

protected:
  std::list<Record*> m_records;
};
