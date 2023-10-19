#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>

// Define el pin al que está conectado el sensor DS18B20
#define ONE_WIRE_BUS 4  // Cambia esto al pin GPIO que estás utilizando
#define base 5  //pin activacion transistor
// Inicializa el bus OneWire
OneWire oneWire(ONE_WIRE_BUS);
bool state = true;
// Inicializa el objeto DallasTemperature
DallasTemperature sensors(&oneWire);

// Objeto para generar la interrupción cada 1 segundo
Ticker timer;
Ticker timer2;
int t=0;
int numero_aleatorio =58545654;

void readTemperature() {
  // Realiza una lectura de temperatura
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0); // Único sensor en el bus
  t=map(temperatureC,0,50,0,1024);
  // Imprime la temperatura en el monitor serial
  Serial.print(millis()/1000);
  Serial.print(",");
  Serial.print(temperatureC);
  Serial.print(",");
  Serial.println(state);
 }

void chanceout(){
  state = !state;
  digitalWrite(base,state);
  
  srand(analogRead(A0));
  // Genera un número aleatorio entre 1 y 7
  numero_aleatorio = rand() % 6 + 1;

  timer2.once(numero_aleatorio*60, chanceout);

}
void setup() {
  pinMode(base,OUTPUT);
  digitalWrite(base,state);
  // Configura la comunicación serie para la salida de datos
  Serial.begin(115200);

  // Inicializa el sensor DS18B20
  sensors.begin();
  
  srand(analogRead(A0));
  // Genera un número aleatorio entre 2 y 6
  numero_aleatorio = rand() % 5 + 2;

  // Configura el temporizador para ejecutar la función readTemperature cada 1 segundo
  timer.attach(1.0, readTemperature);
  //timer2.attach(numero_aleatorio*60, chanceout);
  timer2.once(numero_aleatorio*60, chanceout);
}

void loop() {
  // El código en el bucle principal se ejecutará en paralelo con las interrupciones
  // No es necesario incluir un bucle aquí
}
