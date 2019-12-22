package matificAssignmentOld.java;

import java.awt.Image;

import javax.swing.ImageIcon;

public class Plane implements Item{
	private Image planeImg;
	private int planeSpeed = 1;
    private int x;
    private int y;
    private int xAxis;
    private int planePosition = 50;
    
    Plane(int xSize, String path){	
    	xAxis = xSize;
    	
    	loadImage(path);
    	
    	x = xAxis - planeImg.getWidth(null);
    	y = planePosition;
    }
    
    @Override
    public void loadImage(String path) {
		ImageIcon planeI = new ImageIcon(path);
		planeImg = planeI.getImage(); 
	}
    
    @Override
    public void move() {
        if(x <= -planeImg.getWidth(null))
        {
        	x = xAxis;
        }
        else
        {
        	x -= planeSpeed;
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
        
        return planeImg;
    }

   
}
