package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Taxi extends SelfDrivingCar {

    public Taxi(String name) {
        super();
        this.name = name;
    }

    public Taxi(String name, int lane) {
        super(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.YELLOW);
        g.fillRect(x + 40, y + 40, width + 40, height + 30);
        g.fillRect(x + 20, y + 60, width + 80, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 35, y + 85, radius + 10, radius + 10);
        g.fillOval(x + 75, y + 85, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 48, y + 50, width + 5, height + 5);
        g.fillRect(x + 68, y + 50, width + 5, height + 5);
        g.setColor(Color.ORANGE);
        g.fillRect(x + 60, y + 30, width, height);
    }
}
