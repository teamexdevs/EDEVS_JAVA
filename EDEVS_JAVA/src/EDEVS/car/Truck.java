package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Truck extends SelfDrivingCar {

    public Truck(String name) {
        super();
        this.name = name;
    }

    public Truck(String name, int lane) {
        super(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.GREEN);
        g.fillRect(x + 20, y + 10, width + 90, height + 45);
        g.fillRect(x + 120, y + 35, width + 15, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 40, y + 60, radius + 10, radius + 10);
        g.fillOval(x + 95, y + 60, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 95, y + 20, width + 5, height + 5);
        g.setColor(Color.GRAY);
        g.fillRect(x + 20, y, width + 55, height + 35);
    }
}
