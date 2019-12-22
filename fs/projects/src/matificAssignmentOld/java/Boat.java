package matificAssignmentOld.java;

import java.awt.event.KeyEvent;
import java.awt.Image;
import javax.swing.ImageIcon;

public class Boat implements controlledItem{
	private Image boatImg;
	
	private int dx;
    private int x = 500;
    private int y = 450;
    int boatSpeed = 2;
    
    Boat(String path){	
    	loadImage(path);
    }
    
    @Override
    public void move() {
    	System.out.println("mooved");
        x += dx;
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
        
        return boatImg;
    }
    
    @Override
    public void loadImage(String path) {
		ImageIcon boatI = new ImageIcon(path);
		boatImg = boatI.getImage(); 
	}
	
	public void keyPressed(KeyEvent e/*, int xSize*/) {

        int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT) {
        	System.out.println("left");
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x > 0) ? -boatSpeed : 0;
        	
        }

        if (key == KeyEvent.VK_RIGHT) {
        	System.out.println("right");
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x < 1080 - boatImg.getWidth(null)) ? boatSpeed : 0;
        	
        }
		
    }
	public void keyReleased() {
        dx = 0;
    }


}



