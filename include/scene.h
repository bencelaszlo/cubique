#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

#define MAX_CUBE_NUMBER 10

typedef struct Scene
{
  Camera camera;
  Model cube;
  Material material;
  GLuint texture_id;
  GLuint help_menu_texture_id;
  float cube_translate[MAX_CUBE_NUMBER][3];
  int selected_cube;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene( Scene* scene );

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material( const Material* material );

/**
 * Draw the scene objects.
 */
void draw_scene( const Scene* scene );

/**
  * Detects possible collisions between the selected and other objects.
  */
int can_move( const Scene* scene, const char axis, const char direction );

#endif /* SCENE_H */
