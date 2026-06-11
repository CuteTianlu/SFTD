#pragma once

struct vertex {
};

class Component {
public:
	float X = 0;
	float Y = 0;
	float Z = 0;
	float RotateX;
	float RotateY;
	float RotateZ;

public:
	float VectorX = 0;
	float VectorY = 0;
	float VectorZ = 0;
	float VectorRotateX = 0;
	float VectorRotateY = 0;
	float VectorRotateZ = 0;

public:
	virtual ~Component() = default;
	virtual void Update() const = 0;
	void VectorUpdate();

public:
	
};