#include "arrow.h"
#include "main.h"


Arrow::Arrow(float x, float y, float z, float rotationy, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationy = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const int n = 50;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[18*n];

  for (int i=0;i<n;++i){
	   vertex_buffer_data[18*i]=(4.0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+1]=0.0;
	   vertex_buffer_data[18*i+2]=(4.0*sin(i*2*3.14159/n));

	   vertex_buffer_data[18*i+3]=(4.0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+4]=0.0;
	   vertex_buffer_data[18*i+5]=(4.0*sin((i+1)*2*3.14159/n));

	   vertex_buffer_data[18*i+6]=(0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+7]=-3.6;
	   vertex_buffer_data[18*i+8]=(0*sin((i+1)*2*3.14159/n));

     vertex_buffer_data[18*i+9]=(0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+10]=-3.6;
	   vertex_buffer_data[18*i+11]=(0*sin(i*2*3.14159/n));

	   vertex_buffer_data[18*i+12]=(0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+13]=-3.6;
	   vertex_buffer_data[18*i+14]=(0*sin((i+1)*2*3.14159/n));

	   vertex_buffer_data[18*i+15]=(4.0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+16]=0.0;
	   vertex_buffer_data[18*i+17]=(4.0*sin(i*2*3.14159/n));
   }

   static GLfloat body_vertex_buffer_data[18*n];

   for (int i=0;i<n;++i){
 	   body_vertex_buffer_data[18*i]=(3.0*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+1]=0.0;
 	   body_vertex_buffer_data[18*i+2]=(3.0*sin(i*2*3.14159/n));

 	   body_vertex_buffer_data[18*i+3]=(3.0*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+4]=0.0;
 	   body_vertex_buffer_data[18*i+5]=(3.0*sin((i+1)*2*3.14159/n));

 	   body_vertex_buffer_data[18*i+6]=(3.0*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+7]=4.5;
 	   body_vertex_buffer_data[18*i+8]=(3.0*sin((i+1)*2*3.14159/n));

     body_vertex_buffer_data[18*i+9]=(3.0*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+10]=4.5;
 	   body_vertex_buffer_data[18*i+11]=(3.0*sin(i*2*3.14159/n));

 	   body_vertex_buffer_data[18*i+12]=(3.0*cos((i+1)*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+13]=4.5;
 	   body_vertex_buffer_data[18*i+14]=(3.0*sin((i+1)*2*3.14159/n));

 	   body_vertex_buffer_data[18*i+15]=(3.0*cos(i*2*3.14159/n));
 	   body_vertex_buffer_data[18*i+16]=0.0;
 	   body_vertex_buffer_data[18*i+17]=(3.0*sin(i*2*3.14159/n));
    }


    this->object1 = create3DObject(GL_TRIANGLES, 3*n*2, body_vertex_buffer_data, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*n*2, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Arrow::tick(int f) {
    if(f){
      this->rotation += speed;
    }
    // this->position.x -= speed;
    // this->position.y -= speed;
}
