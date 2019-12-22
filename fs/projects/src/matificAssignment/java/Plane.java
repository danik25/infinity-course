package matificAssignment.java;

public class Plane extends MovingItem{
	private int planeSpeed = 2;
    
    Plane(int xPosition, int yPosition, String path, Status gameStatus){
    	super(xPosition, yPosition, path, gameStatus);
    }
    
    @Override
    public void move() {
    	/* if the plane got out of the screen's boundaries, 
    	 * make it appear on the other side of the screen */
        if(x <= -img.getWidth(null))
        {
        	x = gameStatus.getXAxisSize();
        }
        else
        {
        	x -= planeSpeed;
        }
    }
       
}