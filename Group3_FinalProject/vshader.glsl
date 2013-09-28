#version 330 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 fragmentColor;

uniform vec3 dColor;
uniform mat4 ortho;
uniform mat4 world;

void main()
{
    gl_Position = ortho * world * vec4(vPosition, 0, 1);

	fragmentColor = dColor + vColor;
}
