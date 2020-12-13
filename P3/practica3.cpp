#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos.h"


using namespace std;

// Tipos de objetos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ROTACION_PLY, CONO, CILINDRO, ESFERA, TANQUE, ROBOT} _tipo_objeto;
_tipo_objeto t_objeto = ROBOT;	// Tipo de objeto por defecto.
_modo   	 	 modo = POINTS; // Tipo de modo por defecto.

// Variables que definen la posición de la cámara en coordenadas polares
GLfloat Observer_distance,
 		Observer_angle_x,
 		Observer_angle_y;

// Variables que controlan la ventana y la transformación de perspectiva
GLfloat Size_x,
		Size_y,
		Front_plane,
		Back_plane;

// Variables que determinan la posición y tamaño de la ventana X
int Window_x = 50,
	Window_y = 50,
	Window_width = 450,
	Window_high = 450;

// Objetos
_cubo cubo;
_piramide piramide;
_objeto_ply  ply; 
_rotacion rotacion;
_rotacionply rotacionply;
_cono cono;
_cilindro cilindro;
_esfera esfera;
_tanque tanque;
_robot robot;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{
	switch (t_objeto)
	{
		case CUBO: 			cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);			break;
		case PIRAMIDE: 		piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);		break;
		case OBJETO_PLY: 	ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);			break;
		case ROTACION: 		rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);		break;
		case ROTACION_PLY: 	rotacionply.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);	break;
		case CONO: 			cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);			break;
		case CILINDRO: 		cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);		break;
		case ESFERA: 		esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);		break;
		case TANQUE:		tanque.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);		break;
		case ROBOT: 		robot.draw(modo,0.5,0.7,0.2,0.3,0.6,0.3,2);			break;
	}
}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
	clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
	float Aspect_ratio;
	Aspect_ratio=(float) Alto1/(float )Ancho1;
	Size_y=Size_x*Aspect_ratio;
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

