package matificAssignmentOld.java;

import java.awt.EventQueue;
import javax.swing.JFrame;

public class TheParachutistGame extends JFrame{
	private static final long serialVersionUID = 1L;
	
	private int xAxisSize = 1080;
	private int yAxisSize = 720;
	 
	public TheParachutistGame() 
	{
		try {
			add(new Controller(xAxisSize, yAxisSize));
		} catch (InterruptedException e) {
			System.err.println("faild initalization");
			e.printStackTrace();
		}
		setSize(xAxisSize, yAxisSize);
		
		setTitle("Parachute game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
    }

	
	public static void main(String[] args) {
		EventQueue.invokeLater(() -> {
			TheParachutistGame ex = new TheParachutistGame();
			ex.setVisible(true);
	    });
	}
}