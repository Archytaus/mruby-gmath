#include "mrb_vec2.h"

#include <math.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

static struct RClass* mrb_vec2_class = NULL;

struct mrb_data_type vec2_type = { "Vec2", vec2_free };

struct vec2* allocate_new_vec2(mrb_state* mrb) {
  return (struct vec2 *)mrb_malloc(mrb, sizeof(struct vec2)); 
}

struct vec2* create_new_vec2(mrb_state* mrb, mrb_float x, mrb_float y) {
  struct vec2* newVec2 = allocate_new_vec2(mrb);
  newVec2->x = x;
  newVec2->y = y;
  return newVec2;
}

mrb_value wrap_new_vec2(mrb_state* mrb, mrb_float x, mrb_float y) {
  return vec2_wrap(mrb, mrb_vec2_class, create_new_vec2(mrb, x, y));
}

void 
vec2_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

mrb_value 
vec2_wrap(mrb_state *mrb, struct RClass *tc, struct vec2* tm)
{
  return mrb_obj_value(Data_Wrap_Struct(mrb, tc, &vec2_type, tm));
}

struct vec2*
vec2_get_ptr(mrb_state* mrb, mrb_value value)
{
  return (struct vec2*)mrb_data_get_ptr(mrb, value, &vec2_type);
}

mrb_value vec2_get_x(mrb_state* mrb, mrb_value self)
{
  struct vec2 *vec = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  return mrb_float_value(vec->x);
}

mrb_value vec2_set_x(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec2 *vec = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);
  vec->x = mrb_float(new_value);

  return new_value;
}

mrb_value vec2_get_y(mrb_state* mrb, mrb_value self)
{
  struct vec2 *vec = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  return mrb_float_value(vec->y);
}

mrb_value vec2_set_y(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  mrb_get_args(mrb, "f", &new_value);

  struct vec2 *vec = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);
  vec->y = mrb_float(new_value);

  return new_value;
}

mrb_value vec2_equals(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  return mrb_bool_value(
    selfValue->x == arg->x &&
    selfValue->y == arg->y);
}

mrb_value vec2_plus(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg = (struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec2(mrb, 
    selfValue->x + arg->x, 
    selfValue->y + arg->y);
}

mrb_value vec2_plus_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  selfValue->x += arg->x;
  selfValue->y += arg->y;
  return self;
}

mrb_value vec2_subtract(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  return wrap_new_vec2(mrb, 
    selfValue->x - arg->x, 
    selfValue->y - arg->y);
}

mrb_value vec2_subtract_inplace(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  selfValue->x -= arg->x;
  selfValue->y -= arg->y;
  return self;
}

mrb_value vec2_usubtract(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!selfValue) return mrb_nil_value();

  return wrap_new_vec2(mrb, 
    0 - selfValue->x, 
    0 - selfValue->y);
}

mrb_value vec2_usubtract_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!selfValue) return mrb_nil_value();

  selfValue->x = 0 - selfValue->x;
  selfValue->y = 0 - selfValue->y;
  return self;
}

mrb_value vec2_times(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);

  if (arg)
  {
    return wrap_new_vec2(mrb, 
      selfValue->x * arg->x, 
      selfValue->y * arg->y);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec2(mrb, 
      selfValue->x * modifier, 
      selfValue->y * modifier);
  }

  return mrb_nil_value();
}

mrb_value vec2_times_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);

  if (arg)
  {
    selfValue->x *= arg->x;
    selfValue->y *= arg->y;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x *= modifier;
    selfValue->y *= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec2_divide(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);

  if (arg)
  {
    return wrap_new_vec2(mrb, 
      selfValue->x / arg->x,
      selfValue->y / arg->y);
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    return wrap_new_vec2(mrb, 
      selfValue->x / modifier,
      selfValue->y / modifier);
  }

  return mrb_nil_value();
}

mrb_value vec2_divide_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  mrb_value new_value;
  mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);

  if (arg)
  {
    selfValue->x /= arg->x;
    selfValue->y /= arg->y;
    return self;
  }

  mrb_float modifier;
  mrb_get_args(mrb, "f", &modifier);
  if(modifier)
  {
    selfValue->x /= modifier;
    selfValue->y /= modifier;
    return self;
  }

  return mrb_nil_value();
}

