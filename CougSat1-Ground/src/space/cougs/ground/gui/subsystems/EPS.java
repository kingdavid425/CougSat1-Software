package space.cougs.ground.gui.subsystems;

import java.awt.Component;
import java.awt.FontMetrics;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.Timer;

import space.cougs.ground.gui.UIScaling;
import space.cougs.ground.gui.modules.CISPanel;
import space.cougs.ground.gui.modules.CISTabbedPane;
import space.cougs.ground.gui.modules.power.Battery;
import space.cougs.ground.gui.modules.power.Regulator;
import space.cougs.ground.gui.modules.power.SolarPanel;
import space.cougs.ground.gui.modules.power.Wire;
import space.cougs.ground.gui.utils.AnimationComponent;
import space.cougs.ground.gui.utils.CustomColors;
import space.cougs.ground.gui.utils.GridBagConstraintsWrapper;
import space.cougs.ground.satellites.CougSat;
import space.cougs.ground.utils.Units;

public class EPS extends CISPanel implements UIScaling, SatelliteInfo {
  private static final long serialVersionUID = 1L;
  private static final CISTabbedPane mainPowerPanel = new CISTabbedPane();
  private static final CISPanel powerGeneration = new CISPanel();
  private static final CISPanel powerDistribution = new CISPanel();

  private List<AnimationComponent> movingComponents = new ArrayList<AnimationComponent>();
  private static final double timerDelay = (1 / 10);
  private static int width = 0;
  private static int height = 0;

  private List<Wire> pvWires = new ArrayList<Wire>();
  private List<Regulator> mppList = new ArrayList<Regulator>();
  private List<SolarPanel> solarPanels = new ArrayList<SolarPanel>();
  private List<Battery> batts = new ArrayList<Battery>();
  private List<Wire> mainWires = new ArrayList<Wire>();
  Timer timer = new Timer(100, new MyActionListener());

  public EPS() {
    super();

    for (int i = 0; i < 8; i++) {
      solarPanels.add(new SolarPanel("pV" + i));
      pvWires.add(new Wire("pvWire" + i, i < 4 ? 0 : 1));
      mppList.add(new Regulator("mppt" + i));
    }
    for (int i = 0; i < 1; i++) {
      mainWires.add(new Wire("mainWire" + i, 2));
    }
    for (int i = 0; i < 2; i++) {
      batts.add(new Battery("Battery" + i));
    }
    for (Wire pvWire : pvWires) {
      movingComponents.add(pvWire);
    }
    for (Wire mainWire : mainWires) {
      movingComponents.add(mainWire);
    }
    GridBagConstraintsWrapper gbc = new GridBagConstraintsWrapper();
    gbc.setFill(GridBagConstraintsWrapper.BOTH);
    this.setLayout(new GridBagLayout());

    powerGeneration.setLayout(null);
    for (int i = 0; i < 8; i++) {
      powerGeneration.add(solarPanels.get(i));
      powerGeneration.add(pvWires.get(i));
    }
    for (Wire mainWire : mainWires) {
      powerGeneration.add(mainWire);
    }

    powerGeneration.setBackground(CustomColors.PRIMARY);
    powerGeneration.setOpaque(true);
    powerGeneration.addComponentListener(generationListener);

    powerDistribution.setLayout(null);
    powerDistribution.setBackground(CustomColors.PRIMARY);
    powerDistribution.addComponentListener(distributionListener);

    mainPowerPanel.setBackground(CustomColors.SECONDARY);
    mainPowerPanel.addTab("   Power Gen    ", powerGeneration);
    mainPowerPanel.addTab("   Power Dist   ", powerDistribution);
    mainPowerPanel.setSelectedComponent(powerGeneration);

    timer.start();

    this.add(mainPowerPanel, gbc.setXY(0, 0).setSize(1, 1).setWeight(1.0, 1.0).setInsets(10, 10, 10, 10));
    this.setBackground(CustomColors.SECONDARY);
  }

