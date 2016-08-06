package;

abstract LineKey(String) 
{
	public function new(i0:Int, i1:Int)
	{
		this = if (i0 < i1) i0 + "_" + i1 else i1 + "_" + i0;
	}
	
	public function createShape(problem:Problem):LineShape
	{
		var keys = this.split("_");
		return new LineShape(parsePoint(problem, keys[0]), parsePoint(problem, keys[1]));
	}
	
	private function parsePoint(problem:Problem, key:String):ShapePoint
	{
		var i = Std.parseInt(key);
		var p = problem.points[i];
		return new ShapePoint(p.x, p.y, i);
	}
}