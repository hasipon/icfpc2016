package;
import haxe.macro.Context;
import sys.FileSystem;
import sys.io.File;

class BuildMacro
{
	public static function run():Void
	{
		var dir = "../../problems2";
		for (name in FileSystem.readDirectory(dir))
		{
			Context.addResource(name, File.getBytes(dir + "/" + name));
		}
	}	
}