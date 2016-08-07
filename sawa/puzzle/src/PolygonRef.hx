package;
import haxe.ds.Option;
import thx.Rational;

class PolygonRef
{
	public var start:Int;
	public var end:Int;
	public var inPolyIndex:Int;
	public var poly:Polygon;
	public var length:Option<Rational>;
	
	public function new(start:Int, end:Int, poly:Polygon, inPolyIndex:Int, length:Option<Rational>) 
	{
		this.start = start;
		this.end = end;
		this.inPolyIndex = inPolyIndex;
		this.poly = poly;
		this.length = length;
	}
}