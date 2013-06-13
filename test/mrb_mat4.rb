assert 'default constructor' do
  Mat4.new != nil
end

assert 'constructor setting empty value is identity' do
  value = Mat4.new
  value.identity?
end

assert 'equality' do
  Mat4.new == Mat4.new
end