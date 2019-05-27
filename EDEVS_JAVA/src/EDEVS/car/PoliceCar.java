package EDEVS.car;

import org.jetbrains.annotations.NotNull;

import java.awt.*;

public class PoliceCar extends SelfDrivingCar {

    @Override
    public void draw(@NotNull Graphics g) {
        this.x += velocity;
        g.setColor(Color.WHITE);
        g.fillRect(x + 318, y + 190, width + 45, height + 30);
        g.fillRect(x + 290, y + 215, width + 100, height + 20);
        g.setColor(Color.BLACK);
        g.fillOval(x + 315, y + 240, radius + 10, radius + 10);
        g.fillOval(x + 360, y + 240, radius + 10, radius + 10);
        g.setColor(Color.CYAN);
        g.fillRect(x + 340, y + 195, width + 5, height + 5);
        g.setColor(Color.BLUE);
        g.fillRect(x + 290, y + 215, width + 100, height);
        g.setColor(Color.ORANGE);
        g.fillRect(x + 290, y + 225, width + 100, height - 5);
        g.setColor(Color.RED);
        g.fillRect(x + 335, y + 180, width, height);
        g.setColor(Color.BLUE);
        g.fillRect(x + 345, y + 180, width, height);
    }
}
