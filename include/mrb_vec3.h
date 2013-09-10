#ifndef MRUBY_GMATH_VEC3_H
#define MRUBY_GMATH_VEC3_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct vec3
{
  float x, y, z;
};

void vec3_free(mrb_state *mrb, void *p);

void init_vec3(mrb_state* mrb);
mrb_value vec3_wrap(mrb_state *mrb, struct RClass *tc, struct vec3* tm);
mrb_value wrap_new_vec3(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z);
struct vec3* vec3_get_ptr(mrb_state* mrb, mrb_value value);

mrb_value vec3_get_x(mrb_state* mrb, mrb_value self);
mrb_value vec3_set_x(mrb_state* mrb, mrb_value self);

mrb_value vec3_get_y(mrb_state* mrb, mrb_value self);
mrb_value vec3_set_y(mrb_state* mrb, mrb_value self);

mrb_value vec3_get_z(mrb_state* mrb, mrb_value self);
mrb_value vec3_set_z(mrb_state* mrb, mrb_value self);

#endif