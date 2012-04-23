#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <glew.h>
#include <glut.h>
#include "shader_utils.h"
#include "drawPlant.h"
using namespace std;


//glm::mat3 drawStem(int level, glm::mat3 m);
//glm::mat3 drawLine(glm::mat3 m);

GLuint program;
GLint attribute_coord2d = 0;
GLint attribute_color = 1;
GLint uniform_matrix;  // pointer to uniform variable
glm::mat3 current(1,0,0, //0,0
						 0,1,0, //1,0
						 0,0,1); //2,0

// every vertex is position (2 floats), followed by color (3 floats)
GLfloat leaf_vertices[] = {
  0.0,0.0,   0.5,0.9,0.3,
  0.025,0.019, 0.1 ,0.5,0.1,
  0.030,0.048, 0.4,0.8,0.3,
  0.027,0.062, 0.1,0.5,0.1,
  0.0,0.10,   0.5,0.9,0.3,
  -0.027,0.062,  0.1,0.5,0.3,
  -0.030,0.048,  0.4,0.8,0.3,
  -0.025,0.019,  0.1,0.5,0.1
  };

GLubyte leaf_indicies[] = {
  0, 1, 2, 
  0, 2, 3,
  0, 3, 4, 
  0, 4, 5,
  0, 5, 6,
  0, 6, 7
};

GLfloat stem_vertices[] = {
  0.0,0.0,  0.5,0.5,0.3,
  0.0,0.5,  0.5,0.6,0.3,
  0.5,0.5,  0.4,0.6,0.3,
  0.5,0.0,  0.3,0.4,0.3
};

GLubyte stem_indicies[] = {
  0, 1, 2,
  0, 2, 3
};

GLfloat line_vertices[] = {
	0.0,0.0, 
	0.0,0.2
};

// Turn left by pi/6
//GLfloat TurnLeft[] = 
//  {cos(M_PI/6), -sin(M_PI/6), 0.0, 
//   sin(M_PI/6), cos(M_PI/6), 0.0,
//   0.0,  0.0, 1.0};


// Set up the shaders, compile and link them, get pointers to 
// where the shader variables are in GPU memory. 
int init_resources()
{
  // Error flag is initially false
  GLint link_ok = GL_FALSE;
  // Indices for vertex and fragment shaders
  GLuint vs, fs;

  // create_shader is a function in shader_utils that reads in 
  // a vertex or fragment program from a file, creates a shader 
  // object, puts the program into the object, and compiles it.
  // If all goes well, returns 1. 
  vs = create_shader("plant.v.glsl", GL_VERTEX_SHADER);
  if (vs == 0) return 0;

  fs = create_shader("plant.f.glsl", GL_FRAGMENT_SHADER);
  if (fs == 0) return 0;


  // The GPU program contains both the vertex and shader programs. 
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  // Link them together.
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram: failed\n");
    return 0;
  }
  
  // Now figure out where the linker put everything
  // We don't know where the vertex program is going to store all its
  // input data until after linking. 
  // Results are indicies into some table on the GPU. 

  // Ask for the index of shader variable coord2d. 
  attribute_coord2d = glGetAttribLocation(program, "coord2d");
  if (attribute_coord2d == -1) {
    fprintf(stderr, "Could not bind attribute coord2d\n");
    return 0;
  }

  // Ask for the index of shader variable coord2d. 
  attribute_color = glGetAttribLocation(program, "v_color");
  if (attribute_color == -1) {
    fprintf(stderr, "Could not bind attribute v_color\n");
    return 0;
  }

  // Get linker's index to the uniform variable
  uniform_matrix = glGetUniformLocation(program, "m_transform");
  if (uniform_matrix == -1) {
    fprintf(stderr, "Could not bind uniform variable m_transform \n");
    return 0;
  }


  // If all went well....
  return 1;
}


