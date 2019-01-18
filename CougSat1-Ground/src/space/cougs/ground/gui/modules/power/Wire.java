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
  private int direction = 0;
  private int startDistance = 0;

  private String varName = "";

  public Wire(String name, int direction) {
    varName = name;
    this.direction = direction;
  }

  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    Graphics2D g2d = (Graphics2D) g;

    int length = direction < 2 ? this.getHeight() * 2 : this.getWidth() * 2;
    int y = this.getHeight() / 4;

    g2d.setColor(CustomColors.WIRE_ANIMATION);
    switch (direction) {
    case 0:// left to right
      for (int i = 0; i * length < this.getWidth(); i++) {
        g2d.fillRect(((startDistance) + i * (length) * 2), y, length, length);
      }
      break;
    case 1:// right to left
      for (int i = 0; i * length < this.getWidth(); i++) {
        g2d.fillRect(this.getWidth() - ((startDistance) + i * (length) * 2), y, length, length);
      }
      break;
    case 2:// top to bottom
      for (int i = 0; i * length < this.getHeight(); i++) {
        g2d.fillRect(0, ((startDistance) + i * (length) * 2), length, length);
      }
      break;
    case 3:// bottom to top
      for (int i = 0; i * length < this.getHeight(); i++) {
        g2d.fillRect(0, this.getWidth() - ((startDistance) + i * (length) * 2), length, length);
      }
      break;
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
    this.setToolTipText(String.format("Voltage: %.3fv, Current: %.3fA", this.voltage, this.current));
  }

  public double getVoltage() {
    return voltage;
  }

  public void setVoltage(double newVoltage) {
    this.voltage = newVoltage;
    this.setToolTipText(String.format("Voltage: %.3fv, Current: %.3fA", this.voltage, this.current));
  }

  /**
   * @return the direction
   */
  public int getDirection() {
    return direction;
  }

  /**
   * @param direction the direction to set
   */
  public void setDirection(int direction) {
    this.direction = direction;
  }

  /**
   * @return the startDistance
   */
  public int getStartDistance() {
    return startDistance;
  }

  /**
   * @param startDistance the startDistance to set
   */
  public void setStartDistance(int startDistance) {
    this.startDistance = startDistance;
  }

  /**
   * @return the varName
   */
  public String getVarName() {
    return varName;
  }

  /**
   * @param varName the varName to set
   */
  public void setVarName(String varName) {
    this.varName = varName;
  }

  @Override
  public void updateFrame(double timerDuration) {

    int length = this.getDirection() < 2 ? this.getHeight() * 2 : this.getWidth() * 2;
    double speed = this.getCurrent() / 1.0;

    startDistance += Math.max(length * speed, 1);
    repaint();
  }
}
