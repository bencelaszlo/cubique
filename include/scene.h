#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

#define DEFAULT_CUBE_NUMBER 2048

typedef struct Scene
{
  Camera camera;
  Model cube;
  Material material;
  GLuint texture_id;
  GLuint help_menu_texture_id;
  int selected_cube;
  int cube_number;
  vec3 cube_translate[DEFAULT_CUBE_NUMBER];
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene( Scene* scene );

/**
 * Initalize the lighting of the scene.
 */
void init_lighting();

/**
 * Initalize the current material.
 */
void init_material( const Material* material );

/**
 * Draw the scene objects.
 */
void draw_scene( const Scene* scene );

/**
  * Reset the scene objects.
  */
  void reset_scene( Scene* scene );

#endif /* SCENE_H */
