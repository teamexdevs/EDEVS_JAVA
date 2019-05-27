package EDEVS.car;

import org.jetbrains.annotations.NotNull;

import java.awt.*;

public class Truck extends SelfDrivingCar {

    @Override
    public void draw(@NotNull Graphics g) {
        this.x += velocity;
        g.setColor(Color.GREEN);
        g.fillRect(x + 20, y + 190, width + 90, height + 45);
        g.fillRect(x + 120, y + 215, width + 15, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 40, y + 240, radius + 10, radius + 10);
        g.fillOval(x + 95, y + 240, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 95, y + 200, width + 5, height + 5);
        g.setColor(Color.GRAY);
        g.fillRect(x + 20, y + 180, width + 55, height + 35);
    }
}
