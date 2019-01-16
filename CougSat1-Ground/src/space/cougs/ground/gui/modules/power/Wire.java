package space.cougs.ground.gui.modules.power;

import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import space.cougs.ground.gui.utils.AnimationComponent;
import space.cougs.ground.gui.utils.CustomColors;

public class Wire extends JPanel implements AnimationComponent {
  private static final long serialVersionUID = 1L;

  private double current = 0.0;
  private double voltage = 0.0;
  // private double animationTime = 100;
  private int startDistance = 0;

  private String varName = "";

  public Wire(String name) {
    varName = name;
  }

  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    Graphics2D g2d = (Graphics2D) g;

    // double animationSpeed = animationTime / 1000;
    // double speed = current / 10.0;
    int length = this.getHeight() * 2;
    int height = this.getHeight() * 2;
    int y = this.getHeight() / 4;

    for (int i = 0; i * length < this.getWidth(); i++) {
      g2d.setColor(CustomColors.WIRE_ANIMATION);
      g2d.fillRect(((startDistance) + i * (length) * 2), y, length, height);
    }

    if (startDistance > length * 2) {
      startDistance = 0;
    }
  }

  public String getName() {
    return varName;
  }

  public void setName(String name) {
    this.varName = name;
  }

  public double getCurrent() {
    return current;
  }

  public void setCurrent(double newCurrent) {
    this.current = newCurrent;
  }

  public double getVoltage() {
    return voltage;
  }

  public void setVoltage(double newVoltage) {
    this.voltage = newVoltage;
  }

  @Override
  public void updateFrame(double timerDuration) {

    int length = this.getHeight() * 2;
    double speed = this.getCurrent() / 10.0;

    startDistance += length * speed;
    repaint();
  }
}
