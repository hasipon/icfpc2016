package;
import thx.Rational;

class Line
{
	public var start:Int;
	public var end:Int;
	public var key:LineKey;
	
	// 隣接ポリゴン
	public var polygons:Array<Int>;
	
	public function new(start:Int, end:Int, polygon:Int) 
	{
		this.start = start;
		this.end = end;
		this.key = new LineKey(start, end);
		this.polygons = [polygon];
	}	
	
	public function createShape(problem:Problem):LineShape
	{
		var s = problem.points[start];
		var e = problem.points[end];
		var dx = s.x - e.x;
		var dy = s.y - e.y;
		var d:Rational = dx * dx + dy * dy;
		var isRational = BigIntTools.isSquareNumber(d.num * d.den);
		var isUsed = problem.usedLines.exists(key);
		return new LineShape(s.createShape(start), e.createShape(end), isRational, isUsed);
	}
}
