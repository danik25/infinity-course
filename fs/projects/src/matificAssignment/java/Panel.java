package matificAssignment.java;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;
import java.awt.Toolkit;


public class Panel extends JPanel{
	private static final long serialVersionUID = 1L;
	private Font font = new Font("Serif", Font.PLAIN, 50);
	
	private List<Item> staticImages = new ArrayList<Item>(); // sky, sea and game over 
	private List<MovingItem> movingImages = new ArrayList<MovingItem>(); // plane
	private List<ControlledItem> contImages = new ArrayList<ControlledItem>(); // boat
	private List<RandItem> randImages = new ArrayList<RandItem>(); // parachutist
	
	int score;
	int livesLeft;
	
	Panel(List<Item> staticImages, List<MovingItem> movingImages,
			List<ControlledItem> contImages, List<RandItem> randImages)
	{
		this.staticImages = staticImages;
		this.movingImages= movingImages;
		this.contImages= contImages;
		this.randImages = randImages;
	}
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		setGame(g);
		Toolkit.getDefaultToolkit().sync();
	}
	
	void addListener(KeyListener boatControl)
	{
		addKeyListener(boatControl);
		setFocusable(true);
	}
	
	void setGame(Graphics g) {
		
		/* static images */ //sea, sky, game over
		for(Item img : staticImages)
		{
			g.drawImage(img.getImage(), img.getX(), img.getY(), this);
		}
	
		/* moving images */ //plane
		for(Item item : movingImages)
		{
			g.drawImage(item.getImage(), item.getX(), item.getY(), this);
		}
		
		/* random appearance images */ //parachutist
		for(RandItem randItem : randImages)
		{
			g.drawImage(randItem.getImage(), randItem.getX(), randItem.getY(), this);
		}
		
		/* controlled images */ //boat
		for(ControlledItem contItem : contImages)
		{
			g.drawImage(contItem.getImage(), contItem.getX(), contItem.getY(), this);
		}
		
	    g.setFont(font);
	    /* points tracking */
		g.drawString("score: " + this.score, 30, 60);
		/* number of life tracking */
		g.drawString("lives: " + this.livesLeft, 30, 120);
	}

	void reload(int score, int livesLeft)
	{
		this.score = score;
		this.livesLeft = livesLeft;
		repaint();
	}
}