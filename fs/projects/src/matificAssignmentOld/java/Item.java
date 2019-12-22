package matificAssignmentOld.java;

import java.awt.Image;
import java.awt.event.KeyEvent;

public interface Item {
    void move();
    int getX();
    int getY();
    Image getImage();
    void loadImage(String path);
}

interface controlledItem extends Item{
	void keyPressed(KeyEvent e/*, int xSize*/);
	void keyReleased();
}
