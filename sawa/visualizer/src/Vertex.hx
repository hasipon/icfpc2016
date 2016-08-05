package;

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
		active = false;
	}
	
	public function toString():String
	{
		return '($x, $y, $source)';
	}
}
