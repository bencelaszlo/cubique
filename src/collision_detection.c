#include "callbacks.h"

#include <math.h>

 int check_collision( vec3 object_pos_a, vec3 object_pos_b, float size_a, float size_b )
 {
     int is_colliding = FALSE;
     //check the X-axis
     if ( abs( round( object_pos_a.x - object_pos_b.x ) ) < size_a + size_b ) {
        //check the Y-axis
        if ( abs( round( object_pos_a.y - object_pos_b.y ) ) < size_a + size_b ) {
            //check the Z-axis
            if ( abs( round( object_pos_a.z - object_pos_b.z ) ) < size_a + size_b ) {
              is_colliding = TRUE;
            }
        }
     }

     return is_colliding;
 }

 int check_collision_all( vec3 pos_new ) {
   int is_colliding = FALSE;

   int i = 0;
   while ( !is_colliding && i < scene.cube_number ) {
     if ( i != scene.selected_cube ) {
       is_colliding = check_collision( pos_new, scene.cube_translate[i], 1.0f, 0.0f );
    }
     i++;
   }
   return is_colliding;
 }
