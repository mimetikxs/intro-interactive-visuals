#version 150

// uniforms:  same for all vertices
// -----------------------------------------------

// default uniform, defined by oF
uniform mat4  modelViewProjectionMatrix;
// custom uniforms, defined by us
// ...

// vertex attributes:  different for every vertex
// -----------------------------------------------

// default attribute, defined by oF
in vec4 position;
// custom sttributes, defined by us
// ...

// output to fragment shader
// -----------------------------------------------

out vec4 v_color;


// main
// -----------------------------------------------

void main()
{
    // ...
}
