#include "objetos.h"
#include "file_ply_stl.h"


//*************
// _puntos3D //
//*************
_puntos3D::_puntos3D() {}


//*******************
// Dibujar puntos. //
//*******************
void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);
  for (int i = 0; i < vertices.size(); i++)
    glVertex3fv((GLfloat *) &vertices[i]);
  glEnd();
}


//*****************
// _triangulos3D //
//*****************
_triangulos3D::_triangulos3D() {}


//***************************
// Dibujar en modo arista. //
//***************************
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  for (int i = 0;i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  }
  glEnd();
}


//**************************
// Dibujar en modo sólido //
//**************************
void _triangulos3D::draw_solido(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++) 
	{
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//****************************************************
// Dibujar en modo sólido con apariencia de ajedrez //
//****************************************************
void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < caras.size(); i++) 
	{
		if (i % 2 == 0) glColor3f(r1,g1,b1);
		else			glColor3f(r2,g2,b2);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}


//*******************************
// Dibujar con distintos modos //
//*******************************
void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  switch(modo)
  {
	  case POINTS:      draw_puntos(r1, g1, b1, grosor);                break;
	  case EDGES:       draw_aristas(r1, g1, b1, grosor);               break;
	  case SOLID:       draw_solido(r1, g1, b1);                        break;
	  case SOLID_CHESS: draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);    break;
	}
}

//*********
// _cubo //
//*********
_cubo::_cubo(float tam)
{
	// Vértices
	vertices.resize(8);
	vertices[0].x = -tam/2;	vertices[0].y = -tam/2;	vertices[0].z = tam/2;
	vertices[1].x = tam/2;	vertices[1].y = -tam/2;	vertices[1].z = tam/2;
	vertices[2].x = tam/2;	vertices[2].y = -tam/2;	vertices[2].z = -tam/2;
	vertices[3].x = -tam/2;	vertices[3].y = -tam/2;	vertices[3].z = -tam/2;
	vertices[4].x = -tam/2;	vertices[4].y = tam/2;	vertices[4].z = tam/2;
	vertices[5].x = tam/2;	vertices[5].y = tam/2;	vertices[5].z = tam/2;
	vertices[6].x = tam/2;	vertices[6].y = tam/2;	vertices[6].z = -tam/2;
	vertices[7].x = -tam/2;	vertices[7].y = tam/2;	vertices[7].z = -tam/2;

	// Caras
	caras.resize(12);
	caras[0]._0 = 0;	caras[0]._1 = 1;	caras[0]._2 = 4;
	caras[1]._0 = 1;	caras[1]._1 = 5;	caras[1]._2 = 4;
	caras[2]._0 = 1;	caras[2]._1 = 2;	caras[2]._2 = 5;
	caras[3]._0 = 2;	caras[3]._1 = 6;	caras[3]._2 = 5;
	caras[4]._0 = 2;	caras[4]._1 = 3;	caras[4]._2 = 6;
	caras[5]._0 = 3;	caras[5]._1 = 7;	caras[5]._2 = 6;
	caras[6]._0 = 3;	caras[6]._1 = 0;	caras[6]._2 = 7;
	caras[7]._0 = 0;	caras[7]._1 = 4;	caras[7]._2 = 7;
	caras[8]._0 = 4;	caras[8]._1 = 5;	caras[8]._2 = 6;
	caras[9]._0 = 4;	caras[9]._1 = 6;	caras[9]._2 = 7;
	caras[10]._0 = 3;	caras[10]._1 = 1;	caras[10]._2 = 0;
	caras[11]._0 = 3;	caras[11]._1 = 2;	caras[11]._2 = 1;
}


//*************
// _piramide //
//*************
_piramide::_piramide(float tam, float al)
{
	// Vértices 
	vertices.resize(5); 
	vertices[0].x = -tam/2;	vertices[0].y = -al/2;	vertices[0].z = tam/2;
	vertices[1].x = tam/2;	vertices[1].y = -al/2;	vertices[1].z = tam/2;
	vertices[2].x = tam/2;	vertices[2].y = -al/2;	vertices[2].z = -tam/2;
	vertices[3].x = -tam/2;	vertices[3].y = -al/2;	vertices[3].z = -tam/2;
	vertices[4].x = 0;	    vertices[4].y = al/2;	  vertices[4].z = 0;
	
	// Caras
	caras.resize(6);
	caras[0]._0 = 0;	caras[0]._1 = 1;	caras[0]._2 = 4;
	caras[1]._0 = 1;	caras[1]._1 = 2;	caras[1]._2 = 4;
	caras[2]._0 = 2;	caras[2]._1 = 3;	caras[2]._2 = 4;
	caras[3]._0 = 3;	caras[3]._1 = 0;	caras[3]._2 = 4;
	caras[4]._0 = 3;	caras[4]._1 = 1;	caras[4]._2 = 0;
	caras[5]._0 = 3;	caras[5]._1 = 2;	caras[5]._2 = 1;
}

//***************
// _objeto_ply //
//***************
_objeto_ply::_objeto_ply() {}


int _objeto_ply::parametros(char *archivo)
{
  vector<float> ver_ply ;
  vector<int>   car_ply ;
  int n_ver,n_car;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size()/3;
  n_car = car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);

  // Vértices
  for(int i = 0; i < n_ver; i++) 
  {
    vertices[i].x = ver_ply[3*i];
    vertices[i].y = ver_ply[3*i+1];
    vertices[i].z = ver_ply[3*i+2];
  }

  // Caras
  for(int i = 0; i < n_car; i++) 
  {
    caras[i]._0 = car_ply[3*i];
    caras[i]._1 = car_ply[3*i+1];
    caras[i]._2 = car_ply[3*i+2];
  }

  return(0);
}


