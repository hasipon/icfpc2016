class FractionPoint
  attr_accessor :real
  attr_accessor :imag
  def initialize(real, imag)
    unless real.is_a?(Rational)
      real = Rational(real)
    end
    unless imag.is_a?(Rational)
      imag = Rational(imag)
    end
    @real = real
    @imag = imag
  end
  def - (other)
    other = FractionPoint.new(other.real, other.imag)
    other.real = -1.0 * other.real
    other.imag = -1.0 * other.imag
    self + other
  end
  def + (other)
    ret = FractionPoint.new(@real, @imag)
    ret.real += other.real
    ret.imag += other.imag
    ret
  end
  def dist(other)
    r = self.real - other.real
    i = self.imag - other.imag
    r * r + i * i
  end
  def < (other)
    @real != other.real ? (@real < other.real) : (@imag < other.imag)
  end
  def == (other)
    @real == other.real and @imag == other.imag
  end
  def > (other)
    not ((self < other) or (self == other))
  end
  def <=> (other)
    if self == other
      return 0
    end
    if self < other
      return -1
    end
    if self > other
      return +1
    end
  end
end

ORIGIN = FractionPoint.new(0, 0)

def r(p, a)
  r = Math.cos(a) * p.real() - Math.sin(a) * p.imag()
  i = Math.sin(a) * p.real() + Math.cos(a) * p.imag()
  FractionPoint.new(r, i)
end

def rot_from(p, a, base)
  p = p - base
  r(p, a) + base
end

def f(ps, a, center)
  qs = ps.map { |item| rot_from(item, a, center) } 
  q = qs[0].real - qs[1].real
  if q <= -1
    return -1 * q
  else
    return q
  end
end

def convex_hull(points)
  points.sort!
  return points if points.length <= 3
  def cross(o, a, b)
    (a.real - o.real) * (b.imag - o.imag) - (a.imag - o.imag) * (b.real - o.real)
  end
  lower = Array.new
  points.each{|p|
    while lower.length > 1 and cross(lower[-2], lower[-1], p) <= 0 do lower.pop end
    lower.push(p)
  }
  upper = Array.new
  points.reverse_each{|p|
    while upper.length > 1 and cross(upper[-2], upper[-1], p) <= 0 do upper.pop end
    upper.push(p)
  }
  return lower[0...-1] + upper[0...-1]
end
# fail unless convex_hull((0..9).to_a.repeated_permutation(2).to_a) == [[0, 0], [9, 0], [9, 9], [0, 9]]

ps = []
STDIN.gets.to_i.times do |i|
  real, imag = STDIN.gets.split(" ").at(0).split(",")
  ps.push(FractionPoint.new(real, imag))
end

bbox = convex_hull(ps)

# p "BoundingBox"
# bbox.each { |x| p x }

target = bbox[0]
bbox.each do |p|
  if ORIGIN.dist(target) > ORIGIN.dist(p)
    target = p
  end
end

# p "Target"
# p target

center = FractionPoint.new(
  (bbox[0].real + bbox[1].real + bbox[2].real + bbox[3].real) / 4,
  (bbox[0].imag + bbox[1].imag + bbox[2].imag + bbox[3].imag) / 4,
)

# p "Center"
# p $center

small = Math::PI / 4.0 * -1
large = Math::PI / 4.0

10000.times do |_|
  s = (small * 2 + large) / 3
  l = (large * 2 + small) / 3
  if f(bbox, s, center) < f(bbox, l, center)
    large = l
  else
    small = s
  end
end

a = (small + large) / 2
b = r(target, a)
p Rational(a)
p b.real, b.imag
