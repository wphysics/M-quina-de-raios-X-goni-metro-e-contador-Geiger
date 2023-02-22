// Projéto: Contador Geiger Arduino.
// Autor: Wenderson Rodrigues Fialho da Silva.
// Data: 18/12/2021
// Email: wenderson.f@ufv.br

#define LOG_PERIOD 500                         //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 1000                         //Maximum logging period without modifying this sketch

unsigned long c;                                //variable for GM Tube events
unsigned long cpm;                              //variable for CPM
unsigned int multiplier;                        //variable for calculation CPM in this sketch
unsigned long previousMillis;                   //Essa variável é atualizada constantemente conforme o geiger regista o CPM

void setup()
{
  Serial.begin(115200);
}
void loop()
{ 
  int sinal_geiger = analogRead(A0);                                     // valor em bits
  float sinal_geiger_volt = (2.20 - (sinal_geiger*(3.30/1023)));         // imprime o valor da tensão dos pulsos invertido e normalizado
  int sinal_bits = 674 - sinal_geiger;                                   // valor em bits invertido e normalizado
  if (sinal_bits > 15) {
    c++;
    //Serial.print(c);
    //Serial.print("  ");
    //Serial.println(sinal_bits);
  }
  
  //////////////////////////////////////////////////////// Determina as CPM
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;                               // calculating multiplier, depend on your log period
  unsigned long currentMillis = millis();                             // armazena o valor do tempo atual
  
  // Verifica se é o momento de registra CPM, ou seja, se a diferença entre o tempo atual e a última vez que registou,
  // é maior que o intervalo que foi definido para o evento acontecer.
  
  if(currentMillis - previousMillis > LOG_PERIOD){                    //Verifica se o intervalo já foi atingido
    previousMillis = currentMillis;                                   //Armazena o valor da ultima vez que foi registrado CPM
    cpm = c*multiplier;
    Serial.println(cpm);
    c = 0;
  }
  ////////////////////////////////////////////////////////
  //Serial.println(sinal_bits);
  //delayMicroseconds(500);
  }
