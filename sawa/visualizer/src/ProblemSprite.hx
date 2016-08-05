package;
import flash.Lib;
import flash.display.Shape;
import flash.display.Sprite;
import flash.events.Event;
import flash.events.MouseEvent;
import flash.geom.ColorTransform;
import flash.geom.Point;
import haxe.ds.Option;
import thx.Rational;

class ProblemSprite extends Sprite
{
	public var lines:Array<LineShape>;
	public var polygons:Array<PolygonShape>;
	private var state:ProblemSpriteState;
	private var problem:Problem;
	private var updateText:String->Void;
	
	private static var RED_TRANSFORM:ColorTransform = new ColorTransform(1, 0.2, 0.2, 1, 100);
	private static var DARK_RED_TRANSFORM:ColorTransform = new ColorTransform(0.5, 0.0, 0.0, 1, 30);
	private static var DEFAULT_TRANSFORM:ColorTransform = new ColorTransform();
	
	public function new(problem:Problem, updateText:String->Void) 
	{
		super();
		this.updateText = updateText;
		this.problem = problem;
		lines = [];
		polygons = [];
		state = ProblemSpriteState.Newtral;
		
		for (i in 0...problem.polygons.length)
		{
			var polygon = new PolygonShape(problem, i);
			polygons.push(polygon);
			this.addChild(polygon);
		}
		
		for (line in problem.lineToPolygons.keys())
		{
			var key = line.split("_");
			var line = new LineShape(parsePoint(key[0]), parsePoint(key[1]));
			lines.push(line);
			this.addChild(line);
		}
		
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_MOVE, onMove);
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_UP, onUp);
		addEventListener(Event.REMOVED_FROM_STAGE, onRemove);
		
		updateText("ドラッグを開始してください");
	}
	
	private function parsePoint(key:String):ShapePoint
	{
		var i = Std.parseInt(key);
		var p = problem.points[i];
		return new ShapePoint(p.x, p.y, i);
	}
	
	private function onRemove(e:Event):Void 
	{
		removeEventListener(Event.REMOVED_FROM_STAGE, onRemove);
		Lib.current.stage.removeEventListener(MouseEvent.MOUSE_DOWN, onDown);
		Lib.current.stage.removeEventListener(MouseEvent.MOUSE_MOVE, onMove);
		Lib.current.stage.removeEventListener(MouseEvent.MOUSE_UP, onUp);
	}
	
	private function onUp(e:MouseEvent):Void 
	{
		switch (state)
		{
			case Newtral | LineSelect(_):
				updateText("ドラッグを開始してください");
				state = ProblemSpriteState.Newtral;
				
			case PolygonSelect(line, arr):
				updateText("除去対象をクリックして、openしてください");
				state = ProblemSpriteState.RemoveSelect(line, arr, []);
				
			case RemoveSelect(_):
				// 何もしない
		}
	}
	
	private function onMove(e:MouseEvent):Void 
	{
		switch (state)
		{
			case Newtral:
				// 何もしない
				
			case LineSelect(start):
				var end:Point = this.globalToLocal(new Point(e.stageX, e.stageY));
				end.x /= 100;
				end.y /= 100;
				for (line in lines)
				{
					var ax = start.x, ay = start.y;
					var bx = end.x, by = end.y;
					var cx = line.start.x.toFloat(), cy = line.start.y.toFloat();
					var dx = line.end.x.toFloat(), dy = line.end.y.toFloat();
					
					var ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
					var tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
					var tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
					var td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
					
					if (tc * td < 0 && ta * tb <= 0)
					{
						line.transform.colorTransform = RED_TRANSFORM;
						updateText("ドラッグで折りたたむ面を通過してください。" + end.x + "," + end.y);
						var arr = [];
						state = ProblemSpriteState.PolygonSelect(line, arr);
						
						return;
					}
				}
				
				updateText("ドラッグで折りたたむ線に対して交差してください。" + end.x + "," + end.y);
				state = ProblemSpriteState.LineSelect(end);
				
			case PolygonSelect(line, arr):
				var end:Point = this.globalToLocal(new Point(e.stageX, e.stageY));
				
				switch (polygonsHitTest(arr, end))
				{
					case Some(p):
						p.transform.colorTransform = RED_TRANSFORM;
						arr.push(p);
						
					case None:
				}
				state = ProblemSpriteState.PolygonSelect(line, arr);
				
			case RemoveSelect(_):
				// 何もしない
		}
	}
	
	private function polygonsHitTest(current:Array<PolygonShape>, point:Point):Option<PolygonShape>
	{
		for (polygon in polygons)
		{
			var global = localToGlobal(point);
			if (polygon.hitTestPoint(global.x, global.y, true))
			{
				if (current.indexOf(polygon) == -1)
				{
					return Option.Some(polygon);
				}
			}
		}
		
		return Option.None;
	}
	
	private function onDown(e:MouseEvent):Void 
	{
		switch (state)
		{
			case LineSelect(_) | PolygonSelect(_) | Newtral:
				for (line in lines)
				{
					line.transform.colorTransform = new ColorTransform();
				}
				for (polygon in polygons)
				{
					polygon.transform.colorTransform = new ColorTransform();
				}
				
				updateText("ドラッグで折りたたむ線に対して交差してください。");
				var start = this.globalToLocal(new Point(e.stageX, e.stageY));
				start.x /= 100;
				start.y /= 100;
				state = ProblemSpriteState.LineSelect(start);
				
			case RemoveSelect(line, arr, removes):
				var global = new Point(e.stageX, e.stageY);
				var end:Point = this.globalToLocal(global);
				
				for (polygon in arr)
				{
					if (polygon.hitTestPoint(global.x, global.y, true))
					{
						if (removes.remove(polygon))
						{
							polygon.transform.colorTransform = RED_TRANSFORM;
						}
						else
						{
							polygon.transform.colorTransform = DARK_RED_TRANSFORM;
							removes.push(polygon);
						}
						break;
					}
				}
		}
	}
	
	public function cancel():Void
	{
		switch (state)
		{
			case LineSelect(_) | PolygonSelect(_) | Newtral:
				
				
			case RemoveSelect(_):
				for (line in lines)
				{
					line.transform.colorTransform = new ColorTransform();
				}
				for (polygon in polygons)
				{
					polygon.transform.colorTransform = new ColorTransform();
				}
				updateText("ドラッグを開始してください");
				state = ProblemSpriteState.Newtral;
		}
	}
	
	public function open():Option<Problem>
	{
		switch (state)
		{
			case LineSelect(_) | PolygonSelect(_) | Newtral:
				return Option.None;
				
			case RemoveSelect(line, polygons, removePolygons):
				var newProblem = problem.apply(
					line.start.index, 
					line.end.index, 
					[for (p in polygons) p.index],
					[for (p in removePolygons) p.index]
				);
				return Option.Some(newProblem);
		}
	}
}

