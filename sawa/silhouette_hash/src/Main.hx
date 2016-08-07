package;

import sys.FileSystem;
import sys.io.File;

class Main 
{
	public static var OUTPUT_DIRECTORY:String = "../../silhouette_hash";
	public static var PROBLEM_DIRECTORY:String = "../../problems";
	
	public static function main()
	{
		for (file in FileSystem.readDirectory("../../problems"))
		{
			if (StringTools.endsWith(file, ".txt"))
			{
				start(PROBLEM_DIRECTORY + "/" + file);
			}
		}
		
		Sys.getChar(false);
	}
	
	public static function start(file:String):Void
	{
		var content = File.getContent(file);
		new Pro;
	}
}
