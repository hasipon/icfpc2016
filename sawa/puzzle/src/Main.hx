package;

import com.bit101.components.ComboBox;
import com.bit101.components.InputText;
import com.bit101.components.PushButton;
import flash.Lib;
import flash.display.Shape;
import flash.display.Sprite;
import flash.display.StageScaleMode;
import flash.errors.Error;
import flash.events.Event;
import flash.events.KeyboardEvent;
import flash.text.TextField;
import flash.ui.Keyboard;
import haxe.Http;
import haxe.Json;
import haxe.Resource;
import haxe.Timer;
import haxe.ds.Option;
import thx.BigInt;
import thx.Rational;

/**
 * ...
 * @author shohei909
 */
class Main extends Sprite 
{
	private var problems:Array<ProblemSource>;
	private var solverShape:SolverShape;
	private var solver:Solver;
	private var index:Int;
	
	public function new() 
	{
		super();
		addEventListener(Event.ADDED_TO_STAGE, init);
	}
	public static function main() 
	{
		Timer.delay(Lib.current.addChild.bind(new Main()), 1);
	}
	
	private function init(e:Event):Void 
	{
		stage.scaleMode = StageScaleMode.SHOW_ALL;
		removeEventListener(Event.ADDED_TO_STAGE, init);
		addEventListener(Event.ENTER_FRAME, onFrame);
	
		problems = getProblems();
		index = 0;
		
		solverShape = new SolverShape();
		solverShape.scaleX = solverShape.scaleY = 100;
		solverShape.x = solverShape.y = 200;
		addChild(solverShape);
		
		startSolve();
	}
	
	public function startSolve():Void
	{
		var source = problems[index];
		var problem = new Problem(source.id, source.data);
		solver = new Solver(problem);
	}
	
	private function onFrame(e:Event):Void 
	{
		solver.progress();
		solverShape.draw(solver.currentStates[0]);
	}
	
	public static function getProblems():Array<ProblemSource>
	{
		var arr = Resource.listNames();
		arr.sort(
			function(a:String, b:String):Int
			{
				a = a.toLowerCase();
				b = b.toLowerCase();
				if (a < b) return -1;
				if (a > b) return 1;
				return 0;
			} 
		);
		
		return [
			for (name in arr) 
			{
				Json.parse(Resource.getString(name));
			}
		];
	}
	
	private static var resultEReg = ~/pre(.*)pre/s;
	public function submit(id:Int, solution:String):Void
	{
		var http = new Http("http://52.197.240.199:5000/submit-solution");
		var solution = StringTools.urlEncode(solution);
		var postData = "problem_id=" + id + "&solution=" + solution;
		
		trace("通信中", postData);
		http.onError = function (e)
		{
			trace(e);
		};
		http.onData = function (data:String)
		{
			trace(data);
		};
		
		http.setPostData(postData);
		http.setHeader("ContentType", "application/x-www-form-urlencoded");
		http.request(true);
	}
}
