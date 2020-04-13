#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, float rotationy, color_t color);
    glm::vec3 position;
    float rotation;
    float rotationy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int f);
    double speed;
private:
    VAO *object1,*object2;
};

#endif // ARROW_H
