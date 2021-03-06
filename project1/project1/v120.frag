//
// Alternate fragment shader for 2D assignments.
//
// This will be used if the OpenGL implementation does not
// support OpenGL 3.0 and GLSL 1.30.
//

#version 120

// incoming color from the vertex shader
varying vec4 rescolor;

void main()
{
    gl_FragColor = rescolor;
}
