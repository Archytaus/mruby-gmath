#include "mrb_vec3.h"

#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

static struct RClass* mrb_vec3_class = NULL;

struct mrb_data_type vec3_type = { "Vec3", vec3_free };

struct vec3* allocate_new_vec3(mrb_state* mrb) {
  return (struct vec3 *)mrb_malloc(mrb, sizeof(struct vec3)); 
}

struct vec3* create_new_vec3(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z) {
  struct vec3* newVec3 = allocate_new_vec3(mrb);
  newVec3->x = x;
  newVec3->y = y;
  newVec3->z = z;
  return newVec3;
}

mrb_value wrap_new_vec3(mrb_state* mrb, mrb_float x, mrb_float y, mrb_float z) {
  return vec3_wrap(mrb, mrb_vec3_class, create_new_vec3(mrb, x, y, z));
}

void 
vec3_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value 
vec3_wrap(mrb_state *mrb, struct RClass *tc, struct vec3* tm)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &vec3_type, tm));
}

struct vec3*
vec3_get_ptr(mrb_state* mrb, mrb_value value)
{
  return DATA_CHECK_GET_PTR(mrb, value, &vec3_type, struct vec3);
}

mrb_value vec3_get_x(mrb_state* mrb, mrb_value self)
{
  struct vec3 *vec = vec3_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->x);
}

mrb_value vec3_set_x(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec3 *vec = vec3_get_ptr(mrb, self);
  vec->x = mrb_float(new_value);

  return new_value;
}

mrb_value vec3_get_y(mrb_state* mrb, mrb_value self)
{
  struct vec3 *vec = vec3_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->y);
}

mrb_value vec3_set_y(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec3 *vec = vec3_get_ptr(mrb, self);
  vec->y = mrb_float(new_value);

  return new_value;
}

mrb_value vec3_get_z(mrb_state* mrb, mrb_value self)
{
  struct vec3 *vec = vec3_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec->z);
}

mrb_value vec3_set_z(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec3 *vec = vec3_get_ptr(mrb, self);
  vec->z = mrb_float(new_value);

  return new_value;
}

mrb_value vec3_equals(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_bool_value(
    selfValue->x == arg->x &&
    selfValue->y == arg->y &&
    selfValue->z == arg->z);
}

mrb_value vec3_plus(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec3(mrb, 
    selfValue->x + arg->x, 
    selfValue->y + arg->y,
    selfValue->z + arg->z);
}

mrb_value vec3_plus_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  selfValue->x += arg->x;
  selfValue->y += arg->y;
  selfValue->z += arg->z;
  return self;
}

mrb_value vec3_subtract(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec3(mrb, 
    selfValue->x - arg->x, 
    selfValue->y - arg->y,
    selfValue->z - arg->z);
}

mrb_value vec3_subtract_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  selfValue->x -= arg->x;
  selfValue->y -= arg->y;
  selfValue->z -= arg->z;
  return self;
}

mrb_value vec3_usubtract(mrb_state* mrb, mrb_value self)
{
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!selfValue) return mrb_nil_value();

  return wrap_new_vec3(mrb, 
    0 - selfValue->x, 
    0 - selfValue->y,
    0 - selfValue->z);
}

mrb_value vec3_usubtract_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!selfValue) return mrb_nil_value();

  selfValue->x = 0 - selfValue->x;
  selfValue->y = 0 - selfValue->y;
  selfValue->z = 0 - selfValue->z;
  return self;
}

mrb_value vec3_times(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (arg)
  {
    return wrap_new_vec3(mrb, 
      selfValue->x * arg->x, 
      selfValue->y * arg->y,
      selfValue->z * arg->z);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec3(mrb, 
      selfValue->x * modifier, 
      selfValue->y * modifier,
      selfValue->z * modifier);
  }

  return mrb_nil_value();
}

