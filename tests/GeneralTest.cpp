#include <iostream>
#include "../FuzzyRule.h"
#include "../FuzzyComposition.h"
#include "../Fuzzy.h"
#include "../FuzzyRuleConsequent.h"
#include "../FuzzyOutput.h"
#include "../FuzzyInput.h"
#include "../FuzzyIO.h"
#include "../FuzzySet.h"
#include "../FuzzyRuleAntecedent.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Instanciando um objeto da biblioteca
    Fuzzy* fuzzy = new Fuzzy();

    FuzzySet* seco = new FuzzySet(0, 0 , 0, 42.5);
    FuzzySet* humedo = new FuzzySet(37.5, 60, 60, 82.5);
    FuzzySet* encharcado = new FuzzySet(77.5, 100, 100, 100);

    FuzzySet* frio = new FuzzySet(-5, -5, -5, 12.5);
    FuzzySet* templado = new FuzzySet(7.5, 17.5, 17.5, 27.5);
    FuzzySet* calor = new FuzzySet(22.5, 45, 45, 45);

    FuzzySet* nada = new FuzzySet(0, 0, 0, 0);
    FuzzySet* muyPoco = new FuzzySet(0, 0, 0, 5.5);
    FuzzySet* poco = new FuzzySet(4.5, 7.5, 7.5, 10.5);
    FuzzySet* medio = new FuzzySet(9.5, 12.5, 12.5, 15.5);
    FuzzySet* bastante = new FuzzySet(14.5, 17.5, 17.5, 20.5);
    FuzzySet* mucho = new FuzzySet(19.5, 22.5, 22.5, 25.5);
    FuzzySet* muchisimo = new FuzzySet(24.5, 30, 30, 30);

    // FuzzyInput
    FuzzyInput* humedad = new FuzzyInput(1);
    humedad->addFuzzySet(seco);
    humedad->addFuzzySet(humedo);
    humedad->addFuzzySet(encharcado);

    fuzzy->addFuzzyInput(humedad);

    FuzzyInput* temperatura = new FuzzyInput(2);
    temperatura->addFuzzySet(frio);
    temperatura->addFuzzySet(templado);
    temperatura->addFuzzySet(calor);

    fuzzy->addFuzzyInput(temperatura);

    FuzzyOutput* tiempo = new FuzzyOutput(1);

    tiempo->addFuzzySet(nada);
    tiempo->addFuzzySet(muyPoco);
    tiempo->addFuzzySet(poco);
    tiempo->addFuzzySet(medio);
    tiempo->addFuzzySet(bastante);
    tiempo->addFuzzySet(mucho);
    tiempo->addFuzzySet(muchisimo);

    fuzzy->addFuzzyOutput(tiempo);

    // ############## Rule 1
    FuzzyRuleAntecedent* humedadSecoandTemperaturaFrio = new FuzzyRuleAntecedent();
    humedadSecoandTemperaturaFrio->joinWithAND(seco, frio);

    FuzzyRuleConsequent* thenMedio_1 = new FuzzyRuleConsequent();
    thenMedio_1->addOutput(medio);

    FuzzyRule* fuzzyRule1 = new FuzzyRule(1, humedadSecoandTemperaturaFrio, thenMedio_1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // ############## Rule 2
    FuzzyRuleAntecedent* humedadHumedoandTemperaturaFrio = new FuzzyRuleAntecedent();
    humedadHumedoandTemperaturaFrio->joinWithAND(humedo, frio);

    FuzzyRuleConsequent* thenMuyPoco_1 = new FuzzyRuleConsequent();
    thenMuyPoco_1->addOutput(muyPoco);

    FuzzyRule* fuzzyRule2 = new FuzzyRule(2, humedadHumedoandTemperaturaFrio, thenMuyPoco_1);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // ############## Rule 3
    FuzzyRuleAntecedent* humedadEncharcadoandTemperaturaFrio = new FuzzyRuleAntecedent();
    humedadEncharcadoandTemperaturaFrio->joinWithAND(encharcado, frio);

    FuzzyRuleConsequent* thenNada_1 = new FuzzyRuleConsequent();
    thenNada_1->addOutput(nada);

    FuzzyRule* fuzzyRule3 = new FuzzyRule(3, humedadEncharcadoandTemperaturaFrio, thenNada_1);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // ############## Rule 4
    FuzzyRuleAntecedent* humedadSecoandTemperaturaTemplado = new FuzzyRuleAntecedent();
    humedadSecoandTemperaturaTemplado->joinWithAND(seco, templado);

    FuzzyRuleConsequent* thenBastante = new FuzzyRuleConsequent();
    thenBastante->addOutput(bastante);

    FuzzyRule* fuzzyRule4 = new FuzzyRule(4, humedadSecoandTemperaturaTemplado, thenBastante);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // ############## Rule 5
    FuzzyRuleAntecedent* humedadHumedoandTemperaturaTemplado = new FuzzyRuleAntecedent();
    humedadHumedoandTemperaturaTemplado->joinWithAND(humedo, templado);

    FuzzyRuleConsequent* thenMedio_2 = new FuzzyRuleConsequent();
    thenMedio_2->addOutput(medio);

    FuzzyRule* fuzzyRule5 = new FuzzyRule(5, humedadHumedoandTemperaturaTemplado, thenMedio_2);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // ############## Rule 6
    FuzzyRuleAntecedent* humedadEncharcadoandTemperaturaTemplado = new FuzzyRuleAntecedent();
    humedadEncharcadoandTemperaturaTemplado->joinWithAND(encharcado, templado);

    FuzzyRuleConsequent* thenMuyPoco_2 = new FuzzyRuleConsequent();
    thenMuyPoco_2->addOutput(muyPoco);

    FuzzyRule* fuzzyRule6 = new FuzzyRule(6, humedadEncharcadoandTemperaturaTemplado, thenMuyPoco_2);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // ############## Rule 7
    FuzzyRuleAntecedent* humedadSecoandTemperaturaCalor = new FuzzyRuleAntecedent();
    humedadSecoandTemperaturaCalor->joinWithAND(seco, calor);

    FuzzyRuleConsequent* thenMucho = new FuzzyRuleConsequent();
    thenMucho->addOutput(mucho);

    FuzzyRule* fuzzyRule7 = new FuzzyRule(7, humedadSecoandTemperaturaCalor, thenMucho);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // ############## Rule 8
    FuzzyRuleAntecedent* humedadHumedoandTemperaturaCalor = new FuzzyRuleAntecedent();
    humedadHumedoandTemperaturaCalor->joinWithAND(humedo, calor);

    FuzzyRuleConsequent* thenMuchisimo = new FuzzyRuleConsequent();
    thenMuchisimo->addOutput(muchisimo);

    FuzzyRule* fuzzyRule8 = new FuzzyRule(8, humedadHumedoandTemperaturaCalor, thenBastante);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // ############## Rule 9
    FuzzyRuleAntecedent* humedadEncharcadoandTemperaturaCalor = new FuzzyRuleAntecedent();
    humedadEncharcadoandTemperaturaCalor->joinWithAND(encharcado, calor);

    FuzzyRuleConsequent* thenNada_2 = new FuzzyRuleConsequent();
    thenNada_2->addOutput(nada);

    FuzzyRule* fuzzyRule9 = new FuzzyRule(9, humedadEncharcadoandTemperaturaCalor, thenNada_2);
    fuzzy->addFuzzyRule(fuzzyRule9);

    float entrada_humedad = 81.19;
    float entrada_temperatura = 26.14;

    fuzzy->setInput(1, entrada_humedad);
    fuzzy->setInput(2, entrada_temperatura);

    fuzzy->fuzzify();    

    std::cout << "\n####################"<< std::endl;
    std::cout << "Entradas:"<< std::endl;

    std::cout << "\tHumedad: " << entrada_humedad << std::endl;
    std::cout << "\t\tPertinencias: " << seco->getPertinence() << ", " << humedo->getPertinence() << ", " << encharcado->getPertinence() << std::endl;

    std::cout << "\tTemperatura: " << entrada_temperatura << std::endl;
    std::cout << "\t\tPertinencias: " << frio->getPertinence() << ", " << templado->getPertinence() << ", " << calor->getPertinence() << std::endl;

    std::cout << "Reglas Activadas:" << std::endl;

    for (int i = 1; i < 10; i++) {
        bool wasTheRulleFired = fuzzy->isFiredRule(i);
        if (wasTheRulleFired == 1) {
            std::cout << "\tRegla: " << i << std::endl;
        }    
    }

    float output1 = fuzzy->defuzzify(1);

    std::cout << "Salida:" << std::endl;

    std::cout << "\tRiego: " << output1 << std::endl;
    std::cout << "\t\tPertinencias: " << nada->getPertinence() << ", " << muyPoco->getPertinence() << ", " << poco->getPertinence() << ", " << medio->getPertinence() << ", " << bastante->getPertinence() << ", " << mucho->getPertinence() << ", " << muchisimo->getPertinence() << std::endl;

    return 0;
}