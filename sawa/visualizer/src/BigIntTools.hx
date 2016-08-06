package;
import thx.BigInt;

class BigIntTools
{
	public static function isSquareNumber(i:BigInt):Bool 
	{
		var sq = intSqrt(i);
		return (sq * sq == i);
	}
	
	public static function intSqrt(i:BigInt):BigInt
	{
		// ニュートン法
		var s = BigInt.fromInt(1); 
		var s2 = BigInt.fromInt(1);
		
		do
		{
			s = (i / s + s) / BigInt.fromInt(2); 
			s2 = s + BigInt.fromInt(1);
		}
		while (s * s > i || i >= s2 * s2);
		
		return s;	
	}
}
