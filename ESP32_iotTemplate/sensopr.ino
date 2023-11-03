void sensorVar(){

  int dataVar = analogRead(34);
  
  dtostrf(dataVar, 1, 2, varPotString);
  client.publish("kksbj/suhu", varPotString);
}
