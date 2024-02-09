#include "Vector2.h"
#include <cmath>

// �R���X�g���N�^
Vector2::Vector2()
{
	x = 0;
	y = 0;
}
Vector2::Vector2(float setX, float setY)
{
	x = setX;
	y = setY;
}

Vector2* Vector2::Add(Vector2* val) {
	Vector2 calc = Vector2((this->x + val->x), (this->y + val->y));
	return &calc;
}
Vector2* Vector2::Add(float valX, float valY) {
	Vector2 calc = Vector2((this->x + valX), (this->y + valY));
	return &calc;
}
Vector2* Vector2::Sub(Vector2* val) {
	Vector2 calc = Vector2((this->x - val->x), (this->y - val->y));
	return &calc;
}
Vector2* Vector2::Sub(float valX, float valY) {
	Vector2 calc = Vector2((this->x - valX), (this->y - valY));
	return &calc;
}
Vector2* Vector2::Multi(Vector2* val) {
	Vector2 calc = Vector2((this->x * val->x), (this->y * val->y));
	return &calc;
}
Vector2* Vector2::Multi(float val) {
	Vector2 calc = Vector2((this->x * val), (this->y * val));
	return &calc;
}
Vector2* Vector2::Div(Vector2* val) {
	Vector2 calc = Vector2((this->x / val->x), (this->y / val->y));
	return &calc;
}
Vector2* Vector2::Div(float val) {
	Vector2 calc = Vector2((this->x / val), (this->y / val));
	return &calc;
}

float Vector2::Distance(Vector2* point) {
	// �e���̒������Z�o
	float disX = point->x - this->x;
	float disY = point->y - this->y;
	// �}�C�i�X���폜
	disX *= disX;
	disY *= disY;
	
	// �����Z�o
	float distance = sqrt(disX + disY);

	return distance;
}
Vector2* Vector2::Normalize() {
	Vector2 origin = VECTOR_ZERO;
	// �����Z�o
	float distance = Distance(&origin);
	// �ԋp�p
	Vector2 calc = *this;
	// ���K��
	calc = *calc.Div(distance);

	return calc.Multi(&calc);
}