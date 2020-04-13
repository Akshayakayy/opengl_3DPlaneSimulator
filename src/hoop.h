#include "main.h"

#ifndef HOOP_H
#define HOOP_H


class Hoop {
public:
    Hoop() {}
    Hoop(float x, float y, float radius, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double x, double y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
