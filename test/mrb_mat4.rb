assert 'default constructor' do
  Mat4.new != nil
end

assert 'constructor setting empty value is identity' do
  value = Mat4.new
  assert_true value.identity?
end

assert 'constructor setting initial values from parameters' do
  value = Mat4.new(
    1, 2, 2, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  )

  assert_false value.identity?
  assert_equal 1, value.f11
  assert_equal 2, value.f12
  assert_equal 2, value.f13
  assert_equal 1, value.f14
end

assert 'constructor setting initial values in nested arrays' do
  value = Mat4.new(
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]
  )
  assert_true value.identity?
end

assert 'constructor setting initial values in nested arrays not defaulted to identity' do
  value = Mat4.new(
    [1, 2, 2, 1],
    [0, 0, 0, 0],
    [0, 0, 0, 0],
    [0, 0, 0, 0]
  )

  assert_false value.identity?
  assert_equal 1, value.f11
  assert_equal 2, value.f12
  assert_equal 2, value.f13
  assert_equal 1, value.f14
end

assert 'equality' do
  assert_true Mat4.new == Mat4.new
end

assert 'add' do
  value = Mat4.new + Mat4.new
  expected = Mat4.new(
    [2, 0, 0, 0],
    [0, 2, 0, 0],
    [0, 0, 2, 0],
    [0, 0, 0, 2]
  )

  assert_equal expected, value
end
