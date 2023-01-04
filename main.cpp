/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include <stdlib.h>
#include <windows.h>
#include <stdio.h>

#include <math.h>
#include<iostream>

#define DEG2RAD(d) ( (d) * M_PI/180. )

using namespace std;

int win1;
int win2;

void display();
void reshape(int w,int h);
void keyboard(unsigned char Key, int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void timer(int);

void DrawTriangle(float x,float y ,float sideTall){
      glBegin(GL_TRIANGLES);
      glVertex2f(x,y);
      glVertex2f(x+sideTall -0.1,y+sideTall*0.5);
      glVertex2f(x+sideTall -0.1,y-sideTall*0.5);
      glEnd();

}
 // #define DEG2RAD 3.14159/180.0
void DrawEllipse(float x,float y,float radiusX, float radiusY)
{
   int i;

   glBegin(GL_TRIANGLE_FAN);

   glVertex3f(x,y,0);

   for(i=0;i<360;i++)
   {
      float rad = i ;
      glVertex3f(x + cos(rad)*radiusX,
                  y + sin(rad)*radiusY,0);
   }
   glEnd();
}


void drawFish(float x,float y,float radiusX, float radiusY,float sideTall){
    DrawEllipse(x,y,radiusX, radiusY);
    DrawTriangle((x + radiusX),y,sideTall);
}

void draw3dFish(float x,float y,float radiusX, float radiusY,float sideTall){
    glPushMatrix();
    glTranslatef(x,y,0);
    for(float i = 0; i <= 180; i+=0.3){
    drawFish(0,0,radiusX,radiusY,sideTall);
    glRotatef(DEG2RAD(i),1,0,0);
  }
    glPopMatrix();
}




void DrawBall(float x , float y, float radius){
  glBegin(GL_TRIANGLE_FAN);
  glColor3ub(255,0,0);
  glVertex2f(x, y);
  for (int i = 0; i <= 360; i++){
       glVertex2f((x + (radius * cos(i))), y + radius * sin(i));
  }


  glEnd();
}


void DrawCircle(float x , float y, float radius){
  glBegin(GL_POINTS);
  for (float i = 0; i <= 360; i++){
       glVertex2f((x + (radius * cos(i))), y + radius * sin(i));
  }


  glEnd();
}

void Draw3dBall(float x , float y, float radius){
    glPushMatrix();
   for(float i = 0; i <= 180; i+=0.3){
    glRotatef(i,1,0,0);
    DrawCircle(x , y, radius);

  }
    glPopMatrix();

}
double tx = 0.0, ty = 0.0;
double direction = 0.0;


void DrawHemisphere(float x , float y, float radiusX , float radiusY){
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y,0);
 //   glPolygonMode(GL_FRONT, GL_FILL);

    float radian;
    for (float i = 0; i >= -180; i--){
       radian = i * M_PI / 180;
//       glVertex2f(x + radiusX * cos(i), y + radiusY * sin(i));
      glVertex3f(x + radiusX * cos(radian), y + radiusY * sin(radian),0);
  }
   glEnd();
}


void Draw3dHemisphere(float x , float y, float radiusX , float radiusY){
   glPushMatrix();
   glTranslated(x, y, 0);
   for(float i = -45; i <= 45; i+=0.3){
    glRotatef(DEG2RAD(i),1,0,0);
    DrawHemisphere(0,0,radiusX,radiusY);

  }
    glPopMatrix();
}





void Drawline(float x1 , float y1, float x2 , float y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
   glEnd();
}


float  ArmRotation= 0;
BOOLEAN add = true;







float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;

//------------------------------  reshapeFunc  ---------------------------------

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,2,50.0);
    //gluPerspective (40.0, (GLdouble)w / (GLdouble)h, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}


void drawQuad(){
 glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube


}

int translateX=0,translateY=0;
int translateX2=0,translateY2=0;

void OnMouseClick(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     //store the x,y value where the click happened
    exit(0);
  }
}

void keyboard(unsigned char Key, int x, int y){

    switch(Key){

        case 'd' :(translateX == 9) ? translateX : translateX++;
        break;

        case 'a' : (translateX == -11) ? translateX : translateX--;
        break;

        case 'w' :  (translateY - 10 == 0) ? translateY : translateY++;
        break;

        case 's' :  (translateY - 10 == -12) ? translateY : translateY--;
        break;

        case '8': (translateY2 == 6) ? translateY2 : translateY2++;
        break;

        case '5' : (translateY2 == -3) ? translateY2  :translateY2--;
        break;

        case '6': (translateX2 == 4) ? translateX2 :translateX2++;
        break;

        case '4':(translateX2 == -17) ? translateX2 : translateX2--;
        break;


        case 'f' : glutFullScreen();
        break;

        case 27 : exit(0);
        break;
    }
    cout << translateX << " " << translateX2 << " " << translateX - translateX2 <<"\n";
    cout << translateY << " " << translateY2 << " " << translateY - translateY2  <<"\n";

}

void idleFunc (void)
{
    zRotated += 1;
    glutPostRedisplay();
}

