class Mat4
  @@identity = Mat4.new
  
  def self.identity
    @@identity ||= Mat4.new
  end
end
