import flash.display.Shape;

class PolygonShape extends Shape
{
	public var index:Int;
	public var lines:Array<LineShape>;
	
	public function new (problem:Problem, index:Int)
	{
		super();
		this.index = index;
		this.lines = [];
		
		graphics.clear();
		graphics.beginFill(0x45FE34, 0.2);
		var first = true;
		for (i in problem.polygons[index].vertexes)
		{
			var v = problem.points[i];
			if (first)
			{
				graphics.moveTo(v.x.toFloat() * 1000, v.y.toFloat() * 1000);
				first = false;
			}
			else
			{
				graphics.lineTo(v.x.toFloat() * 1000, v.y.toFloat() * 1000);
			}
		}
		graphics.endFill();
	}
}
