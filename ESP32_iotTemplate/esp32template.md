// Suhu
## Ujikaji sensor ds18b20
```
  sensors.requestTemperatures();       // send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);  // read temperature in °C

  Serial.print("Temperature: ");
  Serial.print(tempC);    // print the temperature in °C
  Serial.print("°C");
```

````
            sensors.requestTemperatures();       // send the command to get temperatures
            float tempC = sensors.getTempCByIndex(0);  // read temperature in °C

            Serial.print("Temperature: ");
            Serial.print(tempC);    // print the temperature in °C
            Serial.print("°C");

            dtostrf(dataVar, 1, 2, varPotString);
            client.publish("husaini/suhu", varPotString);

````
