#include <stdlib.h>
#include <vector>
#include <GL/gl.h>
#include "vertex.h"

using namespace std;

const float AXIS_SIZE = 5000;

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