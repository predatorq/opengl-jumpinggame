#include "myglwidget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGLWidget w;
	w.setWindowTitle("Project");
    w.resize(600, 600);
    w.show();
    return a.exec();
}
