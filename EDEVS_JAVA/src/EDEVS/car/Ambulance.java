package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Ambulance extends SelfDrivingCar {

    public Ambulance(String name) {
        super();
        this.name = name;
    }

    public Ambulance(String name, int lane) {
        super(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.WHITE);
        g.fillRect(x + 20, y + 10, width + 105, height + 45);
        g.setColor(Color.LIGHT_GRAY);
        g.fillRect(x + 140, y + 40, width + 20, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 40, y + 60, radius + 10, radius + 10);
        g.fillOval(x + 95, y + 60, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 95, y + 20, width + 15, height + 5);
        g.setColor(Color.RED);
        g.fillRect(x + 75, y, width, height);
        g.setColor(Color.GREEN);
        g.fillRect(x + 50, y + 28, width + 15, height);
        g.fillRect(x + 58, y + 20, width, height + 15);
    }
}
