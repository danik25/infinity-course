package ElbitAssignment.java;

import java.util.List;
import java.util.ArrayList;

public class Graph
{
	List<GraphObject> graph;
	
	Graph()
	{
		graph = new ArrayList<>();
	}
	
	void add(GraphObject toAdd, GraphObject... connections)
	{
		graph.add(toAdd);
		toAdd.add(connections);
	}

	List <List<Integer>> getPattern(char ... types)
	{
		List <List<Integer>> answer = new ArrayList<>();
		boolean[] isChecked = new boolean[graph.size()];
		
		for(GraphObject obj : graph)
		{
			if(obj.type == types[0])
			{
				List <Integer> sub = new ArrayList<>();
				sub.add(obj.id); //submitting the root of each path
				subPattern(types, obj, sub, 1, answer, isChecked);
			}
		}
		
		return answer;
	}
	
/***************** private assistance method *****************/
	/* recursive functions for looking for the correct path */
	
	private void subPattern(char[] types, GraphObject obj, List <Integer> sub, int index, List <List<Integer>> answer, boolean[] isChecked)
	{
		for(GraphObject subObj : obj.connections)
		{
			if(subObj.type == types[index] && isChecked[obj.connections.indexOf(subObj)] != true)
			{
				// each path has it's own array
				List <Integer> currentSub = new ArrayList<>(sub);
				
				//not allowing the same id appear more than once for each path
				boolean[] currentIsChecked = isChecked.clone();
				currentIsChecked[subObj.connections.indexOf(obj)] = true;
				
				currentSub.add(subObj.id);
				
				if(index == types.length - 1)
				{
					answer.add(currentSub);
				}
				else
				{
					subPattern(types, subObj, currentSub, index + 1, answer, currentIsChecked);
				}	
			}
		}
	}
/**************************************************************/
	
	public class GraphObject 
	{
		private char type;
		private int id;
		private List <GraphObject> connections = new ArrayList<>();  
		
		GraphObject(char type, int id)
		{
			this.type = type;
			this.id = id;
		}
		
		private void add(GraphObject... connections)
		{
			for(GraphObject obj : connections)
			{
				this.connections.add(obj);
				obj.connections.add(this);
			}
		}
		
		@Override
		public String toString()
		{
			return "(type: " + type + ", id: " + id + ")";
		}
		
	}
	
}





