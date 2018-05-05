#include "callbacks.h"

#include <stdio.h>

void load_scene( char* filename )
{
    FILE *fp;

    fp = fopen( filename, "r" );
    if ( fp == NULL ) {
        printf( "ERROR: opening save file.\n" );
    }

    fscanf( fp, "%d\n", &scene.cube_number );

    int i;
    for ( i = 0; i < scene.cube_number; ++i ) {
      fscanf( fp, "%f %f %f\n",  &scene.cube_translate[i].x, &scene.cube_translate[i].y, &scene.cube_translate[i].z );
    }

    fclose( fp );
}

void save_scene()
{
  FILE *fp;

  fp = fopen( "res/savegame/last.save", "w" );
  if ( fp == NULL )
  {
      printf( "ERROR: opening save file.\n" );
  }

  fprintf( fp, "%d\n", scene.cube_number );

  int i;
  for ( i = 0; i < scene.cube_number; ++i ) {
    fprintf( fp, "%f %f %f\n", scene.cube_translate[i].x, scene.cube_translate[i].y, scene.cube_translate[i].z );
  }

  fclose( fp );
}
