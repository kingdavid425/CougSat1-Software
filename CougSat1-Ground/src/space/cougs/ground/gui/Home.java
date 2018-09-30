package space.cougs.ground.gui;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Font;
import java.awt.GridBagLayout;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.text.JTextComponent;

import space.cougs.ground.CougSatGround;
import space.cougs.ground.gui.subsystems.modules.ImageModule;
import space.cougs.ground.gui.subsystems.modules.TitleLabel;
import space.cougs.ground.gui.utils.CustomColors;
import space.cougs.ground.gui.utils.Fonts;
import space.cougs.ground.gui.utils.GridBagConstraintsWrapper;

public class Home extends JPanel implements UIScaling {

	private static final long serialVersionUID = 1L;

	private static final JPanel patchNotesPanel = new JPanel();
	private static final TitleLabel patchNotesHeaderText = new TitleLabel(
			"CIS Patch Notes " + CougSatGround.getVersionnumber());
	private static final JTextArea patchNotesBodyText = new JTextArea("");
	private static final JScrollPane patchNotesScroll = new JScrollPane(patchNotesBodyText);

	private static final JPanel aboutPanel = new JPanel();
	private static final JTextArea aboutPanelBody = new JTextArea("");
	private static final TitleLabel aboutPanelHeader = new TitleLabel("About GroundStation", SwingConstants.CENTER);

	private static final JPanel optionsPanel = new JPanel();
	private static final JPanel filesAndDirectories = new JPanel();
	private static final JTextField homeDirectory = new JTextField(System.getProperty("user.dir"));
	private static final JPanel groundStationParams = new JPanel();
	private static final JTextField groundstationName = new JTextField("Enter GroundStation Name");
	private static final JTextField latittude = new JTextField();
	private static final JTextField longitude = new JTextField();
	private static final JTextField latLongLocator = new JTextField();
	private static final JTextField altitude = new JTextField();
	private static final JTextField rfRecieverDescription = new JTextField();

	private static BufferedImage CISLogo;
	private static ImageModule logoPanel;

