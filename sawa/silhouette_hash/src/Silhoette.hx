package;
import thx.Rational;

class Silhoette
{
	// 元データ
	private var name:String;
	public var points:Array<SilhoettePoint>;
	public var polygone:Array<SilhoettePolygon>;
	
	// 高速化用データ
	public var lines:Map<LineKey, Line>;
	
	public static var newLine:EReg = ~/(\r\n)|\n|\r/g;

	public function new(name:String, input:String) 
	{
		this.name = name;
	}
}

typedef SilhoetteResult = 
{
	x: Rational,
	y: Rational,
	rotateTan: Rational,
	hash: String,
	inner_radius_square: Rational,
	outer_radius_square: Rational,
}

class SilhoettePoint
{
	public var x:Rational;
	public var y:Rational;
	
	public function new (x:Rational, y:Rational)
	{
		
	}
}

class SilhoettePolygon
{
	public var points:Array<Int>;
	public var 
}

