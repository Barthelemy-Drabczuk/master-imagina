///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////  

#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <math.h>


/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>. 
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h" 
*/

#include <GL/glut.h> 
#include "Vector3.h"
#include "Point3.h"

using namespace std;

// D�finition de la taille de la fen�tre
#define WIDTH  480

#define HEIGHT 480

// D�finition de la couleur de la fen�tre
#define RED   0.8
#define GREEN 0.8
#define BLUE  0.8
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108


// Ent�tes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 

double random(double n, long long precision = 100000);
double random(double min, double max, long long precision = 100000);

int main(int argc, char **argv)
{ 
  srand(time(0));
  // initialisation  des param�tres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carr�");

  // initialisation de OpenGL et de la sc�ne
  initGL();  
  init_scene();

  // choix des proc�dures de callback pour 
  // le trac� graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fen�tre
  glutReshapeFunc(&window_reshape);
  // la gestion des �v�nements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des �v�nements utilisateur
  glutMainLoop();  

  return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL() 
{
  glClearColor(RED, GREEN, BLUE, ALPHA);        
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene()
{
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
  // � une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
  render_scene();

  // trace la sc�ne grapnique qui vient juste d'�tre d�finie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport � la fen�tre.
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

  // toutes les transformations suivantes s�appliquent au mod�le de vue 
  glMatrixMode(GL_MODELVIEW);
}

Point3 point(-2 + random(4), -2 + random(4));

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
  switch (key) {    
  case KEY_ESC:  
    exit(1);                    
    break;
  case KEY_I:
    point += Vector3::up * 0.1;
    glutPostRedisplay();
    break;
  case KEY_J:
    point += Vector3::left * 0.1;
    glutPostRedisplay();
    break;
  case KEY_K:
    point += Vector3::down * 0.1;
    glutPostRedisplay();
    break;
  case KEY_L:
    point += Vector3::right * 0.1;
    glutPostRedisplay();
    break;
  default:
    printf ("La touche %d n�est pas active.\n", key);
    break;
  }     
}

GLvoid draw_point(const Point3& point){
  glPointSize(4);
  glBegin(GL_POINTS);
    glVertex3dv(point);
  glEnd();
}

GLvoid draw_line(const Point3& start, const Point3& end){
  glBegin(GL_LINES);
    glVertex3dv(start);
    glVertex3dv(end);
  glEnd();
}


double random(double n, long long precision){
  long long num = n * precision;
  return (rand() % num) / (double)precision;
}

double random(double min, double max, long long precision){
  return min + random((max - min), precision);
}
//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//D�finition de la couleur

  //  Nous cr�ons ici un polygone. Nous pourrions aussi cr�er un triangle ou des lignes. Voir ci-dessous les parties 
  // en commentaires (il faut commenter le bloc qui ne vous int�resse pas et d�commenter celui que vous voulez tester.

   // Cr�ation de deux lignes
/*
  glBegin(GL_LINES);
    glVertex3f(-1, -1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(-1, 1, 0); 
  glEnd();
*/
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x0C0F);

  Point3 line_start(-2, 2);
  Point3 line_end(2, -2);

  Point3 line_start_2(2, 2);
  Point3 line_end_2(-2, -2);

  Point3 projection = point.project_on_line(line_start, line_end);

  //cout << "point = " << point << "\n";
  //cout << "line_start = " << line_start << "\n";
  //cout << "line_end = " << line_end << "\n";
  //cout << "projection(point, line_start, line_end) = " << projection << "\n";

  glColor3f(0, 0, 1);

  draw_point(point);
  draw_line(point, projection);

  glColor3f(1, 0, 0);
 
  draw_point(projection);
  draw_line(line_start, line_end);

  //draw_line(line_start_2, line_end_2);
 // cr�ation d'un polygone
/*	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
	glEnd();
*/

/*
// cr�ation d'un triangle
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
	glEnd();
*/
}
