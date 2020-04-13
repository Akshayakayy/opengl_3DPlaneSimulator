#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->translate = glm::translate (this->position);

    const int n = 50;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[18*n];

  for (int i=0;i<n;++i){
	   vertex_buffer_data[18*i]=(10.0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+1]=0.0;
	   vertex_buffer_data[18*i+2]=(10.0*sin(i*2*3.14159/n));

	   vertex_buffer_data[18*i+3]=(10.0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+4]=0.0;
	   vertex_buffer_data[18*i+5]=(10.0*sin((i+1)*2*3.14159/n));

	   vertex_buffer_data[18*i+6]=(0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+7]=20.6;
	   vertex_buffer_data[18*i+8]=(0*sin((i+1)*2*3.14159/n));

     vertex_buffer_data[18*i+9]=(0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+10]=20.6;
	   vertex_buffer_data[18*i+11]=(0*sin(i*2*3.14159/n));

	   vertex_buffer_data[18*i+12]=(0*cos((i+1)*2*3.14159/n));
	   vertex_buffer_data[18*i+13]=20.6;
	   vertex_buffer_data[18*i+14]=(0*sin((i+1)*2*3.14159/n));

	   vertex_buffer_data[18*i+15]=(10.0*cos(i*2*3.14159/n));
	   vertex_buffer_data[18*i+16]=0.0;
	   vertex_buffer_data[18*i+17]=(10.0*sin(i*2*3.14159/n));
   }

    this->object1 = create3DObject(GL_TRIANGLES, 3*n*2, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
}

void Volcano::addSquare(float x2,float x1,float y2,float y1,float z2,float z1,GLfloat * arr,int baseIndex)
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

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *= (this->translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}
