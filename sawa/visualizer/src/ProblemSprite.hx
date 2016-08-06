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
	public var problem:Problem;
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
		
		for (lineKey in problem.lineToPolygons.keys())
		{
			var line = lineKey.createShape(problem);
			lines.push(line);
			for (p in problem.lineToPolygons[lineKey])
			{
				polygons[p].lines.push(line);
			}
			this.addChild(line);
		}
		
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_DOWN, onDown);
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_MOVE, onMove);
		Lib.current.stage.addEventListener(MouseEvent.MOUSE_UP, onUp);
		
		addEventListener(Event.REMOVED_FROM_STAGE, onRemove);
		updateText("ドラッグを開始してください");
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
				
			case PolygonSelect(_, line, arr):
				updateText("除去対象をクリックして、openしてください");
				state = ProblemSpriteState.RemoveSelect(Option.None, line, arr, []);
				
			case RemoveSelect(_, line, arr, r):
				state = ProblemSpriteState.RemoveSelect(Option.None, line, arr, r);
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
				end.x /= 1000;
				end.y /= 1000;
				for (line in lines)
				{
					if (line.crossTest(start, end))
					{
						line.transform.colorTransform = RED_TRANSFORM;
						updateText("ドラッグで折りたたむ面を通過してください。" + end.x + "," + end.y);
						var arr = [];
						
						switch (polygonsHitTest(start, end))
						{
							case Some(p):
								p.transform.colorTransform = RED_TRANSFORM;
								arr.push(p);
								
							case None:
						}
						
						state = ProblemSpriteState.PolygonSelect(end, line, arr);
						return;
					}
				}
				
				updateText("ドラッグで折りたたむ線に対して交差してください。" + end.x + "," + end.y);
				state = ProblemSpriteState.LineSelect(end);
				
			case PolygonSelect(start, line, arr):
				var end:Point = this.globalToLocal(new Point(e.stageX, e.stageY));
				end.x /= 1000;
				end.y /= 1000;
				
				switch (polygonsHitTest(start, end))
				{
					case Some(p):
						if (arr.indexOf(p) == -1)
						{
							p.transform.colorTransform = RED_TRANSFORM;
							arr.push(p);
						}
						
					case None:
				}
				
				state = ProblemSpriteState.PolygonSelect(end, line, arr);
				
			case RemoveSelect(start, line, arr, removes):
				switch (start)
				{
					case Option.Some(_start):
						var end:Point = this.globalToLocal(new Point(e.stageX, e.stageY));
						end.x /= 1000;
						end.y /= 1000;
						
						switch (polygonsHitTest(_start, end))
						{
							case Option.Some(p):
								if (arr.indexOf(p) != -1)
								{
									if (removes.indexOf(p) == -1)
									{
										p.transform.colorTransform = DARK_RED_TRANSFORM;
										removes.push(p);
									}
								}
								
							case Option.None:
						}
						
						state = ProblemSpriteState.RemoveSelect(Option.Some(end), line, arr, removes);
						
					case Option.None:
				}
				
		}
	}

	private function polygonsHitTest(start:Point, end:Point):Option<PolygonShape>
	{
		var data = Option.None;
		var top = new Point(-10000, 9999999);
		for (line in lines)
		{
			if (!line.crossTest(start, end))
			{
				continue;
			}
			
			var key = new LineKey(line.start.index, line.end.index);
			var hitPolygons = problem.lineToPolygons[key];
			for (hitPolygon in hitPolygons) 
			{
				var count = 0;
				for (pl in polygons[hitPolygon].lines)
				{
					if (pl.crossTest(end, top))
					{
						count++;
					}
				}
				
				if (count % 2 == 1)
				{
					data = Option.Some(polygons[hitPolygon]);
				}
			}
		}
		
		return data;
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
				
				updateText("ドラッグで折りたたむ線に対して交差してください。" + e.stageX + "," + e.stageY);
				var start = this.globalToLocal(new Point(e.stageX, e.stageY));
				start.x /= 1000;
				start.y /= 1000;
				state = ProblemSpriteState.LineSelect(start);
				
			case RemoveSelect(_, line, arr, removes):
				var global = new Point(e.stageX, e.stageY);
				var end:Point = this.globalToLocal(global);
				end.x /= 1000;
				end.y /= 1000;
				
				state = ProblemSpriteState.RemoveSelect(Option.Some(end), line, arr, removes);
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
				
			case RemoveSelect(_, line, polygons, removePolygons):
				var newProblem = problem.clone();
				newProblem.apply(
					line.start.index, 
					line.end.index, 
					[for (p in polygons) p.index],
					[for (p in removePolygons) p.index]
				);
				
				return Option.Some(newProblem);
		}
	}
	
	public function selectAll() :Void
	{
		switch (state)
		{
			case LineSelect(_) | PolygonSelect(_) | Newtral:
				
			case RemoveSelect(p, line, _, removePolygons):
				var arr = [
					for (polygon in polygons)
					{
						if (removePolygons.indexOf(polygon) == -1)
						{
							polygon.transform.colorTransform = RED_TRANSFORM;
						}
						polygon;
					}
				];
				state = ProblemSpriteState.RemoveSelect(p, line, arr, removePolygons);
		}
	}
}

enum ProblemSpriteState
{
	Newtral;
	LineSelect(point:Point);
	PolygonSelect(point:Point, line:LineShape, polygons:Array<PolygonShape>);
	RemoveSelect(point:Option<Point>, line:LineShape, polygons:Array<PolygonShape>, removePolygons:Array<PolygonShape>);
}
