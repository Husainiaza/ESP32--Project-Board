
  lcd.print("BUZ OFF RLY 1 ON");  
  delay (1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,LOW);
  lcd.setCursor(0,0);
  lcd.print("BUZ OFF RLY 2 ON");  
  delay (1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(relay01,HIGH);
  digitalWrite(relay02,HIGH);
  lcd.setCursor(0,0);
  lcd.print("BUZ OFF RLY  OFF"); 
  delay (1000);

  display.clearDisplay();

  int dataVar = analogRead(sensorVar);
  Serial.print("Data Var: ");
  Serial.println(dataVar);

  int dataLDR = analogRead(sensorLDR);
  Serial.print("Data LDR: ");
  Serial.println(dataLDR);

  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println(" IoT Project Board");
  display.setCursor(0,10);
  display.println("K. Komuniti Sbg Jaya");
  display.setCursor(0,25);
  display.print("BACAAN SUHU :");
  display.print(tempC,1);
   
  display.setCursor(0,35);
  display.print("BACAAN Var :");
  display.print(dataVar);

  display.setCursor(0,45);
  display.print("BACAAN Var :");
  display.print(dataLDR);

  display.display();  
}
