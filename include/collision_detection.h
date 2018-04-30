#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

/**
 *  Axis Aligned Bounding Box: returns true if object A is colliding with object B
 */
 int check_collision( vec3 object_pos_a, vec3 object_pos_b, float size_a, float size_b );

/**
  * Return true, if the selected object is colliding with any other object.
  */
 int check_collision_all( vec3 pos_new );

#endif /* COLLISION_DETECTION_H */
