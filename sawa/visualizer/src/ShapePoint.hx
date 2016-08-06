import thx.Rational;

class ShapePoint
{
	public var index:Int;
	public var x:Rational;
	public var y:Rational;
	
	public function new (x:Rational, y:Rational, index:Int)
	{
		this.x = x;
		this.y = y;
		this.index = index;
	}
}
