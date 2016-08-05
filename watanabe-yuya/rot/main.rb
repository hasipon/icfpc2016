n = STDIN.gets.to_i

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
end

ORIGIN = FractionPoint.new(0, 0)

ps = []
n.times do |i|
  real, imag = STDIN.gets.split(" ").at(0).split(",")
  ps.push(FractionPoint.new(real, imag))
end

real_mx = ps[0]
real_mn = ps[0]
imag_mx = ps[0]
imag_mn = ps[0]

ps.each do |p|
  if (p.real < real_mn.real) or (p.real == real_mn.real and p.imag > real_mn.imag)
    real_mn = p
  end
  if (p.real > real_mx.real) or (p.real == real_mx.real and p.imag > real_mx.imag)
    real_mx = p
  end
  if (p.imag < imag_mn.imag) or (p.imag == imag_mn.imag and p.real < imag_mn.real)
    imag_mn = p
  end
  if (p.imag > imag_mx.imag) or (p.imag == imag_mx.imag and p.real < imag_mx.real)
    imag_mx = p
  end
end

bounding_box = [real_mx, real_mn, imag_mx, imag_mn]

# p "BoundingBox"
# bounding_box.each { |x| p x }

target = bounding_box[0]
bounding_box.each do |p|
  if ORIGIN.dist(target) > ORIGIN.dist(p)
    target = p
  end
end

# p "Target"
# p target

$center = FractionPoint.new(
  (real_mx.real - real_mn.real) / 2,
  (imag_mx.imag - imag_mn.imag) / 2
)

# p "Center"
# p $center

def r(p, a)
  p = p - $center
  r = Math.cos(a) * p.real() - Math.sin(a) * p.imag()
  i = Math.sin(a) * p.real() + Math.cos(a) * p.imag()
  FractionPoint.new(r, i) + $center
end

def f(p, a)
  ORIGIN.dist(r(p, a))
end

small = Math::PI / 4.0 * -1
large = Math::PI / 4.0

10000.times do |_|
  s = (small * 2 + large) / 3
  l = (large * 2 + small) / 3
  if f(target, s) < f(target, l)
    large = l
  else
    small = s
  end
end

a = (small + large) / 2
b = r(target, a)
p a
p b.real, b.imag
