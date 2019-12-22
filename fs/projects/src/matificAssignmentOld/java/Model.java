package matificAssignmentOld.java;

import java.awt.Image;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

import javax.swing.ImageIcon;



public class Model {
	private int livesLeft = 3;
	private boolean gameOver = false;
	
	Boat boat;
	Plane plane;
	Parachutist par;
	
	List<staticImg> staticImages = new ArrayList<staticImg>();
	List<Item> movingImages = new ArrayList<Item>();
	List<controlledItem> contImages = new ArrayList<controlledItem>();
	
	/* images paths */
	/* static images */
	String skyPath = "/home/student/Downloads/resources/background.png";
    String seaPath = "/home/student/Downloads/resources/sea.png";
    
    /* moving images */
	String parPath = "/home/student/Downloads/resources/parachutist.png";
	String gameOverPath = "/home/student/Downloads/resources/gameOver.png";
    String planePath = "/home/student/Downloads/resources/plane.png";
    String boatPath = "/home/student/Downloads/resources/boat.png";
	
	BiConsumer<controlledItem, KeyEvent> moveFunc;
	BiConsumer<controlledItem, KeyEvent> stopFunc;
	
	Model(BiConsumer<controlledItem, KeyEvent> movefFunc, BiConsumer<controlledItem, KeyEvent> stopFunc)
	{
		this.moveFunc = moveFunc;
		this.stopFunc = stopFunc;
		init();
	}
	
	void init()
	{		
		boat = new Boat(boatPath);
		plane = new Plane(1080, planePath);
		par = new Parachutist(plane.getX(), plane.getY(), parPath);
		
		staticImages.add(new staticImg(0, 0, skyPath));
		staticImages.add(new staticImg(0, 450, seaPath)); 
		
		movingImages.add(par);
		movingImages.add(plane);
		
		contImages.add(boat);
		movingImages.add(par);
	}
	
	List<staticImg> getStaticImg()
	{
		return staticImages;
	}
	
	List<Item> getMovingImg()
	{
		return movingImages;
	}
	
	List<controlledItem> getcontImg()
	{
		return contImages;
	}
	
	void keyPressed(KeyEvent e)
	{
		for(controlledItem i : contImages)
		{
			moveFunc.accept(i, e);	
		}
	}
	void keyReleased(KeyEvent e)
	{
		for(controlledItem i : contImages)
		{
			stopFunc.accept(i, e);	
		}
	}
	/*
	void assesParAndBoat(int boatLeft, int boatRight, int parLeft, int parRight)
	{
		if(!((boatLeft <= parLeft && boatRight >= parLeft) || 
					(boatRight >= parRight && boatLeft <= parRight)))
		{
			--livesLeft;
			if(livesLeft == 0)
			{
				gameOver = true;
			}
		}
	}*/
	/*
	int getLivesLeft()
	{
		return livesLeft;
	}
	
	boolean isGameOver()
	{
		return gameOver;
	}*/
}
