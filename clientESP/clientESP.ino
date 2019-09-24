#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* senha = "senha";
const String servidor = "192.168.43.20"; // seu servidor
String path;

int pinoBotao = 0;
int botao = 0;         // variable for reading the pushbotao status

void setup () {
  pinMode(pinoBotao, INPUT);

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
  Serial.println("Use este endereço para conectar ao ESP8266");
  Serial.println();
}

void loop() {
  WiFiClient client;
  //Le o valor da porta analogica
  int leitura = analogRead(pinoBotao);
  //Testa o valor da resistencia do circuito -> leitura porta analogica
  //Os valores adotados dependem dos valores dos resistores utilileituraados
  //Recomenda-se adotar uma faixa de variacao dos valores obtidos
  if (leitura > 536 && leitura < 556) botao = 1; //btnEsquerda
  else if (leitura > 353 && leitura < 373) botao = 2; //btnCima
  else if (leitura > 263 && leitura < 283) botao = 3; //btnDireita
  else if (leitura > 210 && leitura < 230) botao = 4; //btnBaixo
  else if (leitura > 174 && leitura < 194) botao = 5; //btnCimaDireita
  else if (leitura > 149 && leitura < 169) botao = 6; //btnCimaEsquerda
  else if (leitura > 130 && leitura < 145) botao = 7; //btnBaixoDireita
  else if (leitura > 101 && leitura < 129) botao = 8; //btnBaixoEsquerda
  else botao = 0;
  Serial.println(analogRead(pinoBotao));

  if (!client.connect(servidor, 80)) {
    Serial.println("Conexao falhou!");
    return;
  }
  //Verifica qual a acao a ser executada em funcao do botao pressionado
  switch (botao) {
    case 1:
      path = "btnEsquerda";
      break;
    case 2:
      path = "btnCima";
      break;
    case 3:
      path = "btnDireita";
      break;
    case 4:
      path = "btnBaixo";
      break;
    case 5:
      path = "btnCimaDir";
      break;
    case 6:
      path = "btnCimaEsq";
      break;
    case 7:
      path = "btnBaixoDir";
      break;
    case 8:
      path = "btnBaixoEsq";
      break;

    default:
      path = "btnHome";
  }
  // Envia a requisicao ao servidor com a acao desejada -> path
  client.print(String("GET /") + path + " HTTP/1.1\r\n" +
               "Host: " + servidor + "\r\n" +
               "Connection: close\r\n" +
               "\r\n");
  client.stop();
  delay(100); //Tempo para não sobrecarregar o servidor
}
