
import java.awt.BasicStroke;
import java.awt.Color;
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
			// 0.5초마다
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			// repaint
			repaint();
			// System.out.println("moved");
			Check();
		}
	}



	private void Check() {
		// TODO Auto-generated method stub
		int Check[][] = new int[5][2];
		Check[0][0] = 1000;
		Check[1][0] = MySDC.x -MySDC2.x;
		Check[2][0] = MySDC.x -MySDC3.x;
		Check[3][0] = MySDC.x -MySDC4.x;
		Check[4][0] = MySDC.x -MySDC5.x;
		
		Check[0][1] = 1000;
		Check[1][1] = MySDC.y -MySDC2.y;
		Check[2][1] = MySDC.y -MySDC3.y;
		Check[3][1] = MySDC.y -MySDC4.y;
		Check[4][1] = MySDC.y -MySDC5.y;
		
		System.out.printf("%d",Check[3][0]);
		if(Check[3][0]<150 && Check[3][0]>-150)
		{
			System.out.println("충돌위험");
			MySDC.velocity -=5;
		}
		else
		{
			MySDC.velocity = 10;
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
	static int x = 10;
	static int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	static int velocity = 10;

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
		g.drawOval(getX()+10, y+20, Width+100, Height+100);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC2 {
	static int x = 10;
	static int y = 160;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	static int velocity = 5;

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
		g.fillRect(x + 20, y + 40, Width + 90, Height + 45);
		g.fillRect(x + 120, y + 65, Width + 15, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 40, y + 90, radius + 10, radius + 10);
		g.fillOval(x + 95, y + 90, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 95, y + 50, Width + 5, Height + 5);
		g.setColor(Color.GRAY);
		g.fillRect(x + 20, y + 30, Width + 55, Height + 35);
		g.drawOval(getX()-10, y-30, Width+180, Height+180);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC3 {
	static int x = 10;
	static int y = 310;
	private int z = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	static int velocity = 5;

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
		g.fillRect(x + 20, y + 30, Width + 105, Height + 45);
		g.setColor(Color.LIGHT_GRAY);
		g.fillRect(x + 140, y + 60, Width + 20, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 40, y + 80, radius + 10, radius + 10);
		g.fillOval(x + 95, y + 80, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 95, y + 40, Width + 15, Height + 5);
		g.setColor(Color.RED);
		g.fillRect(x + 75, y + 20, Width, Height);
		g.setColor(Color.GREEN);
		g.fillRect(x + 50, y + 48, Width + 15, Height);
		g.fillRect(x + 58, y + 40, Width, Height + 15);
		g.drawOval(getX()-10, y-40, Width+180, Height+180);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC4 {
	static int x = 300;
	static int y = 10;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	static int velocity = 5;

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
		g.fillRect(x + 38, y + 40, Width + 35, Height + 30);
		g.fillRect(x + 0, y + 60, Width + 110, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 25, y + 85, radius + 10, radius + 10);
		g.fillOval(x + 75, y + 85, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 55, y + 48, Width + 5, Height + 5);
		g.setColor(Color.BLUE);
		g.fillOval(x + 100, y + 70, radius, radius);
		g.setColor(Color.WHITE);
		g.fillArc(x + 100, y + 70, Width, Height, 0, 90);
		g.fillArc(x + 100, y + 70, Width, Height, 180, 90);
		g.drawOval(getX()-5, y+10, Width+120, Height+110);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
}

class MySDC5 {
	static int x = 300;
	static int y = 160;
	private int Width = 10;
	private int Height = 10;
	private int radius = 10;
	private Color MyColor;
	static int velocity = 5;

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
		g.fillRect(x + 28, y + 40, Width + 45, Height + 30);
		g.fillRect(x + 00, y + 65, Width + 100, Height + 20);
		g.setColor(Color.BLACK);
		g.fillOval(x + 15, y + 90, radius + 10, radius + 10);
		g.fillOval(x + 70, y + 90, radius + 10, radius + 10);
		g.setColor(Color.CYAN);
		g.fillRect(x + 50, y + 45, Width + 5, Height + 5);
		g.setColor(Color.BLUE);
		g.fillRect(x + 0, y + 65, Width + 100, Height);
		g.setColor(Color.ORANGE);
		g.fillRect(x + 0, y + 75, Width + 100, Height - 5);
		g.setColor(Color.RED);
		g.fillRect(x + 45, y + 30, Width, Height);
		g.setColor(Color.BLUE);
		g.fillRect(x + 55, y + 30, Width, Height);
		g.drawOval(getX()-10, y+10, Width+120, Height+110);
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}
	
}