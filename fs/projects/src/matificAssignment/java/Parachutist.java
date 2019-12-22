package matificAssignment.java;

public class Parachutist extends RandItem{
	private int parSpeed = 8;
    private int boatYAxis;
    private int planeYAxis;
    
    
    Parachutist(int boatYAxis, int PlaneXAxis, int PlaneYAxis, String path, Status gameStatus){	
    	super(boatYAxis, PlaneXAxis, PlaneYAxis, path, gameStatus);
    	this.planeYAxis = PlaneYAxis;
    	this.boatYAxis = boatYAxis;
    	
    	setVisible(false);
    }

    @Override
    public void move()
    {  
    	setVisible(true);
    	
    	/* make sure the parachutis doesn't leave the screen's boundaries */
    	if(x >= 0 && x + getImage().getWidth(null) <= gameStatus.getXAxisSize())
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
    	else
    	{  		
    		/* if the  parachutist is not in the screen's boundaries, make it not visible */
    		setVisible(false);
    	}
    }
    
    @Override
    public void drop(int x) {
    	this.x = x;
    	this.y = planeYAxis;
    }
}