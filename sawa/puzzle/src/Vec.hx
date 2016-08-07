package;
import haxe.ds.Option;
import thx.Rational;

class Vec
{
	public var dx:Rational;
	public var dy:Rational;
	
	public function new (start:Vertex, end:Vertex)
	{
		dx = end.x - start.x;
		dy = end.y - start.y;
	}
	
	// 内積
	public function inner(vec:Vec):Rational
	{
		return dx * (vec.dx) + dy * vec.dy;
	}
	
	public function outer(vec:Vec) :Rational
	{
		return dx * (vec.dy) - dy * vec.dx;
	}
	
	public function getLength():Option<Rational>
	{
		var l2 = getLength2();
		var num2 = l2.num * l2.den;
		var num = BigIntTools.intSqrt(num2);
		return if (num * num == num2)
		{
			Option.Some(Rational.create(num, l2.den));
		}
		else
		{
			Option.None;
		}
	}
	
	public function getLength2() :Rational
	{
		return dx * dx + dy * dy;
	}
	
}
