package matificGame.java;

import java.awt.Image;
import java.awt.event.KeyEvent;

import javax.swing.ImageIcon;

public class Parachutist {
	private Image parImg;
	private int parSpeed = 8;
    private int x;
    private int y;
    
    private int xAxis;
    private int yAxis;
    
    Parachutist(int x, int y){	
    	this.xAxis = x;
    	this.yAxis = y;
    	loadImage();
    }
    
    private void loadImage() {
		ImageIcon parI = new ImageIcon("/home/student/Downloads/resources/parachutist.png");
		parImg = parI.getImage(); 
	}
    
    private void init(int x, int y, int boatAxis)
    {
    	this.x = x;
    	this.y = y;
    	fall(boatAxis);
    }
    public void fall(int boatYAxis)
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
    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    
    public Image getImage() {
        return parImg;
    }
    
    public void dropPar(int x, int y, int boatYAxis) {
        init(x, y,boatYAxis);
    }
}
