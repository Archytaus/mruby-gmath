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
mat4_get_f11(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f11);
}

mrb_value
mat4_get_f12(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f12);
}

mrb_value
mat4_get_f13(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f13);
}

mrb_value
mat4_get_f14(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f14);
}

mrb_value
mat4_get_f21(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f21);
}

mrb_value
mat4_get_f22(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f22);
}

mrb_value
mat4_get_f23(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f23);
}

mrb_value
mat4_get_f24(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f24);
}

mrb_value
mat4_get_f31(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f31);
}

mrb_value
mat4_get_f32(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f32);
}

mrb_value
mat4_get_f33(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f33);
}

mrb_value
mat4_get_f34(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f34);
}

mrb_value
mat4_get_f41(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f41);
}

mrb_value
mat4_get_f42(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f42);
}

mrb_value
mat4_get_f43(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f43);
}

mrb_value
mat4_get_f44(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(value->f44);
}

mrb_value 
mat4_set_f11(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f11 = mrb_float(new_value);

  return new_value;
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


mrb_value 
mat4_inspect(mrb_state* mrb, mrb_value self)
{
  char buf[256];
  int len;

  mat4* selfValue = mat4_get_ptr(mrb, self);

  if (!selfValue) return mrb_nil_value();

  len = snprintf(buf, sizeof(buf), 
    "[%.4f,%.4f,%.4f,%.4f][%.4f,%.4f,%.4f,%.4f][%.4f,%.4f,%.4f,%.4f][%.4f,%.4f,%.4f,%.4f]",
    selfValue->f11, selfValue->f12, selfValue->f13, selfValue->f14,
    selfValue->f21, selfValue->f22, selfValue->f23, selfValue->f24,
    selfValue->f31, selfValue->f32, selfValue->f33, selfValue->f34,
    selfValue->f41, selfValue->f42, selfValue->f43, selfValue->f44);

  return mrb_str_new(mrb, buf, len);
}

void init_mat4(mrb_state* mrb)
{
  mrb_mat4_class = mrb_define_class(mrb, "Mat4", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_mat4_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_mat4_class, "==", mat4_equals, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "initialize", mat4_initialize, ARGS_ANY());
  mrb_define_method(mrb, mrb_mat4_class, "identity?", mat4_is_identity, ARGS_NONE());

  mrb_define_method(mrb, mrb_mat4_class, "to_s", mat4_inspect, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "inspect", mat4_inspect, ARGS_NONE());

  mrb_define_method(mrb, mrb_mat4_class, "f11", mat4_get_f11, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f12", mat4_get_f12, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f13", mat4_get_f13, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f14", mat4_get_f14, ARGS_NONE());

  mrb_define_method(mrb, mrb_mat4_class, "f21", mat4_get_f21, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f22", mat4_get_f22, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f23", mat4_get_f23, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f24", mat4_get_f24, ARGS_NONE());

  mrb_define_method(mrb, mrb_mat4_class, "f31", mat4_get_f31, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f32", mat4_get_f32, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f33", mat4_get_f33, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f34", mat4_get_f34, ARGS_NONE());

  mrb_define_method(mrb, mrb_mat4_class, "f41", mat4_get_f41, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f42", mat4_get_f42, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f43", mat4_get_f43, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "f44", mat4_get_f44, ARGS_NONE());

  // mrb_define_method(mrb, mrb_vec2_class, "+", vec2_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add", vec2_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add!", vec2_plus_inplace, ARGS_REQ(1));

}