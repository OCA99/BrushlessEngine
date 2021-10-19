#pragma once

class float3 {
public:
	float3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	float3(float v) {
		this->x = v;
		this->y = v;
		this->z = v;
	}

	float3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float x, y, z;
};