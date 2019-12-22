package matificGame.java;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;

public class Boat{
	private Image boatImg;
	
	private int dx;
    private int x = 500;
    private int y = 450;
    int boatSpeed = 2;
    
    Boat(){	
    	loadImage();
    }
    public void move() {
        x += dx;
    }

    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    
    public Image getImage() {
        
        return boatImg;
    }
    
	private void loadImage() {
		ImageIcon boatI = new ImageIcon("/home/student/Downloads/resources/boat.png");
		boatImg = boatI.getImage(); 
	}
	
	public void keyPressed(KeyEvent e, int xSize) {

        int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT) {
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x > 0) ? -boatSpeed : 0;
        	
        }

        if (key == KeyEvent.VK_RIGHT) {
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x < Console.xAxisSize - boatImg.getWidth(null)) ? boatSpeed : 0;
        	
        }
    }
	public void keyReleased(KeyEvent e) {
        dx = 0;
    }
}


