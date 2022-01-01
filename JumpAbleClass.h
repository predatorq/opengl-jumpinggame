#pragma once
#include"myglwidget.h"
class JumpAbleClass
{

public:

	JumpAbleClass() {}
	~JumpAbleClass() {}

	void jump(float x, float z);
	float posX = 4;
	float posZ = 0;
	float posY = 2;
};