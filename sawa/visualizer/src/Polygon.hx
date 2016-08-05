package;
import flash.geom.Point;

class Polygon
{
	public var vertexes:Array<Int>;
	
	public function new(vertexes:Array<Int>) 
	{
		this.vertexes = vertexes;
	}
	
	public function toString():String
	{
		return vertexes.join("_");
	}
}