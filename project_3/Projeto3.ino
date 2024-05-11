#include <Ethernet.h>
#include <ArduinoHttpClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;
HttpClient cliente = HttpClient(client,"api.thingspeak.com",80);
const int temperatura = A0;
const int fotoresistor = A1;

void setup() {

    Serial.begin(9600);
    while (!Serial)    {}

    Ethernet.begin(mac);   

    Serial.println("");
    Serial.println("-----------------------------------------------");
    Serial.print("Endereco IP: ");
    Serial.println(Ethernet.localIP());
    Serial.println("-----------------------------------------------");
    Serial.println();
   
    delay(1000);

}

void loop() {

    char payload[80];
    int luminosity = map((analogRead(fotoresistor)), 0, 1023, 0, 100);
	  float tempC = ((((analogRead(temperatura)) * 5.0 / 1023.0) - 0.5) * 100.0);
    Serial.println();   
    Serial.print("A0: ");
    Serial.println(luminosity);    
    Serial.print("A1: ");
    Serial.println(tempC);
    Serial.println();  

    // Substituir sua_chave_escrita pela chave de escrita do canal - Write API Key.
    // sprintf(payload,"/update?api_key=sua_chave_escrita&field1=%d&field2=%d&field3=%d&field4=%d",luminosity,tempC,v3,v4);
	sprintf(payload,"/update?api_key=5YN6HJHSXDUKZQDJ&field1=%d&field2=%d",luminosity,tempC);

    Serial.println("Requisicao: GET");
    cliente.get(payload);

    int statusCode = cliente.responseStatusCode();
    String response = cliente.responseBody();

    Serial.print("Codigo de Status: ");
    Serial.println(statusCode);
    Serial.print("Retorno: ");
    Serial.println(response);
    Serial.println();
  
    delay(15000);

}