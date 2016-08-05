n = STDIN.gets.to_i

class Complex
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
    other = other.clone
    other.real = -1.0 * other.real
    other.imag = -1.0 * other.imag
    self + other
  end
  def + (other)
    ret = self.clone
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

ps = []
n.times do |i|
  real, imag = STDIN.gets.split(" ").at(0).split(",")
  ps.push(Complex(real, imag))
end

real_mx = ps[0]
real_mn = ps[0]
imag_mx = ps[0]
imag_mn = ps[0]

ps.each do |p|
  if p.real < real_mn.real
    real_mn = p
  end
  if p.real >= real_mx.real
    real_mx = p
  end
  if p.imag < imag_mn.imag
    imag_mn = p
  end
  if p.imag >= imag_mx.imag
    imag_mx = p
  end
end

ORIGIN = Complex(0, 0)

sq = [real_mx, real_mn, imag_mx, imag_mx]
target = sq[0]
sq.each do |p|
  if ORIGIN.dist(target) > ORIGIN.dist(p)
    target = p
  end
end

center = Complex(
  real_mx.real - real_mn.real,
  imag_mx.imag - imag_mx.imag
)

def f(p, a)
  r = Math.cos(a) * p.real() - Math.sin(a) * p.imag()
  i = Math.sin(a) * p.real() + Math.cos(a) * p.imag()
  ORIGIN.dist(Complex(r, i))
end

small = Math::PI / 4.0 * -1
large = Math::PI / 4.0

1000.times do |_|
  s = (small * 2 + large) / 3
  l = (large * 2 + small) / 3
  if f(target, s) < f(target, l)
    small = s
  else
    large = l
  end
end

a = (small + large) / 2
p a
p f(target, a)
