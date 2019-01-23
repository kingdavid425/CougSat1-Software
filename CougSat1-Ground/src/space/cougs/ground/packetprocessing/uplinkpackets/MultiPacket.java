package space.cougs.ground.packetprocessing.uplinkpackets;

import java.io.File;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class MultiPacket {

    private static String filePath = "O:\\Nate\\Documents\\GitHub\\Packet Encoder\\packets";

    public void MultiPacket() {

        File file = new File(filePath);

        if (!file.exists()) {
            System.out.printf("Decoding packet file not found: %s\n", filePath);
            return;
        }
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();

        File folder = new File(dtf.format(now));
        folder.mkdir();

        // FileInputStream inFile = new FileInputStream(file);
        // ---------------------------------------------------------------------
        // Address
        // Total Length
        // MP Serial Number
        // File Name
        // Packet Serial Number
        // CRC-32 4 bytes
        // Data...

        // Address
        // Packet Serial Number
        // Length of Packet
        // Data...

        // int length = inFile.available();

        // inFile.close();

    }
}
