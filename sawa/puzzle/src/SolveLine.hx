package;

class SolveLine
{
	public var start:Int;
	public var end:Int;
	public var key:LineKey;
	
	public function new(start:Int, end:Int) 
	{
		this.start = start;
		this.end = end;
		this.key = new LineKey(start, end);
	}
}