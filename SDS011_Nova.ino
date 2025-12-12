void SDS011_Setup(){
  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  Serial.println(sds.setActiveReportingMode().toString()); // ensures sensor is in 'active' reporting mode
  Serial.println(sds.setContinuousWorkingPeriod().toString()); // ensures sensor has continuous working period - default but not recommended
}

void SDS011_Loop_Print(){
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);

    // if you want to just print the measured values, you can use toString() method as well
    Serial.println(pm.toString());
  } else {
    // notice that loop delay is set to 0.5s and some reads are not available
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }
}


String SDS011_Return_MP25(){
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
    return String(pm.pm25);
  
  } else {
    delay(500);
    pm = sds.readPm();
    if (pm.isOk()) {
      return String(pm.pm25);
    } else {
      String state = ("Could not read values PM2.5 from sensor, reason: ");
      Serial.print(state);
      Serial.println(pm.statusToString());
      return "0";
    }
  }
}

String SDS011_Return_MP10(){
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
    delay(500);
    return String(pm.pm10);
  } else {
    delay(500);
    pm = sds.readPm();
    if (pm.isOk()) {
      return String(pm.pm10);
    } else {
      String state = ("Could not read values PM10 from sensor, reason: ");
      Serial.print(state);
      Serial.println(pm.statusToString());
      return "0";
    }
  }
}