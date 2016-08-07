package;
import thx.Rational;

class Silhoette
{
	// 元データ
	private var name:String;
	public var polygones:Array<SilhoettePolygon>;
	
	// 高速化用データ
	public var lines:Map<LineKey, Line>;
	
	public static var newLine:EReg = ~/(\r\n)|\n|\r/g;

	public function new(name:String, input:String) 
	{
		this.name = name;
		
		var lines = newLine.split(input);
		var polygonCount:Int = 0;
		var polygons = [
			for ()
			{
				pointCount:
			}
		];
	}
	
	
	// データを算出する。
	public function calc():SilhoetteResult
	{
		var primary = polygones[0];
		var pr = primary.calc();
		return {
			name: name,
			x: primary.center.x,
			y: primary.center.y,
			rotationTan: 
			
		};
	}
}

typedef SilhoetteResult = 
{
	name: String,
	x: Rational,
	y: Rational,
	startPoint: Rational,
	reversed: Bool,
	hash: String,
	
	// 
	periphery_square: Rational;
	inner_radius_square: Rational,
	outer_radius_square: Rational,
	hole_count: Int,
	vertex_count: Int,
}

class SilhoettePoint
{
	public var x:Rational;
	public var y:Rational;
	
	public function new (x:Rational, y:Rational)
	{
		this.x = x;
		this.y = y;
	}
}

class SilhoettePolygon
{
	public var points:Array<SilhoettePoint>;
	public var center:SilhoettePoint;
	public var cosData:Array<Rational>;
	
	// 最も外側にある点の集合
	public var outerPoints:Array<Int>;
	public var innerRadiusSquare:Rational
	public var outerRadiusSquare:Rational
	
	public function new (sourcePoints:Array<SilhoettePoint>)
	{
		this.points = [];
		
		var centerX = Rational.fromInt(0);
		var centerY = Rational.fromInt(0); 
		
		var ps
		var l = length
		for (source in )
		{
			var  = ;
			
			if (cosSquare == 1)
			{
				
			}
			
			points.push();
			centerX += point.x;
			centerY += point.y;
		}
		
		centerX /= points.length;
		centerY /= points.length;
		
		// ルート2以上遠くにある点はない
		innerRadiusSquare = Rational.fromInt(100000);
		outerRadiusSquare = Rational.fromInt(0);
		outerPoints = [];
		
		for (point in points)
		{
			var dx = point.x - centerX;
			var dy = point.y - centerY;
			var radius = dx * dx + dy * dy;
			
			if (outerRadiusSquare == radius)
			{
				outerPoints.push(point);
			}
			else if (outerRadiusSquare < radius)
			{
				outerRadiusSquare = radius;
				outerPoints = [point];
			}
			
			if (innerRadiusSquare > radius)
			{
				innerRadiusSquare = radius;
			}
		}
	}
	
	public function calc():PolygonResult
	{
		
	}
	
	private function calcIndexHash(index:Int, reversed:Bool):String
	{
		
	}
}

class Vec
{
	public function new (start:SilhoettePoint, end:SilhoettePoint)
	{
		var dx = end.x - start.x;
		var dy = end.y - start.y;
	}
	
	// 内積
	public function inner(vec:Vec):Rational
	{
		return dx * (vec.dx) + dy * vec.dy;
	}
	
	// 外積
	public function inner(vec:Vec):Rational
	{
		return dx * (vec.dx) + dy * vec.dy;
	}
	
	// なす角のコサイン2乗
	public function cosSquare():Rational
	{
		return inner
	}
	
	// なす角のサイン2乗
	public function sinSquare():Rational
	{
		
	}
}

private typedef PolygonResult = 
{
	hash: String,
	rotateTan: Rational,
	reversed: Bool,
}
