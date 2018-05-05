#include "camera.h"

#include <GL/glut.h>
#include <math.h>

void init_camera( Camera* camera )
{
  camera->position.x = -10.0f;
  camera->position.y = -10.0f;
  camera->position.z = 0.0f;
  camera->rotation.x = 360.0f;
  camera->rotation.y = 0.0f;
  camera->rotation.z = 50.0f;
  camera->speed.x    = 0.0f;
  camera->speed.y    = 0.0f;
  camera->speed.z    = 0.0f;

  is_help_menu_on = FALSE;
}

void update_camera( Camera* camera, double time )
{
  double angle;
  double side_angle;

  angle = degree_to_radian( camera->rotation.z );
  side_angle = degree_to_radian( camera->rotation.z + 90.0f );

  camera->position.x += cos( angle ) * camera->speed.y * time;
  camera->position.y += sin( angle ) * camera->speed.y * time;
  camera->position.x += cos( side_angle ) * camera->speed.x * time;
  camera->position.y += sin( side_angle ) * camera->speed.x * time;
  camera->position.z += cos( angle ) * camera->speed.z * time;
  camera->position.z += sin( angle ) * camera->speed.z * time;

}

void set_view( const Camera* camera )
{
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glTranslatef( 0.0f, 0.0f, -camera->distance );
  glRotatef( -( camera->rotation.x + 90 ), 1.0f, 0.0f, 0.0f );
  glRotatef( -( camera->rotation.z - 90 ), 0.0f, 0.0f, 1.0f );
  glTranslatef( -camera->position.x, -camera->position.y, -camera->position.z );
}

void rotate_camera( Camera* camera, double horizontal, double vertical )
{
  camera->rotation.z += horizontal;
  camera->rotation.x += vertical;

  if ( camera->rotation.z < 0.0f ) {
    camera->rotation.z += 360.0f;
  }

  if ( camera->rotation.z > 360.0f ) {
    camera->rotation.z -= 360.0f;
  }

  if ( camera->rotation.x < 0.0f ) {
    camera->rotation.x += 360.0f;
  }

  if ( camera->rotation.x > 360.0f ) {
    camera->rotation.x -= 360.0f;
  }
}

void set_camera_speed( Camera* camera, double speed )
{
  camera->speed.y = speed;
}

void set_camera_side_speed( Camera* camera, double speed )
{
  camera->speed.x = speed;
}

void help_menu()
{
  glDisable( GL_LIGHTING );
  glDisable( GL_DEPTH_TEST );
  glEnable( GL_COLOR_MATERIAL );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glColor3f( 0.9, 0.9, 0.9 );

  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );
  glVertex3f( -1, 1, -2.5 );
  glTexCoord2f( 1, 0 );
  glVertex3f( 1, 1, -2.5 );
  glTexCoord2f( 1, 1 );
  glVertex3f( 1, -1, -2.5 );
  glTexCoord2f( 0, 1 );
  glVertex3f( -1, -1, -2.5 );
  glEnd();

  glDisable( GL_COLOR_MATERIAL );
  glEnable( GL_LIGHTING );
  glEnable( GL_DEPTH_TEST );
}
