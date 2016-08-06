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
	
	public function connect(target:Polygon):Polygon
	{
		var matched:Map<LineKey, Array<Int>> = new Map();
		var lines:Map<String, Int> = new Map();
		var vs = vertexes;
		var l = vs.length;
		
		for (i in 0...l)
		{
			var v0 = vs[i];
			var v1 = vs[(i + 1) % l];
			var line = v0 + "_" + v1;
			lines[line] = (i + 1) % l;
		}
		
		var hit:Bool = false;
		inline function searchTarget():Void
		{
			var vs = target.vertexes;
			var l = vs.length;
			
			for (i in 0...l)
			{
				var v0 = vs[i];
				var v1 = vs[(i + 1) % l];
				var line = v1 + "_" + v0;
				if (lines.exists(line))
				{
					matched[new LineKey(v0, v1)] = [lines[line], (i + 1) % l];
					hit = true;
				}
			} 
		}
		
		searchTarget();
		if (!hit)
		{
			target.vertexes.reverse();
			searchTarget();
		}
		if (!hit)
		{
			throw "共通の辺がありませんでした。";
		}
		
		var result = [];
		for (start in 0...vertexes.length)
		{
			var j = 0;
			var i = start;
			var vs = [vertexes, target.vertexes];
			var ls = [vertexes.length, target.vertexes.length];
			for (_ in 0...(vertexes.length + target.vertexes.length))
			{
				var v0 = vs[j][i];
				var v1 = vs[j][(i + 1) % ls[j]];
				var key = new LineKey(v0, v1);
				if (matched.exists(key))
				{
					j = (j + 1) % 2;
					i = matched[key][j];
				}
				else
				{
					result.push(v1);
					i = (i + 1) % ls[j];
				}
				
				if (i == start && j == 0)
				{
					break;
				}
			}
			
			if (result.length > 0)
			{
				break;
			}
		}
		return new Polygon(result);
	}
}
