#include "main.h"

#ifndef SCENE_H
#define SCENE_H


class Ocean {
public:
    Ocean() {}
    Ocean(color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double,double);
    double speed;
private:
    VAO *object;
};

class Sky {
public:
    Sky() {}
    Sky(color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double,double);
    double speed;
private:
    VAO *object;
};

class Skydesign {
public:
    Skydesign() {}
    Skydesign(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(double,double);
    double speed;
private:
    VAO *object;
};

#endif // SCENE_H
