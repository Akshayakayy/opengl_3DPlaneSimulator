#include "main.h"
#include "plane.h"

#ifndef ATTACK_H
#define ATTACK_H


class Attack {
public:
    Attack() {}
    Attack(float x, float y, float z, Plane plane, color_t color);
    glm::vec3 position;
    float rotation;
    float rotationy;
    Plane plane;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int f);
    double speed;
private:
    VAO *object1;
};

#endif // ATTACK_H
