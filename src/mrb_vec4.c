#include "mrb_vec4.h"

#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

static struct RClass* mrb_vec4_class = NULL;

struct mrb_data_type vec4_type = { "Vec4", vec4_free };

struct vec4* allocate_new_vec4(mrb_state* mrb) {
  return (struct vec4 *)mrb_malloc(mrb, sizeof(struct vec4)); 
}

struct vec4* create_new_vec4(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z, mrb_float w) {
  struct vec4* newVec4 = allocate_new_vec4(mrb);
  newVec4->x = x;
  newVec4->y = y;
  newVec4->z = z;
  newVec4->w = w;
  return newVec4;
}

mrb_value wrap_new_vec4(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z, mrb_float w) {
  return vec4_wrap(mrb, mrb_vec4_class, create_new_vec4(mrb, x, y, z, w));
}

void 
vec4_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value 
vec4_wrap(mrb_state *mrb, struct RClass *tc, struct vec4* tm)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &vec4_type, tm));
}

struct vec4*
vec4_get_ptr(mrb_state* mrb, mrb_value value)
{
  return DATA_CHECK_GET_PTR(mrb, value, &vec4_type, struct vec4);
}

mrb_value vec4_get_x(mrb_state* mrb, mrb_value self)
{
  struct vec4 *vec = vec4_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->x);
}

mrb_value vec4_set_x(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec4 *vec = vec4_get_ptr(mrb, self);
  vec->x = mrb_float(new_value);

  return new_value;
}

mrb_value vec4_get_y(mrb_state* mrb, mrb_value self)
{
  struct vec4 *vec = vec4_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->y);
}

mrb_value vec4_set_y(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec4 *vec = vec4_get_ptr(mrb, self);
  vec->y = mrb_float(new_value);

  return new_value;
}

mrb_value vec4_get_z(mrb_state* mrb, mrb_value self)
{
  struct vec4 *vec = vec4_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->z);
}

mrb_value vec4_set_z(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec4 *vec = vec4_get_ptr(mrb, self);
  vec->z = mrb_float(new_value);

  return new_value;
}

mrb_value vec4_get_w(mrb_state* mrb, mrb_value self)
{
  struct vec4 *vec = vec4_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->w);
}

mrb_value vec4_set_w(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec4 *vec = vec4_get_ptr(mrb, self);
  vec->w = mrb_float(new_value);

  return new_value;
}

mrb_value vec4_equals(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_bool_value(
    selfValue->x == arg->x &&
    selfValue->y == arg->y &&
    selfValue->z == arg->z &&
    selfValue->w == arg->w);
}

mrb_value vec4_plus(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec4(mrb, 
    selfValue->x + arg->x, 
    selfValue->y + arg->y,
    selfValue->z + arg->z,
    selfValue->w + arg->w);
}

mrb_value vec4_plus_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  selfValue->x += arg->x;
  selfValue->y += arg->y;
  selfValue->z += arg->z;
  selfValue->w += arg->w;
  return self;
}

mrb_value vec4_subtract(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec4(mrb, 
    selfValue->x - arg->x, 
    selfValue->y - arg->y,
    selfValue->z - arg->z,
    selfValue->w - arg->w);
}

mrb_value vec4_subtract_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  selfValue->x -= arg->x;
  selfValue->y -= arg->y;
  selfValue->z -= arg->z;
  selfValue->w -= arg->w;
  return self;
}

mrb_value vec4_usubtract(mrb_state* mrb, mrb_value self)
{
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!selfValue) return mrb_nil_value();

  return wrap_new_vec4(mrb, 
    0 - selfValue->x, 
    0 - selfValue->y,
    0 - selfValue->z,
    0 - selfValue->w);
}

mrb_value vec4_usubtract_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!selfValue) return mrb_nil_value();

  selfValue->x = 0 - selfValue->x;
  selfValue->y = 0 - selfValue->y;
  selfValue->z = 0 - selfValue->z;
  selfValue->w = 0 - selfValue->w;
  return self;
}

mrb_value vec4_times(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (arg)
  {
    return wrap_new_vec4(mrb, 
      selfValue->x * arg->x, 
      selfValue->y * arg->y,
      selfValue->z * arg->z,
      selfValue->w * arg->w);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec4(mrb, 
      selfValue->x * modifier, 
      selfValue->y * modifier,
      selfValue->z * modifier,
      selfValue->w * modifier);
  }

  return mrb_nil_value();
}

