#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_lighting()
{
  float ambient_light[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  float diffuse_light[] = { 0.0f, 0.0f, 0.0, 0.0f };
  float specular_light[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

  glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv( GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv( GL_LIGHT0, GL_POSITION, position );
}

void init_scene( Scene* scene )
{
  load_model( &( scene->cube ), "res/cube.obj");
  scene->texture_id = load_texture( "res/crate_1.jpg" );

  //Textúra kiválasztása, a második paraméter az azonosítója
  glBindTexture( GL_TEXTURE_2D, scene->texture_id );

  scene->material.ambient.red = 0.25;
  scene->material.ambient.green = 0.20725;
  scene->material.ambient.blue = 0.20725;

  scene->material.diffuse.red = 1.0;
  scene->material.diffuse.green = 0.829;
  scene->material.diffuse.blue = 0.829;

  scene->material.specular.red = 0.296648;
  scene->material.specular.green = 0.296648;
  scene->material.specular.blue = 0.296648;

  scene->material.emission.red = 0.0f;
  scene->material.emission.green = 0.0f;
  scene->material.emission.blue = 0.0f;

  scene->material.shininess = 0.088 * 128;

  //Fények beállítása
  init_lighting( scene );
}

void set_material( const Material* material )
{
  float ambient_material_color[] = {
    material->ambient.red,
    material->ambient.green,
    material->ambient.blue
  };

  float diffuse_material_color[] = {
    material->diffuse.red,
    material->diffuse.green,
    material->diffuse.blue
  };

  float specular_material_color[] = {
    material->specular.red,
    material->specular.green,
    material->specular.blue
  };

  float emission_material_color[] = {
  material->emission.red,
  material->emission.green,
  material->emission.blue
};

  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emission_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &( material->shininess ) );
}

void set_fog()
{
  GLfloat fogDensity = 0.20;
  GLfloat fogColor[4] = { 0.28125, 0.625,  0.75390625, 1.0 };
  glFogi( GL_FOG_MODE, GL_EXP2 );
  glFogfv( GL_FOG_COLOR, fogColor );
  glFogf( GL_FOG_DENSITY, fogDensity );
  glHint( GL_FOG_HINT, GL_NICEST );
  glFogf( GL_FOG_START, 1.25 );
  glFogf( GL_FOG_END, 5.0 );
}

void draw_scene( const Scene* scene )
{
  //Anyagjellemzők beállítása
  set_material( &(scene->material) );
  //Ködhatás jellemzőinek beállítása
  set_fog();

  glDisable( GL_CULL_FACE );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  int i;
  for ( i = 0; i < MAX_CUBE_NUMBER; ++i ) {
    glTranslatef( scene->cube_translate[i][0], scene->cube_translate[i][1], scene->cube_translate[i][2] );
    //Modell kirajzolása
    draw_model( &(scene->cube) );
    //Textúra kiválasztása, a második paraméter az azonosítója
    glBindTexture( GL_TEXTURE_2D, scene->texture_id );
  }
}

int can_move( const Scene* scene, const char axis, const char direction )
{
  int move = 1;

  int i = 0;
  switch ( axis ) {
    case 'x':
      while ( move == 1 && i < MAX_CUBE_NUMBER ) {
        if ( i != scene->selected_cube ) {
          if ( ( scene->cube_translate[i][1] == scene->cube_translate[scene->selected_cube][1] ) && ( scene->cube_translate[i][2] == scene->cube_translate[scene->selected_cube][2] ) ) {
            switch ( direction ) {
               case '+':
                if ( scene->cube_translate[scene->selected_cube][0] + 1.0 == scene->cube_translate[i][0] ) {
                  move = 0;
                }
              break;

              case '-':
                if ( scene->cube_translate[i][0] == scene->cube_translate[scene->selected_cube][0] - 1.0 ) {
                  move = 0;
                }
              break;
             }
          }
        }
        i++;
      }
      break;

    case 'y':
      while ( move == 1 && i < MAX_CUBE_NUMBER ) {
        if ( i != scene->selected_cube ) {
          if ( ( scene->cube_translate[i][0] == scene->cube_translate[scene->selected_cube][0] ) && ( scene->cube_translate[i][2] == scene->cube_translate[scene->selected_cube][2] ) ) {
             switch ( direction ) {
               case '+':
                if ( scene->cube_translate[scene->selected_cube][1] + 1.0 == scene->cube_translate[i][1] ) {
                  move = 0;
                }
              break;

              case '-':
                if ( scene->cube_translate[i][1] == scene->cube_translate[scene->selected_cube][1] - 1.0 ) {
                  move = 0;
                }
              break;
             }
          }
        }
        i++;
      }
      break;

    case 'z':
      while ( move == 1 && i < MAX_CUBE_NUMBER ) {
        if ( i != scene->selected_cube ) {
          if ( ( scene->cube_translate[i][0] == scene->cube_translate[scene->selected_cube][0] ) && ( scene->cube_translate[i][1] == scene->cube_translate[scene->selected_cube][1] ) ) {
             switch ( direction ) {
               case '+':
                if ( scene->cube_translate[scene->selected_cube][2] + 1.0 == scene->cube_translate[i][2] ) {
                  move = 0;
                }
              break;

              case '-':
                if ( scene->cube_translate[i][2] == scene->cube_translate[scene->selected_cube][2] - 1.0 ) {
                  move = 0;
                }
              break;
             }
          }
        }
        i++;
      }
      break;
  }
  return move;
}
