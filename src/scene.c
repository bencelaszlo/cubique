#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_lighting()
{
  float ambient_light[] = { 0.8f, 0.8f, 0.8f, 0.8f };
  float diffuse_light[] = { 0.9f, 0.9f, 0.9f, 0.9f };
  float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

  glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv( GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv( GL_LIGHT0, GL_POSITION, position );
}

void init_material( const Material* material )
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

  glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color );
  glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, &( material->shininess ) );
}

void init_fog()
{
  GLfloat fogDensity = 0.05f;
  GLfloat fogColor[4] = { 0.28125f, 0.625f,  0.75390625f, 1.0f };
  glFogi( GL_FOG_MODE, GL_EXP2 );
  glFogfv( GL_FOG_COLOR, fogColor );
  glFogf( GL_FOG_DENSITY, fogDensity );
  glHint( GL_FOG_HINT, GL_NICEST );
  glFogf( GL_FOG_START, 50.0f );
  glFogf( GL_FOG_END, 100.0f );
}


void init_scene( Scene* scene )
{
  load_model( &( scene->cube ), "res/cube.obj");
  scene->texture_id = load_texture( "res/glass_cube.jpg" );
  scene->help_menu_texture_id = load_texture( "res/help_menu.jpg" );

  scene->material.ambient.red = 0.25f;
  scene->material.ambient.green = 0.20725f;
  scene->material.ambient.blue = 0.20725f;

  scene->material.diffuse.red = 1.0f;
  scene->material.diffuse.green = 0.829f;
  scene->material.diffuse.blue = 0.829f;

  scene->material.specular.red = 0.296648f;
  scene->material.specular.green = 0.296648f;
  scene->material.specular.blue = 0.296648f;

  scene->material.shininess = 0.088f * 128;

  init_lighting( scene );
  init_fog();
  init_material( &(scene->material) );

  reset_scene( scene );
}

void draw_scene( const Scene* scene )
{
  glDisable( GL_CULL_FACE );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  int i;
  for ( i = 0; i < scene->cube_number; ++i ) {
    glPushMatrix();
    glTranslatef( scene->cube_translate[i].x, scene->cube_translate[i].y, scene->cube_translate[i].z );
    draw_model( &(scene->cube) );
    glBindTexture( GL_TEXTURE_2D, scene->texture_id );
    glPopMatrix();
  }
}

void reset_scene( Scene* scene )
{
  int i;
  for ( i = 0; i < scene->cube_number; ++i ) {
    scene->cube_translate[i].x = 0.0f;
    scene->cube_translate[i].y = 0.0f;
    scene->cube_translate[i].z = 0.0f;
  }
}
