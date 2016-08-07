package;
import haxe.ds.Option;

abstract LineKey(String) to String
{
	public function new(i0:Int, i1:Int)
	{
		this = if (i0 < i1) i0 + "_" + i1 else i1 + "_" + i0;
	}
	
	public inline function convert(pointMap:Map<Int, Int>):Option<LineKey>
	{
		var keys = this.split("_").map(Std.parseInt);
		
		return if (pointMap.exists(keys[0]) && pointMap.exists(keys[1]))
		{
			Option.Some(new LineKey(pointMap[keys[0]], pointMap[keys[1]]));
		}
		else
		{
			Option.None;
		}
	}
}