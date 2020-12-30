#include <vector>
#include <string>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

const float AxisSize = 10000;
float tam = 2, 
      alt = 3.0;

void Init();
void OnDraw();
void SpecialKeys(int key,int x,int y);

void prepara_textura(char *file, GLuint *tex_id);
void dibuja(void);
void libera_textura(GLuint *tex_id);


// Identificadores de texturas
GLuint textura_id1,  // Abeto 
       textura_id2,  // Copo
       textura_id3;  // Tronco

// Abeto
GLfloat abeto[] = {-tam,0.0,tam, tam,0.0,tam, 0,alt,0,
                   tam,0.0,tam, tam,0.0,-tam, 0,alt,0,
                   tam,0.0,-tam, -tam,0.0,-tam, 0,alt,0,
                   -tam,0.0,-tam, -tam,0.0,tam, 0,alt,0};

GLfloat tex_abeto[] =  {0.0,1.0, 1.0,1.0, 0.5,0.0,
                        0.0,1.0, 1.0,1.0, 0.5,0.0,
                        0.0,1.0, 1.0,1.0, 0.5,0.0,
                        0.0,1.0, 1.0,1.0, 0.5,0.0};


// Copo 
GLfloat copo[] = {0.0,0.0,0.0, 1.0,0.0,0.0, 1.0,1.0,0.0, 0.0,1.0,0.0,
                  0.0,0.0,0.0, 0.0,-1.0,0.0, 1.0,-1.0,0.0, 1.0,0.0,0.0,
                  0.0,0.0,0.0, -1.0,0.0,0.0, -1.0,-1.0,0.0, 0.0,-1.0,0.0,
                  0.0,0.0,0.0, 0.0,1.0,0.0, -1.0,1.0,0.0, -1.0,0.0,0.0};
   
GLfloat tex_copo[] = {1.0, 1.0, 0.0,1.0, 0.0,0.0, 1.0,0.0,
                      1.0, 1.0, 1.0,0.0, 0.0,0.0, 0.0,1.0,
                      1.0, 1.0, 0.0,1.0, 0.0,0.0, 1.0,0.0,
                      1.0, 1.0, 1.0,0.0, 0.0,0.0, 0.0,1.0};

float ancho = 0.8,
      alto = 3.0;
// Tronco
GLfloat tronco[] = {ancho/2,0.0,-ancho/2, ancho/2,0.0,ancho/2, ancho/2,-alto,ancho/2, ancho/2,-alto,-ancho/2,
                    -ancho/2,0.0,-ancho/2, ancho/2,0.0,-ancho/2, ancho/2,-alto,-ancho/2, -ancho/2,-alto,-ancho/2,
                    -ancho/2,0.0,ancho/2, -ancho/2,0.0,-ancho/2, -ancho/2,-alto,-ancho/2, -ancho/2,-alto,ancho/2,
                    ancho/2,0.0,ancho/2, -ancho/2,0.0,ancho/2, -ancho/2,-alto,ancho/2, ancho/2,-alto,ancho/2};

GLfloat tex_tronco[] = {0.0,0.0, 0.0,1.0, 1.0,0.0, 1.0,1.0,
                        0.0,0.0, 0.0,1.0, 1.0,0.0, 1.0,1.0,
                        0.0,0.0, 0.0,1.0, 1.0,0.0, 1.0,1.0,
                        0.0,0.0, 0.0,1.0, 1.0,0.0, 1.0,1.0};

float latitud = 0.0, 
      longitud = 0.0, 
      radio = 24.0;


void Init(int argc, char **argv)
{
   //Initialize GLUT windows manager
   //Create the window
   glutInit(&argc, argv);
   glutInitWindowSize(800,600);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("P4");

   glEnable(GL_DEPTH_TEST);
   //glEnable(GL_COLOR_MATERIAL);
   glMatrixMode(GL_PROJECTION);
   gluPerspective( 40.0, 800/600.0f, 0.1, 150);
  
   prepara_textura("images/abeto.jpg", &textura_id1);
   prepara_textura("images/copo_trozo.jpg", &textura_id2);
   prepara_textura("images/tronco.jpg", &textura_id3);
}


void draw_axis()
{
   glLineWidth(2);
   glBegin(GL_LINES);
      // eje X, color rojo
      glColor3f(1,0,0);
      glVertex3f(-AxisSize,0,0);
      glVertex3f(AxisSize,0,0);
      // eje Y, color verde
      glColor3f(0,1,0);
      glVertex3f(0,-AxisSize,0);
      glVertex3f(0,AxisSize,0);
      // eje Z, color azul
      glColor3f(0,0,1);
      glVertex3f(0,0,-AxisSize);
      glVertex3f(0,0,AxisSize);
   glEnd();
   glLineWidth(1);
   glColor3f(1,1,1);
}


