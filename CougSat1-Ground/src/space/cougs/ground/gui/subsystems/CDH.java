package space.cougs.ground.gui.subsystems;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.GridBagLayout;
import space.cougs.ground.satellites.CougSat;

import javax.swing.JPanel;
import javax.swing.JTextArea;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.general.DefaultPieDataset;

import space.cougs.ground.gui.UIScaling;
import space.cougs.ground.gui.subsystems.modules.TitleLabel;
import space.cougs.ground.gui.utils.CustomColors;
import space.cougs.ground.gui.utils.Fonts;
import space.cougs.ground.gui.utils.GridBagConstraintsWrapper;

public class CDH extends JPanel implements UIScaling, SatelliteInfo {

	private static final long serialVersionUID = 1L;
	DefaultPieDataset sdUsageData = new DefaultPieDataset( );
	JFreeChart chart = ChartFactory.createPieChart("Disk Usage", sdUsageData, true, true, false);
	DefaultPieDataset dataset = new DefaultPieDataset();

	public CDH() {
		super();

		sdUsageData.setValue( "SD Used", 1);
		sdUsageData.setValue( "SD Free", 1);
		
		
		GridBagConstraintsWrapper gbc = new GridBagConstraintsWrapper();
		gbc.setFill(GridBagConstraintsWrapper.BOTH);

		this.setLayout(new GridBagLayout());
		
		this.add(new ChartPanel( chart ));

		this.add(new TitleLabel("Computer"), gbc.setLocation(0, 0).setSize(3, 1).setWeight(0.0, 0.0));

		this.setBackground(CustomColors.BACKGROUND2);
	}

	@Override
	public void updateUIScaling(UIScale uiScale) {
		Font font = Fonts.BODY_24;
		Font bodyfont = Fonts.BODY_16;

		switch (uiScale) {
		default:
		case SCALE_100:
			font = Fonts.BODY_24;
			bodyfont = Fonts.BODY_16;
			break;
		case SCALE_150:
			font = Fonts.BODY_36;
			bodyfont = Fonts.BODY_24;
			break;
		case SCALE_200:
			font = Fonts.BODY_48;
			bodyfont = Fonts.BODY_32;
			break;
		case SCALE_300:
			font = Fonts.BODY_48;
			bodyfont = Fonts.BODY_48;
			break;
		case SCALE_75:
			font = Fonts.BODY_16;
			bodyfont = Fonts.BODY_12;
			break;
		}
		for (Component component : this.getComponents()) {
			if (component instanceof TitleLabel) {
				component.setFont(font);
				component.setBackground(CustomColors.BACKGROUND1);
				component.setForeground(Color.white);

			} else if (component instanceof JTextArea) {
				component.setFont(bodyfont);
				component.setBackground(CustomColors.BACKGROUND1);
			}
		}
	}

	@Override
	public void updateSatellite(CougSat satellite) {
		
	}
}
