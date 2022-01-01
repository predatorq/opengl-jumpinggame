#include "JumpCubeClass.h"
#include<ctime>

JumpCubeClass::JumpCubeClass(GLfloat* Color){
	if (Color == nullptr){
		this->color[0] = 1.0;
		this->color[1] = 1.0;
		this->color[2] = 0.0;
	}else{
		for(int i=0;i < 3;i++){
			this->color[i] = Color[i];
		}
	}
}

GLfloat JumpCubeClass::GetColor(int index){
	return this->color[index];
}

void JumpCubeClass::ranPOS(int x, int z) {
	srand((unsigned)time(NULL));
	int xOrz = rand() % 2;
	if (xOrz == 0) {
		nextP = true;//x轴方向
		posZ = z;
		posX = x + rand() % 4 + 3;

	}
	else {
		nextP = false;//z轴方向
		posX = x;
		posZ = z + rand() % 4 + 3;
	}
	for (int i=0;i<3;i++){
		this->color[i] = (float)(rand() % 3) + (float)0.1;
	}
}