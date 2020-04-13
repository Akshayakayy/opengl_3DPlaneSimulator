#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double,double);
    double speed;
private:
    VAO *object;
};

#endif // DASHBOARD_H
