/*
ADC => ANALOG TO DIGITAL CONVERTER

CONVERTE A TENSÃO DOS PINOS DE 10 A 15 EM UM VALOR DECIMAL A PARTIR DE UMA VARIÁVEL DE 10 BITS

analogRead(pino) ===> 0 a 1023
0.00V ===> 0
5.00V ===> 1023

2 ^ 2 = 4
2 ^ 3 = 8
2 ^ 4 = 16
...
2 ^ 10 = 1024

*/

// Mapeie os pinos a partir da análise do diagrama no Tinkercad
#define led_vm 12
#define led_am 8 
#define led_vd 6
#define led_az 2

// Declare aqui suas variáveis globais
int valorAnalog; // ===> analogRead() ===> 0 a 1023
float tensao_0_5V, tensao_0_60V;

void setup() {
  Serial.begin(9600);
  
  // Configure os modos dos pinos
  pinMode(led_vm, OUTPUT);
  pinMode(led_am, OUTPUT);
  pinMode(led_vd, OUTPUT);
  pinMode(led_az, OUTPUT);

  // Adicione qualquer outra configuração que seu exercício precisar
  Serial.println("======================= MEDIDOR DE TENSÃO DA 1CCPQ =======================");
}

void loop() {
  medidor();
  comparador();
}

void medidor() {
  valorAnalog = analogRead(A0); // 0 a 1023
  // 0 ===> 0.00V
  // 1023 ===> 5.00V
  tensao_0_5V = map(valorAnalog, 0, 1023, 0, 500) / 100.0;
  tensao_0_60V = map(valorAnalog, 0, 1023, 0, 6000) / 100.0;

  Serial.print("ADC: ");
  Serial.println(valorAnalog);
  Serial.print("VALOR DA TENSAO DA STRING SOLAR (0 - 60V): ");
  Serial.println(tensao_0_60V);
}

void comparador() {
  digitalWrite(led_az, LOW);
  digitalWrite(led_vd, LOW);
  digitalWrite(led_am, LOW);
  digitalWrite(led_vm, LOW);

  // LED AZUL ===> GERAÇÃO ACIMA DE 55V
  if (tensao_0_60V > 55) {
    digitalWrite(led_az, HIGH);
  }
  // LED VERDE ===> GERAÇÃO ENTRE 40V E 55V
  // operador AND => &&
  else if (tensao_0_60V > 40 && tensao_0_60V < 55) {
    digitalWrite(led_vd, HIGH);
  }
  // LED AMARELO ===> GERAÇÃO ENTRE 30V E 40V
  else if (tensao_0_60V > 30 && tensao_0_60V < 40) {
    digitalWrite(led_am, HIGH);
  }
  // LED VERMELHO ===> GERAÇÃO ABAIXO DE 30V
  else {
    digitalWrite(led_vm, HIGH);
  }
}

