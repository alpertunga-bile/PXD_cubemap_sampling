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

vec3 get_val(vec3 vec) {
  int index = get_max_index(abs(vec));
  float float_index = float(index);

  float max_value_sign = clamp(sign(vec[index]) + 1.0, 0.0, 1.0) * 2.0 - 1.0;

  float layer = float_index * 2.0 + ((max_value_sign * -1.0) + 1.0) * 0.5;

  float vec_yz_sign = clamp((float_index * -1.0) + 2.0, 0.0, 1.0) * 2.0 - 1.0;

  vec.y *= vec_yz_sign;
  vec.z *= vec_yz_sign;

  vec[(index + 1) % 2] *= max_value_sign;

  vec2 coord = vec2(vec[(index + 2) % 3], vec[(index + 1) % 3]);

  if (index == 0) {
    coord *= -1.0;
  }

  if (index == 2) {
    coord = coord.yx * -1.0;
  }

  coord = (coord + vec2(1.0)) * 0.5;

  return vec3(coord, layer);
}

void main() { frag_color = vec4(get_val(vec3(1.0)), 1.0); }