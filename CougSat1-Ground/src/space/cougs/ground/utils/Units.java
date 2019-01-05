package space.cougs.ground.utils;

import java.text.SimpleDateFormat;
import java.util.TimeZone;

public final class Units {
  public static double rawToVoltage(long raw) {
    return raw * 100.0e-6; // 100 µV/LSB
  }

  public static double rawToCurrent(long raw) {
    return raw * 150.0e-6; // 100 µA/LSB;
  }

  public static double rawToPower(long raw) {
    return raw * 250.0e-6; // 250 µW/LSB;
  }

  public static int rawToEnergy(long raw) {
    return (int) (raw * 500); // 500J/LSB
  }

  public static double rawToGeographicCoordinate(long raw) {
    return (int) raw * 10.0e-6 / 60.0; // 10 µmin/LSB
  }

  public static long rawToTime(long raw) {
    return raw;
  }

  public static int rawToTemp(long raw) {
    return (byte) raw;
  }

  public static double rawToAngle(long raw) {
    return raw * 360.0 / (1 << 16); // 2^16 = 2Pi
  }

  public static double rawToDecibels(long raw) {
    return (short) raw * 0.001; // 1 mdB/LSB
  }

  public static int rawToFrequency(long raw) {
    return (int) raw * 100; // 100 Hz/LSB
  }

  public static double rawToDataRate(long raw) {
    return Math.pow(raw, 2); // 1 sqrt(bps)/LSB
  }

  public static String timeToString(long time) {
    SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
    format.setTimeZone(TimeZone.getTimeZone("UTC"));
    return format.format(time * 1000);
  }

  public static String toBytes(long raw) {
    int unit = 1000;
    if (raw < unit)
      return raw + "B";
    int exp = (int) (Math.log(raw) / Math.log(unit));
    char pre = ("kMGTPE").charAt(exp - 1);
    return String.format("%.1f %sB", raw / Math.pow(unit, exp), pre);
  }

  public static String toCurrent(double raw) {
    int unit = 1000;
    int i = 0;
    if (Math.abs(raw) > 1)
      return String.format("%.2f A", raw);
    else if (raw == 0)
      return String.format("0 A");
    for (i = 0; raw * Math.pow(unit, i + 1) < unit; i++)
      ;
    char pre = "mµn".charAt(i - 1);
    return String.format("%.2f %sA", raw * Math.pow(unit, i), pre);
  }

  public static String toVoltage(double raw) {
    int unit = 1000;
    int i = 0;
    if (Math.abs(raw) > 1)
      return String.format("%.2f V", raw);
    else if (raw == 0)
      return String.format("0 V");
    for (i = 0; raw * Math.pow(unit, i + 1) < unit; i++)
      ;
    System.out.println(raw);
    System.out.println(i);
    char pre = "mµn".charAt(i - 1);

    return String.format("%.2f %sV", raw * Math.pow(unit, i), pre);
  }
}