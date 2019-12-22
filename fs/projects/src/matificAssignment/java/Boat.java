package matificAssignment.java;

import java.awt.event.KeyEvent;

public class Boat extends ControlledItem{
	private int dx;
    private int boatSpeed = 2;
    
    Boat(int x, int y, String path, Status gameStatus){	
    	super(x, y, path, gameStatus);
    }
    
    @Override
    public void move() {
        x += dx;
    }
    
	public void keyPressed(KeyEvent e) {

        int key = e.getKeyCode();
        
        if (key == KeyEvent.VK_LEFT) {
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x > 0) ? -boatSpeed : 0;
        	
        }

        if (key == KeyEvent.VK_RIGHT) {
        	/* make sure the boat doesn't leave the screen's boundaries */
        	dx = (x < gameStatus.getXAxisSize() - img.getWidth(null)) ? boatSpeed : 0;
        	
        }
    }
	public void keyReleased() {
        dx = 0;
    }
}