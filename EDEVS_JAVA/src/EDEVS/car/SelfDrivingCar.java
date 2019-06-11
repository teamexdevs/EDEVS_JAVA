package EDEVS.car;

import EDEVS.util.GlobalVariables;
import com.sun.istack.internal.NotNull;

import java.awt.*;

public abstract class SelfDrivingCar {
    String name;
    int lane;
    int x;
    int y;
    int width;
    int height;
    int radius;
    int velocity;

    public SelfDrivingCar() {
        this("SelfDrivingCar", 1, (int) (Math.random() * 100) % 10 + 1);
    }

    public SelfDrivingCar(String name) {
        this(name, (int) (Math.random() * 100) % 3 + 1, (int) (Math.random() * 100) % 10 + 1);
    }

    public SelfDrivingCar(String name, int lane) {
        this(name, lane, (int) (Math.random() * 100) % 10 + 1);
    }

    public SelfDrivingCar(String name, int lane, int velocity) {
        this.name = name;
        this.lane = lane;
        this.x = 10;
        this.y = (GlobalVariables.HEIGHT / 3) * (lane - 1);
        this.width = 10;
        this.height = 10;
        this.radius = 10;
        this.velocity = velocity;
    }

    public String getName() {
        return name;
    }

    public int getLane() {
        return lane;
    }

    public int getX() {
        return x;
    }

    public int getVelocity() {
        return velocity;
    }

    public void setVelocity(int velocity) {
        this.velocity = velocity;
    }

    public void tick() {
        x += velocity;
    }

    public abstract void draw(@NotNull Graphics g);
}