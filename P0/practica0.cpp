#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>


void Ejes(int width)
{   
   glLineWidth(width);
   glBegin(GL_LINES);
      // Eje X
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
      // Eje Y
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, -1.0, 0.0);
      glVertex3f(0.0, 1.0, 0.0);   
   glEnd();       
}

void Circle (GLfloat radius, GLfloat cx, GLfloat cy, GLint n, GLenum mode) {
   if       (mode == GL_POINT) glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
   else if  (mode == GL_LINE)  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else if  (mode == GL_FILL)  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                       
   glBegin(GL_POLYGON);
      for (int i = 0; i < n; i++)
         glVertex2f(cx + radius * cos(2.0 * M_PI * i / n), cy + radius * sin(2.0 * M_PI * i / n));
   glEnd();
}

void Monigote()
{ 
   // Polígono que representa la cara rellena en color carne.
   glColor3f(1.0,0.8,0.6); // Color carne.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.20, 0.0, 0.0);
      glVertex3f(0.20, 0.0, 0.0);
      glVertex3f(0.20, 0.55, 0.0);
      glVertex3f(-0.20, 0.55, 0.0);
   glEnd(); 

   // Polígono que representa las líneas de alrededor de la cara en color negro.
   glLineWidth(1);
   glColor3f(0.0,0.0,0.0); // Color negro.
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2, 0.0, 0.0);
      glVertex3f(0.2, 0.0, 0.0);
      glVertex3f(0.2, 0.55, 0.0);
      glVertex3f(-0.2, 0.55, 0.0);
   glEnd();

   // Polígono que representa la nariz rellena de color ojo.
   glColor3f(1.0, 0.0, 0.0); // Color rojo.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.06, 0.17, 0.0);
      glVertex3f(0.06, 0.17, 0.0);
      glVertex3f(0.0, 0.275, 0.0);
   glEnd();

   // Círculos que representan los ojos rellenos de color azul.
   glColor3f(0.0, 0.0, 1.0); // Color azul.
   Circle(0.05, -0.08, 0.35, 20, GL_FILL);
   Circle(0.05, 0.08, 0.35, 20, GL_FILL);

   // Círculos y rectángulo que representan la boca rellenos de color naranja.
   glColor3f(1.0, 0.65, 0.0); // Color naranja.
   glBegin(GL_POLYGON);
      glVertex3f(-0.08, 0.12, 0.0);
      glVertex3f(-0.08, 0.07, 0.0);
      glVertex3f(0.08, 0.07, 0.0);
      glVertex3f(0.08, 0.12, 0.0);
   glEnd();
   Circle(0.025, -0.085, 0.095, 20, GL_FILL);
   Circle(0.025, 0.085, 0.095, 20, GL_FILL);

   // Polígonos que representan las orejas rellenas en color carne.
   glColor3f(1.0,0.8,0.6); // Color carne.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON); // Oreja izquierda.
      glVertex3f(-0.25, 0.35, 0.0);
      glVertex3f(-0.25, 0.16, 0.0);
      glVertex3f(-0.20, 0.16, 0.0);
      glVertex3f(-0.20, 0.35, 0.0);
   glEnd(); 
   glBegin(GL_POLYGON); // Oreja derecha.
      glVertex3f(0.25, 0.16, 0.0);
      glVertex3f(0.25, 0.35, 0.0);
      glVertex3f(0.20, 0.35, 0.0);
      glVertex3f(0.20, 0.16, 0.0);
   glEnd();

   // Polígonos que representan las líneas de alrededor de las orejas en color negro.
   glLineWidth(1);
   glColor3f(0.0,0.0,0.0); // Color negro.
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON); // Oreja izquierda.
      glVertex3f(-0.25, 0.35, 0.0);
      glVertex3f(-0.25, 0.16, 0.0);
      glVertex3f(-0.20, 0.16, 0.0);
      glVertex3f(-0.20, 0.35, 0.0);
   glEnd();
   glBegin(GL_POLYGON); // Oreja derecha.
      glVertex3f(0.25, 0.16, 0.0);
      glVertex3f(0.25, 0.35, 0.0);
      glVertex3f(0.20, 0.35, 0.0);
      glVertex3f(0.20, 0.16, 0.0);
   glEnd();

   // Polígonos que representan el ala y la copa del sombrero en color negro.
   glColor3f(0.0,0.0,0.0); // Color negro.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON); // Ala.
      glVertex3f(-0.28, 0.47, 0.0);
      glVertex3f(-0.28, 0.60, 0.0);
      glVertex3f(0.28, 0.60, 0.0);
      glVertex3f(0.28, 0.47, 0.0);
   glEnd();
   glBegin(GL_POLYGON); // Copa.
      glVertex3f(-0.2, 0.80, 0.0);
      glVertex3f(-0.2, 0.60, 0.0);
      glVertex3f(0.2, 0.60, 0.0);
      glVertex3f(0.2, 0.80, 0.0);
   glEnd();
}

static void Init()
{
   glShadeModel(GL_FLAT);
}

static void Reshape(int width, int height)
{
   glViewport(0, 0, (GLint)width, (GLint)height);
   glOrtho(-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display()
{
   glClearColor(0.5,0.5,0.5,0.0);
   glClear(GL_COLOR_BUFFER_BIT);  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}

static void Keyboard(unsigned char key, int x, int y)
{
   if (key == 27)
      exit(0);
}

int main( int argc, char **argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB);

   glutInitWindowPosition(20, 100);
   glutInitWindowSize(500, 500);
   glutCreateWindow("P0 IG");

   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop();

   return 0;
}

