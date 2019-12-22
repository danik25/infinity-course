package matificAssignmentOld.java;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyEvent;
import java.util.List;
import java.util.concurrent.Semaphore;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class View extends JPanel{
	private static final long serialVersionUID = 1L;

	Graphics2D g2d;
	Font font;
	
	 /* Semaphore for the images finishing to load before the parachute starts falling */
	Semaphore sem; 
	
	private Image skyImg;
	private Image seaImg;
	private Image boatImg;
	private Image planeImg;
	private Image parImg;
	private Image gameOverImg;
	
	ImageIcon parI;
	ImageIcon gameOverI;
	
	Boat boat;
	Plane plane;
	Parachutist par;
	
	int xAxisSize;
	int yAxisSize;
	
	int boatWidth;
	int parWidth;
	
	Model model;
	
	View(int xAxisSize, int yAxisSize, Model model)
	{/*
		this.boat = boat;
		this.plane = plane;
		this.par = par;
		*/
		this.model= model;
		
		this.xAxisSize = xAxisSize;
		this.yAxisSize = yAxisSize;	
		
		//boatWidth = boat.getImage().getWidth(null);
		//parWidth = par.getImage().getWidth(null);
		
		sem = new Semaphore(1);
	}
	
	void setGame(Graphics g, List<staticImg> imgList, List<Item> itemList, List<controlledItem> contItemList) {
		g2d = (Graphics2D) g;
		
		/* static images */
		for(staticImg img : imgList)
		{
			g2d.drawImage(img.getImg(), img.getX(), img.getY(), null);
		}
	
		/* moving images */
		for(Item item : itemList)
		{
			g2d.drawImage(item.getImage(), item.getX(), item.getY(), this);
		}
		
		/* controlled images */
		for(Item contItem : contItemList)
		{
			
			g2d.drawImage(contItem.getImage(), contItem.getX(), contItem.getY(), this);
			System.out.println("x: " + contItem.getX());
		}
		
		//loadImage();
		
		
		/* number of life, and game over image */
		//font = new Font("Serif", Font.PLAIN, 50);
	    //g2d.setFont(font);
		//g2d.drawString("lives: " + model.getLivesLeft(), 30, 60);
		//g2d.drawImage(gameOverImg, 250, 90, this);
	}
	/*	
	private void loadImage() {
		
		parI = new ImageIcon("/home/student/Downloads/resources/parachutist.png");
		gameOverI = new ImageIcon("/home/student/Downloads/resources/gameOver.png");
		
		
        ImageIcon skyI = new ImageIcon("/home/student/Downloads/resources/background.png");
        ImageIcon seaI = new ImageIcon("/home/student/Downloads/resources/sea.png");
        ImageIcon planeI = new ImageIcon("/home/student/Downloads/resources/plane.png");
        ImageIcon boatI = new ImageIcon("/home/student/Downloads/resources/boat.png");
        
        skyImg = skyI.getImage(); 
        seaImg = seaI.getImage(); 
        planeImg = planeI.getImage(); 
        boatImg = boatI.getImage();
        
        sem.release();
    }*/
	
	void move(List<? extends Item> itemList)
	{
		for(Item item : itemList)
		{
			item.move();
		}
		/*
		boat.move();
		plane.move();
		*/
	}
	
	void drop(boolean firstTime)
	{
		/* the first time the parachutist falls */
		if(firstTime)
		{
			try {
				sem.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			parImg = parI.getImage();
		}
		
		par.dropPar(plane.getX(), plane.getY(), boat.getY());
		//model.assesParAndBoat(boat.getX(), boat.getX() + boatWidth, par.getX(), par.getX() + parWidth);
	}
	/*
	void keyPresses(KeyEvent e)
	{
		boat.keyPressed(e/*, xAxisSize*//*);*/
	//}
	/*
	void keyReleased()
	{
		boat.keyReleased();
	}
	*/
	void displayGameOver()
	{
		gameOverImg = gameOverI.getImage();
	}
		
}
