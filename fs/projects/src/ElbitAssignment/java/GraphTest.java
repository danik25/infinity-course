package ElbitAssignment.java;

import static org.junit.jupiter.api.Assertions.*;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class GraphTest {
	
	Graph graph;
	
	@BeforeEach
	void generalTest()
	{	
		graph = new Graph();
		Graph.GraphObject a1 = graph.new GraphObject('A', 1);
		Graph.GraphObject b2 = graph.new GraphObject('B', 2);
		Graph.GraphObject d3 = graph.new GraphObject('D', 3);
		Graph.GraphObject c5 = graph.new GraphObject('C', 5);
		Graph.GraphObject a4 = graph.new GraphObject('A', 4);
		Graph.GraphObject b6 = graph.new GraphObject('B', 6);
		Graph.GraphObject c8 = graph.new GraphObject('C', 8);
		Graph.GraphObject e7 = graph.new GraphObject('E', 7);
		Graph.GraphObject c9 = graph.new GraphObject('C', 9);
		Graph.GraphObject b5 = graph.new GraphObject('B', 5);
		
		graph.add(a1);
		graph.add(b2, a1);
		graph.add(d3, b2);
		graph.add(c5, b2);
		graph.add(a4, c5);
		graph.add(b6, a4, c5);
		graph.add(c8, b6);
		graph.add(e7, a4);
		graph.add(c9, b2);
		graph.add(b5, a4, c8);
	}
	
	@Test
	void existingPatternTest()
	{
		System.out.println("\nexisting pattern test");

		System.out.println(graph.getPattern('A', 'B', 'C'));
		assertEquals(graph.getPattern('A', 'B', 'C').size(), 5);
	}

	@Test
	void notExistingPatternTest()
	{
		System.out.println("\nnot existing pattern test");
		
		System.out.println(graph.getPattern('A', 'B', 'C', 'E'));
		assertEquals(graph.getPattern('A', 'B', 'C', 'E').size(), 0);
	}
	
	@Test
	void repititionTest()
	{
		System.out.println("\nrepitition test");
		
		System.out.println(graph.getPattern('A', 'C', 'B', 'C'));
		assertEquals(graph.getPattern('A', 'C', 'B', 'C').size(), 2);
		
		System.out.println(graph.getPattern('A', 'B', 'A'));
		assertEquals(graph.getPattern('A', 'B', 'A').size(), 0);
	}
}
