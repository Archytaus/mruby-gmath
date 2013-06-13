#include "mrb_gmath.h"
#include "mrb_vec2.h"
#include "mrb_mat4.h"

static struct RClass* mrb_gmath_class = NULL;

void
mrb_mruby_gmath_gem_init(mrb_state* mrb) {
  mrb_gmath_class = mrb_define_module(mrb, "GMath");
  
  init_vec2(mrb);
  init_mat4(mrb);
}

void
mrb_mruby_gmath_gem_final(mrb_state* mrb) {
  // finalizer
}
