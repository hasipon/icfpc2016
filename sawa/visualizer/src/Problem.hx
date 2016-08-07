import flash.display.Graphics;
import flash.display.Shape;
import flash.display.Sprite;
import flash.geom.Point;
import haxe.ds.Option;
import thx.Rational;

class Problem
{
	// 元データ
	public var points:Array<Vertex>;
	public var polygons:Array<Polygon>;
	public var usedLines:Map<LineKey, Bool>;
	
	// 高速化用データ
	public var lines:Map<LineKey, Line>;
	
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
		usedLines = new Map();
		
		refresh();
	}
	
	private function parsePolygon(str:String):Polygon 
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
	
	private static function parseNum(str:String):Rational
	{
		return Rational.fromString(str);
	}
	
	public function create(updateText:String->Void):ProblemSprite
	{
		return new ProblemSprite(this, updateText);
	}
	
	public function apply(startPointIndex:Int, endPointIndex:Int, polygonIndexes:Array<Int>, removePolygonIndexes:Array<Int>):Void
	{
		
		var sv = points[startPointIndex];
		var ev = points[endPointIndex];
		var vecOA = new Vec(sv, ev);
		var newPolygons = [
			for (i in polygonIndexes)
			{
				var polygon:Polygon = polygons[i];
				var vs = [
					for (v in polygon.vertexes)
					{
						resolveMirrorPoint(points[v], vecOA);
					}
				];
				new Polygon(vs);
			}
		];
		
		usedLines[new LineKey(startPointIndex, endPointIndex)] = true;
		// usedLinesの複製
		for (i in 0...polygonIndexes.length)
		{
			var polygon = polygons[polygonIndexes[i]];
			var newPolygon = newPolygons[i];
			var vs = polygon.vertexes;
			var l = vs.length;
			for (i in 0...l)
			{
				var v0 = vs[i];
				var v1 = vs[(i + 1) % l];
				var nv0 = newPolygon.vertexes[i];
				var nv1 = newPolygon.vertexes[(i + 1) % l];
				var k = new LineKey(v0, v1);
				var nk = new LineKey(nv0, nv1);
				if (usedLines.exists(k))
				{
					usedLines[nk] = true;
				}
				if (vecOA.isParallel(new Vec(points[v0], points[v1])))
				{
					usedLines[nk] = true;
					usedLines[k] = true;
				}
			}
		}
		
		addPolygons(newPolygons);
		var removePolygons = [
			for (i in removePolygonIndexes)
			{
				polygons[i];
			}
		];
		
		for (r in removePolygons)
		{
			polygons.remove(r);
		}
		
		refresh();
	}
	
	private function refresh():Void
	{
		// 不要な点を消去して、インデックスを更新
		for (point in points)
		{
			point.active = false;
		}
		// ポリゴンの頂点でない点の削除
		for (polygon in polygons)
		{
			var vs = polygon.vertexes;
			var l = vs.length;
			for (i in 0...l)
			{
				var v0 = points[vs[i]];
				v0.active = true;
			}
		}
		var newPoints = [];
		var pointMap = new Map();
		
		for (i in 0...points.length)
		{
			var point = points[i];
			if (point.active)
			{
				pointMap[i] = newPoints.length;
				newPoints.push(point); 
			}
		}
		points = newPoints;
		applyPointMove(pointMap);
		
		lines = new Map();
		for (j in 0...polygons.length)
		{
			var polygon = polygons[j];
			var v = polygon.vertexes;
			var l = polygon.vertexes.length;
			for (i in 0...l)
			{
				var v0 = v[i];
				var v1 = v[(i + 1) % l];
				var lineKey = new LineKey(v0, v1);
				
				if (lines.exists(lineKey))
				{
					lines[lineKey].polygons.push(j);
				}
				else
				{
					lines[lineKey] = new Line(v0, v1, j);
				}
			}
		}
		
	}
	
	public function applyPointMove(pointMap:Map<Int, Int>):Void
	{
		polygons = [
			for (polygon in polygons)
			{
				new Polygon([for (v in polygon.vertexes) pointMap[v]]);
			}
		];
		var oldUsedLines = usedLines;
		usedLines = new Map();
		for (key in oldUsedLines.keys())
		{
			switch (key.convert(pointMap))
			{
				case Option.Some(data):
					usedLines[data] = true;
					
				case Option.None:
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
		var mirror = new Vertex(p.x, p.y, v.source);
		points.push(mirror);
		return points.length - 1;
	}
	
	public function clone():Problem
	{
		var child = Type.createEmptyInstance(Problem);
		child.points = [for (p in points) p];
		child.polygons = [for (p in polygons) p];
		child.usedLines = [for (key in usedLines.keys()) key => usedLines[key]];
		child.refresh();
		
		return child;
	}
	
	public function output(sourceProblem:Problem):String
	{
		var string = "";
		string += points.length + "\n";
		for (point in points)
		{
			string += point.toString() + "\n";
		}
		
		string += polygons.length + "\n";
		for (polygon in polygons)
		{
			string += polygon.vertexes.length + " " + [for (v in polygon.vertexes) v].join(" ") + "\n";
		}
		
		for (point in points)
		{
			string += sourceProblem.points[point.source].toString() + "\n";
		}
		return string;
	}
	
	public function normalize():Void
	{
		points = [
			for (p in points) {
				var v = new Vertex(p.x, p.y, p.source);
				v;
			}
		];
		
		var p = points[0];
		var corners = [
			MinX => { 
				p: [p], 
				v: function (p:Vertex) return p.x,
				comp: function (v:Vertex->Rational, curent:Vertex, next:Vertex):Comp 
				{
					return if (v(curent) == v(next)) Same else if (v(curent) > v(next)) Over else None;
				}
			},
			MinY => { 
				p: [p], 
				v: function (p:Vertex) return p.y,
				comp: function (v:Vertex->Rational, curent:Vertex, next:Vertex):Comp 
				{
					return if (v(curent) == v(next)) Same else if (v(curent) > v(next)) Over else None;
				}
			},
			MaxX => { 
				p: [p], 
				v: function (p:Vertex) return p.x, 
				comp: function (v:Vertex->Rational, curent:Vertex, next:Vertex):Comp 
				{
					return if (v(curent) == v(next)) Same else if (v(curent) < v(next)) Over else None;
				}
			},
			MaxY => { 
				p: [p], 
				v: function (p:Vertex) return p.y, 
				comp: function (v:Vertex->Rational, curent:Vertex, next:Vertex):Comp 
				{
					return if (v(curent) == v(next)) Same else if (v(curent) < v(next)) Over else None;
				}
			},
		];
		
		for (i in 1...points.length)
		{
			var point = points[i];
			
			for (corner in corners)
			{
				switch (corner.comp(corner.v, corner.p[0], point))
				{
					case Same:
						corner.p.push(point); 
					
					case Over:
						corner.p = [point];
						
					case None:
				}
			}
		}
		
		var minXP = corners[MinX].p[0];
		var minYP = corners[MinY].p[0];
		
		if (corners[MinX].p.length == 1)
		{
			// 回転
			var sin = -(minYP.x - minXP.x);
			var cos = minXP.y - minYP.y;
			for (point in points)
			{
				var px = point.x;
				var py = point.y;
				
				point.x = cos * px - sin * py;
				point.y = sin * px + cos * py;
			}
		}
		
		var minX = corners[MinX].p[0].x;
		var minY = corners[MinY].p[0].y;
		for (point in points)
		{
			point.x -= minX;
			point.y -= minY;
		}
	}
	
	public function reduce():Void
	{
		var pointMap = [0 => 0];
		
		// 同一の点を除去
		for (i in 1...points.length)
		{
			var p0 = points[i];
			for (j in 0...i)
			{
				var p1 = points[j];
				if (p0.x == p1.x && p0.y == p1.y)
				{
					pointMap[i] = j;
					break;
				}
			}
			if (!pointMap.exists(i))
			{
				pointMap[i] = i;
			}
		}
		applyPointMove(pointMap);
		refresh();
		
		// 未使用な線の除去
		while (removeUnusedLine())
		{
			refresh();
		}
		
		// ポリゴンの頂点でない点の削除
		for (polygon in polygons)
		{
			var vs = polygon.vertexes;
			var l = vs.length;
			var newVs = [];
			for (i in 0...l)
			{
				var v0 = points[vs[i]];
				var v1 = points[vs[(i + 1) % l]];
				var v2 = points[vs[(i + 2) % l]];
				var vec0 = new Vec(v0, v1);
				var vec1 = new Vec(v1, v2);
				if (vec0.isZero() || vec1.isZero() || !vec0.isParallel(vec1))
				{
					newVs.push(vs[(i + 1) % l]);
				}
			}
			polygon.vertexes = newVs;
		}
		refresh();
	
		// 線分の途中に点があったらその点を経由
		var neighberPoint = [for (i in 0...points.length) i => []];
		for (line in lines)
		{
			neighberPoint[line.start].push(line.end);
			neighberPoint[line.end].push(line.start);
		}
		for (line in lines)
		{
			var s = points[line.start];
			var e = points[line.end];
			var vec0 = new Vec(s, e);
			var vec0Length = vec0.length2();
			var targets = [];
			
			for (j in neighberPoint[line.start])
			{
				var vec1 = new Vec(s, points[j]);
				var inner = vec0.inner(vec1);
				if (0 < inner && inner < vec0Length &&vec0.isParallel(vec1))
				{
					targets.push( {i:inner, p: j} );
				}
			}
			
			if (targets.length > 0)
			{
				targets.sort(function (a, b) return if (a.i < b.i) -1 else 1);
				
				for (p in line.polygons)
				{
					var polygon = polygons[p];
					var vs = polygon.vertexes;
					var l = vs.length;
					var newVs = [];
					for (i in 0...l)
					{
						var v0 = vs[i];
						var v1 = vs[(i + 1) % l];
						newVs.push(v0);
						if (line.key == new LineKey(v0, v1))
						{
							if (v1 == line.start)
							{
								targets.reverse();
							}
							for (t in targets)
							{
								newVs.push(t.p);
							}
						}
					}
					
					polygon.vertexes = newVs;
				}
			}
			
			usedLines[line.key] = true;
		}
		refresh();
	}
	
	public function removeUnusedLine():Bool
	{
		for (line in lines)
		{
			if (!usedLines.exists(line.key) && line.polygons.length == 2)
			{
				var targets = line.polygons.map(function (i) return polygons[i]);
				
				switch (targets[0].connect(targets[1]))
				{
					case Option.Some(newP):
						polygons.push(newP);
						for (p in targets)
						{
							polygons.remove(p);
						}
						
						return true;
						
					case Option.None:
				}
			}
		}
		
		return false;
	}
	
	public function finalize():Void
	{
		normalize();
		reduce();
	}
	
	public function center():Void
	{
		var x = points[0].x;
		var y = points[0].y;
		for (point in points)
		{
			var px = point.x;
			var py = point.y;
			if (px < x) x = px;
			if (py < y) y = py;
		}
		points = [
			for (point in points)
			{
				new Vertex(point.x - x, point.y - y,point.source);
			}
		];
	}
	
}

enum Comp
{
	None;
	Same;
	Over;
}

enum MinMax
{
	MinX;
	MinY;
	MaxX;
	MaxY;
}

private class Vec 
{
	private var dx:Rational;
	private var dy:Rational;
	public var ev:Vertex;
	public var sv:Vertex;
	
	public function new (sv:Vertex, ev:Vertex)
	{
		this.sv = sv;
		this.ev = ev;
		this.dx = sv.x - ev.x;
		this.dy = sv.y - ev.y;
	}
	
	public function mirror(v:Vertex):RationalPoint
	{
		var bh = new Vec(sv, v);
		var ohScale = inner(bh) / length2();
		var ohx = ohScale * (ev.x - sv.x);
		var ohy = ohScale * (ev.y - sv.y);
		var bhx = v.x - sv.x;
		var bhy = v.y - sv.y;
		
		return new RationalPoint(v.x + (ohx - bhx) * Rational.fromInt(2), v.y + (ohy- bhy) * Rational.fromInt(2));
	}
	
	public function length2():Rational
	{
		return dx * dx + dy * dy;
	}
	
	// 内積
	public function inner(vec:Vec):Rational
	{
		return dx * (vec.dx) + dy * vec.dy;
	}
	
	public function isParallel(vec:Vec):Bool
	{
		return dx * (vec.dy) == dy * vec.dx;
	}
	
	public function isZero():Bool
	{
		return dx.isZero() && dy.isZero();
	}
}

private class RationalPoint
{
	public var y:Rational;
	public var x:Rational;
	
	public function new(x:Rational, y:Rational)
	{
		this.x = x;
		this.y = y;
	}
}
