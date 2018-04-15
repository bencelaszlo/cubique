#include "init.h"

#include <GL/glut.h>

void init_opengl()
{
  glShadeModel( GL_SMOOTH );

  glEnable( GL_NORMALIZE );
  glEnable( GL_AUTO_NORMAL );

  glClearColor( 0.7734375, 0.15625, 0.156525, 0.0f );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glEnable( GL_DEPTH_TEST );
  glClearDepth( 1.0 );

  glEnable( GL_TEXTURE_2D );

  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );

  glEnable( GL_FOG );
}