#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configuracoes iniciais
#define pinoBotao 0
#define pinoLED   BUILTIN_LED
#define pinoIR    2
#define pinoAnalogico A0


unsigned long tempoAnteriorDebounce = 0;
unsigned long debounceDelay = 50;   // tempo do debounce time; aumentar se saida oscila

const char* ssid = "ssid";
const char* senha = "senha";

const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topico = "Sistemas.Embarcados.Topico.SANSUNG";

const char* payload;

WiFiClient clienteWIFI;
PubSubClient clienteMQTT(clienteWIFI);

String strMacAddress;
char macAddress[6];

// Conexão ao servidor MQTT:
void conectaMQTT() {
  // Loop ate conexao
  while (!clienteMQTT.connected()) {
    Serial.print("Aguardando conexao MQTT...");
    if (clienteMQTT.connect(macAddress)) {
      Serial.println("MQTT conectado");
      //faz subscribe automatico no topico
      clienteMQTT.subscribe(topico);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" tentando reconectar em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(pinoAnalogico, INPUT);
  pinMode(pinoLED, OUTPUT);
  

  Serial.begin(9600);

  // Conexao to Wi-Fi
  Serial.print("Conectando ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Mostra IP do servidor
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.RSSI());
  Serial.println("Use este endereço para conectar ao ESP8266");
  Serial.println();
  strMacAddress = WiFi.macAddress();
  strMacAddress.toCharArray(macAddress, 6);
  // Conexao com broker no servidor MQTT
  clienteMQTT.setServer(mqtt_server, 1883);

}

void loop() {
  if (!clienteMQTT.connected()) {
    conectaMQTT();
  }
  clienteMQTT.loop();
  
  if ((millis() - tempoAnteriorDebounce) > 200) {
    int resist = analogRead(pinoAnalogico);
    if(resist > 198 && resist < 239) payload = "Vol_UP";
    else if(resist > 252 && resist < 293) payload = "Vol_DOWN";
    else if(resist > 342 && resist < 383) payload = "Canal_UP";
    else if(resist > 525 && resist < 563) payload = "Canal_DOWN";
    else payload = "Erro"; 

    if(payload != "Erro"){
      Serial.println(payload);
      clienteMQTT.publish(topico, payload);
      digitalWrite(pinoLED, LOW);
    }
    tempoAnteriorDebounce = millis();
  }
  digitalWrite(pinoLED, HIGH);
}


 

