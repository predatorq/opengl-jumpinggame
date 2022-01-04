#pragma once
#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "JumpCubeClass.h"
#include "JumpAbleClass.h"
#include "objUtils.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>


using namespace std;


class JumpCubeClass;
class JumpAbleClass;

class MyGLWidget : public QOpenGLWidget{
	Q_OBJECT

public:
	MyGLWidget(QWidget* parent = Q_NULLPTR);
	void setList();
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	bool onJump = false;
	int cubeCount = 0;
	float offsetX = 0;
	float offsetZ = 0;
	float ss = 0.0;
	GLuint m_box;
	GLuint s_box;
	vector<JumpCubeClass> cubeList;
	vector<JumpCubeClass>::iterator iter;
	JumpAbleClass* jumper;
	string filePath;
	vector<Vertex> obj;
	GLuint texture;
	int score = 0;

};



#endif // MYGLWIDGET_H