	public Home() {
		super();

		GridBagConstraintsWrapper gbc = new GridBagConstraintsWrapper();
		gbc.setFill(GridBagConstraintsWrapper.BOTH);

		this.setLayout(new GridBagLayout());
		this.setBackground(CustomColors.BACKGROUND4);

		// CIS Logo
		try {
			CISLogo = ImageIO.read(new File("resources/images/CISClubLogo.png"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		logoPanel = new ImageModule(CISLogo);
		logoPanel.setBackground(CustomColors.BACKGROUND1);
		this.add(logoPanel, gbc.setLocation(0, 0).setSize(2, 1).setWeight(1.0, 1.0).setInsets(5, 5, 5, 5));

		// options Panel
		optionsPanel.setLayout(new GridBagLayout());
		optionsPanel.setBackground(CustomColors.BACKGROUND2);
		optionsPanel.add(new TitleLabel("Options"), gbc.setLocation(0, 0).setSize(3, 1).setWeight(0.0, 0.0));

		filesAndDirectories.setLayout(new GridBagLayout());
		filesAndDirectories.setBackground(CustomColors.BACKGROUND1);
		filesAndDirectories.add(new TitleLabel("Files and Directories"), gbc.setLocation(1, 0).setSize(3, 1));
		filesAndDirectories.add(new JLabel("Home Directory"), gbc.setLocation(0, 2).setSize(1, 1));

		filesAndDirectories.add(homeDirectory, gbc.setLocation(1, 3).setSize(1, 1).setWeight(1.0, 0.0));
		filesAndDirectories.add(new JLabel("Log Files Directory:"),
				gbc.setLocation(0, 3).setSize(1, 1).setWeight(0.0, 0.0));
		filesAndDirectories.add(new JLabel(System.getProperty("user.dir")), gbc.setLocation(1, 2).setSize(2, 1));
		optionsPanel.add(filesAndDirectories, gbc.setLocation(0, 1).setSize(1, 1));

		groundStationParams.setLayout(new GridBagLayout());
		groundStationParams.setBackground(CustomColors.BACKGROUND1);
		groundStationParams.add(new TitleLabel("Ground Station Params", SwingConstants.CENTER),
				gbc.setLocation(0, 0).setSize(2, 1).setWeight(1.0, 0.0));
		groundStationParams.add(new JLabel("GroundStation Name: "), gbc.setLocation(0, 1).setSize(1, 1));
		groundStationParams.add(new JLabel("Longitude: "), gbc.setLocation(0, 2));
		groundStationParams.add(new JLabel("Latittude:"), gbc.setLocation(0, 3));
		groundStationParams.add(groundstationName, gbc.setLocation(1, 1));
		groundStationParams.add(longitude, gbc.setLocation(1, 2));
		groundStationParams.add(latittude, gbc.setLocation(1, 3));
		groundStationParams.add(new JLabel("Lat Long gives Locator:"), gbc.setLocation(0, 4));
		groundStationParams.add(latLongLocator, gbc.setLocation(1, 4).setWeight(0.0, 0.0));
		groundStationParams.add(new JLabel("Altitude(m):"), gbc.setLocation(0, 5));
		groundStationParams.add(altitude, gbc.setLocation(1, 5));
		groundStationParams.add(new JLabel("Rf-Reciever Description"), gbc.setLocation(0, 6));
		groundStationParams.add(rfRecieverDescription, gbc.setLocation(1, 6));

		optionsPanel.add(groundStationParams, gbc.setLocation(0, 2).setSize(3, 1).setWeight(0.0, 0.0));
		this.add(optionsPanel, gbc.setLocation(2, 0).setSize(1, 5).setWeight(0.0, 1.0).setInsets(5, 5, 5, 5));

		// JFileChooser chooser = new JFileChooser();
		// FileNameExtensionF2lter filter = new FileNameExtensionFilter(
		// "JPG & GIF Images", "jpg", "gif");
		// chooser.setFileFilter(filter);
		// int returnVal = chooser.showOpenDialog(null);
		// if(returnVal == JFileChooser.APPROVE_OPTION) {
		// System.out.println("You chose to open this file: " +
		// chooser.getSelectedFile().getName());
		// }

		// Information Panel

		aboutPanel.setLayout(new GridBagLayout());
		aboutPanel.setBackground(CustomColors.BACKGROUND2);
		aboutPanel.add(aboutPanelHeader, gbc.setLocation(0, 1).setSize(2, 1).setWeight(1.0, 0.0));
		aboutPanel.add(aboutPanelBody, gbc.setLocation(0, 2).setSize(2, 1));
		aboutPanelBody.setText("-Body-\n\n\n\n\n\n\n\n\n");
		this.add(aboutPanel, gbc.setLocation(0, 1).setSize(1, 1).setWeight(1.0, 0.0));

		// Patch Notes
		patchNotesPanel.setLayout(new GridBagLayout());
		patchNotesPanel.setBackground(CustomColors.BACKGROUND2);
		patchNotesPanel.add(patchNotesHeaderText, gbc.setLocation(0, 3).setSize(2, 1).setWeight(1.0, 0.0));

		File file = new File("resources/PatchNotes");
		BufferedReader br = null;
		try {
			br = new BufferedReader(new FileReader(file));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		String tempLine;
		try {
			while ((tempLine = br.readLine()) != null) {
				patchNotesBodyText.append(tempLine + "\n");
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		patchNotesPanel.add(patchNotesScroll, gbc.setLocation(0, 4).setSize(2, 1).setWeight(1.0, 0.25).setInsets(5, 5, 5, 5));
		this.add(patchNotesPanel, gbc.setLocation(0, 3).setSize(2, 1).setWeight(1.0, 0.0));

		this.setBackground(CustomColors.BACKGROUND2);
		this.repaint();

	}

	@Override
	public void updateUIScaling(UIScale uiScale) {
		Font font = Fonts.BODY_24;
		Font bodyfont = Fonts.BODY_16;
		int scrollBarSize = 0;

		switch (uiScale) {
		default:
		case SCALE_100:
			font = Fonts.BODY_24;
			bodyfont = Fonts.BODY_16;
			scrollBarSize = 20;
			break;
		case SCALE_150:
			font = Fonts.BODY_36;
			bodyfont = Fonts.BODY_24;
			scrollBarSize = 30;
			break;
		case SCALE_200:
			font = Fonts.BODY_48;
			bodyfont = Fonts.BODY_32;
			scrollBarSize = 40;
			break;
		case SCALE_300:
			font = Fonts.BODY_48;
			bodyfont = Fonts.BODY_48;
			scrollBarSize = 60;
			break;
		case SCALE_75:
			font = Fonts.BODY_16;
			bodyfont = Fonts.BODY_12;
			scrollBarSize = 15;
			break;
		}

		UIManager.put("ScrollBar.width", scrollBarSize);
		patchNotesScroll.setVerticalScrollBar(patchNotesScroll.createVerticalScrollBar());
		patchNotesScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

		for (Component component : this.getComponents()) {
			if (component instanceof TitleLabel) {
				component.setFont(font);
				component.setBackground(CustomColors.BACKGROUND1);
				component.setForeground(Color.white);

			} else if (component instanceof JTextArea) {
				component.setFont(bodyfont);
				component.setBackground(CustomColors.BACKGROUND1);
			}
			for (Component subComponent : ((Container) component).getComponents()) {
				if (subComponent instanceof TitleLabel) {
					subComponent.setFont(font);
					subComponent.setBackground(CustomColors.BACKGROUND1);
					subComponent.setForeground(Color.white);
				} else if (subComponent instanceof JLabel) {
					subComponent.setFont(bodyfont);
				} else if (subComponent instanceof JTextArea) {
					subComponent.setFont(bodyfont);
					subComponent.setBackground(CustomColors.BACKGROUND1);
					((JTextComponent) subComponent).setEditable(false);
					subComponent.setVisible(true);
				}
				for (Component subsubComponent : ((Container) subComponent).getComponents()) {
					if (subsubComponent instanceof TitleLabel) {
						subsubComponent.setFont(font);
						subsubComponent.setBackground(CustomColors.BACKGROUND1);
						subsubComponent.setForeground(Color.white);
					} else if (subsubComponent instanceof JLabel) {
						subsubComponent.setFont(bodyfont);
					} else if (subsubComponent instanceof JTextArea) {
						subsubComponent.setFont(bodyfont);
						subsubComponent.setBackground(CustomColors.BACKGROUND1);
						((JTextComponent) subsubComponent).setEditable(false);
						subsubComponent.setVisible(true);
					} else if (subsubComponent instanceof JTextField) {
						subsubComponent.setFont(bodyfont);

					}
				}
			}
		}
	}
}