mrb_value vec4_times_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (arg)
  {
    selfValue->x *= arg->x;
    selfValue->y *= arg->y;
    selfValue->z *= arg->z;
    selfValue->w *= arg->w;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x *= modifier;
    selfValue->y *= modifier;
    selfValue->z *= modifier;
    selfValue->w *= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec4_divide(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (arg)
  {
    return wrap_new_vec4(mrb, 
      selfValue->x / arg->x,
      selfValue->y / arg->y,
      selfValue->z / arg->z,
      selfValue->w / arg->w);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec4(mrb, 
      selfValue->x / modifier,
      selfValue->y / modifier,
      selfValue->z / modifier,
      selfValue->w / modifier);
  }

  return mrb_nil_value();
}

mrb_value vec4_divide_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (arg)
  {
    selfValue->x /= arg->x;
    selfValue->y /= arg->y;
    selfValue->z /= arg->z;
    selfValue->w /= arg->w;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x /= modifier;
    selfValue->y /= modifier;
    selfValue->z /= modifier;
    selfValue->w /= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec4_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y, z, w;
  int n;
  struct vec4 *tm;

  tm = (struct vec4*)DATA_PTR(self);
  if (tm) {
    vec4_free(mrb, tm);
  }
  DATA_TYPE(self) = &vec4_type;
  DATA_PTR(self) = NULL;

  n = mrb_get_args(mrb, "|f|fff", &x, &y, &z, &w); // 1 or 2 float arguments

  if (n == 0)
  {
    tm = create_new_vec4(mrb, 0, 0, 0, 0);
  }
  else if (n == 1)
  {
    tm = create_new_vec4(mrb, x, x, x, x);
  }
  else if (n > 1)
  {
    tm = create_new_vec4(mrb, x, y, z, w);
  }

  DATA_PTR(self) = tm;
  return self;
}

mrb_float vec4_calc_length(struct vec4* vector)
{
  return sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z) + (vector->w * vector->w));
}

mrb_value vec4_normalize(mrb_state* mrb, mrb_value self)
{
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);
  mrb_float length = vec4_calc_length(selfValue);

  return wrap_new_vec4(mrb, 
    selfValue->x / length,
    selfValue->y / length,
    selfValue->z / length,
    selfValue->w / length);
}

mrb_value vec4_normalize_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);
  
  mrb_float length = vec4_calc_length(selfValue);
  selfValue->x /= length;
  selfValue->y /= length;
  selfValue->z /= length;
  selfValue->w /= length;
  
  return self;
}

mrb_value vec4_length(mrb_state* mrb, mrb_value self)
{
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec4_calc_length(selfValue));
}

mrb_float vec4_calc_distance(struct vec4* vector, struct vec4* other)
{
  mrb_float x_diff = vector->x - other->x;
  mrb_float y_diff = vector->y - other->y;
  mrb_float z_diff = vector->z - other->z;
  mrb_float w_diff = vector->w - other->w;
  return sqrt((x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff) + (w_diff * w_diff));
}

mrb_value vec4_distance(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(mrb, vec4_calc_distance(selfValue, arg));
}

mrb_float vec4_calc_dot(struct vec4* vector, struct vec4* other)
{
  return (vector->x * other->x) + (vector->y * other->y) + (vector->z * other->z) + (vector->w * other->w);
}

mrb_value vec4_dot(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec4 *arg = vec4_get_ptr(mrb, new_value);
  struct vec4 *selfValue = vec4_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(mrb, vec4_calc_dot(selfValue, arg));
}

mrb_value vec4_inspect(mrb_state* mrb, mrb_value self)
{
  char buf[256];
  int len;

  struct vec4 *selfValue = vec4_get_ptr(mrb, self);
  if (!selfValue) return mrb_nil_value();

  len = snprintf(buf, sizeof(buf), "[%.4f,%.4f,%.4f,%.4f]",
    selfValue->x, selfValue->y, selfValue->z, selfValue->w);
  return mrb_str_new(mrb, buf, len);
}

void init_vec4(mrb_state* mrb)
{
  mrb_vec4_class = mrb_define_class(mrb, "Vec4", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_vec4_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_vec4_class, "x", vec4_get_x, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "x=", vec4_set_x, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "y", vec4_get_y, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "y=", vec4_set_y, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "z", vec4_get_z, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "z=", vec4_set_z, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "w", vec4_get_w, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "w=", vec4_set_w, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "+", vec4_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "add", vec4_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "add!", vec4_plus_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "-", vec4_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "subtract", vec4_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "subtract!", vec4_subtract_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "-@", vec4_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "negate", vec4_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "negate!", vec4_usubtract_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec4_class, "*", vec4_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "multiply", vec4_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "multiply!", vec4_times_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "/", vec4_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "divide", vec4_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "divide!", vec4_divide_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "normalize", vec4_normalize, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "normalize!", vec4_normalize_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec4_class, "length", vec4_length, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec4_class, "dot", vec4_dot, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec4_class, "distance_to", vec4_distance, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "==", vec4_equals, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec4_class, "initialize", vec4_initialize, ARGS_ANY());

  mrb_define_method(mrb, mrb_vec4_class, "to_s", vec4_inspect, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec4_class, "inspect", vec4_inspect, ARGS_NONE());
}