package EDEVS.car;

import com.sun.istack.internal.NotNull;

import java.awt.*;

public abstract class SelfDrivingCar {
    String name;
    int x;
    int y;
    int width;
    int height;
    int radius;
    int velocity;

    public SelfDrivingCar() {
        this("SelfDrivingCar", 10, 10, 10, 10, 10, 5);
    }

    public SelfDrivingCar(String name, int x, int y, int width, int height, int radius) {
        this(name, x, y, width, height, radius, 5);
    }

    public SelfDrivingCar(String name, int x, int y, int width, int height, int radius, int velocity) {
        this.name = name;
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.radius = radius;
        this.velocity = velocity;
    }

    public int getVelocity() {
        return velocity;
    }

    public void setVelocity(int velocity) {
        this.velocity += velocity;
    }

    public void tick() {
        x += velocity;
    }

    public abstract void draw(@NotNull Graphics g);
}