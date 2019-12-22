package matificGame.java;
import java.awt.EventQueue;

import javax.swing.JFrame;

public class ParachutistGame extends JFrame{
	 int xAxis = 1080;
	 int yAxis = 720;
	 
	 public ParachutistGame() {

	        initUI();
	    }

	 private void initUI() {

	        add(new Console(xAxis, yAxis));
	        setSize(xAxis, yAxis);

	        setTitle("Parachute game");
	        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	        setLocationRelativeTo(null);
	 }
	
	public static void main(String[] args) {
	        
	        EventQueue.invokeLater(() -> {
	        	ParachutistGame ex = new ParachutistGame();
	            ex.setVisible(true);
	        });
	    }
}
