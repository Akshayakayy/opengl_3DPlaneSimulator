#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float rotationy, float rotation, color_t color);
    glm::vec3 position;
    float rotation;
    float rotationy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int f);
    double speed;
private:
    VAO *object1;
};

#endif // BOMB_H
