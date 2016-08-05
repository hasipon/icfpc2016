import flash.display.Graphics;
import flash.display.Shape;
import flash.display.Sprite;
import flash.geom.Point;

class Problem
{
	public var points:Array<Vertex>;
	public var polygons:Array<Polygon>; 
	public var lineToPolygons:Map<String, Array<Polygon>>;
	
	public static var newLine:EReg = ~/(\r\n)|\n|\r/g;

	public function new(name:String, input:String) 
	{
		var lines = newLine.split(input);
		var iter = lines.iterator();
		var pointCount = Std.parseInt(iter.next());
		
		points = [
			for (i in 0...pointCount)
			{
				parseVertex(iter.next(), i);
			}
		];
		
		var polygonCount = Std.parseInt(iter.next());
		polygons = [
			for (i in 0...polygonCount)
			{
				parsePolygon(iter.next());
			}
		];
		
		lineToPolygons = new Map();
		for (polygon in polygons)
		{
			var v = polygon.vertexes;
			var l = polygon.vertexes.length;
			for (i in 0...l)
			{
				var v0 = v[i];
				var v1 = v[(i + 1) % l];
				var line = if (v0 < v1)
				{
					v[i] + "_" + v[(i + 1) % l];
				}
				else
				{
					v[(i + 1) % l] + "_" + v[i];
				}
				
				if (lineToPolygons.exists(line))
				{
					var arr = lineToPolygons[line];
					if (arr.length > 1)
					{
						throw "同じ辺を3度以上使用しています。";
					}
					
					arr.push(polygon);
				}
				else
				{
					lineToPolygons[line] = [polygon];
				}
			}
		}
	}
	
	private static function parsePolygon(str:String):Polygon 
	{
		var vs = str.split(" ");
		var data = [
			for (v in vs)
			{
				Std.parseInt(v);
			}
		];
		return new Polygon(data);
	}
	
	private static function parseVertex(str:String, i:Int):Vertex
	{
		var segs = str.split(",");
		return new Vertex(parseNum(segs[0]), parseNum(segs[1]), i);
	}
	
	private static function parseNum(str:String):Float
	{
		var segs = str.split("/");
		return if (segs.length == 1)
		{
			Std.parseFloat(segs[0]);
		}
		else
		{
			Std.parseFloat(segs[0]) / Std.parseFloat(segs[1]);
		}
	}
	
	public function create(updateText:String->Void):ProblemSprite
	{
		return new ProblemSprite(this, updateText);
	}
	
	public function apply(startPointIndex:Int, endPointIndex:Int, polygonIndexes:Array<Int>, removePolygonIndexes:Array<Int>):Problem
	{
		var child = clone(); 
		
		var sv = child.points[startPointIndex];
		var ev = child.points[endPointIndex];
		var vecOA = new Vec(sv, ev);
		var newPolygons = [
			for (i in polygonIndexes)
			{
				var polygon:Polygon = child.polygons[i];
				var vs = [
					for (pv in polygon.vertexes)
					{
						child.resolveMirrorPoint(child.points[pv], vecOA);
					}
				];
				new Polygon(vs);
			}
		];
		
		child.addPolygons(newPolygons);
		var removePolygons = [
			for (i in removePolygonIndexes)
			{
				child.polygons[i];
			}
		];
		
		for (r in removePolygons)
		{
			child.polygons.remove(r);
		}
		
		child.refresh();
		return child;
	}
	
	private function refresh():Void
	{
		for (point in points)
		{
			point.active = false;
		}
		
		lineToPolygons = new Map();
		for (polygon in polygons)
		{
			var v = polygon.vertexes;
			var l = polygon.vertexes.length;
			for (i in 0...l)
			{
				var v0 = v[i];
				var v1 = v[(i + 1) % l];
				var line = if (v0 < v1)
				{
					v[i] + "_" + v[(i + 1) % l];
				}
				else
				{
					v[(i + 1) % l] + "_" + v[i];
				}
				
				if (lineToPolygons.exists(line))
				{
					var arr = lineToPolygons[line];
					arr.push(polygon);
				}
				else
				{
					lineToPolygons[line] = [polygon];
				}
			}
			
			for (i in polygon.vertexes)
			{
				points[i].active = true;
			}
		}
	}
	
	private function addPolygons(polygons:Array<Polygon>):Void
	{
		for (polygon in polygons)
		{
			this.polygons.push(polygon);
		}
	}
	
	public function resolveMirrorPoint(v:Vertex, vecOA:Vec):Int
	{
		var p = vecOA.mirror(v);
		for (i in 0...points.length)
		{
			var cp = points[i];
			if (cp.x == p.x && cp.y == p.y)
			{
				return i;
			}
		}
		
		points.push(new Vertex(p.x, p.y, v.source));
		return points.length - 1;
	}
	
	public function clone():Problem
	{
		var child = Type.createEmptyInstance(Problem);
		child.points = [for (p in points) p];
		child.polygons = [for (p in polygons) p];
		child.lineToPolygons = [for (key in lineToPolygons.keys()) key => lineToPolygons[key]];
		
		return child;
	}
	
	public function output():String
	{
		var string = "";
		var i = 0;
		for (point in points)
		{
			if (!point.active)
			{
				continue;
			}
			i++;
			string += point.x + "," + point.y + " " + point.source + "\n";
		}
		string = i + "\n" + string;
		
		string += polygons.length + "\n";
		for (polygon in polygons)
		{
			string += polygon.vertexes.length + " " + polygon.vertexes.join(" ") + "\n";
		}
		
		return string;
	}
}

private class Vec 
{
	private var dx:Float;
	private var dy:Float;
	public var ev:Vertex;
	public var sv:Vertex;
	
	public function new (sv:Vertex, ev:Vertex)
	{
		this.sv = sv;
		this.ev = ev;
		this.dx = sv.x - ev.x;
		this.dy = sv.y - ev.y;
	}
	
	public function mirror(v:Vertex):Point
	{
		var bh = new Vec(sv, v);
		var ohScale = inner(bh) / length2();
		var ohx = ohScale * (ev.x - sv.x);
		var ohy = ohScale * (ev.y - sv.y);
		var bhx = v.x - sv.x;
		var bhy = v.y - sv.y;
		
		return new Point(v.x + (ohx - bhx) * 2, v.y + (ohy- bhy) * 2);
	}
	
	public function length2():Float
	{
		return dx * dx + dy * dy;
	}
	
	// 内積
	public function inner(vec:Vec):Float
	{
		return dx * (vec.dx) + dy * vec.dy;
	}
}
