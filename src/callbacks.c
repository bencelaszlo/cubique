#include "callbacks.h"
#include "scene.h"

#include <stdio.h>
#include <obj/draw.h>
#include <GL/glut.h>
#include <math.h>

#define VIEWPORT_RATIO ( 4.0 / 3.0 )
#define VIEWPORT_ASPECT 45.0

struct {
  int x;
  int y;
  int is_down;
} mouse_device;

void display()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear the window with current clearing color
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();

  set_view( &camera );
  draw_scene( &scene );

  glPopMatrix();

  if ( is_help_menu_on ) {
      glBindTexture( GL_TEXTURE_2D, scene.help_menu_texture_id );
      help_menu();
  }

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
    if ( button == GLUT_MOUSE_WHEEL_DOWN ) {
      if ( camera.distance <= 5.0f ) {
        camera.distance += 0.5f;
        glutPostRedisplay();
      }
    }
    else if ( button == GLUT_MOUSE_WHEEL_UP ) {
      if ( camera.distance >= 1.0f ) {
        camera.distance -= 0.5f;
        glutPostRedisplay();
      }
    }
    else if ( ( button == GLUT_LEFT_BUTTON ) && (state == GLUT_DOWN ) ) {
      mouse_device.is_down = TRUE;
      mouse_device.x = x;
      mouse_device.y = y;
    }

    if ( state == GLUT_UP ) {
      mouse_device.is_down = FALSE;
    }

}

void motion( int x, int y )
{
  rotate_camera( &camera, mouse_device.x - x, mouse_device.y - y );
  mouse_device.x = x;
  mouse_device.y = y;

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
      case 'd': case 'D':;
          set_camera_side_speed( &camera, -1 );
          break;
      case '+':
          ;
          GLfloat current_ambient[4], current_diffuse[4], current_specular[4];
          glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
          glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
          glGetLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );

          if ( current_ambient[3] < 1.0 ) {

            int i = 0;
            for ( i = 0; i < 4; ++i) {
              current_ambient[i] += 0.1;
              current_diffuse[i] += 0.1;
              current_specular[i] += 0.1f;
            }

            glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
            glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
            glLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );
          }
          break;

      case '-':
          ;
          glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
          glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
          glGetLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );

          if ( current_ambient[3] > 0.1) {

            int i = 0;
            for ( i = 0; i < 4; ++i ) {
              current_ambient[i] -= 0.1;
              current_diffuse[i] -= 0.1;
              current_specular[i] -= 0.1f;
            }

            glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
            glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
            glLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );
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
      glutPostRedisplay();
      break;

  case 'a': case 'A':
  case 'd': case 'D':
      set_camera_side_speed( &camera, 0.0 );
      glutPostRedisplay();
      break;
  }

  glutPostRedisplay();
}

void keyboard_special( int key, int x, int y) {
  switch( key ) {
      case GLUT_KEY_F1:
        is_help_menu_on = ( is_help_menu_on ) ? FALSE : TRUE;
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
