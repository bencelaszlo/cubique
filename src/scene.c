#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_lighting()
{
  float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
  float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

  glLightfv( GL_LIGHT0, GL_AMBIENT, ambient_light );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv( GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv( GL_LIGHT0, GL_POSITION, position );
}

void init_scene( Scene* scene )
{
  //Load resources
  load_model( &( scene->cube ), "res/cube.obj");
  scene->texture_id = load_texture( "res/glass_cube.jpg" );
  scene->help_menu_texture_id = load_texture( "res/help_menu.jpg" );

  glBindTexture( GL_TEXTURE_2D, scene->texture_id ); //Select texture (its second parameter is the id of a loaded texture)

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

  init_lighting( scene ); //Set lights
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
  GLfloat fogDensity = 0.175;
  GLfloat fogColor[4] = { 0.28125, 0.625,  0.75390625, 1.0 };
  glFogi( GL_FOG_MODE, GL_EXP2 );
  glFogfv( GL_FOG_COLOR, fogColor );
  glFogf( GL_FOG_DENSITY, fogDensity );
  glHint( GL_FOG_HINT, GL_NICEST );
  glFogf( GL_FOG_START, 2.0 );
  glFogf( GL_FOG_END, 5.0 );
}

void draw_scene( const Scene* scene )
{
  set_material( &(scene->material) );
  set_fog();

  glDisable( GL_CULL_FACE );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  int i;
  for ( i = 0; i < MAX_CUBE_NUMBER; ++i ) {
    glPushMatrix();
    glTranslatef( scene->cube_translate[i].x, scene->cube_translate[i].y, scene->cube_translate[i].z );
    draw_model( &(scene->cube) );
    glBindTexture( GL_TEXTURE_2D, scene->texture_id );
    glPopMatrix();
  }
}
