#version 460 core

uniform float display_aspect_ratio;
uniform float render_aspect_ratio;
uniform uint  view_layer;
uniform bool  debug;

uniform sampler2D accumulation_render_layer;
uniform sampler2D raw_render_layer;
uniform sampler2D bvh_render_layer;
uniform sampler2D normal_render_layer;

in vec2 uv_coords;
out vec4 color_out;

float f_mapFloat(float from_min, float from_max, float to_min, float to_max, float value) {
	return (to_min + ((to_max - to_min) / (from_max - from_min)) * (value - from_min));
}

vec2 f_mapVec2(vec2 from_min, vec2 from_max, vec2 to_min, vec2 to_max, vec2 value) {
	return vec2(f_mapFloat(from_min.x, from_max.x, to_min.x, to_max.x, value.x), f_mapFloat(from_min.y, from_max.y, to_min.y, to_max.y, value.y));
}

vec3 ColorGrade( vec3 vColor ) {
	vec3 vHue = vec3(1.0, .7, .2);

	vec3 vGamma = 1.0 + vHue * 0.6;
	vec3 vGain = vec3(.9) + vHue * vHue * 8.0;

	vColor *= 1.5;

	float fMaxLum = 100.0;
	vColor /= fMaxLum;
	vColor = pow( vColor, vGamma );
	vColor *= vGain;
	vColor *= fMaxLum;
	return pow(tanh(vColor), vec3(0.57));
}

void main() {
	if (debug) {
		switch      (view_layer) {
			case 0:
				color_out = vec4(ColorGrade(texture(accumulation_render_layer, uv_coords).rgb), 1);
				break;
			case 1:
				color_out = texture(raw_render_layer, uv_coords);
				break;
			case 2:
				color_out = texture(bvh_render_layer, uv_coords);
				break;
			case 3:
				color_out = texture(normal_render_layer, uv_coords);
				break;
		}
	}
	else {
		color_out = vec4(ColorGrade(texture(accumulation_render_layer, uv_coords).rgb), 1);
	}
}