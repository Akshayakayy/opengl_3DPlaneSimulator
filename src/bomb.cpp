#include "bomb.h"
#include "main.h"


Bomb::Bomb(float x, float y, float z, float rotationy, float rotation, color_t color) {
    this->position = glm::vec3(x, y, z);

    this->rotationy = rotationy;
    this->rotation = rotation;
    speed = 1;
    const int n = 50;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[18*n];

  for (int i=0;i<n;++i){
	   vertex_buffer_data[18*i]=(0.3*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+1]=(0.3*sin(i*2*3.14159/n));
	   vertex_buffer_data[18*i+2]=0.0;

	   vertex_buffer_data[18*i+3]=(0.3*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+4]=(0.3*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+5]=0.0;

	   vertex_buffer_data[18*i+6]=(0.3*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+7]=(0.3*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+8]=0.6;

     vertex_buffer_data[18*i+9]=(0.3*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+10]=(0.3*sin(i*2*3.14159/n));
	   vertex_buffer_data[18*i+11]=0.6;

	   vertex_buffer_data[18*i+12]=(0.3*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+13]=(0.3*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+14]=0.6;

	   vertex_buffer_data[18*i+15]=(0.3*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+16]=(0.3*sin(i*2*3.14159/n));
	   vertex_buffer_data[18*i+17]=0.0;
   }

    this->object1 = create3DObject(GL_TRIANGLES, n*2*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);// * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomb::tick(int f) {
    if(f){
      this->rotation += speed;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}
