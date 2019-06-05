import EDEVS.car.Ambulance;
import EDEVS.car.Sedan;
import EDEVS.car.Taxi;
import EDEVS.car.Truck;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class ExplainableDEVS extends JPanel {

	private static ExplainableDEVS explainableDEVS;

	private Taxi taxi;
	private Truck truck;
	private Ambulance ambulance;
	private Sedan sedan;

	private ExplainableDEVS() {
		setBackground(Color.lightGray);
		taxi = new Taxi();
		truck = new Truck();
		ambulance = new Ambulance();
		sedan = new Sedan();
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		float[] dash20 = { 20, 1f };
		g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1, dash20, 0));

		int y1 = getHeight() / 3;
		int y2 = getHeight() - getHeight() / 3;
		g.setColor(Color.WHITE);
		g.drawLine(0, y1, getWidth(), y1);
		g.drawLine(0, y2, getWidth(), y2);

		taxi.draw(g);
		truck.draw(g);
		ambulance.draw(g);
		sedan.draw(g);
	}

	public static void main(String[] args) {
		execute();
	}

	public static void execute() {
		JFrame frame = new JFrame();
		explainableDEVS = new ExplainableDEVS();
		frame.add(explainableDEVS);
		frame.setTitle("E-DEVS SDC Simulation");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1500, 500);
		frame.setVisible(true);
	}

	public static void tick() {
		explainableDEVS.repaint();
		/*
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		*/
	}

	public static void close() {
		System.exit(0);
	}
}