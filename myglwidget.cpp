#include "MyGLWidget.h"

/*###################################################
##  函数: 
##  函数描述：
##  参数描述：
#####################################################*/

ObjLoader::ObjLoader(string filename)
{
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		if (line.substr(0, 2) == "vt")
		{

		}
		else if (line.substr(0, 2) == "vn")
		{

		}
		else if (line.substr(0, 1) == "v")
		{
			vector<GLfloat> Point;
			GLfloat x, y, z;
			istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;
			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			vSets.push_back(Point);

		}
		else if (line.substr(0, 1) == "f")
		{
			vector<GLint> vIndexSets;
			GLint u, v, w;
			istringstream vtns(line.substr(2));
			vtns >> u; vtns >> v; vtns >> w;
			vIndexSets.push_back(u - 1);
			vIndexSets.push_back(v - 1);
			vIndexSets.push_back(w - 1);
			fSets.push_back(vIndexSets);
		}
		else if (line.substr(0, 1) == "#")
		{

		}
		else
		{

		}
	}
	file.close();
}



void ObjLoader::Draw() {
	//glBegin(GL_LINES);
	//for (int i = 0, num = F.size(); i < num; ++i) {
	//	for (int j = 0, n = F[i].size(); j < n; ++j) {
	//		glVertex3dv(V[F[i][j]].data());
	//		glVertex3dv(V[F[i][(j + 1) % n]].data());
	//	}
	//}
	//glEnd();

	glBegin(GL_TRIANGLES);//开始绘制
	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//三个顶点
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		}
		else {
			GLint firstVertexIndex = (fSets[i])[0];//取出顶点索引
			GLint secondVertexIndex = (fSets[i])[1];
			GLint thirdVertexIndex = (fSets[i])[2];

			SV1[0] = (vSets[firstVertexIndex])[0];//第一个顶点
			SV1[1] = (vSets[firstVertexIndex])[1];
			SV1[2] = (vSets[firstVertexIndex])[2];

			SV2[0] = (vSets[secondVertexIndex])[0]; //第二个顶点
			SV2[1] = (vSets[secondVertexIndex])[1];
			SV2[2] = (vSets[secondVertexIndex])[2];

			SV3[0] = (vSets[thirdVertexIndex])[0]; //第三个顶点
			SV3[1] = (vSets[thirdVertexIndex])[1];
			SV3[2] = (vSets[thirdVertexIndex])[2];


			GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
			//(x2-x1,y2-y1,z2-z1)
			vec1[0] = SV1[0] - SV2[0];
			vec1[1] = SV1[1] - SV2[1];
			vec1[2] = SV1[2] - SV2[2];

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = SV1[0] - SV3[0];
			vec2[1] = SV1[1] - SV3[1];
			vec2[2] = SV1[2] - SV3[2];

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

			glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
			glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
		}
	}
	glEnd();
}

/*###################################################
##  函数: MyGLWidget
##  函数描述：初始化画图类
##  参数描述：
##		parent 父类指针
#####################################################*/
MyGLWidget::MyGLWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{
	jumper = new JumpAbleClass();
	ifstream ifile("chess.obj");
	obj = LoadOBJ(ifile);
	int count = 0;
	for (int i = 0; i < 4; i++) { //初始化四个方块
		JumpCubeClass temp;
		temp.posX = count + 4;
		temp.posZ = 0;
		count += 4;
		temp.nextP = true;
		cubeList.insert(cubeList.end(), temp);
	}
}

/*###################################################
##  函数: initializeGL
##  函数描述：初始化显示向量
##  参数描述：无
#####################################################*/
void MyGLWidget::initializeGL(){

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //黑色背景
    glShadeModel(GL_SMOOTH);              //启用阴影平滑

    glClearDepth(1.0);                                 //设置深度缓存
    glEnable(GL_DEPTH_TEST);                           //启用深度测试
    glDepthFunc(GL_LEQUAL);                            //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //告诉系统对透视进行修正

    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};   //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};   //漫散光参数
    GLfloat LightPosition[] = {2.0f, 3.0f, -6.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);      //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);      //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);    //设置光源位置
    glEnable(GL_LIGHT1);                                 //启动一号光源
    glEnable(GL_LIGHTING);                               //启动一号光源
    setList();
}


