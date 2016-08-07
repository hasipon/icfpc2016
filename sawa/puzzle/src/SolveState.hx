package;
import haxe.ds.Option;
import thx.Rational;

class SolveState
{
	// 配置済み多角形
	public var polygons:Array<Polygon>;
	public var vertexes:Array<Vertex>;
	public var usedLines:Map<LineKey, Bool>;
	public var appearedLines:Map<LineKey, Bool>;
	public var addedVertexes:Map<String, Int>;
	
	// 現在走査中の多角形
	public var polygonIndex:Int;
	public var vertexIndex:Int;
	
	public static var CLEAR_SCORE:Float = 1000000000; 
	public static var FAIL_SCORE:Float = -1000000000; 
	
	public var score:Float;
	public var area:Rational;
	
	public function new(problem:Problem, polygonRef:PolygonRef, reversed:Bool, length:Rational)
	{
		this.polygons = [];
		this.usedLines = new Map();
		this.appearedLines = new Map();
		this.addedVertexes = new Map();
		area = Rational.zero;
		
		if (!reversed)
		{
			this.vertexes = [new Vertex(0, 0, polygonRef.start), new Vertex(0, length, polygonRef.end)];
		}
		else
		{
			this.vertexes = [new Vertex(0, 0, polygonRef.end), new Vertex(0, length, polygonRef.start)];
		}
		
		usedLines = new Map();
		if (!addPolygon(problem, new SolveLine(1, 0), polygonRef, reversed))
		{
			throw "ポリゴンの追加に失敗しました";
		}

		polygonIndex = 0;
		vertexIndex = 0;
		score = 0;
		eval();
	}	
	
	private function eval():Void
	{
		if (area > 1)
		{
			score = FAIL_SCORE;
			return;
		}
		if (area == 1)
		{
			score = CLEAR_SCORE;
			return;
		}
		
		score = 0;
		score += area.toFloat();
	}
	
	public function createChildren(problem:Problem):Array<SolveState>
	{
		var poly = polygons[polygonIndex];
		var len = poly.vertexes.length;
		var vi0 = poly.vertexes[vertexIndex];
		var vi1 = poly.vertexes[(vertexIndex + 1) % len];
		var v0 = vertexes[vi0];
		var v1 = vertexes[vi1];
		var key = new LineKey(v0.source, v1.source);
		
		var solveLine = new SolveLine(vi0, vi1);
		var result = [];
		
		function add(reversed:Bool):Void
		{
			var key = if (reversed) new LineKey(v0.source, v1.source) else new LineKey(v1.source, v0.source);
			trace("source" + v0.source + "," +  v1.source);
			if (problem.polygonRefs.exists(key))
			{
				var child = clone();
				var polygonRef = problem.polygonRefs[key];
				
				if (child.addPolygon(problem, solveLine, problem.polygonRefs[key], reversed))
				{
					if (poly.source == polygonRef.poly.source)
					{
						usedLines[new LineKey(vi0, vi1)] = true;
					}
					child.process();
					result.push(child);
				}
			}
		}
		
		if (appearedLines.exists(new LineKey(vi1, vi0)))
		{
			var child = clone();
			child.process();
			result.push(child);
			trace("appeared");
		}
		else
		{
			add(false);
			add(true);
			trace("result:" + result.length);
		}
		
		return result;
	}
	
	private function process():Void
	{
		var poly = polygons[polygonIndex];
		var len = poly.vertexes.length;
		
		vertexIndex++;
		if (len <= vertexIndex)
		{
			polygonIndex++;
			vertexIndex = 0;
		}
		
		eval();
	}
	
	private function clone():SolveState
	{
		var child = Type.createEmptyInstance(SolveState);
		child.polygons = polygons.copy();
		child.vertexes = vertexes.copy();
		child.usedLines = [for (key in usedLines.keys()) key => usedLines[key]];
		child.appearedLines = [for (key in appearedLines.keys()) key => appearedLines[key]];
		child.addedVertexes = [for (key in addedVertexes.keys()) key => addedVertexes[key]];
		child.polygonIndex = polygonIndex;
		child.vertexIndex = vertexIndex;
		child.area = area;
		return child;
	}
	
	private function addPolygon(problem:Problem, solveLine:SolveLine, polygonRef:PolygonRef, reversed:Bool):Bool
	{	
		var sv = vertexes[solveLine.start];
		var ev = vertexes[solveLine.end];
		var va = new Vec(sv, ev);
		var vb = new Vec(problem.vertexes[polygonRef.start], problem.vertexes[polygonRef.end]);
		var psv = problem.vertexes[polygonRef.start];
		
		var cos = vb.inner(va) / va.getLength2();
		var sin = vb.outer(va) / va.getLength2();
		var dx = sv.x - (cos * psv.x - sin * psv.y);
		var dy = sv.y - (sin * psv.x + cos * psv.y);
		trace(dx, dy, cos, sin, cos * cos + sin * sin);
		
		var poly = polygonRef.poly;
		var newVertexes = [];
		
		for (vi in poly.vertexes)
		{
			var v = problem.vertexes[vi];
			
			var x = (cos * v.x - sin * v.y) + dx;
			var y = (sin * v.x + cos * v.y) + dy;
			
			newVertexes.push(new Vertex(x, y, v.source));
		}
		
		if (reversed)
		{
			for (v in newVertexes)
			{
				v.mirror(sv, ev);
			}
			newVertexes.reverse();
		}
		
		var vertexIndexes = [];
		for (v in newVertexes)
		{
			switch (addVertex(v))
			{
				case Option.Some(vi):
					vertexIndexes.push(vi);
					
				case Option.None:
					return false;
			}
		}
		
		var len = vertexIndexes.length;
		for (i in 0...len)
		{
			var vi0 = vertexIndexes[i % len];
			var vi1 = vertexIndexes[(i + 1) % len];
			appearedLines[new LineKey(vi0, vi1)] = true;
		}
		
		var polygon = new Polygon(vertexIndexes, poly.area, poly.source);
		polygons.push(polygon);
		area += polygon.area;
		
		return true;
	}
	
	public function addVertex(vertex:Vertex):Option<Int>
	{
		var key = vertex.x.toString() + "_" + vertex.y.toString();
		return if (addedVertexes.exists(key))
		{
			var id = addedVertexes[key];
			var old = vertexes[id];
			trace(key, old.source, vertex.source);
			if (old.source == vertex.source)
			{
				Option.Some(id);
			}
			else
			{
				Option.None;
			}
		}
		else
		{
			var id = vertexes.length;
			vertexes.push(vertex);
			addedVertexes[key] = id;
			Option.Some(id);
		}
	}
}