bool lado_derecho = true; // Derecho true | Izquierdo false
float velocidad_articulacion = 1.0;
float velocidad_animacion_anterior = 0.0;
float velocidad_animacion = 0.0;
void normal_key(unsigned char Tecla1,int x,int y)
{
	switch (toupper(Tecla1))
	{
		case 'Q':exit(0);

		case '1': modo = POINTS;				break;
		case '2': modo = EDGES;					break;
		case '3': modo = SOLID;					break;
		case '4': modo = SOLID_CHESS;			break;

		case 'Z': t_objeto = ROTACION;			break;
		case 'X': t_objeto = PIRAMIDE;			break;
		case 'C': t_objeto = CUBO;				break;
		case 'V': t_objeto = CONO;				break;
		case 'B': t_objeto = CILINDRO;			break;
		case 'N': t_objeto = ESFERA;			break;
		case 'M': t_objeto = ROTACION;			break;
		case ',': t_objeto = OBJETO_PLY;		break;
		case '.': t_objeto = ROTACION_PLY;		break;


		case 'R': t_objeto = ROBOT;				break;
		case 'T': t_objeto = TANQUE;			break;
		
		case 'Y': lado_derecho = !lado_derecho;	break;

		case 'W':
			if (velocidad_articulacion != 0.0) 
			{
				velocidad_articulacion+=0.2;
				if (velocidad_articulacion > 3.0) velocidad_articulacion = 10.0;
			}
			break;
		case 'E':
			if (velocidad_articulacion != 0.0) 
			{
				velocidad_articulacion-=0.2;
				if (velocidad_articulacion < 0.2) velocidad_articulacion = 0.2;
			}
			break;

		case 'A': 
			if	(velocidad_animacion == 0.0) 
			{
				if (velocidad_animacion_anterior != 0.0)
					velocidad_animacion = velocidad_animacion_anterior;
				else
					velocidad_animacion = 1.0;
				robot = _robot();
			}
			else 
			{
				velocidad_animacion_anterior = velocidad_animacion;
				velocidad_animacion = 0.0;
			}
			break;
		case 'S':
			if (velocidad_animacion != 0.0) 
			{
				velocidad_animacion+=0.2;
				if (velocidad_animacion > 10.0) velocidad_animacion = 10.0;
			}
			break;
		case 'D':
			if (velocidad_animacion != 0.0) 
			{
				velocidad_animacion-=0.2;
				if (velocidad_animacion < 0.2) velocidad_animacion = 0.2;
			}
			break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{
	switch (Tecla1)
	{
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        
		case GLUT_KEY_F1:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho) 
					{
						robot.pierna_dch.giro_cadera+=3*velocidad_articulacion;
						if (robot.pierna_dch.giro_cadera > robot.pierna_dch.giro_cadera_max) 
							robot.pierna_dch.giro_cadera = robot.pierna_dch.giro_cadera_max;
					}
					else
					{
						robot.pierna_izd.giro_cadera+=3*velocidad_articulacion;
						if (robot.pierna_izd.giro_cadera > robot.pierna_izd.giro_cadera_max) 
							robot.pierna_izd.giro_cadera = robot.pierna_izd.giro_cadera_max;
					}					
					break;
				case TANQUE:
					tanque.giro_tubo+=1*velocidad_articulacion;
					if (tanque.giro_tubo > tanque.giro_tubo_max)
						tanque.giro_tubo = tanque.giro_tubo_max;
					break;
			}
			break;

		case GLUT_KEY_F2:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho) 
					{
						robot.pierna_dch.giro_cadera-=3*velocidad_articulacion;
						if (robot.pierna_dch.giro_cadera < robot.pierna_dch.giro_cadera_min) 
							robot.pierna_dch.giro_cadera = robot.pierna_dch.giro_cadera_min;
					}
					else
					{
						robot.pierna_izd.giro_cadera-=3*velocidad_articulacion;
						if (robot.pierna_izd.giro_cadera < robot.pierna_izd.giro_cadera_min) 
							robot.pierna_izd.giro_cadera = robot.pierna_izd.giro_cadera_min;
					}
					break;
				case TANQUE:
					tanque.giro_tubo-=1*velocidad_articulacion;
					if (tanque.giro_tubo < tanque.giro_tubo_min)
						tanque.giro_tubo = tanque.giro_tubo_min;
					break;
			}
			break;
		
		case GLUT_KEY_F3:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho) 
					{				
						robot.pierna_dch.giro_rodilla+=3*velocidad_articulacion;
						if (robot.pierna_dch.giro_rodilla > robot.pierna_dch.giro_rodilla_max)
							robot.pierna_dch.giro_rodilla = robot.pierna_dch.giro_rodilla_max;
					}
					else
					{
						robot.pierna_izd.giro_rodilla+=3*velocidad_articulacion;
						if (robot.pierna_izd.giro_rodilla > robot.pierna_izd.giro_rodilla_max)
							robot.pierna_izd.giro_rodilla = robot.pierna_izd.giro_rodilla_max;
					}
					break;
				case TANQUE: tanque.giro_torreta+=5*velocidad_articulacion; break;
			}
			break;
		
		case GLUT_KEY_F4:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho) 
					{
						robot.pierna_dch.giro_rodilla-=3*velocidad_articulacion;
						if (robot.pierna_dch.giro_rodilla < robot.pierna_dch.giro_rodilla_min)
							robot.pierna_dch.giro_rodilla = robot.pierna_dch.giro_rodilla_min;
					}	
					else
					{
						robot.pierna_izd.giro_rodilla-=3*velocidad_articulacion;
						if (robot.pierna_izd.giro_rodilla < robot.pierna_izd.giro_rodilla_min)
							robot.pierna_izd.giro_rodilla = robot.pierna_izd.giro_rodilla_min;
					}
					break;
				case TANQUE: tanque.giro_torreta-=5*velocidad_articulacion; break;

			}
			break;

		case GLUT_KEY_F5:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_hombro_x+=4*velocidad_articulacion;
						if (robot.brazo_dch.giro_hombro_x > robot.brazo_dch.giro_hombro_max_x)
							robot.brazo_dch.giro_hombro_x = robot.brazo_dch.giro_hombro_max_x;
					}
					else
					{
						robot.brazo_izd.giro_hombro_x+=4*velocidad_articulacion;
						if (robot.brazo_izd.giro_hombro_x > robot.brazo_izd.giro_hombro_max_x)
							robot.brazo_izd.giro_hombro_x = robot.brazo_izd.giro_hombro_max_x;
					}
					break;
			}
			break;

		case GLUT_KEY_F6:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_hombro_x-=4*velocidad_articulacion;
						if (robot.brazo_dch.giro_hombro_x < robot.brazo_dch.giro_hombro_min_x)
							robot.brazo_dch.giro_hombro_x = robot.brazo_dch.giro_hombro_min_x;
					}
					else
					{
						robot.brazo_izd.giro_hombro_x-=4*velocidad_articulacion;
						if (robot.brazo_izd.giro_hombro_x < robot.brazo_izd.giro_hombro_min_x)
							robot.brazo_izd.giro_hombro_x = robot.brazo_izd.giro_hombro_min_x;
					}
					break;
			}
			break;
	
		case GLUT_KEY_F7:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_hombro_z-=4*velocidad_articulacion;
						if (robot.brazo_dch.giro_hombro_z < -robot.brazo_dch.giro_hombro_max_z)
							robot.brazo_dch.giro_hombro_z = -robot.brazo_dch.giro_hombro_max_z;
					}
					else
					{
						robot.brazo_izd.giro_hombro_z+=4*velocidad_articulacion;
						if (robot.brazo_izd.giro_hombro_z > robot.brazo_izd.giro_hombro_max_z)
							robot.brazo_izd.giro_hombro_z = robot.brazo_izd.giro_hombro_max_z;
					}
					break;
			}
			break;
		
		case GLUT_KEY_F8:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_hombro_z+=4*velocidad_articulacion;
						if (robot.brazo_dch.giro_hombro_z > -robot.brazo_dch.giro_hombro_min_z)
							robot.brazo_dch.giro_hombro_z = -robot.brazo_dch.giro_hombro_min_z;	
					}
					else
					{
						robot.brazo_izd.giro_hombro_z-=4*velocidad_articulacion;
						if (robot.brazo_izd.giro_hombro_z < robot.brazo_izd.giro_hombro_min_z)
							robot.brazo_izd.giro_hombro_z = robot.brazo_izd.giro_hombro_min_z;
					}
					break;
			}
			break;

		case GLUT_KEY_F9:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_codo+=3*velocidad_articulacion;
						if (robot.brazo_dch.giro_codo > robot.brazo_dch.giro_codo_max)
							robot.brazo_dch.giro_codo = robot.brazo_dch.giro_codo_max;
					}
					else
					{
						robot.brazo_izd.giro_codo+=3*velocidad_articulacion;
						if (robot.brazo_izd.giro_codo > robot.brazo_izd.giro_codo_max)
							robot.brazo_izd.giro_codo = robot.brazo_izd.giro_codo_max;
					}
					break;
			}
			break;

		case GLUT_KEY_F10:
			switch (t_objeto)
			{
				case ROBOT:
					if (lado_derecho)
					{
						robot.brazo_dch.giro_codo-=3*velocidad_articulacion;
						if (robot.brazo_dch.giro_codo < robot.brazo_dch.giro_codo_min)
							robot.brazo_dch.giro_codo = robot.brazo_dch.giro_codo_min;
					}
					else
					{
						robot.brazo_izd.giro_codo-=3*velocidad_articulacion;
						if (robot.brazo_izd.giro_codo < robot.brazo_izd.giro_codo_min)
							robot.brazo_izd.giro_codo = robot.brazo_izd.giro_codo_min;
					}
					break;
			}
			break;

		case GLUT_KEY_F11:
			switch (t_objeto)
			{
				case ROBOT:
					robot.giro_cuello+=2*velocidad_articulacion;
					if(robot.giro_cuello > robot.giro_cuello_max) 
						robot.giro_cuello = robot.giro_cuello_max;
					break;
				
			}
			break;

		case GLUT_KEY_F12:
			switch (t_objeto)
			{
				case ROBOT:
					robot.giro_cuello-=2*velocidad_articulacion;
					if(robot.giro_cuello < robot.giro_cuello_min) 
						robot.giro_cuello = robot.giro_cuello_min;
					break;
				
			}
			break;

	}
	glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Size_x = 0.5;
	Size_y = 0.5;
	Front_plane = 1;
	Back_plane = 1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance = 4*Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Funcion de animacion
