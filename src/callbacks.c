#include "callbacks.h"
#include "scene.h"

#include <stdio.h>
#include <obj/draw.h>

#define VIEWPORT_RATIO ( 4.0 / 3.0 )
#define VIEWPORT_ASPECT 45.0

struct {
  int x;
  int y;
} mouse_position;

void display()
{
  // Clear the window with current clearing color
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();

  set_view( &camera );
  draw_scene( &scene );
  
  glPopMatrix();

  glutSwapBuffers();
}

void reshape( GLsizei width, GLsizei height )
{
  int x, y, w, h;
  double ratio;

  ratio = (double)width / height;
  if ( ratio > VIEWPORT_RATIO ) {
      w = (int)( (double)height * VIEWPORT_RATIO);
      h = height;
      x = ( width - w ) / 2;
      y = 0;
  }
  else {
      w = width;
      h = (int)( (double)width / VIEWPORT_RATIO );
      x = 0;
      y = ( height - h ) / 2;
  }

  glViewport( x, y, w, h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 5000.0 );
}

#define GLUT_MOUSE_WHEEL_UP 3
#define GLUT_MOUSE_WHEEL_DOWN 4

void mouse( int button, int state, int x, int y )
{
    mouse_position.x = x;
    mouse_position.y = y;

    /*if ( button == GLUT_MOUSE_DOWN ) {

    }*/
}

void motion( int x, int y )
{
  rotate_camera( &camera, mouse_position.x - x, mouse_position.y - y );
  mouse_position.x = x;
  mouse_position.y = y;
  glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y )
{
  switch (key) {
  case 'w': case 'W':
      set_camera_speed( &camera, 1 );
      break;
  case 's': case 'S':
      set_camera_speed( &camera, -1 );
      break;
  case 'a': case 'A':
      set_camera_side_speed( &camera, 1 );
      break;
  case 'd': case 'D':
      set_camera_side_speed( &camera, -1 );
      break;
  case '+':
      ;
      GLfloat current_ambient[4], current_diffuse[4];
      glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
      glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );

      if ( current_ambient[3] < 1.0 ) {
        current_ambient[0] += 0.1;
        current_ambient[1] += 0.1;
        current_ambient[2] += 0.1;
        current_ambient[3] += 0.1;
        current_diffuse[0] += 0.1;
        current_diffuse[1] += 0.1;
        current_diffuse[2] += 0.1;
        current_diffuse[3] += 0.1;
        glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
      }
      break;

  case '-':
      ;
      glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
      glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );

      if ( current_ambient[3] > 0.1) {
        current_ambient[0] -= 0.1;
        current_ambient[1] -= 0.1;
        current_ambient[2] -= 0.1;
        current_ambient[3] -= 0.1;
        current_diffuse[0] -= 0.1;
        current_diffuse[1] -= 0.1;
        current_diffuse[2] -= 0.1;
        current_diffuse[3] -= 0.1;
        glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
      }
      break;

    case 'z': case 'Z':
      if ( can_move( &scene, 'y', '+') ) {
        scene.cube_translate[scene.selected_cube][1] += 1.0f;
      }
      break;

    case 'h': case 'H':
      if ( can_move( &scene, 'y', '-' ) ) {
        scene.cube_translate[scene.selected_cube][1] -= 1.0f;
      }
      break;

    case 'i': case 'I':
      if ( can_move( &scene, 'z', '+' ) ) {
        scene.cube_translate[scene.selected_cube][2] += 1.0f;
      }
      break;

    case 'k': case 'K':
      if ( can_move( &scene, 'z', '-' ) ) {
        scene.cube_translate[scene.selected_cube][2] -= 1.0f;
      }
      break;

    case 'j': case 'J':
      if ( can_move( &scene, 'x', '+' ) == 1 ) {
        scene.cube_translate[scene.selected_cube][0] += 1.0f;
      }
      break;

    case 'l': case 'L':
      if ( can_move( &scene, 'x', '-' ) == 1 ) {
        scene.cube_translate[scene.selected_cube][0] -= 1.0f;
      }
      break;

  case 't': case 'T':
    if ( scene.selected_cube < MAX_CUBE_NUMBER - 1 ) {
      scene.selected_cube++;
    }
    break;

  case 'g': case 'G':
    if ( scene.selected_cube > 0 ) {
      scene.selected_cube--;
    }
    break;

  }

  glutPostRedisplay();
}

void keyboard_up( unsigned char key, int x, int y )
{
  switch ( key ) {
  case 'w': case 'W':
  case 's': case 'S':
      set_camera_speed( &camera, 0.0 );
      break;

  case 'a': case 'A':
  case 'd': case 'D':
      set_camera_side_speed( &camera, 0.0 );
      break;

  case GLUT_KEY_F1:
      scene.draw_menu = ( scene.draw_menu == 1 ) ? 0 : 1;
      break;

  case GLUT_KEY_F11:
      glutFullScreen();
      break;

  }

  glutPostRedisplay();
}

void idle()
{
  static int last_frame_time = 0;
  int current_time;
  double elapsed_time;

  current_time = glutGet( GLUT_ELAPSED_TIME );
  elapsed_time = (double)( current_time - last_frame_time ) / 1000;
  last_frame_time = current_time;

  update_camera( &camera, elapsed_time );

  glutPostRedisplay();
}
