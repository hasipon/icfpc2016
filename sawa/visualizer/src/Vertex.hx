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
		this.x = x;
		this.y = y;
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
}
