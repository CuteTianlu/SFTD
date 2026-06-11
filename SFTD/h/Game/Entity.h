#pragma once

#include "Component/Component.h"

class Entity : public Component {
public:
	Entity();
public:
	float Friction = 0.5f;     //摩擦						1f = 地上动不了
	float AirFriction = 0.3f;		//空气摩擦				1f = 动不了
	float Quality = 1.5f;			//质量					1f = 1kg
	float Gravity = 0.5f;			//重力					1f = 每秒1米↓
	float Elasticity = 0.5f;			//弹性					1f = 完全反弹
};