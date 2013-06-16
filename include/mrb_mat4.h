#ifndef MRUBY_GMATH_MAT4_H
#define MRUBY_GMATH_MAT4_H

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

typedef struct mat4 mat4;

struct mat4
{
  float f11, f12, f13, f14;
  float f21, f22, f23, f24;
  float f31, f32, f33, f34;
  float f41, f42, f43, f44;
};

extern const mat4 mat4_identity_const;

void mat4_free(mrb_state *mrb, void *p);

void init_mat4(mrb_state* mrb);
mrb_value mat4_wrap(mrb_state *mrb, struct mat4* tm);
struct mat4* mat4_get_ptr(mrb_state* mrb, mrb_value value);

#endif