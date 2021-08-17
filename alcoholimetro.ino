//ALCOHOLIMETRO - Aldo Danilo Vargas Esquivel

// declaramos las variables iniciales y los pines del arduino

int sensor = A0;
int read; // en esta variable se guarda la lectura del sensor, para evitar leerla multiples veces en una vuelta del loop.

// valores establecidos como los limites de los niveles que obtiene el sensor
int high = 400;
int medium = 300;

int buzzer = 7;

int G = 11, Y = 10, R = 9; // declaramos las variables de los leds para usarlos de manera más sencilla
int leds[] = {G,Y,R}; // los juntamos para usarlos en conjunto, declararlos en el setup() en una sóla función

// FUNCIONES

// showValue() muestra las lecturas del sensor por medio de los leds, en 3 niveles, verde = bajo, amarillo = medio, rojo = alto
    // en alto tambien activa el buzzer
void showValue(int V){
    for(int l = 0; l < 3; l++){
        digitalWrite(leds[l], 0);
    }

    digitalWrite(V, 1);
    if(V == R){
      alarm();
    }
}


// alarm() es la alarma que sonará al llegar al nivel máximo de alcohol
void alarm(){
  digitalWrite(buzzer, 1);
  delay(80);
  digitalWrite(buzzer, 0);
  delay(80);
  digitalWrite(buzzer, 1);
  delay(80);
  digitalWrite(buzzer, 0);
  delay(80);
  digitalWrite(buzzer, 1);
  delay(80);
  digitalWrite(buzzer, 0);
  delay(80);
  digitalWrite(buzzer, 1);
  delay(80);
  digitalWrite(buzzer, 0);
  delay(300);
}

// getAlcohol() obtiene el nivel de alcohol y los muestra con  la función showValue() o el monitor serial
void getAlcohol(){
    read  = analogRead(sensor);

    if( read <= medium ){
        Serial.println("Continue");
        showValue(G);
    } else if(read > medium && read < high){
        Serial.println("Precaucion");
        showValue(Y);
    } else{
        Serial.println("Detenido");
        showValue(R);
    }
}

// start() sólo es una animación que se muestra al encender el arduino
void start(){
    digitalWrite(G, 1);
    delay(100);
    digitalWrite(Y, 1);
    delay(100);
    digitalWrite(R, 1);
    delay(100);
    digitalWrite(G, 0);
    delay(100);
    digitalWrite(Y, 0);
    delay(100);
    digitalWrite(R, 0);

    delay(500);
}

void setup()
{
	pinMode(sensor, INPUT);

  pinMode(buzzer, OUTPUT);

    for(int l = 0; l < 3; l++){
        pinMode(leds[l], OUTPUT);
    }

    start();

    Serial.begin(9600);
}

// ¿El loop() queda muy sencillo no?
void loop()
{
	read = analogRead(sensor);
    Serial.println(read);
    getAlcohol();
    delay(500);
}