void texture (void){

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

  //  glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
  //  glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}



//----------------------------------  main  ------------------------------------
void init(){
    glClearColor(0.0,0.0,0.0,0.0);
}


int main (int argc, char **argv)
{
    glutInit               (&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // buffer mode
    glutInitWindowSize     (1000, 1000);
    glutInitWindowPosition (0, 0);
    glutCreateWindow       ("20103183 && 20102914");

    glClearColor (0.0, 0.0, 0.0, 0);


    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(OnMouseClick);
    glutTimerFunc(0,timer,0);
//  glutIdleFunc(idleFunc);
//	glutKeyboardFunc(processNormalKeys);
//	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

    init();


    glClearColor(0,0,0,1);
    texture(); // Lighting and textures

    init();

    glutMainLoop();
}

void drawCloud(){
    glColor3ub(255,255,255);
    glutSolidSphere(1.0, 50, 50);

    glTranslated(1, 0, 0);
    glutSolidSphere(1.0, 50, 50);
    glTranslated(-1, 1, 0);
    glutSolidSphere(1.0, 50, 50);
    glTranslated(1, 0, 0);
    glutSolidSphere(1.0, 50, 50);
    glTranslated(1, 0, 0);
    glutSolidSphere(1.0, 50, 50);
    glTranslated(1, 0, 0);
    glutSolidSphere(1.0, 50, 50);

}

float step=0;


int counter1 = 0;
int counter2 = 0;
void display()
{

    glPushMatrix();
   // win1 = glutGetWindow();
   // win2 = glutCreateSubWindow(win1,0, 0, 300, 300);
    glPopMatrix();




    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //printf("%d",translateX);

    glTranslated(0,0,-18);

    // DrawSun
    glPushMatrix();
    glTranslated(-7, 5, -1);
    glColor3ub(255,0,0);

    glutSolidSphere(1.0, 50, 50);

    glPopMatrix();


    glPushMatrix();
    glTranslated(7, 8, -1);

    drawCloud();
    glPushMatrix();
    glTranslated(-22, 0, 0);
    drawCloud();
    glPopMatrix();


    glPopMatrix();



    glPushMatrix();
     glColor4f(0, 0, 1, 0.5);

    // Draw square
    glTranslated(0,0,-1);
    //glColor3f(0, 0, 1);

    glBegin(GL_QUADS);
        glVertex3d(15,1,0);
        glVertex3d(-15,1,0);
        glVertex3d(-15,-15,0);
        glVertex3d(15,-15,0);


        glVertex3d(15,1,-4);
        glVertex3d(-15,1,-4);
        glVertex3d(-15,-15,-4);
        glVertex3d(15,-15,-4);


    glEnd();

    glPopMatrix();
    // End DrawSun
    glColor3ub(245,255,105);

   // glPushMatrix();
//    glTranslated(0,0,-1);
    // draw some fish

    draw3dFish(6 + translateX2,-6 + translateY2,0.7,0.5,0.4);

   // glPopMatrix();


    // translate for fish

    //DrawEllipse(5 ,5 , 1,2);
    glPushMatrix();


    // Draw boat
    // translate for boat

    glTranslated(translateX,0,0);
    glColor3ub(102, 51, 0);
    Draw3dHemisphere(0,-0.6,3.5,2);

    glPushMatrix();
    glLineWidth(8);

    // Draw ship sail


    Drawline(0,-0.6,0,4);
    glPopMatrix();
    glPushMatrix();
    glTranslated(1.5,2,0);
    glRotated(180,0,0,0);
    DrawTriangle(-1.9,0,3.5);
    glPopMatrix();


    // Draw stick man body
    glPushMatrix();
    glTranslated(-1,0,0);
    glColor3f(1,1,1);
    glLineWidth(2);
    Drawline(0,1,0,4);

    glPushMatrix();
    // Draw stick man legs
    glTranslatef(0,1,0);
    glRotatef(140,0,0,1);
    Drawline(0,0,0,2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,1,0);
    glRotatef(-140,0,0,1);
    Drawline(0,0,0,2);
    glPopMatrix();

// Draw stick man arms
    glPushMatrix();
    glTranslatef(0,2.8,0);
    glRotatef(140,0,0,1);
    Drawline(0,0,0,2);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,2.8,0.0001);



 //   glRotatef((-50 * ArmRotation - 40),0,0,1);
    Drawline(0,0,2.01,0);
    glPushMatrix();
    glTranslatef(2,0,0.0001);
    Drawline(0,0,0,-10 + translateY);

    glPopMatrix();
    glPopMatrix();

    // Draw Stick Man Head


    glPushMatrix();
    glColor3f(1,1,1);
    glPointSize(2);
    glTranslatef(0,4.8,0);
    glutSolidSphere(0.8, 50, 50);;
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    if(translateX - translateX2 == 5 && translateY - translateY2 == 1 ){
        translateX = 0;
        translateX2 = 0;
        translateY = 0;
        translateY2 = 0;
        counter1++;
        PlaySound(TEXT("mixkit-retro-game-notification-212.wav"), NULL, SND_ASYNC|SND_FILENAME);
        cout <<"the result is " << counter1 << " : " <<  counter2 ;
        }

    if(translateX2 == -17){
        translateX = 0;
        translateX2 = 0;
        translateY = 0;
        translateY2 = 0;
        counter2++;
        PlaySound("mixkit-retro-game-notification-212.wav", NULL, SND_ASYNC|SND_FILENAME);
        cout <<"the result is " << counter1 << " : " <<  counter2 ;
    }



    glutSwapBuffers();

}




void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);


}


