#include "Racket.h"

void Racket::setSize(unsigned int s){
  this->size = s;
}

void Racket::setPosition(const Vector2D& pos){
  this->position = pos;
}

unsigned int Racket::getSize(){
  return this->size;
}

Vector2D Racket::getPosition(){
  return this->position;
}
