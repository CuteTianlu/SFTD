#pragma once

#include "Component.h"

class Camera : public Component {
public:
	float fov = 70.0f;
	virtual void Update() const override;
};