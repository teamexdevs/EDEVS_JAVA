import EDEVS.car.*;
import EDEVS.util.GlobalVariables;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class ExplainableDEVS extends JPanel {

	private static ExplainableDEVS explainableDEVS;

	private ArrayList<SelfDrivingCar> cars = new ArrayList<>();

	private ExplainableDEVS() {
		setBackground(Color.lightGray);
		cars.add(new Taxi("Taxi", 1));
		cars.add(new Truck("Truck", 2));
		cars.add(new Ambulance("Ambulance", 3));
		//cars.add(new Sedan("Sedan"));
		//cars.add(new PoliceCar("PoliceCar"));
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

		int[] minLaneX = { Integer.MAX_VALUE, Integer.MAX_VALUE, Integer.MAX_VALUE };
		for (SelfDrivingCar car: cars) { minLaneX[car.getLane()-1] = Math.min(minLaneX[car.getLane()-1], car.getX()); }
		for (int i = 0; i < minLaneX.length; ++i) if (minLaneX[i] >= GlobalVariables.WIDTH / 4) {
			switch ((int) (Math.random() * 10) % 5) {
				case 0:
					cars.add(new Taxi(String.format("Taxi@%s", System.currentTimeMillis()), i+1));
					break;
				case 1:
					cars.add(new Truck(String.format("Truck@%s", System.currentTimeMillis()), i+1));
					break;
				case 2:
					cars.add(new Ambulance(String.format("Ambulance@%s", System.currentTimeMillis()), i+1));
					break;
				case 3:
					cars.add(new Sedan(String.format("Sedan@%s", System.currentTimeMillis()), i+1));
					break;
				case 4:
					cars.add(new PoliceCar(String.format("PoliceCar@%s", System.currentTimeMillis()), i+1));
					break;
			}
		}

		ArrayList<SelfDrivingCar> achievedCars = new ArrayList<>();
		for (SelfDrivingCar car: cars) {
			if (car.getX() >= GlobalVariables.WIDTH) {
				achievedCars.add(car);
			} else {
				car.draw(g);
			}
		}
		cars.removeAll(achievedCars);
		System.out.println(String.format("Repaint: %d cars left..", cars.size()));
	}

	public static void main(String[] args) {
		execute();
		while (true)
			tick();
	}

	public static void execute() {
		JFrame frame = new JFrame();
		explainableDEVS = new ExplainableDEVS();
		frame.add(explainableDEVS);
		frame.setTitle("E-DEVS SDC Simulation");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(GlobalVariables.WIDTH, GlobalVariables.HEIGHT);
		frame.setVisible(true);
	}

	public static void tick() {
		explainableDEVS.repaint();
		/*
		/*/
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		//*/
	}

	public static void close() {
		System.exit(0);
	}
}