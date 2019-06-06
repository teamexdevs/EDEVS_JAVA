package EDEVS;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class EDEVS_SDC extends JPanel {
	private int Width;
	private int Height;
	private MySDC mySDC;
	private MySDC2 mySDC2;
	private MySDC3 mySDC3;
	private MySDC4 mySDC4;
	private MySDC5 mySDC5;

	public EDEVS_SDC() {
		setBackground(Color.lightGray);

		mySDC = new MySDC();
		mySDC2 = new MySDC2();
		mySDC3 = new MySDC3();
		mySDC4 = new MySDC4();
		mySDC5 = new MySDC5();

	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		Graphics2D g2 = (Graphics2D) g;
		float dash20[] = { 20, 1f };
		g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1, dash20, 0));

		int x1 = getHeight() / 3;
		int x2 = getHeight() - getHeight() / 3;
		g.setColor(Color.WHITE);
		g.drawLine(0, x1, getWidth(), x1);
		g.setColor(Color.WHITE);
		g.drawLine(0, x2, getWidth(), x2);

		if (mySDC.getX() == 1300) {

		} else
			mySDC.draw(g);

		if (mySDC2.getX() == 1300) {

		} else
			mySDC2.draw(g);

		if (mySDC3.getX() == 1300) {

		} else
			mySDC3.draw(g);

		if (mySDC4.getX() == 1300) {

		} else
			mySDC4.draw(g);

		if (mySDC5.getX() == 1300) {

		} else
			mySDC5.draw(g);

		System.out.println("repainted");
	}

	public void start() {
		while (true) {
			// 0.5√ ∏∂¥Ÿ
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			// repaint
			repaint();
			// System.out.println("moved");
		}
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame();
		EDEVS_SDC Sdc = new EDEVS_SDC();
		frame.add(Sdc);
		frame.setTitle("E-DEVS SDC Simulation");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1800, 500);
		frame.setVisible(true);
		Sdc.start();
	}
}

class MySDC {
	private int x = 10;
	private int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	private int velocity = 5;

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public MySDC() {
	}

	public MySDC(int x, int y, int Width, int Height, int radius, Color MyColor) {
		this.setX(x);
		this.y = y;
		this.Width = Width;
		this.Height = Height;
		this.radius = radius;
		this.MyColor = MyColor;
	}

	public void draw(Graphics g) {
		this.setX(this.getX() + velocity);

		g.setColor(Color.YELLOW);
		g.fillRect(getX() + 40, y + 40, Width + 40, Height + 30);
		g.fillRect(getX() + 20, y + 60, Width + 80, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(getX() + 35, y + 85, radius + 10, radius + 10);
		g.fillOval(getX() + 75, y + 85, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(getX() + 48, y + 50, Width + 5, Height + 5);
		g.fillRect(getX() + 68, y + 50, Width + 5, Height + 5);
		g.setColor(Color.ORANGE);
		g.fillRect(getX() + 60, y + 30, Width, Height);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC2 {
	private int x = 10;
	private int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	private int velocity = 5;

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public MySDC2() {
	}

	public MySDC2(int x, int y, int Width, int Height, int radius, Color MyColor) {
		this.setX(x);
		this.y = y;
		this.Width = Width;
		this.Height = Height;
		this.radius = radius;
		this.MyColor = MyColor;
	}

	public void draw(Graphics g) {
		this.x += velocity;

		g.setColor(Color.GREEN);
		g.fillRect(x + 20, y + 190, Width + 90, Height + 45);
		g.fillRect(x + 120, y + 215, Width + 15, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 40, y + 240, radius + 10, radius + 10);
		g.fillOval(x + 95, y + 240, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 95, y + 200, Width + 5, Height + 5);
		g.setColor(Color.GRAY);
		g.fillRect(x + 20, y + 180, Width + 55, Height + 35);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC3 {
	private int x = 10;
	private int y = 10;
	private int z = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	private int velocity = 5;

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public MySDC3() {
	}

	public MySDC3(int x, int y, int Width, int Height, int radius, Color MyColor) {
		this.setX(x);
		this.y = y;
		this.Width = Width;
		this.Height = Height;
		this.radius = radius;
		this.MyColor = MyColor;
	}

	public void draw(Graphics g) {
		this.x += velocity;

		g.setColor(Color.WHITE);
		g.fillRect(x + 20, y + 330, Width + 105, Height + 45);
		g.setColor(Color.LIGHT_GRAY);
		g.fillRect(x + 140, y + 360, Width + 20, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 40, y + 380, radius + 10, radius + 10);
		g.fillOval(x + 95, y + 380, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 95, y + 340, Width + 15, Height + 5);
		g.setColor(Color.RED);
		g.fillRect(x + 75, y + 320, Width, Height);
		g.setColor(Color.GREEN);
		g.fillRect(x + 50, y + 348, Width + 15, Height);
		g.fillRect(x + 58, y + 340, Width, Height + 15);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC4 {
	private int x = 10;
	private int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	private int velocity = 5;

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public MySDC4() {
	}

	public MySDC4(int x, int y, int Width, int Height, int radius, Color MyColor) {
		this.setX(x);
		this.y = y;
		this.Width = Width;
		this.Height = Height;
		this.radius = radius;
		this.MyColor = MyColor;
	}

	public void draw(Graphics g) {
		this.x += velocity;
		g.setColor(Color.PINK);
		g.fillRect(x + 328, y + 40, Width + 35, Height + 30);
		g.fillRect(x + 290, y + 60, Width + 110, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 315, y + 85, radius + 10, radius + 10);
		g.fillOval(x + 365, y + 85, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 345, y + 48, Width + 5, Height + 5);
		g.setColor(Color.BLUE);
		g.fillOval(x + 390, y + 70, radius, radius);
		g.setColor(Color.WHITE);
		g.fillArc(x + 390, y + 70, Width, Height, 0, 90);
		g.fillArc(x + 390, y + 70, Width, Height, 180, 90);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC5 {
	private int x = 10;
	private int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	private int velocity = 5;

	public int getVelocity() {
		return velocity;
	}

	public void setVelocity(int velocity) {
		this.velocity = velocity;
	}

	public MySDC5() {
	}

	public MySDC5(int x, int y, int Width, int Height, int radius, Color MyColor) {
		this.setX(x);
		this.y = y;
		this.Width = Width;
		this.Height = Height;
		this.radius = radius;
		this.MyColor = MyColor;
	}

	public void draw(Graphics g) {
		this.x += velocity;
		g.setColor(Color.WHITE);
		g.fillRect(x + 318, y + 190, Width + 45, Height + 30);
		g.fillRect(x + 290, y + 215, Width + 100, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 315, y + 240, radius + 10, radius + 10);
		g.fillOval(x + 360, y + 240, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 340, y + 195, Width + 5, Height + 5);
		g.setColor(Color.BLUE);
		g.fillRect(x + 290, y + 215, Width + 100, Height);
		g.setColor(Color.ORANGE);
		g.fillRect(x + 290, y + 225, Width + 100, Height - 5);
		g.setColor(Color.RED);
		g.fillRect(x + 335, y + 180, Width, Height);
		g.setColor(Color.BLUE);
		g.fillRect(x + 345, y + 180, Width, Height);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}