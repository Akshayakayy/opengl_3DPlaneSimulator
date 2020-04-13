#include "main.h"

#ifndef LAND_H
#define LAND_H


class Land {
public:
    Land() {}
    Land(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 translate;
    float landSize;
    void draw(glm::mat4 VP);
    void addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex);
private:
    VAO *object1;
};

#endif
