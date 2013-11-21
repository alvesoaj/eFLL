#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

// variables to take x number of readings and then average them
// to remove the jitter/noise from the DYP-ME007 sonar readings
const int numOfReadings = 10;
// number of readings to take/ items in the array
int readings[numOfReadings];
// stores the distance readings in an array
int arrayIndex = 0;
// arrayIndex of the current item in the array
int total = 0;
// stores the cumlative total
int averageDistance = 0;
// DYP-ME007 echo pin (digital 5)
int echoPin = 5;
// DYP-ME007 trigger pin (digital 4)
int initPin = 4;
// stores the pulse in Micro Seconds
unsigned long pulseTime = 0;
// variable for storing the distance (cm)
unsigned long dist = 0;
// Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();

void setup(){
  Serial.begin(9600);
  
  // set init pin as output
  pinMode(initPin, OUTPUT);
  // set echo pin as input
  pinMode(echoPin, INPUT);
  // create array loop to iterate over every item in the array
  for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  // Criando o FuzzyInput distancia
  FuzzyInput* distance = new FuzzyInput(1);
  // Criando os FuzzySet que compoem o FuzzyInput distancia 
  FuzzySet* small = new FuzzySet(0, 20, 20, 40); // Distancia pequena
  distance->addFuzzySet(small); // Adicionando o FuzzySet small em distance
  FuzzySet* safe = new FuzzySet(30, 50, 50, 70); // Distancia segura
  distance->addFuzzySet(safe); // Adicionando o FuzzySet safe em distance
  FuzzySet* big = new FuzzySet(60, 80, 80, 80); // Distancia grande
  distance->addFuzzySet(big); // Adicionando o FuzzySet big em distance
  
  fuzzy->addFuzzyInput(distance); // Adicionando o FuzzyInput no objeto Fuzzy
  
  // Criando o FuzzyOutput velocidade
  FuzzyOutput* velocity = new FuzzyOutput(1);
  // Criando os FuzzySet que compoem o FuzzyOutput velocidade 
  FuzzySet* slow = new FuzzySet(0, 10, 10, 20); // Velocidade lenta
  velocity->addFuzzySet(slow); // Adicionando o FuzzySet slow em velocity
  FuzzySet* average = new FuzzySet(10, 20, 30, 40); // Velocidade normal
  velocity->addFuzzySet(average); // Adicionando o FuzzySet average em velocity
  FuzzySet* fast = new FuzzySet(30, 40, 40, 50); // Velocidade alta
  velocity->addFuzzySet(fast); // Adicionando o FuzzySet fast em velocity
  
  fuzzy->addFuzzyOutput(velocity); // Adicionando o FuzzyOutput no objeto Fuzzy
  
  //-------------------- Montando as regras Fuzzy
  // FuzzyRule "SE distancia = pequena ENTAO velocidade = lenta"
  FuzzyRuleAntecedent* ifDistanceSmall = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceSmall->joinSingle(small); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocitySlow = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocitySlow->addOutput(slow);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenVelocitySlow); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule01); // Adicionando o FuzzyRule ao objeto Fuzzy
  
  // FuzzyRule "SE distancia = segura ENTAO velocidade = normal"
  FuzzyRuleAntecedent* ifDistanceSafe = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceSafe->joinSingle(safe); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocityAverage = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocityAverage->addOutput(average);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenVelocityAverage); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule02); // Adicionando o FuzzyRule ao objeto Fuzzy
  
  // FuzzyRule "SE distancia = grande ENTAO velocidade = alta"
  FuzzyRuleAntecedent* ifDistanceBig = new FuzzyRuleAntecedent(); // Instanciando um Antecedente para a expresso
  ifDistanceBig->joinSingle(big); // Adicionando o FuzzySet correspondente ao objeto Antecedente
  FuzzyRuleConsequent* thenVelocityFast = new FuzzyRuleConsequent(); // Instancinado um Consequente para a expressao
  thenVelocityFast->addOutput(fast);// Adicionando o FuzzySet correspondente ao objeto Consequente
  // Instanciando um objeto FuzzyRule
  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenVelocityFast); // Passando o Antecedente e o Consequente da expressao
  fuzzy->addFuzzyRule(fuzzyRule03); // Adicionando o FuzzyRule ao objeto Fuzzy
}

void loop(){
  // send 10 microsecond pulse
  digitalWrite(initPin, HIGH);
  // wait 10 microseconds before turning off
  delayMicroseconds(10);
  // stop sending the pulse
  digitalWrite(initPin, LOW);
  
  // Look for a return pulse, it should be high as the pulse goes low-high-low
  pulseTime = pulseIn(echoPin, HIGH);
  // Distance = pulse time / 58 to convert to cm.
  dist = pulseTime/58;
  // subtract the last distance
  total = total - readings[arrayIndex];
  // add distance reading to array
  readings[arrayIndex] = dist;
  // add the reading to the total
  total = total + readings[arrayIndex];
  
  arrayIndex = arrayIndex + 1;
  // go to the next item in the array
  // At the end of the array (10 items) then start again
  if (arrayIndex >= numOfReadings) {
    arrayIndex = 0;
  }
  // calculate the average distance
  averageDistance = total / numOfReadings;
  // print out the average distance to the debugger
  
  fuzzy->setInput(1, averageDistance);
  
  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);
  
  Serial.print("Distancia: ");
  Serial.print(averageDistance);
  Serial.print("Velocidade: ");
  Serial.println(output);
  // wait 100 milli seconds before looping again
  delay(100);
}