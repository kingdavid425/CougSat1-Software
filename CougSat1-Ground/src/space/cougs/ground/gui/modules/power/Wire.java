package space.cougs.ground.gui.modules.power;

import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

import space.cougs.ground.gui.utils.AnimationComponent;

public class Wire extends JPanel implements AnimationComponent {
  private static final long serialVersionUID = 1L;
	private double current = 0.0;
	private double voltage = 0.0;
	private String varName = "";
	private double animationTime = 100;

	public Wire(String name) {

		varName = name;
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;

		for (int i = 0; i < this.getHeight(); i++) {
			g2d.fillRect(i * 20, 0, 20, this.getHeight() / 2);
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
		animationTime = timerDuration;
		repaint();
	}
}
