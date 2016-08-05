package;

class Vertex
{
	public var source:Int;
	public var y:Float;
	public var x:Float;
	
	public function new(x:Float, y:Float, source:Int) 
	{
		this.x = x;
		this.y = y;
		this.source = source;
	}
	
	public function toString():String
	{
		return '($x, $y, $source)';
	}
}
