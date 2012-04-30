#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
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
  0.0,0.0, 0.6,0.4,0.1,
  0.0,0.2, 0.6,0.4,0.1,
  0.1,0.2, 0.6,0.4,0.1,
  0.2,0.3, 0.6,0.4,0.1,
  0.4,0.5, 0.6,0.4,0.1,
  0.5,0.6, 0.6,0.4,0.1,
  0.6,0.7, 0.6,0.4,0.1,
  0.7,0.8, 0.6,0.4,0.1,
  0.8,0.9, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
    0.0,0.0, 0.6,0.4,0.1,
  0.0,0.2, 0.6,0.4,0.1,
  0.1,0.2, 0.6,0.4,0.1,
  0.2,0.3, 0.6,0.4,0.1,
  0.4,0.5, 0.6,0.4,0.1,
  0.5,0.6, 0.6,0.4,0.1,
  0.6,0.7, 0.6,0.4,0.1,
  0.7,0.8, 0.6,0.4,0.1,
  0.8,0.9, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
    0.0,0.0, 0.6,0.4,0.1,
  0.0,0.2, 0.6,0.4,0.1,
  0.1,0.2, 0.6,0.4,0.1,
  0.2,0.3, 0.6,0.4,0.1,
  0.4,0.5, 0.6,0.4,0.1,
  0.5,0.6, 0.6,0.4,0.1,
  0.6,0.7, 0.6,0.4,0.1,
  0.7,0.8, 0.6,0.4,0.1,
  0.8,0.9, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
    0.0,0.0, 0.6,0.4,0.1,
  0.0,0.2, 0.6,0.4,0.1,
  0.1,0.2, 0.6,0.4,0.1,
  0.2,0.3, 0.6,0.4,0.1,
  0.4,0.5, 0.6,0.4,0.1,
  0.5,0.6, 0.6,0.4,0.1,
  0.6,0.7, 0.6,0.4,0.1,
  0.7,0.8, 0.6,0.4,0.1,
  0.8,0.9, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1
};

GLubyte stem_indicies[] = {
  0, 1, 2,
  0, 2, 3
};

GLfloat line_vertices[] = {
	0.0,0.0, 0.6,0.4,0.1,
	0.0,0.2, 0.6,0.4,0.1,
};

GLfloat curve_vertices[] = {
  0.0,0.0, 0.6,0.4,0.1,
  0.0,0.2, 0.5,0.2,0.1,
  0.1,0.2, 0.4,0.1,0.1,
  0.2,0.3, 0.6,0.4,0.1,
  0.4,0.5, 0.5,0.2,0.1,
  0.5,0.6, 0.4,0.4,0.1,
  0.6,0.7, 0.6,0.4,0.1,
  0.7,0.8, 0.6,0.4,0.1,
  0.8,0.9, 0.5,0.2,0.1,
  0.9,1.0, 0.6,0.4,0.1,
  0.9,1.0, 0.6,0.4,0.1
};

GLubyte curve_indicies[] = {
  0, 1, 2, 
  0, 2, 3,
  0, 3, 4, 
  0, 4, 5,
  0, 5, 6,
  0, 6, 7,
  0, 7, 8,
  0, 8, 9,
  0, 9, 10
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
    t = drawStem(level-1, t);
    temp = t;
    t = turnLeft(t,M_PI/8);
    drawPlant(level-1, t);
    t = temp;
    t = turnRight(t, M_PI/8);
    drawPlant(level-1, t);
  }
}

void drawPalm(int level, glm::mat3 t){
	for(int i = 0; i < level; i++){
		drawPalmStem(t);
		t = forward(t,0.001,0.3);
	}
}

void beginPlant(void){
  glUseProgram(program);
  //glEnableVertexAttribArray(attribute_coord2d);
  //glEnableVertexAttribArray(attribute_color);
  cout << "Begin drawing...\n"; 
  glm::mat3 current(0.4,0,0, //0,0
					0,0.5,0, //1,0
					0,0.-0.9,1); //2,0
  //drawPlant(1,current);
  drawPalm(5, current);
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

glm::mat3 forward(glm::mat3 t, float x, float y){
  
  glm::mat3 rotM(1, 0, 0,
                 0, 1, 0,
                 x, y, 1);
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
    drawLine(m);
    //cout << "Draw a line\n";
    m = m * translateM2;
  }
  else {
    m = drawStem(level-1, m);
  }

	return m;
}

