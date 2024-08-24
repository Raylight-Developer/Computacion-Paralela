#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 coords;

uniform float display_aspect_ratio;
uniform float render_aspect_ratio;

out vec2 uv_coords;

void main() {
	if (display_aspect_ratio < render_aspect_ratio)
		gl_Position = vec4(position * vec2(1.0, display_aspect_ratio/render_aspect_ratio), 0.0, 1.0);
	else
		gl_Position = vec4(position * vec2(render_aspect_ratio/display_aspect_ratio, 1.0), 0.0, 1.0);
	uv_coords = coords;
}