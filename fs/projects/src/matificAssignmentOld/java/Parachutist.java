package matificAssignmentOld.java;

import java.awt.Image;
import javax.swing.ImageIcon;

public class Parachutist implements Item{
	private Image parImg;
	private int parSpeed = 8;
    private int x;
    private int y;
    private int boatYAxis;
    
    
    Parachutist(int PlaneXAxis, int PlaneYAxis, String path){	
    	this.x = PlaneXAxis;
    	this.y = PlaneYAxis;
    	loadImage(path);
    }
    @Override
    public void loadImage(String path) {
		ImageIcon parI = new ImageIcon(path);
		parImg = parI.getImage(); 
	}
    
    private void init(int x, int y, int boatAxis)
    {
    	this.x = x;
    	this.y = y;
    	this.boatYAxis = boatAxis;
    	move();
    }
    
    @Override
    public void move()
    {  
    	while(y < boatYAxis)
    	{    		
    		y += parSpeed;
    		try {
    			/* meant for slowing down the fall of the  parachutist */
				Thread.sleep(30);
			} catch (InterruptedException e) {
				/* in case of failure in the sleep method, we don't need the game to stop */
			}
    	}
    }
    
    @Override
    public int getX() {
        return x;
    }
    @Override
    public int getY() {
        return y;
    }
    
    @Override
    public Image getImage() {
        return parImg;
    }
    
    public void dropPar(int x, int y, int boatYAxis) {
        init(x, y,boatYAxis);
    }

}
