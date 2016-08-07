package;
import flash.display.Shape;

class SolverShape extends Shape
{
	public function draw(state:SolveState):Void
	{
		graphics.clear();
		for (polygon in state.polygons)
		{
			graphics.beginFill(0xFF2255, 0.3);
			graphics.lineStyle(0.2, 0xDD2255, 0.5);
			graphics.moveTo(
				state.vertexes[polygon.vertexes[0]].x.toFloat(), 
				state.vertexes[polygon.vertexes[0]].y.toFloat()
			);
			trace("d");
			
			for (vi in polygon.vertexes)
			{
				var v = state.vertexes[vi];
				trace("p", v.x.toFloat(), v.y.toFloat());
				graphics.lineTo(v.x.toFloat(), v.y.toFloat());
			}
			
			graphics.endFill();
		}
	}
}