/*###################################################
##  函数: resizeGL
##  函数描述：当显示窗口改变的时候，修改view矩阵
##  参数描述：
##      w 是新窗口的宽度
##		h 是新窗口的高度
#####################################################*/
void MyGLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, (GLint)w, (GLint)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect;
	glViewport(0, 0, w, h);

	if (w >= h) {
		aspect = w / h;
		glOrtho(-10 * aspect, 10 * aspect, -10, 10, -10, 100);
	}
	else {
		aspect = h / w;
		glOrtho(-10, 10, -10 * aspect, 10 * aspect, -10, 10);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*###################################################
##  函数: setList
##  函数描述：初始化两个显示列表，一个底下的平台一个玩家本身
##  参数描述：无
#####################################################*/
void MyGLWidget::setList() {
	m_box = glGenLists(2);
	glNewList(m_box, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)  
	glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)  
	glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)  
	glNormal3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)  
	glNormal3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)  
	glNormal3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)  
	glNormal3f(1.0f, 1.0f, 1.0f);                   //右下(顶面) 


	glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)  
	glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)  


	glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)  
	glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)  
	glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)  
	glNormal3f(1.0f, 1.0f, 1.0f);                   //右上(前面)  
	glNormal3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)  
	glNormal3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)  
	glNormal3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

	glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)  
	glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)  


	glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)  
	glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)  
	glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)  
	glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)  


	glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)  
	glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)  
	glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)  
	glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)  
	glNormal3f(1.0f, 1.0f, -1.0f);                  //右上(右面)  
	glNormal3f(1.0f, 1.0f, 1.0f);                   //左上(右面)  
	glNormal3f(1.0f, -1.0f, 1.0f);                  //左下(右面)  
	glNormal3f(1.0f, -1.0f, -1.0f);                 //右下(右面)  
	glEnd();
	glEndList();

	s_box = m_box + 1;
	glNewList(s_box, GL_COMPILE);
	glScalef(0.3, 0.3, 0.3);
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < this->obj.size(); i++) {
		glVertex3f(obj[i].point[0], obj[i].point[1], obj[i].point[2]);
		glNormal3f(obj[i].normal[0], obj[i].normal[1], obj[i].normal[2]);
	}
	glEnd();
	glEndList();

}

/*###################################################
##  函数: paintGL
##  函数描述：update调用
##  参数描述：无
#####################################################*/
void MyGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存  

	for (iter = cubeList.begin(); iter != cubeList.end(); iter++) {

		GLfloat mat_ambient[] = { iter->GetColor(0), iter->GetColor(1), iter->GetColor(2), 1.0 };
		GLfloat mat_diffuse[] = { iter->GetColor(0), iter->GetColor(1), iter->GetColor(2), 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 5.0 };

		GLfloat light_position[] = { 1.0, 0.0, 1.0,0.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		JumpCubeClass tCube = *iter;
		glLoadIdentity();
		gluLookAt(-1, 3, 5, 0.0, 0, 0, 0, 1, 0);
		glRotatef(30, 0.0f, 1.0f, 0.0f);
		glTranslatef(tCube.posX - 6, 0, tCube.posZ);
		glTranslatef(-offsetX, 0, -offsetZ);

		glCallList(m_box);
	}

	glLoadIdentity();
	gluLookAt(-1, 3, 5, 0.0, 0, 0, 0, 1, 0);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
	glTranslatef(jumper->posX - 6, jumper->posY, jumper->posZ);
	glTranslatef(-offsetX, 0, -offsetZ);

	glCallList(s_box);

}

/*###################################################
##  函数: keyPreeeEvent
##  函数描述：检测按下的按键
##  参数描述：eventt传入按键事件，获取键位
#####################################################*/
void  MyGLWidget::keyPressEvent(QKeyEvent* eventt) {
	switch (eventt->key()) {
	case Qt::Key_K:
		ss += float(0.2);
		break;
	}
}

