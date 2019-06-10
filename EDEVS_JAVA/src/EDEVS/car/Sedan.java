package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Sedan extends SelfDrivingCar {

    public Sedan(String name) {
        super();
        this.name = name;
    }

    public Sedan(String name, int lane) {
        super(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    @Override
    public void draw(@NotNull Graphics g) {
        tick();
        g.setColor(Color.PINK);
        g.fillRect(x + 58, y + 45, width + 35, height + 30);
        g.fillRect(x + 20, y + 65, width + 110, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 45, y + 90, radius + 10, radius + 10);
        g.fillOval(x + 95, y + 90, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 75, y + 53, width + 5, height + 5);
        g.setColor(Color.BLUE);
        g.fillOval(x + 120, y + 75, radius, radius);
        g.setColor(Color.WHITE);
        g.fillArc(x + 120, y + 75, width, height, 0, 90);
        g.fillArc(x + 120, y + 75, width, height, 180, 90);

        //g.drawOval(x, y, 300, 300);
    }
}