  private final ComponentListener generationListener = new ComponentListener() {
    @Override
    public void componentHidden(ComponentEvent e) {
    }

    @Override
    public void componentMoved(ComponentEvent e) {
    }

    @Override
    public void componentResized(ComponentEvent e) {
      double voltage = 0.0;
      double current = 0.0;
      int y = 0;
      FontMetrics fontMetrics = powerGeneration.getFontMetrics(solarPanels.get(0).getFont());

      for (int i = 0; i < solarPanels.size() / 2; i++) { // left 4 pV
        voltage = solarPanels.get(i).getVoltage();
        current = solarPanels.get(i).getCurrent();
        String printValues = Units.toVoltage(voltage) + " " + Units.toCurrent(current);
        width = 2
            + Math.max(fontMetrics.stringWidth(solarPanels.get(i).getName()), fontMetrics.stringWidth(printValues));
        height = fontMetrics.getHeight() * 2 + 4;
        y = 10 + 10 * i + i * height;
        solarPanels.get(i).setBounds(10, y, width, height);
        pvWires.get(i).setBounds(10 + width, y + height / 2, powerGeneration.getWidth() / 2 - width - 10, 10);
      }
      for (int i = solarPanels.size() / 2; i < solarPanels.size(); i++) { // right 4 pV
        voltage = solarPanels.get(i).getVoltage();
        current = solarPanels.get(i).getCurrent();
        String printValues = Units.toVoltage(voltage) + " " + Units.toCurrent(current);
        width = 2
            + Math.max(fontMetrics.stringWidth(solarPanels.get(i).getName()), fontMetrics.stringWidth(printValues));
        height = fontMetrics.getHeight() * 2 + 4;
        y = 10 + 10 * (i - solarPanels.size() / 2) + (i - solarPanels.size() / 2) * height;
        solarPanels.get(i).setBounds(powerGeneration.getWidth() - 10 - width, y, width, height);
        pvWires.get(i).setBounds(powerGeneration.getWidth() / 2, y + height / 2,
            powerGeneration.getWidth() / 2 - width - 10, 10);
      }
      mainWires.get(0).setBounds(powerGeneration.getWidth() / 2 - 5, 0, 10, powerGeneration.getHeight() * 3/4);

      repaint();
    }

    @Override
    public void componentShown(ComponentEvent e) {
      this.componentResized(e);
    }
  };

  private final ComponentListener distributionListener = new ComponentListener() {
    @Override
    public void componentHidden(ComponentEvent e) {
    }

    @Override
    public void componentMoved(ComponentEvent e) {
    }

    @Override
    public void componentResized(ComponentEvent e) {
    }

    @Override
    public void componentShown(ComponentEvent e) {
      this.componentResized(e);
    }
  };

  public final class MyActionListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent arg0) {
      for (AnimationComponent movingComponent : movingComponents) {
        movingComponent.updateFrame(timerDelay);
      }
    }
  }

  @Override
  public void updateUIScaling(UIScale uiScale) {
    for (Component child : this.getComponents()) {
      if (child instanceof UIScaling)
        ((UIScaling) child).updateUIScaling(uiScale);
    }
  }

  public void updateSatellite(CougSat satellite) {
    int i = 0;
    double voltage = 0.0;
    double current = 0.0;
    for (SolarPanel solarPanel : solarPanels) {

      solarPanel.setVoltage(satellite.getEPS().getPVVoltage(i));
      solarPanel.setCurrent(satellite.getEPS().getPVCurrent(i));
      voltage += satellite.getEPS().getPVVoltage(i);
      current += satellite.getEPS().getPVCurrent(i);
      i++;
    }
    mainWires.get(0).setVoltage(voltage);
    mainWires.get(0).setCurrent(current);
    i = 0;
    for (Wire wire : pvWires) {
      wire.setVoltage(satellite.getEPS().getPVVoltage(i));
      wire.setCurrent(satellite.getEPS().getPVCurrent(i));
      i++;
    }
    // batts.get(0).setVoltage(satellite.getEPS().getBatteryVoltage(0));
    // batts.get(0).setVoltage(satellite.getEPS().getBatteryCurrent(1));
    // batts.get(0).setVoltage(satellite.getEPS().getBatteryVoltage(1));
    // batts.get(0).setVoltage(satellite.getEPS().getBatteryCurrent(1));
  }
}