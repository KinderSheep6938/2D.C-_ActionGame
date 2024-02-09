#include "Camera.h"
#include <iostream>

Camera::Camera(Player* pl, Block* bl) {
	pos = VECTOR_ZERO;
	playerPtr = pl;
	blockListPtr = bl;
}

void Camera::Scroll(Vector2* val) {
	// ˆÚ“®—Ê‰ÁŽZ
	pos = *pos.Add(val);

	playerPtr->GetCollider()->Translate(val);

	for (int i = 0;i < BLOCK_POOL;i++) {
		blockListPtr[i].GetCollider()->Translate(val);
	}
}