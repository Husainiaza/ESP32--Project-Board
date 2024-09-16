void sensorCahaya(){

  int dataAnalogLDR = analogRead(34);
  Serial.println(dataAnalogLDR);

  float volts = dataAnalogLDR * 3.3 / 4095.0; // Convert reading to voltage 
  float amps = volts / 10000.0; // Convert to amps across 10K resistor 
  float microamps = amps * 1000000.0; // Convert amps to microamps 
  float lux = microamps * 2.0; // 2 microamps = 1 lux
  Serial.println(lux);

  lcd.setCursor(0,3);
  lcd.print("BACAAN LDR :");
  lcd.setCursor(12,3);
  lcd.print(dataAnalogLDR);
  
  dtostrf(dataAnalogLDR, 1, 2, varPotString);
  client.publish("iotkksj/cahaya", varPotString);

 
}

void sensorSuhu(){
  DS18B20.requestTemperatures();       // send the command to get temperatures
  float tempC = DS18B20.getTempCByIndex(0);  // read temperature in °C
  float tempF = tempC * 9 / 5 + 32; // convert °C to °F

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  ");  // separator between °C and °F
  Serial.print(tempF);    // print the temperature in °F
  Serial.println("°F");

  lcd.setCursor(0,2);
  lcd.print("BACAAN SUHU:");
  lcd.setCursor(12,2);
  lcd.print(tempC);

  dtostrf(tempC, 1, 2, varPotString);
  client.publish("iotkksj/suhuc", varPotString);

  dtostrf(tempF, 1, 2, varPotString);
  client.publish("iotkksj/suhuf", varPotString);

}