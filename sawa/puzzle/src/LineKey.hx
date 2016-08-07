package;
import haxe.ds.Option;

abstract LineKey(String) to String
{
	public function new(i0:Int, i1:Int)
	{
		this = i0 + "_" + i1;
	}
}