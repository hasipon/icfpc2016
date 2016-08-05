package;

import com.bit101.components.ComboBox;
import com.bit101.components.PushButton;
import flash.Lib;
import flash.display.Shape;
import flash.display.Sprite;
import flash.display.StageScaleMode;
import flash.events.Event;
import flash.text.TextField;
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
	private var problems:Array<String>;
	private var index:Int = 0;
	private var problemSprite:ProblemSprite;
	private var textField:TextField;
	private var currentProblem:Array<Problem>;
	private var currentIndex:Int;
	
	private var outputField:TextField;
	private var outputField2:TextField;
	private var redoButton:PushButton;
	private var undoButton:PushButton;
	
	
	public function new() 
	{
		super();
		addEventListener(Event.ADDED_TO_STAGE, init);
	}
	
	private function init(e:Event):Void 
	{
		stage.scaleMode = StageScaleMode.SHOW_ALL;
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
		outputField2.height = 380;
		outputField2.x = 800;
		outputField2.y = 410;
		addChild(outputField2);
		
		graphics.lineStyle(1, 0, 0.1);
		graphics.beginFill(0, 0.05);
		graphics.drawRect(300, 300, 250, 250);
		
		var comboBox = new ComboBox(this, 0, 20, problems[index], problems);
		comboBox.addEventListener(Event.SELECT, onSelect);
		new PushButton(this, 0, 50, "cancel", cancel);
		new PushButton(this, 0, 70, "open", open);
		undoButton = new PushButton(this, 0, 90, "< undo", undo);
		redoButton = new PushButton(this, 0, 110, "redo >", redo);
		new PushButton(this, 0, 130, "normalize", normalize);
		new PushButton(this, 0, 150, "select_all", selectAll);
		
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
	
	private function normalize(e:Event):Void 
	{
		var child = currentProblem[currentIndex].clone();
		child.normalize();
		addProblem(child);
	}
	
	private function selectAll(e:Event):Void 
	{
		problemSprite.selectAll();
	}
	
	private function onSelect(e:Event):Void 
	{
		var box:ComboBox = e.currentTarget;
		updateTarget(box.selectedIndex);
	}
	
	private function updateTarget(index:Int):Void
	{
		this.index = index;
		this.name = problems[index];
		currentProblem = [new Problem(name, Resource.getString(name))];
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
		problemSprite.scaleX = problemSprite.scaleY = 2.5;
		problemSprite.x = 300;
		problemSprite.y = 300;
		
		outputField.text = problem.output(currentProblem[0]);
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
