#include "plane.h"
#include "main.h"


Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationx = 20;
    this->rotationy = 0;

    speed = 0.01;
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

	   vertex_buffer_data[18*i+6]=(0.15*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+7]=(0.15*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+8]=0.6;

     vertex_buffer_data[18*i+9]=(0.15*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+10]=(0.15*sin(i*2*3.14159/n));
	   vertex_buffer_data[18*i+11]=0.6;

	   vertex_buffer_data[18*i+12]=(0.15*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+13]=(0.15*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+14]=0.6;

	   vertex_buffer_data[18*i+15]=(0.3*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+16]=(0.3*sin(i*2*3.14159/n));
	   vertex_buffer_data[18*i+17]=0.0;
   }

   static GLfloat body_vertex_buffer_data[18*n];

   for (int i=0;i<n;++i){
 	   body_vertex_buffer_data[18*i]=(0.3*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+1]=(0.3*sin(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+2]=0.0;

 	   body_vertex_buffer_data[18*i+3]=(0.3*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+4]=(0.3*sin((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+5]=0.0;

 	   body_vertex_buffer_data[18*i+6]=(0.3*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+7]=(0.3*sin((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+8]=-4.5;

     body_vertex_buffer_data[18*i+9]=(0.3*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+10]=(0.3*sin(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+11]=-4.5;

 	   body_vertex_buffer_data[18*i+12]=(0.3*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+13]=(0.3*sin((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+14]=-4.5;

 	   body_vertex_buffer_data[18*i+15]=(0.3*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+16]=(0.3*sin(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+17]=0.0;
    }

    static GLfloat back_vertex_buffer_data[18*n];

  for (int i=0;i<n;++i){
	   back_vertex_buffer_data[18*i]=(0.3*cos(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+1]=(0.3*sin(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+2]=-4.5;

	   back_vertex_buffer_data[18*i+3]=(0.3*cos((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+4]=(0.3*sin((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+5]=-4.5;

	   back_vertex_buffer_data[18*i+6]=(0.19*cos((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+7]=(0.19*sin((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+8]=-4.8;

     back_vertex_buffer_data[18*i+9]=(0.19*cos(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+10]=(0.19*sin(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+11]=-4.8;

	   back_vertex_buffer_data[18*i+12]=(0.19*cos((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+13]=(0.19*sin((i+1)*2*3.14159/n));
	   back_vertex_buffer_data[18*i+14]=-4.8;

	   back_vertex_buffer_data[18*i+15]=(0.3*cos(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+16]=(0.3*sin(i*2*3.14159/n));
	   back_vertex_buffer_data[18*i+17]=-4.5;
   }

   static GLfloat booster_vertex_buffer_data[18*n];

   for (int i=0;i<n;++i){
 	   booster_vertex_buffer_data[9*i]=(0.19*cos(i*2*3.14159/n));
 	   booster_vertex_buffer_data[9*i+1]=(0.19*sin(i*2*3.14159/n));
 	   booster_vertex_buffer_data[9*i+2]=-4.8;

 	   booster_vertex_buffer_data[9*i+3]=(0.19*cos((i+1)*2*3.14159/n));
 	   booster_vertex_buffer_data[9*i+4]=(0.19*sin((i+1)*2*3.14159/n));
 	   booster_vertex_buffer_data[9*i+5]=-4.8;

 	   booster_vertex_buffer_data[9*i+6]=0.0;
 	   booster_vertex_buffer_data[9*i+7]=0.0;
 	   booster_vertex_buffer_data[9*i+8]=-4.8;
    }

    static GLfloat wing_vertex_buffer_data[]={
      0.3f,  0.0f, -1.0f,
      0.3f,  0.0f, -2.2f,
      2.6f,  0.0f, -3.2f,
      -0.3f,  0.0f, -1.0f,
      -0.3f,  0.0f, -2.2f,
      -2.6f,  0.0f, -3.2f,

      0.3f,  0.0f, -3.3f,
      0.3f,  0.0f, -4.0f,
      1.3f,  0.0f, -4.2f,
      -0.3f,  0.0f, -3.3f,
      -0.3f,  0.0f, -4.0f,
      -1.3f,  0.0f, -4.2f,
    };

    static GLfloat mwing_vertex_buffer_data[]={
      0.0f,  0.3f, -3.0f,
      0.0f,  0.3f, -4.0f,
      0.0f,  1.3f, -4.2f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 3*n*2, body_vertex_buffer_data, COLOR_DGREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n*2, vertex_buffer_data, COLOR_DGREY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3*n*2, back_vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3*n, booster_vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 12, wing_vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 3, mwing_vertex_buffer_data, COLOR_WHITE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 roll    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 10));
    //glm::mat4 rotate2    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, -0.5, 0));
    glm::mat4 pitch    = glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(0.2, 0, 0));

    glm::mat4 yaw    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0, -1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * yaw * roll * pitch);
    //Matrices.model *= (rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick(int f) {
    // if(f){
    //   this->rotation += speed;
    // }
    // this->position.x -= speed;
    // this->position.y -= speed;
}
