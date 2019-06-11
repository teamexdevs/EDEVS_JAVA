import EDEVS.car.*;
import EDEVS.util.GlobalVariables;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class ExplainableDEVS extends JPanel {

	private HashMap<String, SelfDrivingCar> cars = new HashMap<>();
	private boolean[] isEmpty = new boolean[3];

	public static final int MIN_VELOCITY = 1;
	public static final int MAX_VELOCITY = 10;

	private ExplainableDEVS() {
		setBackground(Color.lightGray);
	}

	private static class Holder {
		private final static ExplainableDEVS Instance = new ExplainableDEVS();
	}

	public static ExplainableDEVS getInstance() {
		return Holder.Instance;
	}

	public void spawnCar(String name, int lane) {
		System.out.println(String.format("[System] spawnCar(name=%s, lane=%d)", name, lane));
		switch ((int) (Math.random() * 100) % 5) {
			case 0:
				cars.put(name, new Taxi(name, lane)); break;
			case 1:
				cars.put(name, new Truck(name, lane)); break;
			case 2:
				cars.put(name, new Ambulance(name, lane)); break;
			case 3:
				cars.put(name, new Sedan(name, lane)); break;
			case 4:
				cars.put(name, new PoliceCar(name, lane));
		}
	}

	public SelfDrivingCar getCarByName(String name) {
		return cars.get(name);
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

		//for (SelfDrivingCar car: cars.values())
		//	car.draw(g);
		cars.values().forEach(car -> car.draw(g));
		//System.out.println(String.format("Repaint: %d cars left..", cars.size()));
	}

	public void updateLaneStatus() {
		for (int i = 1; i <= 3; ++i) {
			final int lane = i;
			isEmpty[lane-1] = cars.values().stream()
					.filter(car -> car.getLane() == lane)
					.noneMatch(car -> car.getX() < GlobalVariables.WIDTH / 4);
		}
	}

	public boolean getLaneStatus(int lane) {
		return isEmpty[lane-1];
	}

	public int getDistance(String name) {
		SelfDrivingCar car = cars.get(name);
		List<SelfDrivingCar> frontal = cars.values().stream()
				.filter(_car -> _car.getLane() == car.getLane())
				.filter(_car -> _car.getX() > car.getX())
				.sorted((car1, car2) -> car2.getX() - car1.getX())
				.collect(Collectors.toList());
		if (frontal.isEmpty()) {
			return Integer.MAX_VALUE;
		} else {
			return frontal.get(0).getX() - car.getX();
		}
	}

	public int getVelocityOf(String name) {
		return cars.get(name).getVelocity();
	}

	public void accelerate(String name, int accel) {
		SelfDrivingCar car = cars.get(name);
		int velocity = car.getVelocity();
		if (velocity == MAX_VELOCITY) return;
		car.setVelocity(velocity + accel);
	}

	public void slowdown(String name, int decel) {
		SelfDrivingCar car = cars.get(name);
		int velocity = car.getVelocity();
		if (velocity == MIN_VELOCITY) return;
		car.setVelocity(velocity - decel);
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
		ExplainableDEVS exdevs = ExplainableDEVS.getInstance();
		while (true) {
			if (exdevs.cars.size() < 10)
				exdevs.spawnCar("Car@" + System.currentTimeMillis(), (int) (Math.random() * 100) % 3 + 1);
			System.out.println("======================== DISTANCE ========================");
			for (SelfDrivingCar car: exdevs.cars.values()) {
				int distance = exdevs.getDistance(car.getName());
				System.out.println(String.format("[Tickin] Name: %s, Distance: %d, Velocity: %d", car.getName(), distance, car.getVelocity()));
				if (distance <= 300) {
					exdevs.slowdown(car.getName(), 1);
				}
			}
			exdevs.tick();
		}
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
		List<String> carsOutOfRange = cars.keySet().stream()
				.filter(name -> cars.get(name).getX() >= GlobalVariables.WIDTH)
				.collect(Collectors.toList());
		carsOutOfRange.forEach(name -> cars.remove(name));
		updateLaneStatus();
		repaint();
		/*
		try {
			Thread.sleep(100);
		} catch (Exception e) {
			e.printStackTrace();
		}
		*/
	}

	public static void close() {
		System.exit(0);
	}
}