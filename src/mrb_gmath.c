#include "mrb_gmath.h"

static struct RClass* mrb_gmath_class = NULL;

void
mrb_mruby_gmath_gem_init(mrb_state* mrb) {
  mrb_gmath_class = mrb_define_module(mrb, "GMath");
  
}

void
mrb_mruby_gmath_gem_final(mrb_state* mrb) {
  // finalizer
}
