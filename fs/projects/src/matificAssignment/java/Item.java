package matificAssignment.java;

import java.awt.Image;
import java.awt.event.KeyEvent;

import javax.swing.ImageIcon;
 
public class Item{ // sea, sky, game over 
	protected int x;
	protected int y;
	protected Image img;
	protected boolean isVisible = true;
	protected Status gameStatus;
	
	Item(int x, int y, String path, Status gameStatus){
		this.x = x;
		this.y = y;
		this.img = (new ImageIcon(path)).getImage();
		this.gameStatus = gameStatus;
	}
	
	int getX()
    {
    	return this.x;
    }
	
    int getY()
    {
    	return this.y;
    }
  
    Image getImage()
    {
    	if(isVisible)
    	{
    		return this.img;
    	}
    	return null;
    }
    
    void setVisible(boolean vis)
    {
    	isVisible = vis;
    }
    
    boolean isVisible()
    {
    	return isVisible;
    }
}
 
abstract class MovingItem extends Item{ //plane
	
	 MovingItem(int x, int y, String path, Status gameStatus)
	{
		super(x, y, path, gameStatus);
	}
    abstract void move();
}

/* controlled moving items */ 
abstract class ControlledItem extends MovingItem{ //boat
	ControlledItem(int x, int y, String path, Status gameStatus) {
		super(x, y, path, gameStatus);
	}
	abstract void keyPressed(KeyEvent e);
	abstract void keyReleased();
}

/* random moving items */ 
abstract class RandItem extends MovingItem { //parachutist
	RandItem(int boatYAxis, int PlaneXAxis, int PlaneYAxis, String path, Status gameStatus) {
		super(PlaneXAxis, PlaneYAxis, path, gameStatus);
	}
	abstract void drop(int x);
}