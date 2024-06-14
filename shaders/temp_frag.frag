#version 460

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

const float coord_cached_values[16] = {1.0,  2.0, 1.0,  -1.0, 1.0, 0.0,
                                       2.0,  1.0, -1.0, 0.0,  1.0, -1.0,
                                       -1.0, 1.0, 1.0,  0.0};

vec3 get_val(vec3 vec) {
  int index = get_max_index(abs(vec));

  float max_value_sign = coord_cached_values[12 + (int(sign(vec[index])) + 1)];

  float layer = float(index) * 2.0 + ((max_value_sign * -1.0) + 1.0) * 0.5;

  float vec_yz_sign = coord_cached_values[index * 4];

  vec.y *= vec_yz_sign;
  vec.z *= vec_yz_sign;

  vec[(index + 1) % 2] *= max_value_sign;

  vec2 coord = vec2(vec[int(coord_cached_values[index * 4 + 1])],
                    vec[int(coord_cached_values[index * 4 + 2])]) *
               coord_cached_values[index * 4 + 3];

  return vec3((coord + vec2(1.0)) * 0.5, layer);
}

void main() { frag_color = vec4(get_val(vec3(1.0)), 1.0); }