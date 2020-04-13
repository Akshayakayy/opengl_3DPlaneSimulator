#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z) {
  this->position = glm::vec3(x, y, z);
  // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
  // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
  const int n = 6;

  static GLfloat vertex_buffer_data[9*n];

  for (int i=0;i<n;++i){
	   vertex_buffer_data[9*i]=(2.1*cos(i*2*3.14159/n));
	   vertex_buffer_data[9*i+1]=(2.1*sin(i*2*3.14159/n));
	   vertex_buffer_data[9*i+2]=0.0;

	   vertex_buffer_data[9*i+3]=(2.1*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[9*i+4]=(2.1*sin((i+1)*2*3.14159/n));
	   vertex_buffer_data[9*i+5]=0.0;

	   vertex_buffer_data[9*i+6]=0.0;
	   vertex_buffer_data[9*i+7]=0.0;
	   vertex_buffer_data[9*i+8]=0.0;
   }

   static GLfloat vertex_buffer_data_1[9*n];

   for (int i=0;i<n;++i){
 	   vertex_buffer_data_1[9*i]=(2.1*cos(i*2*3.14159/n));
 	   vertex_buffer_data_1[9*i+1]=0.0;
 	   vertex_buffer_data_1[9*i+2]=(2.1*sin(i*2*3.14159/n));

 	   vertex_buffer_data_1[9*i+3]=(2.1*cos((i+1)*2*3.14159/n));
 	   vertex_buffer_data_1[9*i+4]=0.0;
 	   vertex_buffer_data_1[9*i+5]=(2.1*sin((i+1)*2*3.14159/n));

 	   vertex_buffer_data_1[9*i+6]=0.0;
 	   vertex_buffer_data_1[9*i+7]=0.0;
 	   vertex_buffer_data_1[9*i+8]=0.0;
    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data_1, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_WALL, GL_FILL);
}

void Parachute::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex)
{
    int i;
    if(x1==x2) {
        const GLfloat temp[] = {
            x1, y2, z2,
            x1, y1, z2,
            x1, y2, z1,

            x1, y1, z1,
            x1, y1, z2,
            x1, y2, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
    else if(y1==y2) {
        const GLfloat temp[] = {
            x2, y1, z2,
            x1, y1, z2,
            x2, y1, z1,

            x2, y1, z1,
            x1, y1, z2,
            x1, y1, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
    else if(z1==z2) {
        const GLfloat temp[] = {
            x2, y2, z1,
            x1, y2, z1,
            x2, y1, z1,

            x1, y1, z1,
            x1, y2, z1,
            x2, y1, z1,
        };
        for(i=0;i<18;i++) arr[baseIndex*18+i] = temp[i];
    }
}

void Parachute::draw(glm::mat4 VP) {
  Matrices.model = glm::mat4(1.0f);
  glm::mat4 translate = glm::translate (this->position);    // glTranslatef
  //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
  // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
  // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
  Matrices.model *= (translate);// * rotate);
  glm::mat4 MVP = VP * Matrices.model;
  glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
  draw3DObject(this->object1);
  draw3DObject(this->object);
}
