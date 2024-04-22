/* Bancos de Dados Aplicados à Internet das Coisas (IoT)
Professor: José Luiz Zem
Pós Graduação em Engenharia e Administração de Sistemas de Banco de Dados – UNICAMP.

Vinícius Henrique de Oliveira

*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* Pinos dos sensores e do LCD */
const int SENSOR_TEMPERATURA_PINO = A0; //Termômetro de temperatura TMP36 no pino A0
const int PINO_TRIG = 2;   //Ativador Trig do sensor de distância HC-SR04 no pino digital 2
const int PINO_ECHO = 3;   //Receptor Echo do sensor de distância HC-SR04 no pino digital 3
const int SENSOR_LUMINOSIDADE_PINO = A1;   //Sensor de brilho LDR no pino A1
const int SENSOR_UMIDADE_SOLO_PINO = A2; //Sensor de hidratação do solo no pino A2

//Display LCD com o endereço I2C
LiquidCrystal_I2C lcd(0x20, 16, 2); //Endereço I2C do display LCD

void setup() {
  //Display LCD
  lcd.init();
  lcd.backlight();

  //Configurar pinos dos sensores
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
}

void loop() {
  //Informações (stats)
  displayStaticInfo();

  //Leitura dos sensores e exibição no LCD
  float temperaturaC = readTemperature();
  float temperaturaF = temperaturaC * 9.0 / 5.0 + 32; //Convertendo para ºF
  float distanciaCm = readDistance();
  float distanciaPol = distanciaCm * 0.393701; //Convertendo para polegadas
  int luminosidade = readLuminosidade();
  int umidadeSolo = readUmidadeSolo();

  //Apresentar leituras dos sensores
  displayTemperatura(temperaturaC, temperaturaF);
  displayDistancia(distanciaCm, distanciaPol);
  displayLuminosidade(luminosidade);
  displayUmidadeSolo(umidadeSolo);
}

//Exibição para o LCD
void displayTemperatura(float temperaturaC, float temperaturaF) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperaturaC, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperaturaF, 1);
  lcd.print(" F");
  delay(2000);
}

void displayDistancia(float distanciaCm, float distanciaPol) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distanciaCm, 1);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(distanciaPol, 1);
  lcd.print(" in");
  delay(3000); //3s
}

void displayLuminosidade(int luminosidade) {
  int valorBruto = analogRead(SENSOR_LUMINOSIDADE_PINO); //Valor bruto do sensor LDR

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR: ");
  lcd.print(valorBruto);

  lcd.setCursor(0, 1);
  lcd.print("Brilho: ");
  lcd.print(luminosidade);
  lcd.print(" %");
  delay(3000); //3s
}


void displayUmidadeSolo(int umidadeSolo) {
  int valorBruto = analogRead(SENSOR_UMIDADE_SOLO_PINO); // Capturar o valor bruto do sensor de umidade do solo

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Higrometro: ");
  lcd.print(valorBruto);

  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(umidadeSolo);
  lcd.print(" %");
  delay(3000); //3s
}


//Ler os valores dos sensores
float readTemperature() {
  int valorSensor = analogRead(SENSOR_TEMPERATURA_PINO);
  float voltagem = valorSensor * 5.0 / 1023.0;
  float temperaturaC = (voltagem - 0.5) * 100.0;
  return temperaturaC;
}

float readDistance() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  long duracao = pulseIn(PINO_ECHO, HIGH);
  float distanciaCm = duracao * 0.034 / 2;
  return distanciaCm;
}

int readLuminosidade() {
  int valorSensor = analogRead(SENSOR_LUMINOSIDADE_PINO);
  return map(valorSensor, 0, 1023, 0, 100); //Mapear o valor de 0-1023 para 0-100%
}

int readUmidadeSolo() {
  int valorSensor = analogRead(SENSOR_UMIDADE_SOLO_PINO);
  return map(valorSensor, 0, 1023, 0, 100); //Mapear o valor de 0-1023 para 0-100%
}

void displayStaticInfo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Faculdade Tech");
  lcd.setCursor(0, 1);
  lcd.print("Unicamp");
  delay(3000); //3s
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bancos de Dados");
  lcd.setCursor(0, 1);
  lcd.print("Aplicado à IoT");
  delay(3000); //3s
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Componentes:");
  lcd.setCursor(0, 1);
  lcd.print("Vinícius H.O");
  delay(2000); //3s
}


