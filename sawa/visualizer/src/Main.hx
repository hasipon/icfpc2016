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
	private var index:Int = 14;
	private var problemSprite:ProblemSprite;
	private var textField:TextField;
	private var currentProblem:Array<Problem>;
	private var currentIndex:Int;
	
	private var outputField:TextField;
	private var outputField2:TextField;
	private var redoButton:PushButton;
	private var undoButton:PushButton;
	private var submitButton:PushButton;
	var inputText:InputText;
	var comboBox:ComboBox;
	
	public function new() 
	{
		super();
		addEventListener(Event.ADDED_TO_STAGE, init);
	}
	
	private function init(e:Event):Void 
	{
		stage.scaleMode = StageScaleMode.SHOW_ALL;
		stage.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
		removeEventListener(Event.ADDED_TO_STAGE, init);
		problems = getProblems();
		
		textField = new TextField();
		textField.width = stage.stageWidth;
		addChild(textField);
		
		outputField = new TextField();
		outputField.selectable = true;
		addChild(outputField);
		outputField.backgroundColor = 0xEEEEEE;
		outputField.background = true;
		outputField.border = true;
		outputField.width = 390;
		outputField.height = 380;
		outputField.x = 800;
		outputField.y = 10;
		addChild(outputField);
		
		outputField2 = new TextField();
		outputField2.selectable = true;
		addChild(outputField2);
		outputField2.backgroundColor = 0xEEEEEE;
		outputField2.background = true;
		outputField2.border = true;
		outputField2.width = 390;
		outputField2.height = 350;
		outputField2.x = 800;
		outputField2.y = 440;
		addChild(outputField2);
		
		graphics.lineStyle(1, 0, 0.1);
		graphics.beginFill(0, 0.05);
		graphics.drawRect(300, 300, 250, 250);
		
		comboBox = new ComboBox(this, 0, 20, problems[index].id, 
			[for (p in problems) p.id + " (" + (if (p.solution != null) Std.int(p.solution.resemblance * 100) else 0) + "%)" ]
		);
		comboBox.addEventListener(Event.SELECT, onSelect);
		inputText = new InputText(this, 0, 50, "", null);
		new PushButton(this, 100, 50, "go", input);
		new PushButton(this, 0, 70, "cancel(C)", cancel);
		new PushButton(this, 0, 90, "open(O)", open);
		undoButton = new PushButton(this, 0, 110, "< undo(Z)", undo);
		redoButton = new PushButton(this, 0, 130, "redo(Y) >", redo);
		new PushButton(this, 0, 150, "normalize(N)", finalize);
		new PushButton(this, 0, 170, "centering(Q)", center);
		new PushButton(this, 0, 190, "select_all(A)", selectAll);
		new PushButton(this, 0, 210, "remove_all(D)", removeAll);
		submitButton = new PushButton(this, 800, 400, "submit(S)", submit);
		submitButton.enabled = false;
		
		updateTarget(index);
	}
	
	
	private function onKeyDown(e:KeyboardEvent):Void 
	{
		switch (e.keyCode)
		{
			case Keyboard.A:
				selectAll(null);
				
			case Keyboard.C:
				cancel(null);
				
			case Keyboard.O:
				open(null);
				
			case Keyboard.Q:
				center(null);
				
			case Keyboard.Z:
				undo(null);
				
			case Keyboard.Y:
				redo(null);
				
			case Keyboard.N:
				finalize(null);
				
			case Keyboard.R:
				reduce(null);
				
			case Keyboard.D:
				removeAll(null);
				
			case Keyboard.S:
				submit(null);
		}
	}
	
	public function removeAll(e:Event):Void 
	{
		problemSprite.removeAll();
	}
	
	private function input(e:Event):Void 
	{
		var l = problems.length;
		for (i in 0...l)
		{
			if (problems[i].id == inputText.text)
			{
				comboBox.selectedIndex = i;
				onSelect(null);
			}
		}
	}
	
	private function undo(e:Event):Void 
	{
		if (undoButton.enabled)
		{
			update(currentIndex - 1);
		}
	}
	
	private function redo(e:Event):Void 
	{
		if (redoButton.enabled)
		{
			update(currentIndex + 1);
		}
	}
	
	private function center(e:Event):Void 
	{
		var child = currentProblem[currentIndex].clone();
		child.center();
		addProblem(child);
	}
	
	private function finalize(e:Event):Void 
	{
		var child = currentProblem[currentIndex].clone();
		child.finalize();
		addProblem(child);
	}
	
	private function reduce(e):Void
	{
		var child = currentProblem[currentIndex].clone();
		child.reduce();
		addProblem(child);
	}
	
	private function selectAll(e:Event):Void 
	{
		problemSprite.selectAll();
	}
	
	private function onSelect(e:Event):Void 
	{
		updateTarget(comboBox.selectedIndex);
	}
	
	private function updateTarget(index:Int):Void
	{
		this.index = index;
		this.name = problems[index].id;
		currentProblem = [new Problem(name, problems[index].data)];
		update(0);
	}

	public function open(e):Void
	{
		switch (problemSprite.open())
		{
			case Option.Some(newProblem):
				addProblem(newProblem);
				
			case Option.None:
		}
	}
	
	private function addProblem(newProblem:Problem) 
	{
		currentProblem = currentProblem.slice(0, currentIndex + 1);
		currentProblem.push(newProblem);
		update(currentIndex + 1);		
	}
	
	public function cancel(e):Void
	{
		problemSprite.cancel();
	}
	
	public function update(currentIndex:Int):Void
	{
		this.currentIndex = currentIndex;
		if (problemSprite != null)
		{
			removeChild(problemSprite);
			problemSprite = null;
		}
		
		var problem = currentProblem[currentIndex];
		problemSprite = problem.create(updateText);
		problemSprite.scaleX = problemSprite.scaleY = 0.25;
		problemSprite.x = 300;
		problemSprite.y = 300;
		
		outputField.text = problem.output(currentProblem[0]).split("-0").join("0");
		outputField2.text = outputField.text.length + "Byte です。";
		
		// outputField.text = Resource.getString(name).split("\r\n").join("\n") + problem.output2();
		undoButton.enabled = (currentIndex > 0);
		redoButton.enabled = currentIndex < (currentProblem.length - 1);
		
		addChild(problemSprite);
	}
	
	public function updateText(text:String):Void
	{
		textField.text = text;
	}
	
	public static function main() 
	{
		Timer.delay(Lib.current.addChild.bind(new Main()), 1);
	}
	
	public static function getProblems():Array<ProblemSource>
	{
//		var inputDir = File.applicationDirectory.resolvePath("input");
//		
//		return [
//			for (file in Resource.listNames())
//			{
//				var stream = new FileStream();
//				stream.open(file, FileMode.READ);
//				stream.position = 0;
//				var content = stream.readUTFBytes(stream.bytesAvailable);
//				stream.close();
//				new Problem(file.name, content);
//			}
//		];

		var arr = Resource.listNames();
		arr.sort(
			function(a:String, b:String):Int
			{
				var ai = Std.parseInt(a);
				var bi = Std.parseInt(b);
				if (ai < bi) return -1;
				if (ai > bi) return 1;
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
	public function submit(e:Event):Void
	{
//		var http = new Http("http://52.197.240.199:5000/submit-solution");
//		var id = problems[index].id;
//		var solution = StringTools.urlEncode(outputField.text);
//		var postData = "problem_id=" + id + "&solution=" + solution;
//		
//		outputField2.text = "通信中";
//		submitButton.enabled = false;
//		http.onError = function (e)
//		{
//			outputField2.text = "error";
//			submitButton.enabled = true;
//		};
//		http.onData = function (data:String)
//		{
//			if (resultEReg.match(StringTools.htmlUnescape(data)))
//			{
//				outputField2.text = resultEReg.matched(1);
//			}
//			else
//			{
//				outputField2.text = data;
//			}
//			
//			submitButton.enabled = true;
//		};
//		
//		http.setPostData(postData);
//		http.setHeader("ContentType", "application/x-www-form-urlencoded");
//		http.request(true);
	}
}