mrb_value vec2_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y;
  int n;
  struct vec2 *tm;

  tm = (struct vec2*)DATA_PTR(self);
  if (tm) {
    vec2_free(mrb, tm);
  }
  DATA_TYPE(self) = &vec2_type;
  DATA_PTR(self) = NULL;

  n = mrb_get_args(mrb, "|f|f", &x, &y); // 1 or 2 float arguments

  if (n == 0)
  {
    tm = create_new_vec2(mrb, 0, 0);
  }
  else if (n == 1)
  {
    tm = create_new_vec2(mrb, x, x);
  }
  else if (n == 2)
  {
    tm = create_new_vec2(mrb, x, y);
  }

  DATA_PTR(self) = tm;
  return self;
}

mrb_float vec2_calc_length(struct vec2* vector)
{
  return sqrt((vector->x * vector->x) + (vector->y * vector->y));
}

mrb_value vec2_normalize(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);
  mrb_float length = vec2_calc_length(selfValue);

  return wrap_new_vec2(mrb, 
    selfValue->x / length,
    selfValue->y / length);
}

mrb_value vec2_normalize_inplace(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);
  
  mrb_float length = vec2_calc_length(selfValue);
  selfValue->x /= length;
  selfValue->y /= length;
  
  return self;
}

mrb_value vec2_length(mrb_state* mrb, mrb_value self)
{
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  return mrb_float_value(vec2_calc_length(selfValue));
}

mrb_float vec2_calc_distance(struct vec2* vector, struct vec2* other)
{
  mrb_float x_diff = vector->x - other->x;
  mrb_float y_diff = vector->y - other->y;
  return sqrt((x_diff * x_diff) + (y_diff * y_diff));
}

mrb_value vec2_distance(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(vec2_calc_distance(selfValue, arg));
}

mrb_float vec2_calc_dot(struct vec2* vector, struct vec2* other)
{
  return (vector->x * other->x) + (vector->y * other->y);
}

mrb_value vec2_dot(mrb_state* mrb, mrb_value self)
{
  mrb_value new_value;
  int args = mrb_get_args(mrb, "o", &new_value);
  struct vec2* arg =(struct vec2*)mrb_data_get_ptr(mrb, new_value, &vec2_type);
  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);

  if (!arg) return mrb_nil_value();

  return mrb_float_value(vec2_calc_dot(selfValue, arg));
}

mrb_value vec2_inspect(mrb_state* mrb, mrb_value self)
{
  char buf[256];
  int len;

  struct vec2* selfValue = (struct vec2*)mrb_data_get_ptr(mrb, self, &vec2_type);
  if (!selfValue) return mrb_nil_value();

  len = snprintf(buf, sizeof(buf), "[%.4f,%.4f]",
    selfValue->x, selfValue->y);
  return mrb_str_new(mrb, buf, len);
}

void init_vec2(mrb_state* mrb)
{
  mrb_vec2_class = mrb_define_class(mrb, "Vec2", mrb->object_class);
  MRB_SET_INSTANCE_TT(mrb_vec2_class, MRB_TT_DATA);

  mrb_define_method(mrb, mrb_vec2_class, "x", vec2_get_x, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "x=", vec2_set_x, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "y", vec2_get_y, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "y=", vec2_set_y, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "+", vec2_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "add", vec2_plus, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "add!", vec2_plus_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "-", vec2_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "subtract", vec2_subtract, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "subtract!", vec2_subtract_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "-@", vec2_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "negate", vec2_usubtract, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "negate!", vec2_usubtract_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec2_class, "*", vec2_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "multiply", vec2_times, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "multiply!", vec2_times_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "/", vec2_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "divide", vec2_divide, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "divide!", vec2_divide_inplace, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "normalize", vec2_normalize, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "normalize!", vec2_normalize_inplace, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec2_class, "length", vec2_length, ARGS_NONE());

  mrb_define_method(mrb, mrb_vec2_class, "dot", vec2_dot, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_vec2_class, "distance_to", vec2_distance, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "==", vec2_equals, ARGS_REQ(1));

  mrb_define_method(mrb, mrb_vec2_class, "initialize", vec2_initialize, ARGS_ANY());

  mrb_define_method(mrb, mrb_vec2_class, "to_s", vec2_inspect, ARGS_NONE());
  mrb_define_method(mrb, mrb_vec2_class, "inspect", vec2_inspect, ARGS_NONE());
}