//*************
// _rotacion //
//*************
_rotacion::_rotacion() {}


//*************
// _cono //
//*************
_cono::_cono(float radio, float altura, int num)
{
  vector<_vertex3f> perfil;
	_vertex3f vertice_aux;
  vertice_aux.x = radio; vertice_aux.y = -altura/2.0; vertice_aux.z = 0.0;
	perfil.push_back(vertice_aux);
  vertice_aux.x = 0.0; vertice_aux.y = altura/2.0; vertice_aux.z = 0.0;
	perfil.push_back(vertice_aux);
  parametros(perfil, num, 1);
}


//*************
// _cilindro //
//*************
_cilindro::_cilindro(float radio, float altura, int num)
{
  vector<_vertex3f> perfil;
	_vertex3f vertice_aux;
  vertice_aux.x = radio; vertice_aux.y = -altura/2.0; vertice_aux.z = 0.0;
	perfil.push_back(vertice_aux);
  vertice_aux.x = radio; vertice_aux.y = altura/2.0; vertice_aux.z = 0.0;
	perfil.push_back(vertice_aux);
  parametros(perfil, num, 0);
}


//*************
// _esfera //
//*************
_esfera::_esfera(float radio, int n, int num)
{
  vector<_vertex3f> perfil;
	_vertex3f vertice_aux;
  for (int i = 1; i < n; i++) 
  {
    vertice_aux.x = radio*cos(M_PI*i/n-M_PI/2.0);
    vertice_aux.y = radio*sin(M_PI*i/n-M_PI/2.0);
    vertice_aux.z = 0.0;
    perfil.push_back(vertice_aux);
  }
  parametros(perfil, num, 2);
}


//****************
// _rotacionply //
//****************
_rotacionply::_rotacionply() {}

void _rotacionply::parametros(char *archivo, int num) 
{
  _objeto_ply obj;
  obj.parametros(archivo);
  _rotacion::parametros(obj.vertices, num, 0);
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo)
{
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio, altura;

  // Revertimos la generatriz si no se ha incluido de abajo hacia arriba.
  if (perfil.size() >= 2 && perfil[0].y > perfil[perfil.size()-1].y)
    reverse(perfil.begin(), perfil.end());

  // Tratamiento de los vértices
  num_aux = perfil.size();

  if (tipo == 1) 
  {
    num_aux = 1;
    altura = perfil[1].y;
  }

  if (tipo == 2)
    radio = sqrt(perfil[0].x*perfil[0].x + perfil[0].y*perfil[0].y);

  vertices.resize(num_aux*num+2);
  
  for (int j = 0; j < num; j++)
  {
    for (int i = 0; i < num_aux; i++)
    {
      vertice_aux.x =  perfil[i].x*cos(2.0*M_PI*j/(1.0*num)) + perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z = -perfil[i].x*sin(2.0*M_PI*j/(1.0*num)) + perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y =  perfil[i].y;
      vertices[i+j*num_aux] = vertice_aux;
    }
  }

  // Tratamiento de las caras
  caras.resize(2*(num_aux-1)*num + 2*num);

  int c = 0;
  if (tipo == 0 || tipo == 2)
    for (int j = 0; j < num; j++)
    {
        for (int i = 0; i < num_aux-1; i++) 
        {
          caras[c]._0 = num_aux*j+1+i;
          caras[c]._1 = num_aux*j+i;
          caras[c]._2 = num_aux*((j+1)%num)+1+i;
          c++;
          caras[c]._0 = num_aux*((j+1)%num)+i;
          caras[c]._1 = num_aux*((j+1)%num)+1+i;
          caras[c]._2 = num_aux*j+i;
          c++;
      }
    }
      
  // Tapa inferior
  if (fabs(perfil[0].x) > 0.0) 
  {
    vertices[num_aux*num]._0 = 0.0;
    if (tipo == 0) vertices[num_aux*num]._1 = perfil[0].y;
    if (tipo == 1) vertices[num_aux*num]._1 = -altura;
    if (tipo == 2) vertices[num_aux*num]._1 = -radio;
    vertices[num_aux*num]._2 = 0.0;

    for (int j = 0; j < num; j++) 
    {
      caras[c]._0 = num_aux*num;
      caras[c]._1 = num_aux*((j+1)%num);
      caras[c]._2 = num_aux*j;
      c++;
    }
  }

  // Tapa superior
  if (fabs(perfil[num_aux-1].x) > 0.0) 
  {
    vertices[num_aux*num+1]._0 = 0.0;
    if (tipo == 0) vertices[num_aux*num+1]._1 = perfil[num_aux-1].y;
    if (tipo == 1) vertices[num_aux*num+1]._1 = altura;
    if (tipo == 2) vertices[num_aux*num+1]._1 = radio;
    vertices[num_aux*num+1]._2 = 0.0;

    for (int j = 0; j < num; j++) 
    {
      caras[c]._0 = num_aux*num+1;
      caras[c]._1 = num_aux*j+num_aux-1;
      caras[c]._2 = num_aux*((j+1)%num)+num_aux-1;
      c++;
    }
  }
}