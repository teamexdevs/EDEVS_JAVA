package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class PoliceCar extends SelfDrivingCar {

    public PoliceCar(String name) {
        super();
        this.name = name;
    }

    public PoliceCar(String name, int lane) {
        super(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.WHITE);
        g.fillRect(x + 48, y + 10, width + 45, height + 30);
        g.fillRect(x + 20, y + 35, width + 100, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 45, y + 60, radius + 10, radius + 10);
        g.fillOval(x + 90, y + 60, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 70, y + 15, width + 5, height + 5);
        g.setColor(Color.BLUE);
        g.fillRect(x + 20, y + 35, width + 100, height);
        g.setColor(Color.ORANGE);
        g.fillRect(x + 20, y + 45, width + 100, height - 5);
        g.setColor(Color.RED);
        g.fillRect(x + 65, y, width, height);
        g.setColor(Color.BLUE);
        g.fillRect(x + 75, y, width, height);
    }
}
