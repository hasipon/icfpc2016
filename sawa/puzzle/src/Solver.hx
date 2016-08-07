package;
import haxe.ds.Option;

class Solver
{
	private var problem:Problem;
	public var currentStates:Array<SolveState>;
	
	public function new(problem:Problem) 
	{
		this.problem = problem;
		this.currentStates = [];
		
		for (polygonRef in problem.polygonRefs)
		{
			switch (polygonRef.length)
			{
				case Option.Some(length):
					currentStates.push(new SolveState(problem, polygonRef, false, length));
					currentStates.push(new SolveState(problem, polygonRef, true, length));
					
				case Option.None:
			}
		}
	}
	
	public function progress():Option<SolveState>
	{
		var nextStates = [];
		for (current in currentStates)
		{
			for (child in current.createChildren(problem))
			{
				if (child.score >= SolveState.CLEAR_SCORE)
				{
					trace("clear");
					return Option.Some(child);
				}
				if (child.score <= SolveState.FAIL_SCORE)
				{
					
					trace("fail");
					continue;
				}
				
				trace("score:" + child.score);
				nextStates.push(child);
			}
		}
		
		currentStates = nextStates;
		return None;
	}
}