// Draw the leaf
void drawLeaf(glm::mat3 t) {

  // Send the program to the GPU
  //glUseProgram(program);

  // Now hook up input data to program.

  // Two attributes for the vertex, position and color.
  // Let OpenGL know we'll use both of them. 
  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_color);

  // Describe the position attribute and where the data is in the array
  glVertexAttribPointer(
    attribute_coord2d, // attribute ID
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is, don't normalize
    5*sizeof(float),  // stride between one position and the next
    leaf_vertices  // pointer to first position in the C array
  );

  // Describe the position attribute and where the data is in the array
  glVertexAttribPointer(
    attribute_color, // attribute ID
    3,                 // number of elements per vertex, here (r,g,b)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is, don't normalize
    5*sizeof(float),  // stride between one position and the next
    leaf_vertices+2    // pointer to first position index of a color in the C array
  );
  

  // give the matrix a value
  glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &t[0][0]);
  //glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, TurnLeft);

  // Send the triangle vertices to the GPU  - actually draw! 
  glDrawElements(GL_TRIANGLES, 7*3, GL_UNSIGNED_BYTE, leaf_indicies);
 /* 
  glVertexAttribPointer(
    attribute_coord2d, // attribute ID
    2,                 // number of elements per vertex, here (x,y)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is, don't normalize
    5*sizeof(float),  // stride between one position and the next
    stem_vertices  // pointer to first position in the C array
  );

  // Describe the position attribute and where the data is in the array
  glVertexAttribPointer(
    attribute_color, // attribute ID
    3,                 // number of elements per vertex, here (r,g,b)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is, don't normalize
    5*sizeof(float),  // stride between one position and the next
    stem_vertices+2    // pointer to first position index of a color in the C array
  );
  */
  //current = drawStem(1, current);
  /*glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &originalMatrix[0][0]);
  glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_BYTE, stem_indicies);

  glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, TurnLeft);
  glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_BYTE, stem_indicies);*/

  
  // Done with the attributes
  glDisableVertexAttribArray(attribute_coord2d);
  glDisableVertexAttribArray(attribute_color);

}

void drawPlant(int level, glm::mat3 t){
  if(level == 0){
    cout << "Draw leaf\n";
    drawLeaf(t); 
  }
  else {
    glm::mat3 temp;
    cout << "Draw stem\n";
    drawStem(level-1, t);
    temp = t;
    t = turnLeft(t,M_PI/10);
    drawPlant(level-1, t);
    t = temp;
    t = turnRight(t, M_PI/10);
    drawPlant(level-1, t);
  }
}

void beginPlant(void){
  glUseProgram(program);
  //glEnableVertexAttribArray(attribute_coord2d);
  //glEnableVertexAttribArray(attribute_color);
  cout << "Begin drawing...\n"; 
  drawPlant(2,current);
  
  //glDisableVertexAttribArray(attribute_coord2d);
  //glDisableVertexAttribArray(attribute_color);
  
}

glm::mat3 turnLeft(glm::mat3 t, float angle){
  
//GLfloat TurnLeft[] = 
//  {cos(M_PI/6), -sin(M_PI/6), 0.0, 
//   sin(M_PI/6), cos(M_PI/6), 0.0,
//   0.0,  0.0, 1.0};
  glm::mat3 rotM(cos(angle), sin(angle),0,
                 -sin(angle), cos(angle), 0,
                 0, 0, 1);
  return t * rotM;

}

glm::mat3 turnRight(glm::mat3 t, float angle){
  
  glm::mat3 rotM(cos(-angle), sin(-angle),0,
                 -sin(-angle), cos(-angle), 0,
                 0, 0, 1);
  return t * rotM;

}

glm::mat3 drawStem(int level, glm::mat3 m){
   glm::mat3 scaleMatrix(1,0,0,
                        0,0.8,0,
                        0,0,1
                       );
   glm::mat3 translateM(1,0,0,
                        0,1,0,
                        0,-0.8,1);

   glm::mat3 translateM2(1,0,0,
                        0,1,0,
                        0,0.2,1);


  if(level == 0){
    m = translateM * m;
    drawLine(m);
    //cout << "Draw a line\n";
    m = translateM2 * m;
  }
  else {
    m = drawStem(level-1, m);
    drawStem(level-1,m);
  }

	return m;
}

glm::mat3 drawLine(glm::mat3 m){
  glEnableVertexAttribArray(attribute_coord2d);
	glVertexAttribPointer(
		attribute_coord2d, // attribute ID
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is, don't normalize
		2*sizeof(float),  // stride between one position and the next in the arr
		line_vertices  // pointer to first position in the C array
	);
	
	//glVertexAttribPointer(
	//	attribute_color, // attribute ID
	//	3,                 // number of elements per vertex, here (r,g,b)
	//	GL_FLOAT,          // the type of each element
	//	GL_FALSE,          // take our values as-is, don't normalize
	//	5*sizeof(float),  // stride between one position and the next
	//	line_vertices+2    // pointer to first position index of a color in the C array
	//);
	glColor3f(0.4,0.8,0.1);
	glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	glDrawArrays(GL_LINES,0,2);
  glDisableVertexAttribArray(attribute_coord2d);
	return m;
}

void free_resources()
{
  glDeleteProgram(program);
}
