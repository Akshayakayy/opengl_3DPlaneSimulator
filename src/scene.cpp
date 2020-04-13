#include "scene.h"
#include "main.h"

Ocean::Ocean(color_t color) {
    this->position = glm::vec3(0, -50, 0);
    this->rotation = 0;
    speed = 0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
      -50000.0f, 0.0f, -50000.0f,
      -50000.0f, 0.0f, 50000.0f,
      50000.0f,  0.0f, -50000.0f,
      50000.0f, 0.0f, -50000.0f,
      -50000.0f,0.0f, 50000.0f,
      50000.0f,  0.0f, 50000.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Ocean::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
  //  glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ocean::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ocean::tick(double x,double y) {
    //this->rotation += speed;
    this->position.x += x;
    this->position.y += y;
}

Sky::Sky(color_t color) {
    this->position = glm::vec3(0, 0, 50);
    this->rotation = 0;
    speed = 0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
      -100.0f, 65.0f, 0.0f,
      -100.0f, -14.0f, 0.0f,
      100.0f,  -14.0f, 0.0f,
      -100.0f, 65.0f, 0.0f,
      100.0f, 65.0f, 0.0f,
      100.0f,  -14.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Sky::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
  //  glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sky::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Sky::tick(double x,double y) {
    //this->rotation += speed;
    this->position.x += x;
    this->position.y += y;
}

Skydesign::Skydesign(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
      0.0f, 6.5f, 0.0f,
      0.0f, 0.0f, 0.0f,
      1,  0.0f, 0.0f,
      0.0f, 6.5f, 0.0f,
      1, 6.5f, 0.0f,
      1,  0.0f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Skydesign::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
  //  glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Skydesign::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Skydesign::tick(double x,double y) {
    //this->rotation += speed;
    this->position.x += x;
    this->position.y += y;

    if(this->position.x < -5)
    {
      this->position.x = 4;
    }
}
