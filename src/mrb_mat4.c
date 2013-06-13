#include "mrb_mat4.h"

#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

const mat4 mat4_identity_const = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

static struct RClass* mrb_mat4_class = NULL;

mrb_data_type mat4_type = { "Mat4", mat4_free };

mat4* 
allocate_new_mat4(mrb_state* mrb) {
  return (struct mat4 *)mrb_malloc(mrb, sizeof(struct mat4)); 
}

void 
mat4_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value 
mat4_wrap(mrb_state *mrb, struct RClass *tc, struct mat4* tm)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &mat4_type, tm));
}

struct mat4*
mat4_get_ptr(mrb_state* mrb, mrb_value value)
{
  return (struct mat4*)mrb_data_get_ptr(mrb, value, &mat4_type);
}

struct mat4* 
create_new_mat4_identity(mrb_state* mrb) 
{
  struct mat4* matrix = allocate_new_mat4(mrb);
  memcpy(matrix, &mat4_identity_const, sizeof(mat4));
  return matrix;
}

mrb_value 
mat4_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y;
  int n;
  struct mat4 *tm;

  tm = (struct mat4*)DATA_PTR(self);
  if (tm) {
    mat4_free(mrb, tm);
  }
  DATA_TYPE(self) = &mat4_type;
  DATA_PTR(self) = NULL;

  tm = create_new_mat4_identity(mrb);

  DATA_PTR(self) = tm;
  return self;
}

mrb_value 
mat4_equals(mrb_state *mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct mat4* arg = mat4_get_ptr(mrb, new_value);
  struct mat4* value = mat4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_bool_value(
    value->f11 == arg->f11 &&
    value->f12 == arg->f12 &&
    value->f13 == arg->f13 &&
    value->f14 == arg->f14 &&

    value->f21 == arg->f21 &&
    value->f22 == arg->f22 &&
    value->f23 == arg->f23 &&
    value->f24 == arg->f24 &&

    value->f31 == arg->f31 &&
    value->f32 == arg->f32 &&
    value->f33 == arg->f33 &&
    value->f34 == arg->f34 &&

    value->f41 == arg->f41 &&
    value->f42 == arg->f42 &&
    value->f43 == arg->f43 &&
    value->f44 == arg->f44);
}

mrb_value 
mat4_is_identity(mrb_state *mrb, mrb_value self)
{
  mat4* value = mat4_get_ptr(mrb, self);

  return mrb_bool_value(
    value->f11 == mat4_identity_const.f11 &&
    value->f12 == mat4_identity_const.f12 &&
    value->f13 == mat4_identity_const.f13 &&
    value->f14 == mat4_identity_const.f14 &&

    value->f21 == mat4_identity_const.f21 &&
    value->f22 == mat4_identity_const.f22 &&
    value->f23 == mat4_identity_const.f23 &&
    value->f24 == mat4_identity_const.f24 &&

    value->f31 == mat4_identity_const.f31 &&
    value->f32 == mat4_identity_const.f32 &&
    value->f33 == mat4_identity_const.f33 &&
    value->f34 == mat4_identity_const.f34 &&

    value->f41 == mat4_identity_const.f41 &&
    value->f42 == mat4_identity_const.f42 &&
    value->f43 == mat4_identity_const.f43 &&
    value->f44 == mat4_identity_const.f44);
}

void init_mat4(mrb_state* mrb)
{
  mrb_mat4_class = mrb_define_class(mrb, "Mat4", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_mat4_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_mat4_class, "==", mat4_equals, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "initialize", mat4_initialize, ARGS_ANY());
  mrb_define_method(mrb, mrb_mat4_class, "identity?", mat4_is_identity, ARGS_NONE());
  // mrb_define_method(mrb, mrb_mat4_class, "to_s", vec2_inspect, ARGS_NONE());
  // mrb_define_method(mrb, mrb_mat4_class, "inspect", vec2_inspect, ARGS_NONE());
}