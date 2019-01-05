package space.cougs.ground.gui.modules.power;

import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import space.cougs.ground.gui.utils.AnimationComponent;

public class Wire extends JPanel implements AnimationComponent {
  private static final long serialVersionUID = 1L;

  private double current       = 0.0;
  private double voltage       = 0.0;
  // private double animationTime = 100;

  private int Distance = 0;

  private String varName = "";

  public Wire(String name) {
    varName = name;
  }

  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    Graphics2D g2d = (Graphics2D)g;

	double speed = current/5.0;
	int length = this.getHeight() * 2;
  int x = 0;
  int startDistance = Distance;

	// for(int i = 0; x < this.getWidth();i++)
	// {
	// 	x = i * (int) speed * (length * 3) + startDistance;
	// 	g2d.fillRect(x, this.getHeight()/4, length, this.getHeight()/2);
	// }

  if (startDistance > length)
  {
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
	// animationTime = timerDuration;
	Distance++;
    repaint();
  }
}
