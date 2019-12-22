package matificAssignment.java;

import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;
import java.util.function.BiConsumer;

public class Status {
	private final int xAxisSize = 1080;
	private final int yAxisSize = 720;
	
	private final String path = "/home/student/Downloads/resources/";
	
	private int livesLeft = 3;
	private int score = 0;
	
	/* remember the boundaries of int, if you want to change the number of points per catch */
	private final int pointsPerCatch = 10;
	
	private Boat boat;
	private Plane plane;
	private Parachutist par;
	
	/* lists of items kinds, for future capability to insert a new item at ease */
	private List<Item> staticImages = new ArrayList<Item>(); // sky, sea and game over 
	private List<MovingItem> movingImages = new ArrayList<MovingItem>(); // plane
	private List<ControlledItem> contImages = new ArrayList<ControlledItem>(); // boat
	private List<RandItem> randImages = new ArrayList<RandItem>(); // parachutist
	
	/* static images paths */
	private String skyPath = path + "background.png";
	private String seaPath = path + "sea.png";
	private String gameOverPath = path + "gameOver.png";
	private Item gameOverItem; // game over
    
    /* moving images paths */
	private String parPath = path + "parachutist.png";
	private String planePath = path + "plane.png";
	private String boatPath = path + "boat.png";
	
	/* callback functions, accepted from the game manager */
	private BiConsumer<ControlledItem, KeyEvent> moveFunc;
	private BiConsumer<ControlledItem, KeyEvent> stopFunc;
	private BiConsumer<RandItem, Integer> randFunc;
	private BiConsumer<Parachutist, Boat> assessFunc;
	
	Status(BiConsumer<ControlledItem, KeyEvent> moveFunc, 
			BiConsumer<ControlledItem, KeyEvent> stopFunc, 
			BiConsumer<RandItem, Integer> randFunc,
			BiConsumer<Parachutist, Boat> assessmentFunction)
	{
		this.moveFunc = moveFunc;
		this.stopFunc = stopFunc;
		this.randFunc = randFunc;
		this.assessFunc = assessmentFunction;
		init();
	}
	
	private void init()
	{		
		boat = new Boat(500, 400, boatPath, this);
		plane = new Plane(700, 50, planePath, this);
		par = new Parachutist(boat.getY(), plane.getX(), plane.getY(), parPath, this);
		
		/* static items */
		staticImages.add(new Item(0, 0, skyPath, this));
		staticImages.add(new Item(0, 450, seaPath, this)); 
		gameOverItem = new Item(275, 55, gameOverPath, this);
		/* setting the visibility of the parachutist to false for the beginning of the game*/
		gameOverItem.setVisible(false);
		staticImages.add(gameOverItem);
		
		/* moving items, the lists are meant for future addition of items */
		randImages.add(par);
		movingImages.add(plane);
		contImages.add(boat);
	}
	
	
	/********** getters **********/
	
	int getXAxisSize()
	{
		return xAxisSize;
	}
	
	int getYAxisSize()
	{
		return yAxisSize;
	}
	
	List<Item> getItems()
	{
		return staticImages;
	}
	
	List<MovingItem> getMovingItems()
	{
		return movingImages;
	}
	
	List<ControlledItem> getcontItems()
	{
		return contImages;
	}
	
	List<RandItem> getRandItems()
	{
		return randImages;
	}
	
	int getLivesLeft()
	{
		return livesLeft;
	}
	
	int getScore()
	{
		return score;
	}
	
	/*************************/
	
	void subLives()
	{
		--livesLeft;
	}
	
	boolean isGameOver()
	{
		return livesLeft == 0;
	}
	
	void updateGameOverImg()
	{
		/* making the 'game over' image to appear */
		gameOverItem.setVisible(true);
	}
	
	void updateScore()
	{
		score += pointsPerCatch;
	}
	
	/* moving the moving and controlled items */
	void move()
	{
		for(ControlledItem i : contImages)
		{
			i.move();
		}
		for(MovingItem i : movingImages)
		{
			i.move();
		}
	}
	
	void randomAction()
	{
		for(RandItem i : randImages)
		{
			randFunc.accept(i, plane.getX());	
		}
	}
	
	/* assessing if the parachutist and the boat have met */
	void assesParAndBoat()
	{
		assessFunc.accept(par, boat);
	}
	
	void keyPressed(KeyEvent e)
	{
		for(ControlledItem i : contImages)
		{
			moveFunc.accept(i, e);	
		}
	}
	
	void keyReleased(KeyEvent e)
	{
		for(ControlledItem i : contImages)
		{
			stopFunc.accept(i, e);	
		}
	}
}