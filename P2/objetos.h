#include <stdlib.h>
#include <vector>
#include <GL/gl.h>
#include "vertex.h"

const float AXIS_SIZE = 5000;
typedef enum {POINTS, EDGES, SOLID_CHESS, SOLID} _modo;

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
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
};


//*********
// _cubo //
//*********
class _cubo: public _triangulos3D
{
	public:
		_cubo(float tam = 0.5);
};


//*************
// _piramide //
//*************
class _piramide: public _triangulos3D
{
	public:
		_piramide(float tam = 0.5, float al = 0.75);
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


//*************
// _cono //
//*************
class _cono: public _rotacion
{ 
	public:
		_cono(float radio, float altura, int num);
};


//*************
// _cilindro //
//*************
class _cilindro: public _rotacion
{ 
	public:
		_cilindro(float radio, float altura, int num);
};


//*************
// _esfera //
//*************
class _esfera: public _rotacion
{ 
	public:
		_esfera(float radio, int n, int num);
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