package thx;

abstract Rational(RationalImpl) from RationalImpl to RationalImpl {
  public static var zero(default, never) : Rational = { num : BigInt.zero, den : BigInt.one };

  public var num(get, never) : BigInt;
  public var den(get, never) : BigInt;

  public function new(num:BigInt, den:BigInt)
  {
	  this = { num: num, den: den };
  }
  
  @:from public static function fromString(s : String) {
    var parts = s.split("/").map(StringTools.trim);
    if(parts.length > 2)
      throw ('string "$s" cannot be parsed to a Rational');
    if(parts.length == 1)
      return create(BigInt.fromString(parts[0]), BigInt.one);
    return create(BigInt.fromString(parts[0]), BigInt.fromString(parts[1]));
  }

  @:from public static function fromBigInt(i : BigInt)
    return create(i, BigInt.one);

  @:from public static function fromInt(i : Int)
    return create(i, BigInt.one);

  public static function create(num : BigInt, den : BigInt) {
    if(den == 0)
      throw ('division by zero');
    var g = num.gcd(den);
    num = num / g;
    den = den / g;
    if(den < 0) {
      num = -num;
      den = -den;
    }
    if(num == 0)
      den = 1;
    return new Rational(num, den);
  }

  public function abs() : Rational
    return new Rational(num.abs(), den);

  @:op(-A)
  public function negate() : Rational
    return new Rational(-num, den);

  @:op(A+B)
  public function add(that : Rational) : Rational {
    if(compareTo(zero) == 0) return that;
    if (that.compareTo(zero) == 0) return this;
    var a = compareTo(zero);
	var b = that.compareTo(zero);
	
	var f = num.gcd(that.num),
        g = den.gcd(that.den),
        s : { num : BigInt, den : BigInt } = create(
              (num / f) * (that.den / g) +
              (that.num / f) * (den / g),
              den.lcm(that.den)
            );

    s.num = s.num * f;
    return s;
  }

  @:op(A-B)
  public function subtract(that : Rational) : Rational
    return add(that.negate());

  // minimize overflow by cross-cancellation
  @:op(A*B)
  public function multiply(that : Rational) : Rational {
    var c = create(num, that.den),
        d = create(that.num, den);
    return create(c.num * d.num, c.den * d.den);
  }

  @:op(A/B)
  public function divide(that : Rational) : Rational
    return multiply(that.reciprocal());

  public function reciprocal() : Rational
    return create(den, num);

  inline public function isZero() : Bool
    return num.isZero();

  inline public function isNegative() : Bool
    return num.isNegative();

  public function compareTo(that : Rational) : Int {
    var lhs = num * that.den,
        rhs = den * that.num;
    return lhs.compareTo(rhs);
  }

  public function greaterThan(that : Rational) : Bool
    return compareTo(that) > 0;

  @:op(A>B)
  static public function greater(self : Rational, that : Rational) : Bool
    return self.compareTo(that) > 0;

  public function greaterEqualsTo(that : Rational) : Bool
    return compareTo(that) >= 0;

  @:op(A>=B)
  static public function greaterEquals(self : Rational, that : Rational) : Bool
    return self.compareTo(that) >= 0;

  public function lessThan(that : Rational) : Bool
    return compareTo(that) < 0;

  @:op(A<B)
  static public function less(self : Rational, that : Rational) : Bool
    return self.compareTo(that) < 0;

  public function lessEqualsTo(that : Rational) : Bool
    return compareTo(that) <= 0;

  @:op(A<=B)
  static public function lessEquals(self : Rational, that : Rational) : Bool
    return self.compareTo(that) <= 0;

  public function equalsTo(that : Rational) : Bool
    return compareTo(that) == 0;

  @:op(A==B)
  static public function equals(self : Rational, that : Rational) : Bool
    return self.compareTo(that) == 0;

  public function notEqualsTo(that : Rational) : Bool
    return compareTo(that) != 0;

  @:op(A!=B)
  public static function notEquals(self : Rational, that : Rational) : Bool
    return self.compareTo(that) != 0;

  public function toFloat() : Float
    return num.toFloat() / den.toFloat();

  public function toString() : String {
    var str = if(den == 1)
      '${num.toString()}';
    else
      '${num.toString()}/${den.toString()}'; // ⁄ or /
	  
	if (str == "-0")
	{
		str = "0";
	}
	return str;
  }

  inline function get_num() return this.num;
  inline function get_den() return this.den;
}

typedef RationalImpl = {
  num : BigInt,
  den : BigInt
}
