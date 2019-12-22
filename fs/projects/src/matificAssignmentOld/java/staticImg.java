package matificAssignmentOld.java;

import java.awt.Image;

import javax.swing.ImageIcon;

public class staticImg {
	int x;
	int y;
	String path;
	
	public staticImg(int xPos, int yPos, String path) {
		this.x = xPos;
		this.y = yPos;
		this.path = path;
	}
	
	Image getImg()
	{
		return new ImageIcon(path).getImage();
	}
	
	int getX()
	{
		return x;
	}
	
	int getY()
	{
		return y;
	}
}
