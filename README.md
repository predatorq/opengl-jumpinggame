# CGProject

Use OpenGL to reproduce a WeChat-like Jump game.

The project is made by VS2019, the sln file is the project main file which can be opened by Visual Studio.

The final project for CG course in SYSU.

## Description

- Jump is a mini-game on WeChat platform, with single player and multiplayer modes (up to 8 players). The game is played by long pressing the screen to operate the chess to accumulate power to jump, jumping to the platform counts as 1 point, jumping to the middle of the platform, then 2 points for the first time, 4 points for the second time, 6 points for the third time, 8 points for the fourth time, and so on, up to 16 times in a row.

- For this computer graphics assignment, we have simplified and changed the game to a certain extent

## Code Information

- Color: randomly generated.

- Illumination model settings:

```cpp
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 5.0 };
GLfloat light_position[] = { 1.0, 0.0, 1.0,0.0 };
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
```

- Chess: import by obj file.

- Action: parabola

```cpp
			onJump = true;
			bool onOrDrop = false;  // true means drop 
			do{
				if (cubeList.at(cubeCount+1).nextP) {
					jumper->posX += xOrZSpeed;
					preMove += xOrZSpeed;
					jumper->posY += ySpeed;
					update();
					ySpeed -= 0.1;
					sleep(10);
				}
				else {...}
			} while (jumper->posY >= 2.0f);
```

- Player Feedback: When the player holds down the K key, the jump buildup process adds to the animation *the vertical compression* of the pieces gives the player feedback on the game.

```cpp
        // using QT
        void  MyGLWidget::keyPressEvent(QKeyEvent *eventt) {
	        switch (eventt->key()) {
	        case Qt::Key_K:
		        ss+=0.2;
		        break;
	        }
        }
```
