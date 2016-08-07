package;
import haxe.Json;
import haxe.io.Bytes;
import haxe.macro.Context;
import sys.FileSystem;
import sys.io.File;

class BuildMacro
{
	public static function run():Void
	{
		var solutionFiles = new Map();
		var dir = "../../solutions";
		for (name in FileSystem.readDirectory(dir))
		{
			if (StringTools.endsWith(name, ".json"))
			{
				var id = name.split("-")[0];
				var data = Json.parse(File.getContent(dir + "/" + name));
				solutionFiles[id] = data;
			}
		}
		
		var dir = "../../problems2";
		for (name in FileSystem.readDirectory(dir))
		{
			var id = name.split(".txt")[0];
			var solution = if (solutionFiles.exists(id)){
					var s = solutionFiles[id];
					if (s.resemblance >= 1)  continue;
					s;
				} else null;
			
			Context.addResource(
				id, 
				Bytes.ofString(
					Json.stringify(
						{
							id: id,
							data : File.getContent(dir + "/" + name),
							solution : solution,
						}
					)
				)
			);
		}
	}	
}
