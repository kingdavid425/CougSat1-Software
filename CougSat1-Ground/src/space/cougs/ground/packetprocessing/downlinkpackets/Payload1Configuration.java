package space.cougs.ground.packetprocessing.downlinkpackets;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import space.cougs.ground.satellites.CougSat;
import space.cougs.ground.utils.CISErrors;
import space.cougs.ground.utils.FileUtils;

public class Payload1Configuration extends DownlinkPacket { // camera multipacket
  public static final int ID = 0x14;
  private static int LENGTH = 0x00;
  private int buf = 0;
  private long serial = 0;

  @Override
  public CISErrors decodePacket(File file, CougSat satellite) {
    FileInputStream inFile = null;
    FileOutputStream outFile = null;
    CISErrors result = CISErrors.SUCCESS;
    try {
      inFile = new FileInputStream(file);

      inFile.read(); // Recipient/header/command ID - gets handled in Packet Header
      LENGTH = inFile.read(); // packet length

      serial = FileUtils.readNextBytes(inFile, 2); // get serial Number

      outFile = new FileOutputStream(String.format("%l", serial));

      while (LENGTH > 0) {
        buf = inFile.read();

        outFile.write(buf);
        outFile.close();


        LENGTH--;
      }
    } catch (IOException e) {
      System.out.printf("Failed to decode telemetry from %s\n", file.getAbsolutePath());
      e.printStackTrace();
    }
    return result;
  }
}