//***************************************************************************
int girando_cuello = 0;
int girando_pierna_izd = 0;
int girando_pierna_dch = 1;
int girando_brazo_izd = 1;
int girando_brazo_dch = 0;
int girando_codo_izd = 1;
int girando_codo_dch = 0;
void movimiento()
{
	if (velocidad_animacion != 0) 
	{
		if (girando_cuello == 0) 
		{
			robot.giro_cuello-=velocidad_animacion;
			if (robot.giro_cuello < robot.giro_cuello_min + 30.0)
			{
				robot.giro_cuello = robot.giro_cuello_min + 30.0;
				girando_cuello = 1;
			}
		}
		if (girando_cuello == 1) 
		{
			robot.giro_cuello+=velocidad_animacion;
			if (robot.giro_cuello > robot.giro_cuello_max - 30.0) 
			{
				
				robot.giro_cuello = robot.giro_cuello_max - 30.0;
				girando_cuello = 0;
			}
		}

		if (girando_pierna_izd == 0) 
		{
			robot.pierna_izd.giro_cadera-=velocidad_animacion;
			if (robot.pierna_izd.giro_cadera < robot.pierna_izd.giro_cadera_min + 40.0)
			{
				robot.pierna_izd.giro_cadera = robot.pierna_izd.giro_cadera_min + 40.0;
				girando_pierna_izd = 1;
			}
		}
		if (girando_pierna_izd == 1) 
		{
			robot.pierna_izd.giro_cadera+=velocidad_animacion;
			if (robot.pierna_izd.giro_cadera > robot.pierna_izd.giro_cadera_max - 10.0) 
			{
				
				robot.pierna_izd.giro_cadera = robot.pierna_izd.giro_cadera_max -10.0;
				girando_pierna_izd = 0;
			}
		}

		if (girando_pierna_dch == 0) 
		{
			robot.pierna_dch.giro_cadera-=velocidad_animacion;
			if (robot.pierna_dch.giro_cadera < robot.pierna_dch.giro_cadera_min + 40.0)
			{
				robot.pierna_dch.giro_cadera = robot.pierna_dch.giro_cadera_min + 40.0;
				girando_pierna_dch = 1;
			}
		}
		if (girando_pierna_dch == 1) 
		{
			robot.pierna_dch.giro_cadera+=velocidad_animacion;
			if (robot.pierna_dch.giro_cadera > robot.pierna_dch.giro_cadera_max - 10.0) 
			{
				
				robot.pierna_dch.giro_cadera = robot.pierna_dch.giro_cadera_max - 10.0;
				girando_pierna_dch = 0;
			}
		}

		if (girando_brazo_izd == 0) 
		{
			robot.brazo_izd.giro_hombro_x-=velocidad_animacion;
			if (robot.brazo_izd.giro_hombro_x < robot.brazo_izd.giro_hombro_min_x + 140.0)
			{
				robot.brazo_izd.giro_hombro_x = robot.brazo_izd.giro_hombro_min_x + 140.0;
				girando_brazo_izd = 1;
			}
		}
		if (girando_brazo_izd == 1) 
		{
			robot.brazo_izd.giro_hombro_x+=velocidad_animacion;
			if (robot.brazo_izd.giro_hombro_x > robot.brazo_izd.giro_hombro_max_x - 25.0)
			{
				robot.brazo_izd.giro_hombro_x = robot.brazo_izd.giro_hombro_max_x - 25.0;
				girando_brazo_izd = 0;
			}
		}

		if (girando_brazo_dch == 0) 
		{
			robot.brazo_dch.giro_hombro_x-=velocidad_animacion;
			if (robot.brazo_dch.giro_hombro_x < robot.brazo_dch.giro_hombro_min_x + 140.0)
			{
				robot.brazo_dch.giro_hombro_x = robot.brazo_dch.giro_hombro_min_x + 140.0;
				girando_brazo_dch = 1;
			}
		}
		if (girando_brazo_dch == 1) 
		{
			robot.brazo_dch.giro_hombro_x+=velocidad_animacion;
			if (robot.brazo_dch.giro_hombro_x > robot.brazo_dch.giro_hombro_max_x - 25.0)
			{
				robot.brazo_dch.giro_hombro_x = robot.brazo_dch.giro_hombro_max_x - 25.0;
				girando_brazo_dch = 0;
			}
		}

		if (girando_codo_izd == 0) 
		{
			robot.brazo_izd.giro_codo-=velocidad_animacion;
			if (robot.brazo_izd.giro_codo < robot.brazo_izd.giro_codo_min + 50.0)
			{
				robot.brazo_izd.giro_codo = robot.brazo_izd.giro_codo_min + 50.0;
				girando_codo_izd = 1;
			}
		}
		if (girando_codo_izd == 1) 
		{
			robot.brazo_izd.giro_codo+=velocidad_animacion;
			if (robot.brazo_izd.giro_codo > robot.brazo_izd.giro_codo_max)
			{
				robot.brazo_izd.giro_codo = robot.brazo_izd.giro_codo_max;
				girando_codo_izd = 0;
			}
		}

		if (girando_codo_dch == 0) 
		{
			robot.brazo_dch.giro_codo-=velocidad_animacion;
			if (robot.brazo_dch.giro_codo < robot.brazo_dch.giro_codo_min + 50.0)
			{
				robot.brazo_dch.giro_codo = robot.brazo_dch.giro_codo_min + 50.0;
				girando_codo_dch = 1;
			}
		}
		if (girando_codo_dch == 1) 
		{
			robot.brazo_dch.giro_codo+=velocidad_animacion;
			if (robot.brazo_dch.giro_codo > robot.brazo_dch.giro_codo_max)
			{
				robot.brazo_dch.giro_codo = robot.brazo_dch.giro_codo_max;
				girando_codo_dch = 0;
			}
		}

	}	

	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{
	// perfil 
	vector<_vertex3f> perfil2;
	_vertex3f aux;

	aux.x = 1.0; aux.y = 1.5; aux.z = 0.0;
	perfil2.push_back(aux);
	
	aux.x = 1.0; aux.y = -1.5; aux.z = 0.0;
	perfil2.push_back(aux);


	rotacion.parametros(perfil2, 6, 0);


	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x,Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width,Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("P3 IG");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);
	// asignación de la función llamada "movimiento" al evento correspondiente
	glutIdleFunc(movimiento);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.parametros(argv[1]);

	rotacionply.parametros(argv[1], 12);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