void sleep(unsigned int msec)
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/*###################################################
##  函数: keyReleaseEvent
##  函数描述：松开按键，处理跳一跳过程
##  参数描述：eventt传入按键事件，获得松开的是哪个按键
#####################################################*/
void  MyGLWidget::keyReleaseEvent(QKeyEvent* eventt) {
	switch (eventt->key()) {
	case Qt::Key_K:
		if (onJump) {
			return;
		}
		if (!eventt->isAutoRepeat()) {
			onJump = true;
			float xOrZSpeed = ss / 10;
			if (xOrZSpeed > 0.5) {
				xOrZSpeed = 0.5f;
			}
			float ySpeed = float(1.2);
			float preMove = float(0.0);
			bool onOrDrop = false;//true means drop 

			do {// 这是没有掉下去的情况
				if (cubeList.at(cubeCount + 1).nextP) {//x轴
					jumper->posX += xOrZSpeed;//移动方块
					preMove += xOrZSpeed;
					jumper->posY += ySpeed;
					update();
					ySpeed -= float(0.1);
					sleep(10);
				}
				else {
					jumper->posZ += xOrZSpeed;
					preMove += xOrZSpeed;
					jumper->posY += ySpeed;
					update();
					ySpeed -= float(0.1);
					sleep(10);
				}
			} while (jumper->posY >= 2.0f);

			if (cubeList.at(cubeCount + 1).nextP) {
				if ((jumper->posX - cubeList.at(cubeCount).posX) <= 1) {

					onOrDrop = false;
				}
				else {
					if (((jumper->posX - cubeList.at(cubeCount + 1).posX) <= 1 && (jumper->posX - cubeList.at(cubeCount + 1).posX) > 0) || ((cubeList.at(cubeCount + 1).posX - jumper->posX) <= 1) && (cubeList.at(cubeCount + 1).posX - jumper->posX) > 0) {
						
						onOrDrop = false;
						cubeCount++;
						JumpCubeClass last = cubeList.at(cubeList.size() - 1);
						JumpCubeClass newCube;
						newCube.ranPOS(last.posX, last.posZ);
						cubeList.insert(cubeList.end(), newCube);
					}
					else {
						onOrDrop = true;
					}
				}
			}
			else {
				if ((jumper->posZ - cubeList.at(cubeCount).posZ) <= 1) {
					onOrDrop = false;
				}
				else {
					if (((jumper->posZ - cubeList.at(cubeCount + 1).posZ) <= 1 && (jumper->posZ - cubeList.at(cubeCount + 1).posZ) > 0) || ((cubeList.at(cubeCount + 1).posZ - jumper->posZ) <= 1) && (cubeList.at(cubeCount + 1).posZ - jumper->posZ) > 0) {
						onOrDrop = false;
						cubeCount++;
						JumpCubeClass last = cubeList.at(cubeList.size() - 1);
						JumpCubeClass newCube;
						newCube.ranPOS(last.posX, last.posZ);
						cubeList.insert(cubeList.end(), newCube);
					}
					else {
						onOrDrop = true;
					}
				}
			}
			if (onOrDrop) {
				do {
					//我不管
					jumper->posY += ySpeed;
					update();
					ySpeed -= float(0.1);
					sleep(10);
				} while (jumper->posY >= 0.0f);
				sleep(1000);
				if (cubeList.at(cubeCount + 1).nextP) {

					jumper->posX = cubeList.at(cubeCount).posX;
					ss = 0.0;
					jumper->posY = 2;
					update();
					onOrDrop = false;
					onJump = false;
					break;
				}
				else {
					jumper->posZ = cubeList.at(cubeCount).posZ;
					ss = 0.0;
					jumper->posY = 2;
					update();
					onOrDrop = false;
					onJump = false;
					break;
				}
			}


			ss = 0.0;
			jumper->posY = 2;
			if (cubeList.at(cubeCount + 1).nextP) {//移动镜头
				float tempOffset = offsetX + preMove;
				while (offsetX <= tempOffset) {
					offsetX += float(0.1);
					update();
					sleep(1);
				}
			}
			else {
				float tempOffset = offsetZ + preMove;
				while (offsetZ <= tempOffset) {
					offsetZ += float(0.1);
					update();
					sleep(1);
				}
			}



			onJump = false;
		}

		break;
	}
}