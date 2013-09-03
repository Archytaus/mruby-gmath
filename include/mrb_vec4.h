#ifndef MRUBY_GMATH_VEC4_H
#define MRUBY_GMATH_VEC4_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct vec4
{
  float x, y, z, w;
};

void vec4_free(mrb_state *mrb, void *p);

void init_vec4(mrb_state* mrb);
mrb_value vec4_wrap(mrb_state *mrb, struct RClass *tc, struct vec4* tm);
mrb_value wrap_new_vec4(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z, mrb_float w);
struct vec4* vec4_get_ptr(mrb_state* mrb, mrb_value value);

mrb_value vec4_get_x(mrb_state* mrb, mrb_value self);
mrb_value vec4_set_x(mrb_state* mrb, mrb_value self);

mrb_value vec4_get_y(mrb_state* mrb, mrb_value self);
mrb_value vec4_set_y(mrb_state* mrb, mrb_value self);

#endif