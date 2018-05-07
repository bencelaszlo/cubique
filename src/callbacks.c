#include "callbacks.h"
#include "collision_detection.h"
#include "io.h"

#define VIEWPORT_RATIO ( 16.0f / 9.0f )
#define VIEWPORT_ASPECT 45.0f

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
  gluPerspective( VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01f, 15000.0f );
}

#define GLUT_MOUSE_WHEEL_UP 3
#define GLUT_MOUSE_WHEEL_DOWN 4
void mouse( int button, int state, int x, int y )
{
  if ( button == GLUT_MOUSE_WHEEL_DOWN ) {
    if ( camera.distance <= 50.0f ) {
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
      set_camera_speed( &camera, 5 );
      break;
    case 's': case 'S':
      set_camera_speed( &camera, -5 );
      break;
    case 'a': case 'A':
      set_camera_side_speed( &camera, 5 );
      break;
    case 'd': case 'D':;
      set_camera_side_speed( &camera, -5 );
      break;
    case '+':
      ;
      GLfloat current_ambient[4], current_diffuse[4], current_specular[4];
      glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
      glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
      glGetLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );

      if ( current_specular[3] < 1.0f ) {

        int i;
        for ( i = 0; i < 4; ++i) {
          current_ambient[i] += 0.1f;
          current_diffuse[i] += 0.1f;
          current_specular[i] += 0.1f;
        }

        glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
        glLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );
      }
      if ( current_specular[3] > 0.1f ) {
        glEnable( GL_FOG );
        glClearColor( 0.28125f, 0.625f, 0.75390625f, 0.0f );
      }
      break;

    case '-':
      ;
      glGetLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
      glGetLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
      glGetLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );

      if ( current_specular[3] > 0.0f ) {

        int i;
        for ( i = 0; i < 4; ++i ) {
          current_ambient[i] -= 0.1f;
          current_diffuse[i] -= 0.1f;
          current_specular[i] -= 0.1f;
        }

        glLightfv( GL_LIGHT0, GL_AMBIENT, current_ambient );
        glLightfv( GL_LIGHT0, GL_DIFFUSE, current_diffuse );
        glLightfv( GL_LIGHT0, GL_SPECULAR, current_specular );
      }
      else if ( current_specular[3] < 0.1f ) {
        glDisable( GL_FOG );
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
      }
      break;

    case 'z': case 'Z':
      ;
      vec3 new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.y += 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].y += 1.0f;
      }
      break;

    case 'h': case 'H':
      new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.y -= 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].y -= 1.0f;
      }
      break;

    case 'i': case 'I':
      new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.z += 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].z += 1.0f;
      }
      break;

    case 'k': case 'K':
      new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.z -= 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].z -= 1.0f;
      }
      break;

    case 'j': case 'J':
      new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.x += 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].x += 1.0f;
      }
      break;

    case 'l': case 'L':
      new_pos = scene.cube_translate[scene.selected_cube];
      new_pos.x -= 1.0f;
      if ( !check_collision_all( new_pos ) ) {
        scene.cube_translate[scene.selected_cube].x -= 1.0f;
      }
      break;

    case 't': case 'T':
      if ( scene.selected_cube < DEFAULT_CUBE_NUMBER - 1 ) {
        scene.selected_cube++;
      } else {
        scene.selected_cube = 0;
      }
      break;

    case 'g': case 'G':
      if ( scene.selected_cube > 0 ) {
        scene.selected_cube--;
      } else {
        scene.selected_cube = DEFAULT_CUBE_NUMBER - 1;
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
      set_camera_speed( &camera, 0.0f );
      glutPostRedisplay();
      break;

    case 'a': case 'A':
    case 'd': case 'D':
      set_camera_side_speed( &camera, 0.0f );
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

    case GLUT_KEY_F2:
      save_scene();
      break;

    case GLUT_KEY_F3:
      load_scene( "res/savegame/last.save" );
      break;

    case GLUT_KEY_F4:
      reset_scene( &scene );
      break;

    case GLUT_KEY_F5:
      load_scene( "res/savegame/iglu.save" );
      break;

    case GLUT_KEY_F6:
      load_scene( "res/savegame/pyramid.save" );
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
