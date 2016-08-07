import flash.display.Graphics;
import flash.display.Shape;
import flash.display.Sprite;
import flash.geom.Point;
import haxe.ds.Option;
import thx.Rational;

class Problem
{
	// 元データ
	public var vertexes:Array<Vertex>;
	public var polygons:Array<Polygon>;
	
	// 高速化用データ
	public var polygonRefs:Map<LineKey, PolygonRef>;
	
	public static var newLine:EReg = ~/(\r\n)|\n|\r/g;

	public function new(name:String, input:String) 
	{
		var inputs = newLine.split(input);
		var iter = inputs.iterator();
		var pointCount = Std.parseInt(iter.next());
		vertexes = [
			for (i in 0...pointCount)
			{
				parseVertex(iter.next(), i);
			}
		];
		
		var polygonCount = Std.parseInt(iter.next());
		polygons = [
			for (i in 0...polygonCount)
			{
				parsePolygon(iter.next(), i);
			}
		];
		
		polygonRefs = new Map();
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
				
				var line;
				var reversed:Bool;
				
				if (polygonRefs.exists(lineKey))
				{
					throw "線の使用が重複";
				}
				else
				{
					polygonRefs[lineKey] = new PolygonRef(v0, v1, polygon, i, new Vec(vertexes[v0], vertexes[v1]).getLength());
				}
			}
		}
	}
	
	private function parsePolygon(str:String, index:Int):Polygon 
	{
		var vs = str.split(" ");
		var data = [
			for (v in vs)
			{
				Std.parseInt(v);
			}
		];
		
		var area = Rational.zero;
		var len = data.length;
		var v = vertexes[data[0]];
		for (i in 0...len)
		{
			var v0 = vertexes[data[i % len]];
			var v1 = vertexes[data[(i + 1) % len]];
			area += new Vec(v, v0).outer(new Vec(v, v1));
		}
		
		return new Polygon(data, area / 2, index);
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
}
