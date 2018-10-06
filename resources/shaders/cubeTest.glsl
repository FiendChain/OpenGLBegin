#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

uniform mat4 u_MVP;

out vec3 v_Color;

void main() {
    gl_Position = u_MVP * vec4(position, 1);
    v_Color = vertexColor;
}
#endshader

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Color;

void main() {
    color = vec4(v_Color, 1);
}
#endshader