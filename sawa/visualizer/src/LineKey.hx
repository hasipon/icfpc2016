package;

abstract LineKey(String) 
{
	public function new(i0:Int, i1:Int)
	{
		this = if (i0 < i1) i0 + "_" + i1 else i1 + "_" + i0;
	}	
}