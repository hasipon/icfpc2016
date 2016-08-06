import flash.display.Shape;
import flash.geom.Point;

class LineShape extends Shape
{
	public var start:ShapePoint;
	public var end:ShapePoint;
	
	public function new (start:ShapePoint, end:ShapePoint)
	{
		super();
		this.start = start;
		this.end = end;
		graphics.clear();
		graphics.lineStyle(0.01, 0x45FE34);
		graphics.moveTo(start.x.toFloat() * 1000, start.y.toFloat() * 1000);
		graphics.lineTo(end.x.toFloat() * 1000, end.y.toFloat() * 1000);
	}
	
	public function crossTest(_start:Point, _end:Point):Bool
	{
		var ax = _start.x, ay = _start.y;
		var bx = _end.x, by = _end.y;
		var cx = start.x.toFloat(), cy = start.y.toFloat();
		var dx = end.x.toFloat(), dy = end.y.toFloat();
		
		var ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
		var tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
		var tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
		var td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
		
		return tc * td < 0 && ta * tb <= 0;
	}
}
