package matificAssignment.java;

import javax.swing.JFrame;

public class Frame extends JFrame{
	private static final long serialVersionUID = 1L;
	
	Frame(Panel panel, Status gameStatus)
	{
		setSize(gameStatus.getXAxisSize(), gameStatus.getYAxisSize());	
		setTitle("Parachute game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		setVisible(true);
		
		add(panel);
	}
}