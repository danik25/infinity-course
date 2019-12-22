package matificAssignmentOld.java;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.concurrent.Semaphore;
import java.util.function.BiConsumer;
import java.util.function.Consumer;
import java.util.function.Function;

import javax.swing.JPanel;
import javax.swing.Timer;


public class Controller extends JPanel{
	private static final long serialVersionUID = 1L;
	
	/* a random number of milliseconds to wait between a parachutist falls, between max and min  */
	int randMinTime = 35;
	int randMaxTime = 50;
	
	private Timer timer;
	private final int DELAY = 5;
	
	int xAxisSize;
	int yAxisSize;
	
	View view;
	Model model;
	/*
	Boat boat;
	Plane plane;
	Parachutist par;
	*/
	Controller(int xAxisSize, int yAxisSize) throws InterruptedException
	{
		this.xAxisSize = xAxisSize;
		this.yAxisSize = yAxisSize;
		init();
	}	
	
	void init() throws InterruptedException  
	{		

		model = new Model(new moveFunction(), new stopFunction());
		view = new View(xAxisSize, yAxisSize, model);
		
		boatControl boatController = new boatControl();
		timer = new Timer(DELAY, boatController);
        timer.start();
        
        /* different thread for the parachute */ 
        //Thread parThread = new Thread(new parRandomDropping()); 
        //parThread.start();
	}
	
	@Override
	public void paintComponent(Graphics g)
	{
		view.setGame(g, model.getStaticImg(), model.getMovingImg(), model.getcontImg());
	}
	
	class boatControl implements ActionListener{

		boatControl()
		{ 
			KeyListener boatListener = new boatAdapter();
			addKeyListener(boatListener);
			setFocusable(true);
		}
		
		@Override
		public void actionPerformed(ActionEvent arg0) {
			/*if(model.isGameOver() == true)
			{
				view.displayGameOver();
				timer.stop();
			}*/

			view.move(model.getMovingImg());
			view.move(model.getcontImg());
			System.out.println("repainting");
			repaint();
		}
		
		private class boatAdapter extends KeyAdapter {
			@Override
	        public void keyPressed(KeyEvent e) {
	        	model.keyPressed(e);
	        	//view.keyPresses(e);
	        }
			
	        @Override
	        public void keyReleased(KeyEvent e) {
	        	//view.keyReleased();
	        }

	    }
	}
	
	class parRandomDropping implements Runnable
	{
		double interval;
		boolean isFirstDrop = true;
		
		@Override
		public void run() {
			while(true /*!model.isGameOver()*/)
			{
				try {
					interval = (Math.random() * ((randMaxTime - randMinTime) * 100 + 1) + randMinTime);
					Thread.sleep((long)interval);
				} catch (InterruptedException e) {
					/* in case of failure in the sleep method, we don't need the game to stop */
				}
				view.drop(isFirstDrop);
				isFirstDrop = false;
			}
		}
	}
	
	class moveFunction implements BiConsumer<controlledItem, KeyEvent>
	{
		@Override
		public void accept(controlledItem item, KeyEvent e) {
			item.keyPressed(e);
		}
	}
	class stopFunction implements BiConsumer<controlledItem, KeyEvent>
	{
		@Override
		public void accept(controlledItem item, KeyEvent e) {
			item.keyReleased();
		}
	}
}
