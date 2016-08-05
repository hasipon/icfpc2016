package;

import com.bit101.components.ComboBox;
import com.bit101.components.PushButton;
import flash.Lib;
import flash.display.Shape;
import flash.display.Sprite;
import flash.events.Event;
import flash.text.TextField;
import haxe.Resource;
import haxe.Timer;
import haxe.ds.Option;

/**
 * ...
 * @author shohei909
 */
class Main extends Sprite 
{
	private var problems:Array<String>;
	private var index:Int = 0;
	private var problemSprite:ProblemSprite;
	private var textField:TextField;
	private var currentProblem:Array<Problem>;
	private var currentIndex:Int;
	
	private var outputField:TextField;
	private var redoButton:PushButton;
	private var undoButton:PushButton;
	
	public function new() 
	{
		super();
		addEventListener(Event.ADDED_TO_STAGE, init);
	}
	
	private function init(e:Event):Void 
	{
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
		outputField.width = 290;
		outputField.height = 700;
		outputField.x = 800;
		outputField.y = 50;
		
		graphics.lineStyle(1, 0, 0.1);
		graphics.beginFill(0, 0.05);
		graphics.drawRect(300, 300, 250, 250);
		addChild(outputField);
		
		var comboBox = new ComboBox(this, 0, 20, problems[index], problems);
		comboBox.addEventListener(Event.SELECT, onSelect);
		new PushButton(this, 0, 50, "cancel", cancel);
		new PushButton(this, 0, 70, "open", open);
		undoButton = new PushButton(this, 0, 90, "undo", undo);
		redoButton = new PushButton(this, 0, 110, "redo", redo);
		
		updateTarget(index);
	}
	
	private function undo(e:Event):Void 
	{
		update(currentIndex - 1);
	}
	
	private function redo(e:Event):Void 
	{
		update(currentIndex + 1);
	}
	
	private function onSelect(e:Event):Void 
	{
		var box:ComboBox = e.currentTarget;
		updateTarget(box.selectedIndex);
	}
	
	private function updateTarget(index:Int):Void
	{
		var name = problems[index];
		currentProblem = [new Problem(name, Resource.getString(name))];
		update(0);
	}

	public function open(e):Void
	{
		switch (problemSprite.open())
		{
			case Option.Some(newProblem):
				currentProblem = currentProblem.slice(0, index + 1);
				currentProblem.push(newProblem);
				update(index + 1);
				
			case Option.None:
		}
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
		problemSprite.scaleX = problemSprite.scaleY = 2.5;
		problemSprite.x = 300;
		problemSprite.y = 300;
		
		outputField.text = problem.output();
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
	
	public static function getProblems():Array<String>
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
				a = a.toLowerCase();
				b = b.toLowerCase();
				if (a < b) return -1;
				if (a > b) return 1;
				return 0;
			} 
		);
		
		return arr;
	}
}