enum ProblemSpriteState
{
	Newtral;
	LineSelect(point:Point);
	PolygonSelect(line:LineShape, polygons:Array<PolygonShape>);
	RemoveSelect(line:LineShape, polygons:Array<PolygonShape>, removePolygons:Array<PolygonShape>);
}

class ShapePoint
{
	public var index:Int;
	public var x:Rational;
	public var y:Rational;
	
	public function new (x:Rational, y:Rational, index:Int)
	{
		this.x = x;
		this.y = y;
		this.index = index;
	}
}

class LineShape extends Shape
{
	public var start:ShapePoint;
	public var end:ShapePoint;
	
	public function new (start:ShapePoint, end:ShapePoint)
	{
		super();
		this.start = start;
		this.end = end;
		graphics.clear();
		graphics.lineStyle(0.01, 0x45FE34);
		graphics.moveTo(start.x.toFloat() * 100, start.y.toFloat() * 100);
		graphics.lineTo(end.x.toFloat() * 100, end.y.toFloat() * 100);
	}
}

class PolygonShape extends Shape
{
	public var index:Int;
	
	public function new (problem:Problem, index:Int)
	{
		super();
		this.index = index;
		graphics.clear();
		graphics.beginFill(0x45FE34, 0.2);
		var first = true;
		for (i in problem.polygons[index].vertexes)
		{
			var v = problem.points[i];
			if (first)
			{
				graphics.moveTo(v.x.toFloat() * 100, v.y.toFloat() * 100);
				first = false;
			}
			else
			{
				graphics.lineTo(v.x.toFloat() * 100, v.y.toFloat() * 100);
			}
		}
		graphics.endFill();
	}
}
