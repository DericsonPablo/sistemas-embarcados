#define led_frente 14
#define led_tras 13
#define led_direita 15
#define led_esquerda 12

int frente = LOW;
int traz = LOW;
int esquerda = LOW;
int direita = LOW;

void setup() {
  pinMode(led_frente, OUTPUT);
  pinMode(led_tras, OUTPUT);
  pinMode(led_direita, OUTPUT);
  pinMode(led_esquerda, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    if(c == '1') frente = HIGH;
    if(c == '2') tras = HIGH;
    if(c == '3') esquerda = HIGH;
    if(c == '4') direita = HIGH;
    if(c == '5'){
      frente = HIGH;
      direita = HIGH;
    }
    if(c == '6'){
      tras = HIGH;
      direita = HIGH;
    }
    if(c == '7'){
      tras = HIGH;
      esquerda = HIGH;
    }
    if(c == '8'){
      frente = HIGH;
      esquerda = HIGH;
    }
    if(c == '9'){
      frente = HIGH;
      direita = HIGH;
      tras = HIGH;
    }
    if(c == 'a'){
      direita = HIGH;
      tras = HIGH;
      esquerda = HIGH;
    }
    if(c == 'b'){
      tras = HIGH;
      esquerda = HIGH;
      frente = HIGH;
    }
    if(c == 'c'){
      esquerda = HIGH;
      frente = HIGH;
      direita = HIGH;
    }
    if(c == 'd'){
      digitalWrite(led_frente, HIGH);
      delay(50);
      digitalWrite(led_frente, LOW);
      digitalWrite(led_direita, HIGH);
      delay(50);
      digitalWrite(led_direita, LOW);
      digitalWrite(led_tras, HIGH);
      delay(50);
      digitalWrite(led_tras, LOW);
      digitalWrite(led_esquerda, HIGH);
      delay(50);
      digitalWrite(led_esquerda, LOW);
      delay(50);
    }
    if(c == '0'){
      frente = LOW;
      tras = LOW;
      direita = LOW;
      esquerda = LOW;
    }
  }
  digitalWrite(led_frente, frente);
  digitalWrite(led_tras, tras);
  digitalWrite(led_direita, direita);
  digitalWrite(led_esquerda, esquerda);
  
}
