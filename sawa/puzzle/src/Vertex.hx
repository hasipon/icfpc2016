package;
import thx.Rational;

class Vertex
{
	public var source:Int;
	public var y:Rational;
	public var x:Rational;
	public var active:Bool;
	
	public function new(x:Rational, y:Rational, source:Int) 
	{
		this.x = new Rational(x.num, y.den);
		this.y = new Rational(y.num, y.den);
		this.source = source;
		active = true;
	}
	
	public function toString():String
	{
		var xd = x.den.toString();
		var xStr = if (xd == "1") x.num.toString() else x.num.toString() + "/" + x.den.toString();
		var yd = y.den.toString();
		var yStr = if (yd == "1") y.num.toString() else y.num.toString() + "/" + y.den.toString();
		return xStr + "," + yStr;
	}
	
	public function createShape(index:Int):ShapePoint
	{
		return new ShapePoint(x, y, index);
	}
	
	public function isOnSquare():Bool
	{
		return (x.isZero() || x == 1) && (y.isZero() || y == 1);
	}
	
	
	public function mirror(sv:Vertex, ev:Vertex):Void
	{
		var vec = new Vec(sv, ev);
		var bh = new Vec(sv, this);
		var ohScale = vec.inner(bh) / vec.getLength2();
		var ohx = ohScale * (ev.x - sv.x);
		var ohy = ohScale * (ev.y - sv.y);
		var bhx = this.x - sv.x;
		var bhy = this.y - sv.y;
		
		this.x = this.x + (ohx - bhx) * Rational.fromInt(2);
		this.y = this.y + (ohy - bhy) * Rational.fromInt(2);
	}
}
