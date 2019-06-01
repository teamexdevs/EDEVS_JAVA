package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public class Ambulance extends SelfDrivingCar {

    @Override
    public void draw(@NotNull Graphics g) {
        this.x += velocity;
        g.setColor(Color.WHITE);
        g.fillRect(x + 20, y + 330, width + 105, height + 45);
        g.setColor(Color.LIGHT_GRAY);
        g.fillRect(x + 140, y + 360, width + 20, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 40, y + 380, radius + 10, radius + 10);
        g.fillOval(x + 95, y + 380, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 95, y + 340, width + 15, height + 5);
        g.setColor(Color.RED);
        g.fillRect(x + 75, y + 320, width, height);
        g.setColor(Color.GREEN);
        g.fillRect(x + 50, y + 348, width + 15, height);
        g.fillRect(x + 58, y + 340, width, height + 15);
    }
}
