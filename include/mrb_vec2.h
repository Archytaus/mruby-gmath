#ifndef MRUBY_GMATH_VEC2_H
#define MRUBY_GMATH_VEC2_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct vec2
{
  float x, y;
};

void vec2_free(mrb_state *mrb, void *p);

void init_vec2(mrb_state* mrb);
mrb_value vec2_wrap(mrb_state *mrb, struct RClass *tc, struct vec2* tm);
mrb_value wrap_new_vec2(mrb_state* mrb, mrb_float x, mrb_float y);
struct vec2* vec2_get_ptr(mrb_state* mrb, mrb_value value);

mrb_value vec2_get_x(mrb_state* mrb, mrb_value self);
mrb_value vec2_set_x(mrb_state* mrb, mrb_value self);

mrb_value vec2_get_y(mrb_state* mrb, mrb_value self);
mrb_value vec2_set_y(mrb_state* mrb, mrb_value self);

#endif