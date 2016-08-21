#include <iostream>
#include "../../FuzzyRule.h"
#include "../../FuzzyComposition.h"
#include "../../Fuzzy.h"
#include "../../FuzzyRuleConsequent.h"
#include "../../FuzzyOutput.h"
#include "../../FuzzyInput.h"
#include "../../FuzzyIO.h"
#include "../../FuzzySet.h"
#include "../../FuzzyRuleAntecedent.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Instanciando um objeto da biblioteca
    Fuzzy* fuzzy = new Fuzzy();

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

    for(int dist = 0; dist < 100; dist++){
        fuzzy->setInput(1, dist);

        fuzzy->fuzzify();

        float output = fuzzy->defuzzify(1);
        cout << "Entrada: " << dist << ", Saida: " << output << endl;
    }
    return 0;
}