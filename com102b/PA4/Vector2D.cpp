#include "Vector2D.h"

Vector2D& Vector2D::Set(float r, float s){
  this->x = r;
  this->y = s;
  return *this;
}

Vector2D& Vector2D::operator +=(const Vector2D& v){
  this->x += v.x;
  this->y += v.y;
  return *this;
}

Vector2D& Vector2D::operator -=(const Vector2D& v){
  this->x -= v.x;
  this->y -= v.y;
  return *this;
}

Vector2D& Vector2D::operator *=(float t){
  this->x *= t;
  this->y *= t;
  return *this;
}

Vector2D& Vector2D::operator /=(float t){
  this->x *= t;
  this->y *= t;
  return *this;
}

Vector2D Vector2D::operator -(void) const{
  return Vector2D(-this->x, -this->y);
}

Vector2D Vector2D::operator +(const Vector2D& v) const{
  return Vector2D(this->x + v.x, this->y + v.y);
}

Vector2D Vector2D::operator -(const Vector2D& v) const{
  return Vector2D(this->x - v.x, this->y - v.y);
}

Vector2D Vector2D::operator *(float t) const{
  return Vector2D(this->x * t, this->y * t);
}

Vector2D Vector2D::operator /(float t) const{
  return Vector2D(this->x / t, this->y / t);
}

bool Vector2D::operator ==(const Vector2D& v) const{
  return this->x == v.x && this->y == v.y;
}

bool Vector2D::operator !=(const Vector2D& v) const{
  return !(this->x == v.x && this->y == v.y);
}
