#include <stdlib.h>
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <algorithm>

const float AXIS_SIZE = 5000;
typedef enum {POINTS, EDGES, SOLID_CHESS, SOLID, SELECT} _modo;

//*************
// _puntos3D //
//*************
class _puntos3D
{
	public:
		vector<_vertex3f> vertices;

		_puntos3D();
		void draw_puntos(float r, float g, float b, int grosor);	
};

//*****************
// _triangulos3D //
//*****************
class _triangulos3D: public _puntos3D
{
	public:
		vector<_vertex3i> caras;
		
		_triangulos3D();
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
		void draw_seleccion(float c);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//*********
// _cubo //
//*********
class _cubo: public _triangulos3D
{
	public:
		_cubo(float tam = 1.0);
};


//*************
// _piramide //
//*************
class _piramide: public _triangulos3D
{
	public:
		_piramide(float tam = 1.0, float al = 0.75);
};


//***************
// _objeto_ply //
//***************
class _objeto_ply: virtual public _triangulos3D
{
	public:
		_objeto_ply();
		int parametros(char *archivo);
};


//*************
// _rotacion //
//*************
class _rotacion: virtual public _triangulos3D
{ 
	int num;
	vector<_vertex3f> perfil;
	public:
		_rotacion();
		void parametros(vector<_vertex3f> perfil, int num, int tipo);
};


//*********
// _cono //
//*********
class _cono: public _rotacion
{ 
	public:
		_cono(float radio = 0.5, float altura = 1.0, int num = 20);
};


//*************
// _cilindro //
//*************
class _cilindro: public _rotacion
{ 
	public:
		_cilindro(float radio = 0.5, float altura = 1.0, int num = 20);
};


//***********
// _esfera //
//***********
class _esfera: public _rotacion
{ 
	public:
		_esfera(float radio = 0.5, int n = 20, int num = 20);
};


//****************
// _rotacionply //
//****************
class _rotacionply: public _rotacion, public _objeto_ply
{ 
	public:
		_rotacionply();
		void parametros(char *archivo, int num);
};


//***********
// _chasis //
//***********
class _chasis: public _triangulos3D
{
	protected:
		_rotacion rodamiento;
		_cubo base;
	
	public:
		float altura;

		_chasis();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//************
// _torreta //
//************
class _torreta: public _triangulos3D
{
	protected:
		_cubo base;
		_piramide parte_trasera;
	
	public:
		float altura;
		float anchura;

		_torreta();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//*********
// _tubo //
//*********
class _tubo: public _triangulos3D
{
	protected:
		_rotacion tubo_abierto; // caña del cañón

	public:
		_tubo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//***********
// _tanque //
//***********
class _tanque: public _triangulos3D
{
	protected:
		_chasis chasis;
		_torreta torreta;
		_tubo tubo;
	
	public:
		float giro_tubo;
		float giro_torreta;
		
		float giro_tubo_min;
		float giro_tubo_max;

		_tanque();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

//***********
// _pierna //
//***********
class _pierna: public _triangulos3D
{
	private:
		_esfera cadera;
		_cilindro superior;
		_esfera rodilla;
		_cilindro inferior;
		_cubo pie;

	public:
		float anchura;
		float altura;
		float profundidad;
	
		float giro_cadera;
		float giro_cadera_max;
		float giro_cadera_min;
		float giro_rodilla;
		float giro_rodilla_max;
		float giro_rodilla_min;

		_pierna(float anchura = 0.125, float altura = 1, float profundidad = 0.20);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//***********
// _tronco //
//***********
class _tronco: public _triangulos3D
{
	private:
		_cubo tronco;

	public:
		float anchura;
		float altura;
		float profundidad;

		_tronco(float anchura = 0.5, float altura = 0.75, float profundidad = 0.25);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//**********
// _brazo //
//**********
class _brazo: public _triangulos3D
{
	private:
		_esfera hombro;
		_cilindro superior;
		_esfera codo;
		_cilindro inferior;
		_esfera mano;

	public:
		float anchura;
		float altura;
		float profundidad;
	
		float giro_hombro_x;
		float giro_hombro_max_x;
		float giro_hombro_min_x;
		float giro_hombro_z;
		float giro_hombro_max_z;
		float giro_hombro_min_z;
		float giro_codo;
		float giro_codo_max;
		float giro_codo_min;

		_brazo(float anchura = 0.1, float altura = 0.8, float profundidad = 0.15);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//***********
// _cuello //
//***********
class _cuello: public _triangulos3D
{
	private:
		_cilindro cuello;

	public:
		float anchura;
		float altura;
		float profundidad;

		_cuello(float anchura = 0.15, float altura = 0.10, float profundidad = 0.10);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//***********
// _cabeza ///
//***********
class _cabeza: public _triangulos3D
{
	private:
		_cubo cabeza;

	public:
		float anchura;
		float altura;
		float profundidad;

		_cabeza(float anchura = 0.3, float altura = 0.35, float profundidad = 0.15);
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};

//************
// _robot //
//************
class _robot: public _triangulos3D
{
	private:
		_cabeza cabeza;
		_cuello cuello;
		_tronco tronco;

	public:
		_pierna pierna_izd;
		_pierna pierna_dch;
		_brazo brazo_izd;
		_brazo brazo_dch;

		float giro_cuello;
		float giro_cuello_max;
		float giro_cuello_min;

		float r_seleccion, g_seleccion, b_seleccion;
		int activo[7];
		int cambiar[7];

		_robot();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
		void select(float c);
};