void OnDraw(void)
{
   // Cámara orbital
   float observador[3];
   float phir,thetar;
   phir=latitud*M_PI/180.0; 
   thetar=longitud*M_PI/180.0;
   observador[0]=radio*sin(thetar)*cos(phir);
   observador[1]=radio*sin(phir);
   observador[2]=radio*cos(phir)*cos(thetar);

   // Cleaning the screen
   glClearColor(0.5,0.5,0.5,1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Define view
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // eye position -> observador
   // target -> (0,0,0)
   // define positive Y axis  -> (0.0, 1.0, 0.0)		
   gluLookAt (observador[0],observador[1],observador[2],0.0,0.0,0.0,0.0,1.0,0.0);

   draw_axis();
   
   // Put your code here to draw objects
   dibuja();

   // No delete this line
   glutSwapBuffers();
}


void SpecialKeys(int key,int x,int y)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:longitud +=2.0;break;
      case GLUT_KEY_RIGHT:longitud -=2.0;break;
      case GLUT_KEY_UP:latitud +=2.0;break;
      case GLUT_KEY_DOWN:latitud -=2.0;break;
      case GLUT_KEY_PAGE_UP:radio +=1.0;break;
      case GLUT_KEY_PAGE_DOWN:radio -=1.0;if (radio<1) radio=1;break;
	}
   glutPostRedisplay();
}


void prepara_textura (char *file, GLuint *tex_id )
{
   vector<unsigned char> data; 
   CImg<unsigned char> image;

   image.load(file);

   // empaquetamos bien los datos
   for (long y = 0; y < image.height(); y ++)
      for (long x = 0; x < image.width(); x ++)
      {
         unsigned char *r = image.data(x, y, 0, 0);
         unsigned char *g = image.data(x, y, 0, 1);
         unsigned char *b = image.data(x, y, 0, 2);
         data.push_back(*r);
         data.push_back(*g);
         data.push_back(*b);
      }

   glGenTextures(1, tex_id);
   glBindTexture(GL_TEXTURE_2D, *tex_id);

   //glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // Transfiere los datos a GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}


void dibuja (void)
{
   glEnable(GL_TEXTURE_2D);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

   glActiveTexture(GL_TEXTURE0);
   
   // Abeto
   glBindTexture(GL_TEXTURE_2D, textura_id1);
   glVertexPointer(3, GL_FLOAT, 0, abeto);
   glTexCoordPointer(2, GL_FLOAT, 0, tex_abeto);
   
      // Parte inferior del abeto
   glColor3f(0.6,0.6,0.6);
   glDrawArrays(GL_TRIANGLES, 0, 12);

      // Parte superior del abeto
   glColor3f(1.0,1.0,1.0);
   glPushMatrix();
      glTranslatef(0.0,2.5,0.0);
      glScalef(0.6,0.6,0.6);
      glDrawArrays(GL_TRIANGLES, 0, 12);
   glPopMatrix();

   // Copo
   glBindTexture(GL_TEXTURE_2D, textura_id2);
   glVertexPointer(3, GL_FLOAT, 0, copo);
   glTexCoordPointer(2, GL_FLOAT, 0, tex_copo);

   glPushMatrix();
      glTranslatef(0.0,4.8,0.0);
      glScalef(0.5,0.5,0.5);
      glDrawArrays(GL_QUADS, 0, 16);
   glPopMatrix();

   // Tronco
   glBindTexture(GL_TEXTURE_2D, textura_id3);
   glVertexPointer(3, GL_FLOAT, 0, tronco);
   glTexCoordPointer(2, GL_FLOAT, 0, tex_tronco);
   
   glDrawArrays(GL_QUADS, 0, 16);

   glDisableClientState(GL_VERTEX_ARRAY);
   glBindTexture(GL_TEXTURE_2D, 0);
   glDisable(GL_TEXTURE_2D);
}


void libera_textura (GLuint *tex_id)
{
   glDeleteTextures(1, tex_id);
}


int main(int argc, char** argv)
{
   Init(argc, argv);
   
   //Enter the callbacks
   glutDisplayFunc(OnDraw);
   glutSpecialFunc(SpecialKeys);

   glutMainLoop(); // begin the loop

   // LIBERA LA TEXTURA
   libera_textura(&textura_id1);
   return 0;
}
