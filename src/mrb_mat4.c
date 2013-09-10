#include "mrb_mat4.h"

#include <string.h>
#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/array.h>

#include "mrb_vec2.h"

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
  return DATA_CHECK_GET_PTR(mrb, value, &mat4_type, struct mat4);
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
  return mrb_float_value(mrb, value->f11);
}

mrb_value
mat4_get_f12(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f12);
}

mrb_value
mat4_get_f13(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f13);
}

mrb_value
mat4_get_f14(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f14);
}

mrb_value
mat4_get_f21(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f21);
}

mrb_value
mat4_get_f22(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f22);
}

mrb_value
mat4_get_f23(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f23);
}

mrb_value
mat4_get_f24(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f24);
}

mrb_value
mat4_get_f31(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f31);
}

mrb_value
mat4_get_f32(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f32);
}

mrb_value
mat4_get_f33(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f33);
}

mrb_value
mat4_get_f34(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f34);
}

mrb_value
mat4_get_f41(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f41);
}

mrb_value
mat4_get_f42(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f42);
}

mrb_value
mat4_get_f43(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f43);
}

mrb_value
mat4_get_f44(mrb_state* mrb, mrb_value self) {
  mat4* value = mat4_get_ptr(mrb, self);
  return mrb_float_value(mrb, value->f44);
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
  mrb_get_args(mrb, "o", &new_value);
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
  mrb_get_args(mrb, "o", &new_value);
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

mrb_value
mat4_orthogonal(mrb_state* mrb, mrb_value self)
{
  mrb_value left_value, right_value, top_value, bottom_value, near_value, far_value;
  mrb_get_args(mrb, "ffffff", &left_value, &right_value, &top_value, &bottom_value, &near_value, &far_value);
  mrb_float left = mrb_float(left_value);
  mrb_float right = mrb_float(right_value);
  mrb_float top = mrb_float(top_value);
  mrb_float bottom = mrb_float(bottom_value);
  mrb_float near = mrb_float(near_value);
  mrb_float far = mrb_float(far_value);

  struct mat4* matrix = allocate_new_mat4(mrb);
  matrix->f11 = 2.0f / (right - left);
  matrix->f12 = 0.0f;
  matrix->f13 = 0.0f;
  matrix->f14 = 0.0f;

  matrix->f21 = 0.0f;
  matrix->f22 = 2.0f / (top - bottom);
  matrix->f23 = 0.0f;
  matrix->f24 = 0.0f;

  matrix->f31 = 0.0f;
  matrix->f32 = 0.0f;
  matrix->f33 = -2.0f / (near - far);
  matrix->f34 = 0.0f;

  matrix->f41 = (right + left) / (right - left);
  matrix->f42 = (top + bottom) / (top - bottom);
  matrix->f43 = (far + near) / (far - near);
  matrix->f44 = 1.0f;

  return mat4_wrap(mrb, matrix);
}

mrb_value
mat4_orthogonal_2d(mrb_state* mrb, mrb_value self)
{
  mrb_value left_value, right_value, top_value, bottom_value;
  mrb_get_args(mrb, "ffff", &left_value, &right_value, &top_value, &bottom_value);
  mrb_float left = mrb_float(left_value);
  mrb_float right = mrb_float(right_value);
  mrb_float top = mrb_float(top_value);
  mrb_float bottom = mrb_float(bottom_value);

  struct mat4* matrix = allocate_new_mat4(mrb);
  matrix->f11 = 2.0f / (right - left);
  matrix->f12 = 0.0f;
  matrix->f13 = 0.0f;
  matrix->f14 = 0.0f;

  matrix->f21 = 0.0f;
  matrix->f22 = 2.0f / (top - bottom);
  matrix->f23 = 0.0f;
  matrix->f24 = 0.0f;

  matrix->f31 = 0.0f;
  matrix->f32 = 0.0f;
  matrix->f33 = -1.0f;
  matrix->f34 = 0.0f;

  matrix->f41 = (left + right) / (left - right);
  matrix->f42 = (bottom + top) / (bottom - top);
  matrix->f43 = 0.0f;
  matrix->f44 = 1.0f;

  return mat4_wrap(mrb, matrix);
}

mrb_value
mat4_perspective(mrb_state* mrb, mrb_value self)
{
  mrb_value fov_value, aspect_value, near_value, far_value;
  mrb_get_args(mrb, "ffff", &fov_value, &aspect_value, &near_value, &far_value);
  mrb_float fov = mrb_float(fov_value);
  mrb_float aspect_ratio = mrb_float(aspect_value);
  mrb_float near = mrb_float(near_value);
  mrb_float far = mrb_float(far_value);

  mrb_float width = 1.0f / tan(fov * 0.5f);
  mrb_float height = width / aspect_ratio;

  struct mat4* matrix = allocate_new_mat4(mrb);
  matrix->f11 = width;
  matrix->f12 = 0.0f;
  matrix->f13 = 0.0f;
  matrix->f14 = 0.0f;

  matrix->f21 = 0.0f;
  matrix->f22 = height;
  matrix->f23 = 0.0f;
  matrix->f24 = 0.0f;

  matrix->f31 = 0.0f;
  matrix->f32 = 0.0f;
  matrix->f33 = 1.0f / (near - far);
  matrix->f34 = near / (near - far);

  matrix->f41 = 0.0f;
  matrix->f42 = 0.0f;
  matrix->f43 = 0.0f;
  matrix->f44 = 1.0f;

  return mat4_wrap(mrb, matrix);
}

mrb_value
mat4_transform_vec2(mrb_state* mrb, mat4* m, struct vec2* v) {
  return wrap_new_vec2(mrb, v->x * m->f11 + v->y * m->f21 + 1 * m->f41, v->x * m->f12 + v->y * m->f22 + 1 * m->f42);
}

mrb_value
mat4_transform(mrb_state* mrb, mrb_value self)
{
  mrb_value vector;
  mrb_get_args(mrb, "o", &vector);

  const char* vector_class = mrb_obj_classname(mrb, vector);
  mat4* selfValue = mat4_get_ptr(mrb, self);

  if (strcmp(vector_class, "Vec2") == 0) {
    return mat4_transform_vec2(mrb, selfValue, vec2_get_ptr(mrb, vector));
  }
  
  return mrb_nil_value();
}

mat4 
generate_inverse(mat4* m)
{
  mat4 inv;

  inv.f11 = m->f22  * m->f33 * m->f44 - 
             m->f22  * m->f34 * m->f43 - 
             m->f32  * m->f23  * m->f44 + 
             m->f32  * m->f24  * m->f43 +
             m->f42 * m->f23  * m->f34 - 
             m->f42 * m->f24  * m->f33;

  inv.f21 = -m->f21  * m->f33 * m->f44 + 
            m->f21  * m->f34 * m->f43 + 
            m->f31  * m->f23  * m->f44 - 
            m->f31  * m->f24  * m->f43 - 
            m->f41 * m->f23  * m->f34 + 
            m->f41 * m->f24  * m->f33;

  inv.f31 = m->f21  * m->f32 * m->f44 - 
           m->f21  * m->f34 * m->f42 - 
           m->f31  * m->f22 * m->f44 + 
           m->f31  * m->f24 * m->f42 + 
           m->f41 * m->f22 * m->f34 - 
           m->f41 * m->f24 * m->f32;

  inv.f41 = -m->f21  * m->f32 * m->f43 + 
             m->f21  * m->f33 * m->f42 +
             m->f31  * m->f22 * m->f43 - 
             m->f31  * m->f23 * m->f42 - 
             m->f41 * m->f22 * m->f33 + 
             m->f41 * m->f23 * m->f32;

  inv.f12 = -m->f12  * m->f33 * m->f44 + 
            m->f12  * m->f34 * m->f43 + 
            m->f32  * m->f13 * m->f44 - 
            m->f32  * m->f14 * m->f43 - 
            m->f42 * m->f13 * m->f34 + 
            m->f42 * m->f14 * m->f33;

  inv.f22 = m->f11  * m->f33 * m->f44 - 
           m->f11  * m->f34 * m->f43 - 
           m->f31  * m->f13 * m->f44 + 
           m->f31  * m->f14 * m->f43 + 
           m->f41 * m->f13 * m->f34 - 
           m->f41 * m->f14 * m->f33;

  inv.f32 = -m->f11  * m->f32 * m->f44 + 
            m->f11  * m->f34 * m->f42 + 
            m->f31  * m->f12 * m->f44 - 
            m->f31  * m->f14 * m->f42 - 
            m->f41 * m->f12 * m->f34 + 
            m->f41 * m->f14 * m->f32;

  inv.f42 = m->f11  * m->f32 * m->f43 - 
            m->f11  * m->f33 * m->f42 - 
            m->f31  * m->f12 * m->f43 + 
            m->f31  * m->f13 * m->f42 + 
            m->f41 * m->f12 * m->f33 - 
            m->f41 * m->f13 * m->f32;

  inv.f13 = m->f12  * m->f23 * m->f44 - 
           m->f12  * m->f24 * m->f43 - 
           m->f22  * m->f13 * m->f44 + 
           m->f22  * m->f14 * m->f43 + 
           m->f42 * m->f13 * m->f24 - 
           m->f42 * m->f14 * m->f23;

  inv.f23 = -m->f11  * m->f23 * m->f44 + 
            m->f11  * m->f24 * m->f43 + 
            m->f21  * m->f13 * m->f44 - 
            m->f21  * m->f14 * m->f43 - 
            m->f41 * m->f13 * m->f24 + 
            m->f41 * m->f14 * m->f23;

  inv.f33 = m->f11  * m->f22 * m->f44 - 
            m->f11  * m->f24 * m->f42 - 
            m->f21  * m->f12 * m->f44 + 
            m->f21  * m->f14 * m->f42 + 
            m->f41 * m->f12 * m->f24 - 
            m->f41 * m->f14 * m->f22;

  inv.f43 = -m->f11  * m->f22 * m->f43 + 
             m->f11  * m->f23 * m->f42 + 
             m->f21  * m->f12 * m->f43 - 
             m->f21  * m->f13 * m->f42 - 
             m->f41 * m->f12 * m->f23 + 
             m->f41 * m->f13 * m->f22;

  inv.f14 = -m->f12 * m->f23 * m->f34 + 
            m->f12 * m->f24 * m->f33 + 
            m->f22 * m->f13 * m->f34 - 
            m->f22 * m->f14 * m->f33 - 
            m->f32 * m->f13 * m->f24 + 
            m->f32 * m->f14 * m->f23;

  inv.f24 = m->f11 * m->f23 * m->f34 - 
           m->f11 * m->f24 * m->f33 - 
           m->f21 * m->f13 * m->f34 + 
           m->f21 * m->f14 * m->f33 + 
           m->f31 * m->f13 * m->f24 - 
           m->f31 * m->f14 * m->f23;

  inv.f34 = -m->f11 * m->f22 * m->f34 + 
             m->f11 * m->f24 * m->f32 + 
             m->f21 * m->f12 * m->f34 - 
             m->f21 * m->f14 * m->f32 - 
             m->f31 * m->f12 * m->f24 + 
             m->f31 * m->f14 * m->f22;

  inv.f44 = m->f11 * m->f22 * m->f33 - 
            m->f11 * m->f23 * m->f32 - 
            m->f21 * m->f12 * m->f33 + 
            m->f21 * m->f13 * m->f32 + 
            m->f31 * m->f12 * m->f23 - 
            m->f31 * m->f13 * m->f22;

  float det = m->f11 * inv.f11 + m->f12 * inv.f21 + m->f13 * inv.f31 + m->f14 * inv.f41;

  if (det == 0)
    return inv;

  det = 1.0 / det;

  inv.f11 *= det;
  inv.f12 *= det;
  inv.f13 *= det;
  inv.f14 *= det;
  inv.f21 *= det;
  inv.f22 *= det;
  inv.f23 *= det;
  inv.f24 *= det;
  inv.f31 *= det;
  inv.f32 *= det;
  inv.f33 *= det;
  inv.f34 *= det;
  inv.f41 *= det;
  inv.f42 *= det;
  inv.f43 *= det;
  inv.f44 *= det;

  return inv;
}

mrb_value
mat4_invert(mrb_state* mrb, mrb_value self)
{  
  mat4* m = mat4_get_ptr(mrb, self);
  mat4* newMatrix = allocate_new_mat4(mrb);

  mat4 inv = generate_inverse(m);

  memcpy(newMatrix, &inv, sizeof(mat4));

  return mat4_wrap(mrb, newMatrix);
}

mrb_value
mat4_invert_inplace(mrb_state* mrb, mrb_value self)
{  
  mat4* m = mat4_get_ptr(mrb, self);

  mat4 inv = generate_inverse(m);;

  memcpy(m, &inv, sizeof(mat4));

  return self;
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

  mrb_define_method(mrb, mrb_mat4_class, "f11=", mat4_set_f11, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f12=", mat4_set_f12, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f13=", mat4_set_f13, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f14=", mat4_set_f14, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "f21=", mat4_set_f21, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f22=", mat4_set_f22, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f23=", mat4_set_f23, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f24=", mat4_set_f24, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "f31=", mat4_set_f31, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f32=", mat4_set_f32, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f33=", mat4_set_f33, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f34=", mat4_set_f34, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "f41=", mat4_set_f41, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f42=", mat4_set_f42, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f43=", mat4_set_f43, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_mat4_class, "f44=", mat4_set_f44, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "+", mat4_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add", vec2_plus, ARGS_REQ(1));
  // mrb_define_method(mrb, mrb_vec2_class, "add!", vec2_plus_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "transform", mat4_transform, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_mat4_class, "invert", mat4_invert, ARGS_NONE());
  mrb_define_method(mrb, mrb_mat4_class, "invert!", mat4_invert_inplace, ARGS_NONE());

  mrb_define_class_method(mrb, mrb_mat4_class, "orthogonal", mat4_orthogonal, ARGS_REQ(6));
  mrb_define_class_method(mrb, mrb_mat4_class, "orthogonal_2d", mat4_orthogonal_2d, ARGS_REQ(4));

  mrb_define_class_method(mrb, mrb_mat4_class, "perspective", mat4_perspective, ARGS_REQ(4));
}