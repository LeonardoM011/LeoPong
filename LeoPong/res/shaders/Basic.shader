#shader VERTEX_SHADER

#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 u_MVP;

void main() {
	gl_Position = u_MVP * vec4(position, 0.0, 1.0);
}

#shader FRAGMENT_SHADER

#version 330 core

layout(location = 0) out vec4 color;

void main() {
	color = vec4(1.0, 1.0, 1.0, 1.0);
}
