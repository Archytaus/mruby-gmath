#include "mrb_mat4.h"

#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/array.h>

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
mat4_wrap(mrb_state *mrb, struct mat4* tm)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_mat4_class, &mat4_type, tm));
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

mrb_float 
mrb_get_float_value(mrb_value value) {
    if (mrb_type(value) == MRB_TT_FIXNUM) {
      return (mrb_float)mrb_fixnum(value);
    } else if (mrb_type(value) == MRB_TT_FLOAT) {
      return mrb_float(value);
    }

    return NAN;
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

  mrb_value *argv;
  int argc;

  mrb_get_args(mrb, "*" , &argv, &argc);
  // printf("Argument count: %i\n", argc);

  if (argc == 0)
  {
    tm = create_new_mat4_identity(mrb);
  }
  else if (argc == 4) 
  {
    for (int i=0; i<argc; i++) {
      mrb_check_type(mrb, argv[i], MRB_TT_ARRAY);
    }
    
    struct RArray *f1 = mrb_ary_ptr(argv[0]);
    struct RArray *f2 = mrb_ary_ptr(argv[1]);
    struct RArray *f3 = mrb_ary_ptr(argv[2]);
    struct RArray *f4 = mrb_ary_ptr(argv[3]);

    tm = allocate_new_mat4(mrb);
    tm->f11 = mrb_get_float_value(f1->ptr[0]);
    tm->f12 = mrb_get_float_value(f1->ptr[1]);
    tm->f13 = mrb_get_float_value(f1->ptr[2]);
    tm->f14 = mrb_get_float_value(f1->ptr[3]);

    tm->f21 = mrb_get_float_value(f2->ptr[0]);
    tm->f22 = mrb_get_float_value(f2->ptr[1]);
    tm->f23 = mrb_get_float_value(f2->ptr[2]);
    tm->f24 = mrb_get_float_value(f2->ptr[3]);

    tm->f31 = mrb_get_float_value(f3->ptr[0]);
    tm->f32 = mrb_get_float_value(f3->ptr[1]);
    tm->f33 = mrb_get_float_value(f3->ptr[2]);
    tm->f34 = mrb_get_float_value(f3->ptr[3]);

    tm->f41 = mrb_get_float_value(f4->ptr[0]);
    tm->f42 = mrb_get_float_value(f4->ptr[1]);
    tm->f43 = mrb_get_float_value(f4->ptr[2]);
    tm->f44 = mrb_get_float_value(f4->ptr[3]);
  }
  else if (argc == 16) 
  {
    tm = allocate_new_mat4(mrb);
    tm->f11 = mrb_get_float_value(argv[0]);
    tm->f12 = mrb_get_float_value(argv[1]);
    tm->f13 = mrb_get_float_value(argv[2]);
    tm->f14 = mrb_get_float_value(argv[3]);

    tm->f21 = mrb_get_float_value(argv[4]);
    tm->f22 = mrb_get_float_value(argv[5]);
    tm->f23 = mrb_get_float_value(argv[6]);
    tm->f24 = mrb_get_float_value(argv[7]);

    tm->f31 = mrb_get_float_value(argv[8]);
    tm->f32 = mrb_get_float_value(argv[9]);
    tm->f33 = mrb_get_float_value(argv[10]);
    tm->f34 = mrb_get_float_value(argv[11]);

    tm->f41 = mrb_get_float_value(argv[12]);
    tm->f42 = mrb_get_float_value(argv[13]);
    tm->f43 = mrb_get_float_value(argv[14]);
    tm->f44 = mrb_get_float_value(argv[15]);
  }

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
mat4_set_f12(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f12 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f13(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f13 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f14(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f14 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f21(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f21 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f22(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f22 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f23(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f23 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f24(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f24 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f31(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f31 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f32(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f32 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f33(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f33 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f34(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f34 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f41(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f41 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f42(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f42 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f43(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f43 = mrb_float(new_value);

  return new_value;
}

mrb_value 
mat4_set_f44(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  mat4* value = mat4_get_ptr(mrb, self);
  value->f44 = mrb_float(new_value);

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

mrb_value
mat4_plus(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct mat4* arg = mat4_get_ptr(mrb, new_value);
  struct mat4* value = mat4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  struct mat4* matrix = allocate_new_mat4(mrb);
  matrix->f11 = value->f11 + arg->f11;
  matrix->f12 = value->f12 + arg->f12;
  matrix->f13 = value->f13 + arg->f13;
  matrix->f14 = value->f14 + arg->f14;
  
  matrix->f21 = value->f21 + arg->f21;
  matrix->f22 = value->f22 + arg->f22;
  matrix->f23 = value->f23 + arg->f23;
  matrix->f24 = value->f24 + arg->f24;

  matrix->f31 = value->f31 + arg->f31;
  matrix->f32 = value->f32 + arg->f32;
  matrix->f33 = value->f33 + arg->f33;
  matrix->f34 = value->f34 + arg->f34;

  matrix->f41 = value->f41 + arg->f41;
  matrix->f42 = value->f42 + arg->f42;
  matrix->f43 = value->f43 + arg->f43;
  matrix->f44 = value->f44 + arg->f44;

  return mat4_wrap(mrb, matrix);
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

  mrb_define_method(mrb, mrb_mat4_class, "+", mat4_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add", vec2_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add!", vec2_plus_inplace, ARGS_REQ(1));

}