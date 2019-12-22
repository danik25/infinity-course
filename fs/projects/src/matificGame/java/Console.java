package matificGame.java;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import javax.swing.Timer;
import java.awt.Toolkit;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Console extends JPanel{
	private static final long serialVersionUID = 1L;

	Graphics2D g2d;
	
	int randMinTime = 35;
	int randMaxTime = 50;
	
	private Image sky;
	private Image sea;
	
	private Boat boat;
	private Plane plane;
	private Parachutist par;
	
	private Timer Timer;
	
	private final int DELAY = 5;
	
	static int xAxisSize;
	static int yAxisSize;
	
	Console(int xAxis, int yAxis){
		xAxisSize = xAxis;
		yAxisSize = yAxis;
		
		boatControl boatController = new boatControl();
		
		boat = new Boat();
		plane = new Plane(xAxisSize, yAxisSize);
		par = new Parachutist(plane.getX(), plane.getY());
		
		Timer = new Timer(DELAY, boatController);
        Timer.start();
        
        /* different thread for the parachute */
        Thread parThread = new Thread(new parRandomDropping()); 
        parThread.start();

	}
	
	@Override
	public void paintComponent(Graphics g) {
		
		super.paintComponent(g);
		
		setGame(g);
		Toolkit.getDefaultToolkit().sync();

	}

	private void setGame(Graphics g) {
		
		loadImage();
		g2d = (Graphics2D) g;

		/* static images */
		g2d.drawImage(sky, 0, 0, null);
		g2d.drawImage(sea, 0, 450, null);
		
		g2d.drawImage(boat.getImage(), boat.getX(), boat.getY(), this);
		g2d.drawImage(plane.getImage(), plane.getX(), plane.getY(), this);
		g2d.drawImage(par.getImage(), par.getX(), par.getY(), this);
		

	}
	
	private void loadImage() {
        ImageIcon skyI = new ImageIcon("/home/student/Downloads/resources/background.png");
        ImageIcon seaI = new ImageIcon("/home/student/Downloads/resources/sea.png");
        
        sky = skyI.getImage(); 
        sea = seaI.getImage(); 
    }

	
	class boatControl implements ActionListener{

		boatControl()
		{
			KeyListener boatListener = new boatAdapter();
			addKeyListener(boatListener);
			setFocusable(true);
			
			KeyListener parListener = new boatAdapter();
			addKeyListener(parListener);
			setFocusable(true);
		}
		@Override
		public void actionPerformed(ActionEvent arg0) {
			boat.move();
			plane.fly();
	        repaint();
		}
		
		private class boatAdapter extends KeyAdapter {

	        @Override
	        public void keyReleased(KeyEvent e) {
	            boat.keyReleased(e);
	        }

	        @Override
	        public void keyPressed(KeyEvent e) {
	            boat.keyPressed(e, xAxisSize);
	        }
	    }
		
		
	}
	
	class parRandomDropping implements Runnable
	{
		double interval;
		@Override
		public void run() {
			while(true)
			{
				try {
					interval = (Math.random() * ((randMaxTime - randMinTime) * 100 + 1) + randMinTime);
					Thread.sleep((long)interval);
				} catch (InterruptedException e) {
					/* in case of failure in the sleep method, we don't need the game to stop */
				}
				par.dropPar(plane.getX(), plane.getY(), boat.getY());
			}
		}
	}
}



