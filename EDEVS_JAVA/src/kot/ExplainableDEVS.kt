package kot

import EDEVS.car.*
import EDEVS.util.GlobalVariables

import java.awt.BasicStroke
import java.awt.Color
import java.awt.Graphics
import java.awt.Graphics2D
import java.util.ArrayList

import javax.swing.JFrame
import javax.swing.JPanel

class ExplainableDEVS private constructor() : JPanel() {

    private val cars = ArrayList<SelfDrivingCar>()

    init {
        background = Color.lightGray
        cars.add(Taxi("Taxi"))
        cars.add(Truck("Truck"))
        cars.add(Ambulance("Ambulance"))
        //cars.add(new Sedan("Sedan"));
        //cars.add(new PoliceCar("PoliceCar"));
    }

    public override fun paintComponent(g: Graphics) {
        super.paintComponent(g)

        val g2 = g as Graphics2D
        val dash20 = floatArrayOf(20f, 1f)
        g2.stroke = BasicStroke(1f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1f, dash20, 0f)

        val y1 = height / 3
        val y2 = height - height / 3
        g.setColor(Color.WHITE)
        g.drawLine(0, y1, width, y1)
        g.drawLine(0, y2, width, y2)

        if (cars.filter { it.x < GlobalVariables.WIDTH / 3 }.isEmpty()) {
            cars.add(PoliceCar("PoliceCar#2"))
        }
        val achievedCars = ArrayList<SelfDrivingCar>()
        for (car in cars) {
            if (car.x >= GlobalVariables.WIDTH) {
                achievedCars.add(car)
            } else {
                car.draw(g)
            }
        }
        cars.removeAll(achievedCars)
        println(String.format("Repaint: %d cars left..", cars.size))
    }

    companion object {

        private var explainableDEVS: ExplainableDEVS? = null

        @JvmStatic
        fun main(args: Array<String>) {
            execute()
            while (true)
                tick()
        }

        fun execute() {
            val frame = JFrame()
            explainableDEVS = ExplainableDEVS()
            frame.add(explainableDEVS)
            frame.title = "E-DEVS SDC Simulation"
            frame.defaultCloseOperation = JFrame.EXIT_ON_CLOSE
            frame.setSize(GlobalVariables.WIDTH, GlobalVariables.HEIGHT)
            frame.isVisible = true
        }

        fun tick() {
            explainableDEVS!!.repaint()
            try
            {
                Thread.sleep(100)
            }
            catch (e:InterruptedException) {
                e.printStackTrace()
            }
	    }

        fun close() {
            System.exit(0)
        }
    }
}