mrb_value vec3_times_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (arg)
  {
    selfValue->x *= arg->x;
    selfValue->y *= arg->y;
    selfValue->z *= arg->z;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x *= modifier;
    selfValue->y *= modifier;
    selfValue->z *= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec3_divide(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (arg)
  {
    return wrap_new_vec3(mrb, 
      selfValue->x / arg->x,
      selfValue->y / arg->y,
      selfValue->z / arg->z);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec3(mrb, 
      selfValue->x / modifier,
      selfValue->y / modifier,
      selfValue->z / modifier);
  }

  return mrb_nil_value();
}

mrb_value vec3_divide_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (arg)
  {
    selfValue->x /= arg->x;
    selfValue->y /= arg->y;
    selfValue->z /= arg->z;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x /= modifier;
    selfValue->y /= modifier;
    selfValue->z /= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec3_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y, z;
  int n;
  struct vec3 *tm;

  tm = (struct vec3*)DATA_PTR(self);
  if (tm) {
    vec3_free(mrb, tm);
  }
  DATA_TYPE(self) = &vec3_type;
  DATA_PTR(self) = NULL;

  n = mrb_get_args(mrb, "|f|ff", &x, &y, &z); // 1 or 2 float arguments

  if (n == 0)
  {
    tm = create_new_vec3(mrb, 0, 0, 0);
  }
  else if (n == 1)
  {
    tm = create_new_vec3(mrb, x, x, x);
  }
  else if (n > 1)
  {
    tm = create_new_vec3(mrb, x, y, z);
  }

  DATA_PTR(self) = tm;
  return self;
}

mrb_float vec3_calc_length(struct vec3* vector)
{
  return sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
}

mrb_value vec3_normalize(mrb_state* mrb, mrb_value self)
{
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);
  mrb_float length = vec3_calc_length(selfValue);

  return wrap_new_vec3(mrb, 
    selfValue->x / length,
    selfValue->y / length,
    selfValue->z / length);
}

mrb_value vec3_normalize_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);
  
  mrb_float length = vec3_calc_length(selfValue);
  selfValue->x /= length;
  selfValue->y /= length;
  selfValue->z /= length;
  
  return self;
}

mrb_value vec3_length(mrb_state* mrb, mrb_value self)
{
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  return mrb_float_value(mrb, vec3_calc_length(selfValue));
}

mrb_float vec3_calc_distance(struct vec3* vector, struct vec3* other)
{
  mrb_float x_diff = vector->x - other->x;
  mrb_float y_diff = vector->y - other->y;
  mrb_float z_diff = vector->z - other->z;
  return sqrt((x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff));
}

mrb_value vec3_distance(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(mrb, vec3_calc_distance(selfValue, arg));
}

mrb_float vec3_calc_dot(struct vec3* vector, struct vec3* other)
{
  return (vector->x * other->x) + (vector->y * other->y) + (vector->z * other->z);
}

mrb_value vec3_dot(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec3 *arg = vec3_get_ptr(mrb, new_value);
  struct vec3 *selfValue = vec3_get_ptr(mrb, self);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(mrb, vec3_calc_dot(selfValue, arg));
}

mrb_value vec3_inspect(mrb_state* mrb, mrb_value self)
{
  char buf[256];
  int len;

  struct vec3 *selfValue = vec3_get_ptr(mrb, self);
  if (!selfValue) return mrb_nil_value();

  len = snprintf(buf, sizeof(buf), "[%.4f,%.4f,%.4f]",
    selfValue->x, selfValue->y, selfValue->z);
  return mrb_str_new(mrb, buf, len);
}

void init_vec3(mrb_state* mrb)
{
  mrb_vec3_class = mrb_define_class(mrb, "Vec3", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_vec3_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_vec3_class, "x", vec3_get_x, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "x=", vec3_set_x, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "y", vec3_get_y, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "y=", vec3_set_y, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "z", vec3_get_z, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "z=", vec3_set_z, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "+", vec3_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "add", vec3_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "add!", vec3_plus_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "-", vec3_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "subtract", vec3_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "subtract!", vec3_subtract_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "-@", vec3_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "negate", vec3_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "negate!", vec3_usubtract_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec3_class, "*", vec3_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "multiply", vec3_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "multiply!", vec3_times_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "/", vec3_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "divide", vec3_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "divide!", vec3_divide_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "normalize", vec3_normalize, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "normalize!", vec3_normalize_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec3_class, "length", vec3_length, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec3_class, "dot", vec3_dot, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec3_class, "distance_to", vec3_distance, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "==", vec3_equals, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec3_class, "initialize", vec3_initialize, ARGS_ANY());

  mrb_define_method(mrb, mrb_vec3_class, "to_s", vec3_inspect, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec3_class, "inspect", vec3_inspect, ARGS_NONE());
}