package matificGame.java;

import java.awt.Image;

import javax.swing.ImageIcon;

public class Plane{
	private Image planeImg;
	private int planeSpeed = 1;
    private int x;
    private int y;
    private int xAxis;
    private int yAxis;
    
    Plane(int xSize, int ySize){	
    	xAxis = xSize;
    	yAxis = ySize;
    	
    	loadImage();
    	
    	x = xAxis - planeImg.getWidth(null);
    	y = 50;
    	System.out.println(Console.xAxisSize);
    }
    
    private void loadImage() {
		ImageIcon planeI = new ImageIcon("/home/student/Downloads/resources/plane.png");
		planeImg = planeI.getImage(); 
	}
    
    public void fly() {
        if(x <= -planeImg.getWidth(null))
        {
        	x = xAxis;
        }
        else
        {
        	x -= planeSpeed;
        }
    }

    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    
    public Image getImage() {
        
        return planeImg;
    }
    
    public Parachutist getPar()
    {
    	return new Parachutist(x, y);
    }
    /*
    public class Parachutist {
    	boolean visible;
    	private Image parImg;
    	private int parSpeed = 2;
        private int x;
        private int y;
        
        Parachutist(int x, int y){	
        	this.x = x;
        	this.y = y;
        	loadImage();
        }
        
        private void loadImage() {
    		ImageIcon parI = new ImageIcon("/home/student/Downloads/resources/parachutist.png");
    		parImg = parI.getImage(); 
    	}
        
        public void fall()
        {
        	y += parSpeed;
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
        
        public boolean isVisible() {
            return visible;
        }

        public void setVisible(Boolean visible) {
            this.visible = visible;
        }
    }*/
}
