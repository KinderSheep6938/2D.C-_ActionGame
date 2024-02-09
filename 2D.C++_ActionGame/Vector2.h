#pragma once

#define VECTOR_ONE Vector2(1,1)
#define VECTOR_ZERO Vector2(0,0)

struct Vector2
{
	float x;
	float y;

public:
	// コンストラクタ
	Vector2();
	Vector2(float setX, float setY);

	//演算
	Vector2* Add(Vector2*);
	Vector2* Add(float, float);
	Vector2* Sub(Vector2*);
	Vector2* Sub(float, float);
	Vector2* Multi(Vector2*);
	Vector2* Multi(float);
	Vector2* Div(Vector2*);
	Vector2* Div(float);
	float Distance(Vector2* point);
	Vector2* Normalize();
	
};