#version 310 es

precision highp float;

layout(location = 0) out vec4 frag_color;

int get_max_index(vec3 vec) {
  float max_val = vec.x;
  int index = 0;

  if (vec.y > max_val) {
    max_val = vec.y;
    index = 1;
  }

  if (vec.z > max_val) {
    index = 2;
  }

  return index;
}

layout(std140, binding = 0) uniform CachedValues {
  float coord_cached_values[16];
};

vec3 UVWToUVLayer(vec3 vec) {
  int index = get_max_index(abs(vec));

  float max_value_sign = coord_cached_values[13 + (int(sign(vec[index])))];

  float layer = float(index) * 2.0 + ((max_value_sign * -1.0) + 1.0) * 0.5;

  float vec_yz_sign = coord_cached_values[index * 4];

  vec.y *= vec_yz_sign;
  vec.z *= vec_yz_sign;

  vec[(index + 1) % 2] *= max_value_sign;

  vec /= vec[index];

  vec2 coord = vec2(vec[int(coord_cached_values[index * 4 + 1])],
                    vec[int(coord_cached_values[index * 4 + 2])]) *
               coord_cached_values[index * 4 + 3];

  return vec3((coord + vec2(1.0)) * 0.5, layer);
}

layout(location = 0) in vec3 random_value;
layout(location = 1) in vec3 color;

void main() {
  vec3 temp_vec = UVWToUVLayer(random_value);
  frag_color = vec4(color, 1.0);
}
