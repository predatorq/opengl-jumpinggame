#include "JumpCubeClass.h"
#include<ctime>

/*###################################################
##  函数: JumpCubeClass
##  函数描述：给定颜色初始化方块颜色
##  参数描述：
##		*Color RGB三个颜色分量的数组
#####################################################*/
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

/*###################################################
##  函数: GetColor
##  函数描述：返回RGB颜色的分量
##  参数描述：
##		index 指定返回的分量是R、G、B的哪一个
#####################################################*/
GLfloat JumpCubeClass::GetColor(int index){
	return this->color[index];
}

/*###################################################
##  函数: ranPOS
##  函数描述：给定当前方块的位置，生成下一个方块的位置
##  参数描述：
##		x 当前方块在x轴的位置
##		z 当前方块在z轴的位置
#####################################################*/
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
	for (int i = 0; i < 3; i++) {
		color[i] = (float)rand() / 255.0;
		int temp = (int)color[i];
		color[i] -= temp;
		if (color[i] > 0.8)
			color[i] -= 0.1;
		if (color[i] < 0.2)
			color[i] += 0.1;
	}
}