glm::mat3 drawLine(glm::mat3 m){
  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_color);
  
	glVertexAttribPointer(
		attribute_coord2d, // attribute ID
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is, don't normalize
		5*sizeof(float),  // stride between one position and the next in the arr
		line_vertices  // pointer to first position in the C array
	);
	
	glVertexAttribPointer(
		attribute_color, // attribute ID
		3,                 // number of elements per vertex, here (r,g,b)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is, don't normalize
		5*sizeof(float),  // stride between one position and the next
		line_vertices+2    // pointer to first position index of a color in the C array
	);
	//glColor3f(0.6,0.2,0.1);
	glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	glDrawArrays(GL_LINES,0,2);
	glDisableVertexAttribArray(attribute_coord2d);
	glDisableVertexAttribArray(attribute_color);
	return m;
}

glm::mat3 drawPalmStem(glm::mat3 m){

  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_color);

	glVertexAttribPointer(
		attribute_coord2d, // attribute ID
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is, don't normalize
		5*sizeof(float),  // stride between one position and the next in the arr
		stem_vertices  // pointer to first position in the C array
	);
	
	glVertexAttribPointer(
		attribute_color, // attribute ID
		3,                 // number of elements per vertex, here (r,g,b)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is, don't normalize
		5*sizeof(float),  // stride between one position and the next
		stem_vertices+2    // pointer to first position index of a color in the C array
	);
	

	float xver[3] = { 0.0, -0.05, 0.0  };
	float yver[3] = { 0.0, 0.15, 0.3 };
	getCurve(xver, yver);
	int i = 0, j = 0;
	for(i = 0; i < 55; i++){
		stem_vertices[j] =  curve_vertices[i];
		j++;
	}
	//glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	//glDrawElements(GL_TRIANGLES, 10*3, GL_UNSIGNED_BYTE, curve_indicies);
	
	float xver2[3] = { 0.2, 0.25, 0.2  };
	float yver2[3] = { 0.0, 0.15, 0.3 };
	getCurve(xver2, yver2);
	for(i = 0; i < 55; i++){
		stem_vertices[j] =  curve_vertices[i];
		j++;
	}
	//glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	//glDrawElements(GL_TRIANGLES, 10*3, GL_UNSIGNED_BYTE, curve_indicies);

	float xver3[3] = { 0.0, 0.1, 0.2  };
	float yver3[3] = { 0.0, -0.025, 0.0 };
	getCurve(xver3, yver3);
	for(i = 0; i < 55; i++){
		stem_vertices[j] =  curve_vertices[i];
		j++;
	}
	//glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	//glDrawElements(GL_TRIANGLES, 10*3, GL_UNSIGNED_BYTE, curve_indicies);

	float xver4[3] = { 0.0, 0.1, 0.2  };
	float yver4[3] = { 0.3, 0.275, 0.3 };
	getCurve(xver4, yver4);
	for(i = 0; i < 55; i++){
		stem_vertices[j] =  curve_vertices[i];
		j++;
	}
//	glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
//	glDrawElements(GL_TRIANGLES, 10*3, GL_UNSIGNED_BYTE, curve_indicies);
	
	////glColor3f(0.6,0.2,0.1);
	glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &m[0][0]);
	glDrawArrays(GL_TRIANGLE_FAN,0,44);  
	int r = 0;
	for(i = 0; i < 44; i++){
	  cout << "x y " << stem_vertices[r] << " " << stem_vertices[++r] << endl;
	  r+=4;
	}
	

	//float xver2[3] = { 0.0, 0.05, 0.0  };
	//float yver2[3] = { 0.0, 0.15, 0.3 };
	//getCurve(xver2, yver2);
	//glm::mat3 toTheRight = forward(m, 0.2, 0);
	//glUniformMatrix3fv(uniform_matrix, 1, GL_FALSE, &toTheRight[0][0]);
	//glDrawElements(GL_TRIANGLES, 9*3, GL_UNSIGNED_BYTE, curve_indicies);

	glDisableVertexAttribArray(attribute_coord2d);
	glDisableVertexAttribArray(attribute_color);
	return m;
}

void getCurve(float x[], float y[]){
  float ax = x[0], bx = x[1], cx = x[2];
  float ay = y[0], by = y[1], cy = y[2];
  int i = 0;
  for(int t = 0; t <= 10; t++){
    float x = curveValue((float)t/10, ax, bx, cx);
    float y = curveValue((float)t/10, ay, by, cy);
    curve_vertices[i] = x;
    i++;
    curve_vertices[i] = y;
    i += 4;
    //cout << "x y " << x << " " << y << endl;
  }
  //for(i = 0; i < 55; i+=5){
  //  cout << curve_vertices[i] << endl;
  //}
}


float curveValue(float t, float a, float b, float c){
  float val = 0;
  val = ((1-t)*(1-t)*a) + (2*(1-t)*t*b) + ((t*t)*c);
  return val;
}

void free_resources()
{
  glDeleteProgram(program);
}
