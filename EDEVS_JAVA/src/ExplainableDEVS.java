import EDEVS.car.*;
import EDEVS.util.GlobalVariables;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.stream.Collectors;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class ExplainableDEVS extends JPanel {

	private ArrayList<SelfDrivingCar> cars = new ArrayList<>();
	private boolean[] isEmpty = new boolean[3];

	private ExplainableDEVS() {
		setBackground(Color.lightGray);
		for (int i = 1; i <= 3; ++i) {
			spawnCar("Car#" + i, i);
		}
	}

	private static class Holder {
		private final static ExplainableDEVS Instance = new ExplainableDEVS();
	}

	public static ExplainableDEVS getInstance() {
		return Holder.Instance;
	}

	public void spawnCar(String name, int lane) {
		switch ((int) (Math.random() * 100) % 5) {
			case 0:
				cars.add(new Taxi(name, lane)); break;
			case 1:
				cars.add(new Truck(name, lane)); break;
			case 2:
				cars.add(new Ambulance(name, lane)); break;
			case 3:
				cars.add(new Sedan(name, lane)); break;
			case 4:
				cars.add(new PoliceCar(name, lane));
		}
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		float[] dash20 = { 20, 1f };
		g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1, dash20, 0));

		int y1 = getHeight() / 3;
		int y2 = getHeight() / 3 * 2;
		g.setColor(Color.WHITE);
		g.drawLine(0, y1, getWidth(), y1);
		g.drawLine(0, y2, getWidth(), y2);

		cars.forEach(car -> car.draw(g));
		System.out.println(String.format("Repaint: %d cars left..", cars.size()));
	}

	public void updateLaneStatus() {
		for (int i = 1; i <= 3; ++i) {
			final int lane = i;
			isEmpty[i] = cars.stream()
					.filter(car -> car.getLane() == lane)
					.allMatch(car -> car.getX() >= GlobalVariables.WIDTH / 4);
		}
	}

	public boolean getLaneStatus(int lane) {
		return isEmpty[lane];
	}

	/*
	public boolean[] getLaneStatus() {
		boolean[] isEmpty = new boolean[3];
		for (int i = 1; i <= 3; ++i) {
			final int lane = i;
			isEmpty[i] = cars.stream()
					.filter(car -> car.getLane() == lane)
					.allMatch(car -> car.getX() >= GlobalVariables.WIDTH / 4);
		}
		return isEmpty;

		//return Stream.of(1, 2, 3).map(lane -> cars.stream()
		//		.filter(car -> car.getLane() == lane)
		//		.noneMatch(car -> car.getX() >= GlobalVariables.WIDTH / 4))
		//		.collect(Collectors.toList());
	}
	*/

	public static void main(String[] args) {
		execute();
		while (true)
			ExplainableDEVS.getInstance().tick();
	}

	public static void execute() {
		JFrame frame = new JFrame();
		ExplainableDEVS panel = ExplainableDEVS.getInstance();
		frame.add(panel);
		frame.setTitle("E-DEVS SDC Simulation");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(GlobalVariables.WIDTH, GlobalVariables.HEIGHT);
		frame.setVisible(true);
	}

	public void tick() {
		cars.removeAll(
				cars.stream()
						.filter(car -> car.getX() >= GlobalVariables.WIDTH)
						.collect(Collectors.toList()));
		repaint();
	}

	public static void close() {
		System.exit(0);
	}
}