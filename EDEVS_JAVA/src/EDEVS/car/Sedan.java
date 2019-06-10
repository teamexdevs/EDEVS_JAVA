package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Sedan extends SelfDrivingCar {

    public Sedan(String name) {
        super();
        this.name = name;
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.PINK);
        g.fillRect(x + 328, y + 40, width + 35, height + 30);
        g.fillRect(x + 290, y + 60, width + 110, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 315, y + 85, radius + 10, radius + 10);
        g.fillOval(x + 365, y + 85, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 345, y + 48, width + 5, height + 5);
        g.setColor(Color.BLUE);
        g.fillOval(x + 390, y + 70, radius, radius);
        g.setColor(Color.WHITE);
        g.fillArc(x + 390, y + 70, width, height, 0, 90);
        g.fillArc(x + 390, y + 70, width, height, 180, 90);
    }
}
