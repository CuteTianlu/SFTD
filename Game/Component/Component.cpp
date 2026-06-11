#include "../../h/Game/Component/Component.h"

void Component::VectorUpdate() {
	X += VectorX;
	Y += VectorY;
	X += VectorX;
	RotateX += VectorRotateX;
	RotateY += VectorRotateY;
	RotateZ += VectorRotateX;
}