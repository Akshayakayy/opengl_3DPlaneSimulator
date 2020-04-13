#include "hoop.h"
#include "main.h"
Hoop::Hoop(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 180;
    this->radius = 5;
    const int n = 50;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[18*n];
    for (int i=0;i<n;++i){
  	   vertex_buffer_data[18*i]=(radius*cos(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+1]=(radius*sin(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+2]=0.0;

  	   vertex_buffer_data[18*i+3]=(radius*cos((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+4]=(radius*sin((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+5]=0.0;

  	   vertex_buffer_data[18*i+6]=((radius-1)*cos((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+7]=((radius-1)*sin((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+8]=0.6;

       vertex_buffer_data[18*i+9]=((radius-1)*cos(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+10]=((radius-1)*sin(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+11]=0.6;

  	   vertex_buffer_data[18*i+12]=((radius-1)*cos((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+13]=((radius-1)*sin((i+1)*2*3.14159/n));
  	   vertex_buffer_data[18*i+14]=0.6;

  	   vertex_buffer_data[18*i+15]=(radius*cos(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+16]=(radius*sin(i*2*3.14159/n));
  	   vertex_buffer_data[18*i+17]=0.0;
     }

    this->object = create3DObject(GL_TRIANGLES, 3*n*2, vertex_buffer_data, COLOR_WALLDESIGN, GL_FILL);
}

void Hoop::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Hoop::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Hoop::tick(double x, double y) {
    this->position.x += x;
    this->position.y += y;
}

bounding_box_t Hoop::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y - this->radius/2, this->radius*2, this->radius };
    return bbox;
}
