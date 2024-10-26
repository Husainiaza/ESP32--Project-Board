// Suhu
## Ujikaji sensor ds18b20
```
  sensor.requestTemperatures();       // send the command to get temperatures
  tempC = sensor.getTempCByIndex(0);  // read temperature in °C

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
```
  
