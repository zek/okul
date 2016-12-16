#include "Ball.h"

void Ball::setPosition(const Vector2D& pos){
  this->position = pos;
}

void Ball::setDirection(Vector2D& dir){
  this->direction = dir;
}

void Ball::setVelocity(float vel){
  this->velocity = vel;
}

void Ball::setRadious(float rad){
  this->radius = rad;
}

void Ball::setColor(float R, float G, float B){
  this->color_r = R;
  this->color_g = G;
  this->color_b = B;
}

Vector2D Ball::getPosition(){
  return this->position;
}

Vector2D Ball::getDirection(){
  return this->direction;
}

float Ball::getVelocity(){
  return this->velocity;
}

float Ball::getRadious(){
  return this->radius;
}

float Ball::getRed(){
  return this->color_r;
}

float Ball::getGreen(){
  return this->color_g;
}

float Ball::getBlue(){
  return this->color_b;
}

Vector2D Ball::updatePosition(){
  Vector2D v = Vector2D(this->direction.x * this->velocity + this->position.x, this->direction.y * this->velocity + this->position.y);
  this->setPosition(v);
  return v;
}
