package il.co.ilrd.Composite;

import java.io.*; // file
import java.util.*; // list

public class Tree {
	TreeComponent root;
	
	public Tree(String path)
	{
		root = new DirComposite(path);
	}
	
	void print(int gap) 
	{
		root.print(0);
	}
	
	class DirComposite extends TreeComponent
	{
		List <TreeComponent> treeList = new ArrayList<TreeComponent>();
		
		public DirComposite(String path) 
		{
			try { 
	            File f = new File(path); 
	            File[] files = f.listFiles(); 
	  
	            for (File s : files) 
	            { 
	            	TreeComponent file = null;
	            	if(s.isDirectory())
	            	{
	            		file = new DirComposite(s.toString());
	            	}
	            	else
	            	{
	            		file = new FileLeaf(s.getName()); 
	            	}
	            	treeList.add(file);
	            	System.out.println(file.name);
	            } 
	            this.name = f.getName();
	        } 
	        catch (Exception e) { 
	            System.err.println("not exsists"); 
	        }
		}
		@Override
		void print(int gap) 
		{
			for(int i = 0; i < gap; ++i)
			{
				System.out.print(" ");
			}
			
			System.out.println(this.name);	
			for(TreeComponent t : treeList)
			{
				t.print(gap + 2);
			}
		}
	}
		
	class FileLeaf extends TreeComponent
	{
			
		public FileLeaf(String name) 
		{
			this.name = name;
		}
		@Override
		void print(int gap) 
		{
			for(int i = 0; i < gap; ++i)
			{
				System.out.print(" ");
			}
			System.out.println(this.name);
		}
	}
}

abstract class TreeComponent {
	String name; 
	void print(int gap) {} 
}

