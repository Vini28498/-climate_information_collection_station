/* Projeto: Bancos de Dados Aplicados à Internet das Coisas (IoT)
Professor: José Luiz Zem
Pós-Graduação em Engenharia e Administração de Sistemas de Banco de Dados – UNICAMP.

Autor: Vinícius Henrique de Oliveira */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <NewPing.h> 

LiquidCrystal_I2C display(0x27, 16, 2); 
NewPing ultrasonicSensor(10, 9); 

const int temperaturePin = A0; 
const int lightSensorPin = A3; 

void setup() {
  display.init(); 
  display.backlight(); 
  Serial.begin(9600); 
}

void loop() {
  //
  display.clear();
  display.setCursor(0, 0);
  display.print("Faculdade  Tech");
  display.setCursor(0, 1);
  display.print("Unicamp");
  delay(2000);

  //Etapa 2
  display.clear();
  display.setCursor(0, 0);
  display.print("Banco de Dados");
  display.setCursor(0, 1);
  display.print("Aplicados a IoT");
  delay(2000);

  //Etapa 3

  display.clear();
  display.setCursor(0, 0);
  display.print("Projeto 2");
  delay(2000);

  //Etapa 4
  display.clear();
  display.setCursor(0, 0);
  display.print("Componentes");
  display.setCursor(0, 1);
  display.print("Vinicius H O");
  delay(2000);

    display.clear();
    display.setCursor(0, 0);
    display.print("Recuperar dados");
    display.setCursor(0, 1);
    display.print("dos sensores");
    delay(2000); 

  float tempCelsius = analogRead(temperaturePin) * 0.48828125; 
  float tempFahrenheit = (tempCelsius * 9.0 / 5.0) + 32.0; 
  display.clear();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(tempCelsius);
  display.print("C");
  display.setCursor(0, 1);
  display.print("Temp: ");
  display.print(tempFahrenheit);
  display.println("F");
  delay(2000);

  // Etapa 5
  int distanceCm = ultrasonicSensor.ping_cm(); 
  float distanceInches = distanceCm * 0.393701; 
  display.clear();
  display.setCursor(0, 0);
  display.print("Dist: ");
  display.print(distanceCm);
  display.print("cm");
  display.setCursor(0, 1);
  display.print("Dist: ");
  display.print(distanceInches);
  display.println("in");
  delay(2000);

  // Etapa 6
  int lightSensorValue = analogRead(lightSensorPin); 
  int luminosityPercentage = map(lightSensorValue, 0, 1023, 0, 100); 
  display.clear();
  display.setCursor(0, 0);
  display.print("LDR: ");
  display.print(lightSensorValue);
  display.setCursor(0, 1);
  display.print("Luminos: ");
  display.print(luminosityPercentage);
  display.print("%");
  delay(2000);
}
