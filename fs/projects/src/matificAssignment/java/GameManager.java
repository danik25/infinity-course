package matificAssignment.java;

import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.function.BiConsumer;
import javax.swing.Timer;

public class GameManager{
	
	/* a random number of milliseconds to wait between a parachutist falls, between max and min  */
	private int randMinTime = 35;
	private int randMaxTime = 50;
	
	private Timer timer;
	private static final int DELAY = 5;

	private Status gameStatus;
	private Panel panel;
	
	void init()  
	{		
		gameStatus = new Status(new moveFunction(), new stopFunction(), new randFunction(), new assessmentFunction());
		panel = new Panel(gameStatus.getItems(), gameStatus.getMovingItems(), 
							gameStatus.getcontItems(), gameStatus.getRandItems());
		panel.addListener(new boatAdapter());
		new Frame(panel, gameStatus);	
		
		boatControl boatController = new boatControl();
		timer = new Timer(DELAY, boatController);
        timer.start();
        
        /* different thread for the parachute */ 
        Thread parThread = new Thread(new parRandomDropping()); 
        parThread.start();
	}
	
	private class boatControl implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			if(gameStatus.isGameOver())
			{
				timer.stop();
			}
			gameStatus.move();
			panel.reload(gameStatus.getScore(), gameStatus.getLivesLeft()); 
		}
	}
	
	private class boatAdapter extends KeyAdapter {
		@Override
        public void keyPressed(KeyEvent e) {
        	gameStatus.keyPressed(e);
        }
		
        @Override
        public void keyReleased(KeyEvent e) {
        	gameStatus.keyReleased(e);
        }
    }
	
	/* separate thread, for random dropping of the parachutist */
	private class parRandomDropping implements Runnable
	{
		double interval;
		
		@Override
		public void run() {
			while(!gameStatus.isGameOver())
			{
				/* sleep for a random amount of time, between parachutist's drop */
				try {
					interval = (Math.random() * ((randMaxTime - randMinTime) * 100 + 1) + randMinTime);
					Thread.sleep((long)interval);
				} catch (InterruptedException e) {
					/* in case of failure in the sleep method, we don't need the game to stop */
				}
	
				gameStatus.randomAction();
				gameStatus.assesParAndBoat();
			}
		}
	}
	
	/*============================== callback functions ==============================*/
	
	/* movement functions for controlled items */
	private class moveFunction implements BiConsumer<ControlledItem, KeyEvent>
	{
		@Override
		public void accept(ControlledItem item, KeyEvent e) {
			item.keyPressed(e);
		}
	}
	private class stopFunction implements BiConsumer<ControlledItem, KeyEvent>
	{
		@Override
		public void accept(ControlledItem item, KeyEvent e) {
			item.keyReleased();
		}
	}
	
	/* movement function for a drop of the parachutist */
	private class randFunction implements BiConsumer<RandItem,Integer>
	{
		@Override
		public void accept(RandItem item, Integer x) {
			item.drop(x);
			item.move();
		}
	}
	
	/* functions that checks whether there was a collision between the boat and the parachutist */
	private class assessmentFunction implements BiConsumer<Parachutist,Boat>
	{
		@Override
		public void accept(Parachutist par, Boat boat) {	
			if(par.isVisible)
			{
				Rectangle boatRec = new Rectangle(boat.getX(), boat.getY(), boat.getImage().getWidth(null), boat.getImage().getHeight(null));
				Rectangle parRec = new Rectangle(par.getX(), par.getY(), par.getImage().getWidth(null), par.getImage().getHeight(null));
				
				/* checks if the two intersected */
				if (!boatRec.intersects(parRec)) {
					gameStatus.subLives();
					
					if(gameStatus.getLivesLeft() == 0)
					{
						gameStatus.updateGameOverImg();
					}
				}
				
				else
				{
					gameStatus.updateScore();
				}
				
				par.setVisible(false);
			}
		}
	}
}