#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotationx;
    float rotationy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int f);
    double speed;
private:
    VAO *object1, *object2, *object3, *object4, *object5, *object6;
};

#endif // PLANE_H
