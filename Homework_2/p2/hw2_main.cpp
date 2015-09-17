//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Modified by Floyd Richardson [and Dr. Radkowski] on 9/17/15
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"


using namespace std;

static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    gl_FrontColor = vec4(1.0, 1.0, 0.0 , 1.0);                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_FragColor =  gl_Color;                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;

// Added by Floyd Richardson
GLuint vao;






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

// Added by Floyd Richardson
unsigned int vboID[4]; // Our Vertex Buffer Object


/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    float* vertices = new float[135];  // Vertices for our square
    float *colors = new float[135]; // Colors for our vertices
    
    // FRONT SMALL FACE
    vertices[0] = -0.6; vertices[1] = -0.2; vertices[2] = 0.6; // Top left corner
    colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // Top left corner
    
    vertices[3] = -0.6; vertices[4] = -0.6; vertices[5] = 0.6; // Bottom left corner
    colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // Bottom left corner
    
    vertices[6] = -0.2; vertices[7] = -0.2; vertices[8] = 0.6; // Top Right corner
    colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // Top Right corner
    
    vertices[9] = -0.2; vertices[10] = -0.6; vertices[11] = 0.6; // Bottom right corner
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner
    
    // RIGHT SIDE UNANGLED LONG FACE
    vertices[12] = -0.2; vertices[13] = -0.2; vertices[14] = -0.2; // Top right corner
    colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0; // Top right corner
    
    vertices[15] = -0.2; vertices[16] = -0.6; vertices[17] = -0.2; // Bottom right corner
    colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // Bottom right corner
    
    // FRONT LARGE FACE BOTTOM SECTOR
    vertices[18] = 0.6; vertices[19] = -0.2; vertices[20] = -0.2; // Top right corner
    colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0; // Top right corner
    
    vertices[21] = 0.6; vertices[22] = -0.6; vertices[23] = -0.2; // Bottom right corner
    colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0; // Bottom right corner
    
    // RIGHT SIDE UNANGLED SMALL FACE
    vertices[24] = 0.6; vertices[25] = -0.2; vertices[26] = -0.6; // Top right corner
    colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0; // Top right corner
    
    vertices[27] = 0.6; vertices[28] = -0.6; vertices[29] = -0.6; // Bottom right corner
    colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0; // Bottom right corner
    
     // BACK FACE BOTTOM SECTOR
    vertices[30] = -0.6; vertices[31] = -0.2; vertices[32] = -0.6; // Top left  corner
    colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0; // Top left corner
    
    vertices[33] = -0.6; vertices[34] = -0.6; vertices[35] = -0.6; // Bottom left  corner
    colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0; // Bottom left corner
    
    //LEFT SIDE BOTTOM SECTOR
    vertices[36] = -0.6; vertices[37] = -0.2; vertices[38] = 0.6; // Top left  corner
    colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0; // Top left corner
    
    vertices[39] = -0.6; vertices[40] = -0.6; vertices[41] = 0.6; // Bottom left  corner
    colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0; // Bottom left corner
    
    //REPEATED HALF FACE
    vertices[42] = -0.2; vertices[43] = -0.6; vertices[44] = 0.6; // Bottom right  corner
    colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0; // Bottom right corner
    
    //BOTTOM FACE LEFT SECTOR
    vertices[45] = -0.6; vertices[46] = -0.6; vertices[47] = -0.6; // Top left  corner
    colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0; // Top left corner

    vertices[48] = -0.2; vertices[49] = -0.6; vertices[50] = -0.6; //Top right corner
    colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0; //Top right corner
    
    //BACK FACE LEFT SECTOR
    vertices[51] = -0.6; vertices[52] = 0.2; vertices[53] = -0.6; //Top left corner
    colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0; //Top left corner
    
    vertices[54] = -0.2; vertices[55] = 0.2; vertices[56] = -0.6; //Top right corner
    colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0; //Top right corner
    
    //TOP SMALL FACE
    vertices[57] = -0.6; vertices[58] = 0.2; vertices[59] = -0.2; //Bottom left corner
    colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0; //Bottom left corner
    
    vertices[60] = -0.2; vertices[61] = 0.2; vertices[62] = -0.2; //Bottom right corner
    colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0; //Bottom right corner
    
    //FRONT LARGE FACE LEFT SECTOR
    vertices[63] = -0.6; vertices[64] = -0.2; vertices[65] = -0.2; //Bottom left corner
    colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0; //Bottom left corner
    
    vertices[66] = -0.2; vertices[67] = -0.2; vertices[68] = -0.2; //Bottom right corner
    colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0; //Bottom right corner
    
    //TOP UNANGLED LONG FACE
    vertices[69] = -0.6; vertices[70] = -0.2; vertices[71] = 0.6; //Bottom left corner
    colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0; //Bottom left corner
    
    vertices[72] = -0.2; vertices[73] = -0.2; vertices[74] = 0.6; //Bottom right corner
    colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0; //Bottom right corner
    
    //REPEATED FACE + REPEATED HALF FACE
    vertices[75] = -0.6; vertices[76] = -0.2; vertices[77] = -0.2; //Top left corner
    colors[75] = 0.0; colors[76] = 0.0; colors[77] = 0.; //Top left corner
    
    vertices[78] = -0.2; vertices[79] = -0.2; vertices[80] = -0.2; //Top right corner
    colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0; //Top right corner
    
    vertices[81] = -0.2; vertices[82] = 0.2; vertices[83] = -0.2; //Top right corner
    colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0; //Top right corner
    
    //FRONT LARGE FACE UPPER RIGHT SECTOR
    vertices[84] = 0.6; vertices[85] = -0.2; vertices[86] = -0.2; //Bottom right corner
    colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0; //Bottom right corner
    
    //ANGLED FACE
    vertices[87] = 0.6; vertices[88] = -0.2; vertices[89] = -0.6; //Bottom right corner
    colors[87] = 0.0; colors[88] = 0.0; colors[89] = 1.0; //Bottom right corner
    
    vertices[90] = -0.2; vertices[91] = 0.2; vertices[92] = -0.6; //Top right corner
    colors[90] = 0.0; colors[91] = 0.0; colors[92] = 1.0; //Top right corner
    
    //BACK LARGE FACE RIGHT SECTOR
    vertices[93] = -0.2; vertices[94] = -0.6; vertices[95] = -0.6; //Bottom left corner
    colors[93] = 0.0; colors[94] = 0.0; colors[95] = 1.0; //Bottom left corner
    
    vertices[96] = 0.6; vertices[97] = -0.6; vertices[98] = -0.6; //Bottom right corner
    colors[96] = 0.0; colors[97] = 0.0; colors[98] = 1.0; //Bottom right corner
    
    //BOTTOM FACE RIGHT SECTOR
    vertices[99] = -0.2; vertices[100] = -0.6; vertices[101] = -0.2; //Bottom left corner
    colors[99] = 0.0; colors[100] = 0.0; colors[101] = 1.0; //Bottom left corner
    
    vertices[102] = 0.6; vertices[103] = -0.6; vertices[104] = -0.2; //Bottom right corner
    colors[102] = 0.0; colors[103] = 0.0; colors[104] = 1.0; //Bottom right corner
    
    //REPEATED FACES
    vertices[105] = -0.2; vertices[106] = -0.2; vertices[107] = -0.2; //Middle left corner(front face right sector)
    colors[105] = 0.0; colors[106] = 0.0; colors[107] = 1.0; //Middle left corner(front face right sector)
    
    vertices[108] = 0.6; vertices[109] = -0.2; vertices[110] = -0.2; //Top right corner
    colors[108] = 0.0; colors[109] = 0.0; colors[110] = 1.0; //Top right corner
    
    vertices[111] = -0.2; vertices[112] = 0.2; vertices[113] = -0.2; //Top left corner
    colors[111] = 0.0; colors[112] = 0.0; colors[113] = 1.0; //Top left corner
    
    vertices[114] = 0.6; vertices[115] = -0.2; vertices[116] = -0.6; //Bottom right corner (angled face)
    colors[114] = 0.0; colors[115] = 0.0; colors[116] = 1.0; //Bottom right corner (angled face)
    
    vertices[117] = -0.2; vertices[118] = 0.2; vertices[119] = -0.6; //Top right corner
    colors[117] = 0.0; colors[118] = 0.0; colors[119] = 1.0; //Top right corner
    
    vertices[120] = -0.2; vertices[121] = -0.2; vertices[122] = -0.6; //Bottom left corner (back face top sector)
    colors[120] = 0.0; colors[121] = 0.0; colors[122] = 1.0; //Bottom left corner (back face top sector)
    
    vertices[123] = -0.6; vertices[124] = 0.2; vertices[125] = -0.6; //Top left corner
    colors[123] = 0.0; colors[124] = 0.0; colors[125] = 1.0; //Top left corner
    
    vertices[126] = -0.6; vertices[127] = -0.2; vertices[128] = -0.6; //Bottom left corner
    colors[126] = 0.0; colors[127] = 0.0; colors[128] = 1.0; //Bottom left corner
    
    //LEFT FACE TOP SECTOR
    vertices[129] = -0.6; vertices[130] = 0.2; vertices[131] = -0.2; //Top left corner
    colors[129] = 0.0; colors[130] = 0.0; colors[131] = 1.0; //Bottom left corner
    
    vertices[132] = -0.6; vertices[133] = -0.2; vertices[134] = -0.2; //Bottom left corner
    colors[132] = 0.0; colors[133] = 0.0; colors[134] = 1.0; //Bottom right corner
    
    
    
    
    
    glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, &vboID[0]); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 135 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 135 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createMyModel(void)
{
    float* vertices = new float[135];  // Vertices for our square
    float *colors = new float[135]; // Colors for our vertices
    
    //FIRST TRIANGLE STRIP
    // FRONT SMALL FACE
    vertices[0] = -0.6; vertices[1] = -0.2; vertices[2] = 0.6; // Top left corner
    colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0; // Top left corner
    
    vertices[3] = -0.6; vertices[4] = -0.6; vertices[5] = 0.6; // Bottom left corner
    colors[3] = 0.0; colors[4] = 0.0; colors[5] = 1.0; // Bottom left corner
    
    vertices[6] = -0.2; vertices[7] = -0.2; vertices[8] = 0.6; // Top Right corner
    colors[6] = 0.0; colors[7] = 0.0; colors[8] = 1.0; // Top Right corner
    
    vertices[9] = -0.2; vertices[10] = -0.6; vertices[11] = 0.6; // Bottom right corner
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner
    
    // RIGHT SIDE UNANGLED LONG FACE
    vertices[12] = -0.2; vertices[13] = -0.2; vertices[14] = -0.2; // Top right corner
    colors[12] = 0.0; colors[13] = 0.0; colors[14] = 1.0; // Top right corner
    
    vertices[15] = -0.2; vertices[16] = -0.6; vertices[17] = -0.2; // Bottom right corner
    colors[15] = 0.0; colors[16] = 0.0; colors[17] = 1.0; // Bottom right corner
    
    // FRONT LARGE FACE BOTTOM SECTOR
    vertices[18] = 0.6; vertices[19] = -0.2; vertices[20] = -0.2; // Top right corner
    colors[18] = 0.0; colors[19] = 0.0; colors[20] = 1.0; // Top right corner
    
    vertices[21] = 0.6; vertices[22] = -0.6; vertices[23] = -0.2; // Bottom right corner
    colors[21] = 0.0; colors[22] = 0.0; colors[23] = 1.0; // Bottom right corner
    
    // RIGHT SIDE UNANGLED SMALL FACE
    vertices[24] = 0.6; vertices[25] = -0.2; vertices[26] = -0.6; // Top right corner
    colors[24] = 0.0; colors[25] = 0.0; colors[26] = 1.0; // Top right corner
    
    vertices[27] = 0.6; vertices[28] = -0.6; vertices[29] = -0.6; // Bottom right corner
    colors[27] = 0.0; colors[28] = 0.0; colors[29] = 1.0; // Bottom right corner
    
     // BACK FACE BOTTOM SECTOR
    vertices[30] = -0.6; vertices[31] = -0.2; vertices[32] = -0.6; // Top left  corner
    colors[30] = 0.0; colors[31] = 0.0; colors[32] = 1.0; // Top left corner
    
    vertices[33] = -0.6; vertices[34] = -0.6; vertices[35] = -0.6; // Bottom left  corner
    colors[33] = 0.0; colors[34] = 0.0; colors[35] = 1.0; // Bottom left corner
    
    //LEFT SIDE BOTTOM SECTOR
    vertices[36] = -0.6; vertices[37] = -0.2; vertices[38] = 0.6; // Top left  corner
    colors[36] = 0.0; colors[37] = 0.0; colors[38] = 1.0; // Top left corner
    
    vertices[39] = -0.6; vertices[40] = -0.6; vertices[41] = 0.6; // Bottom left  corner
    colors[39] = 0.0; colors[40] = 0.0; colors[41] = 1.0; // Bottom left corner
    
    //SECOND TRIANGLE STRIP
    //BOTTOM FACE LEFT SECTOR
    vertices[42] = -0.6; vertices[43] = -0.6; vertices[44] = 0.6; // Bottom left  corner
    colors[42] = 0.0; colors[43] = 0.0; colors[44] = 1.0; // Bottom left corner
    
    vertices[45] = -0.2; vertices[46] = -0.6; vertices[47] = 0.6; // Bottom right  corner
    colors[45] = 0.0; colors[46] = 0.0; colors[47] = 1.0; // Bottom right corner
    
    vertices[48] = -0.6; vertices[49] = -0.6; vertices[50] = -0.6; // Top left  corner
    colors[48] = 0.0; colors[49] = 0.0; colors[50] = 1.0; // Top left corner

    vertices[51] = -0.2; vertices[52] = -0.6; vertices[53] = -0.6; //Top right corner
    colors[51] = 0.0; colors[52] = 0.0; colors[53] = 1.0; //Top right corner
    
    //BACK FACE LEFT SECTOR
    vertices[54] = -0.6; vertices[55] = 0.2; vertices[56] = -0.6; //Top left corner
    colors[54] = 0.0; colors[55] = 0.0; colors[56] = 1.0; //Top left corner
    
    vertices[57] = -0.2; vertices[58] = 0.2; vertices[59] = -0.6; //Top right corner
    colors[57] = 0.0; colors[58] = 0.0; colors[59] = 1.0; //Top right corner
    
    //TOP SMALL FACE
    vertices[60] = -0.6; vertices[61] = 0.2; vertices[62] = -0.2; //Bottom left corner
    colors[60] = 0.0; colors[61] = 0.0; colors[62] = 1.0; //Bottom left corner
    
    vertices[63] = -0.2; vertices[64] = 0.2; vertices[65] = -0.2; //Bottom right corner
    colors[63] = 0.0; colors[64] = 0.0; colors[65] = 1.0; //Bottom right corner
    
    //FRONT LARGE FACE LEFT SECTOR
    vertices[66] = -0.6; vertices[67] = -0.2; vertices[68] = -0.2; //Bottom left corner
    colors[66] = 0.0; colors[67] = 0.0; colors[68] = 1.0; //Bottom left corner
    
    vertices[69] = -0.2; vertices[70] = -0.2; vertices[71] = -0.2; //Bottom right corner
    colors[69] = 0.0; colors[70] = 0.0; colors[71] = 1.0; //Bottom right corner
    
    //TOP UNANGLED LONG FACE
    vertices[72] = -0.6; vertices[73] = -0.2; vertices[74] = 0.6; //Bottom left corner
    colors[72] = 0.0; colors[73] = 0.0; colors[74] = 1.0; //Bottom left corner
    
    vertices[75] = -0.2; vertices[76] = -0.2; vertices[77] = 0.6; //Bottom right corner
    colors[75] = 0.0; colors[76] = 0.0; colors[77] = 1.0; //Bottom right corner
    
    //THIRD TRIANGLE STRIP
    //FRONT LARGE FACE UPPER RIGHT SECTOR
    vertices[78] = -0.2; vertices[79] = -0.2; vertices[80] = -0.2; //Top right corner
    colors[78] = 0.0; colors[79] = 0.0; colors[80] = 1.0; //Top right corner
    
    vertices[81] = -0.2; vertices[82] = 0.2; vertices[83] = -0.2; //Top right corner
    colors[81] = 0.0; colors[82] = 0.0; colors[83] = 1.0; //Top right corner
    
    vertices[84] = 0.6; vertices[85] = -0.2; vertices[86] = -0.2; //Bottom right corner
    colors[84] = 0.0; colors[85] = 0.0; colors[86] = 1.0; //Bottom right corner
    
    //ANGLED FACE
    vertices[87] = 0.6; vertices[88] = -0.2; vertices[89] = -0.6; //Bottom right corner
    colors[87] = 0.0; colors[88] = 0.0; colors[89] = 1.0; //Bottom right corner
    
    vertices[90] = -0.2; vertices[91] = 0.2; vertices[92] = -0.6; //Top right corner
    colors[90] = 0.0; colors[91] = 0.0; colors[92] = 1.0; //Top right corner
    
    //BACK LARGE FACE RIGHT SECTOR
    vertices[93] = -0.2; vertices[94] = -0.6; vertices[95] = -0.6; //Bottom left corner
    colors[93] = 0.0; colors[94] = 0.0; colors[95] = 1.0; //Bottom left corner
    
    vertices[96] = 0.6; vertices[97] = -0.6; vertices[98] = -0.6; //Bottom right corner
    colors[96] = 0.0; colors[97] = 0.0; colors[98] = 1.0; //Bottom right corner
    
    //BOTTOM FACE RIGHT SECTOR
    vertices[99] = -0.2; vertices[100] = -0.6; vertices[101] = -0.2; //Bottom left corner
    colors[99] = 0.0; colors[100] = 0.0; colors[101] = 1.0; //Bottom left corner
    
    vertices[102] = 0.6; vertices[103] = -0.6; vertices[104] = -0.2; //Bottom right corner
    colors[102] = 0.0; colors[103] = 0.0; colors[104] = 1.0; //Bottom right corner
    
    //FOURTH TRIANGLE STRIP
    //LEFT FACE TOP SECTOR
    vertices[105] = -0.6; vertices[106] = 0.2; vertices[107] = -0.6; //Top left corner
    colors[105] = 0.0; colors[106] = 0.0; colors[107] = 1.0; //Top left corner
    
    vertices[108] = -0.6; vertices[109] = -0.2; vertices[110] = -0.6; //Bottom left corner
    colors[108] = 0.0; colors[109] = 0.0; colors[110] = 1.0; //Bottom left corner
    
    vertices[111] = -0.6; vertices[112] = 0.2; vertices[113] = -0.2; //Top left corner
    colors[111] = 0.0; colors[112] = 0.0; colors[113] = 1.0; //Bottom left corner
    
    vertices[114] = -0.6; vertices[115] = -0.2; vertices[116] = -0.2; //Bottom left corner
    colors[114] = 0.0; colors[115] = 0.0; colors[116] = 1.0; //Bottom right corner
    
    
    
    
    
    glGenVertexArrays(1, &vaoID[1]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[1]); // Bind our Vertex Array Object so we can use it
    
    
    glGenBuffers(2, &vboID[2]); // Generate our Vertex Buffer Object
    
    // vertices
    glBindBuffer(GL_ARRAY_BUFFER, vboID[2]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 117 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
  
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Disable our Vertex Array Object
    
    
    //Color
    glBindBuffer(GL_ARRAY_BUFFER, vboID[3]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 117 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array
    
    glBindVertexArray(0); // Disable our Vertex Buffer Object
    
    
    delete [] vertices; // Delete our vertices from memory
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{
	// Bind the buffer and switch it to an active buffer
        glBindVertexArray(vaoID[0]);
         glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
		 glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
        // Draw the triangles
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 45);
        // Unbind our Vertex Array Object
        glBindVertexArray(0);
}

/*!
 ADD YOUR CODE TO RENDER YOUR MODEL TO THIS FUNCTION
 */
void renderMyModel(void)
{
	// Bind the buffer and switch it to an active buffer
        glBindVertexArray(vaoID[1]);
        
        // Draw the triangles
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);
        glDrawArrays(GL_TRIANGLE_STRIP, 14, 12);
        glDrawArrays(GL_TRIANGLE_STRIP, 26, 9);
        glDrawArrays(GL_TRIANGLE_STRIP, 35, 4);
        // Unbind our Vertex Array Object
        glBindVertexArray(0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
    createMyModel();
    
}


/*!
 This function updates the virtual camera
 */
bool updateCamera()
{
    // Compute the MVP matrix from keyboard and mouse input
    computeMatricesFromInputs();
    viewMatrix =  getViewMatrix(); // get the current view matrix
    
    return true;
}





int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    
    //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    // this creates the scene
    setupScene();
    
    

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        
        // update the virtual camera
        // ignore this line since we did not introduced cameras.
        updateCamera();
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // send the view matrix to our shader
        
        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderTriangleStripModel();
        
        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
        renderMyModel();
        
        
        glUseProgram(0);
        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

