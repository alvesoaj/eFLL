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
	Fuzzy* fuzzy = new Fuzzy();

    FuzzySet* t1 = new FuzzySet(0, 0, 0, 2);
    // FuzzySet* t2 = new FuzzySet(-1.5, 7.5, 7.5, 16.5);  // Antes
    FuzzySet* t2 = new FuzzySet(1.5, 7.5, 7.5, 16.5);  // después
    FuzzySet* t3 = new FuzzySet(3.5, 12.5, 12.5, 21.5);
    FuzzySet* t4 = new FuzzySet(9.5, 18.5, 18.5, 27.5);
    FuzzySet* t5 = new FuzzySet(14.5, 23.5, 23.5, 32.5);
    // FuzzySet* t6 = new FuzzySet(24.5, 37, 37, 37); // Antes
    FuzzySet* t6 = new FuzzySet(24.5, 37, 39, 39); // después - La temperatura puedes ser major que 37 grados

    FuzzySet* mbaja = new FuzzySet(0, 0, 0, 212);
    FuzzySet* baja = new FuzzySet(0, 212, 212, 425);
    FuzzySet* media = new FuzzySet(212, 425, 425, 638);
    FuzzySet* alta = new FuzzySet(425, 637, 637, 850);
    // FuzzySet* malta = new FuzzySet(637, 850, 850, 850); // Antes
    FuzzySet* malta = new FuzzySet(637, 850, 900, 900); // después - Las puertas analogicas de Arduino varian de 0 a 1024

    FuzzySet* v10 = new FuzzySet(0, 0, 0, 10);
    FuzzySet* v9 = new FuzzySet(0, 10, 10, 20);
    FuzzySet* v8 = new FuzzySet(10, 20, 20, 30);
    FuzzySet* v7 = new FuzzySet(20, 30, 30, 40);
    FuzzySet* v6 = new FuzzySet(30, 40, 40, 50);
    FuzzySet* v5 = new FuzzySet(40, 50, 50, 60); 
    FuzzySet* v4 = new FuzzySet(50, 60, 60, 70); 
    FuzzySet* v3 = new FuzzySet(60, 70, 70, 80);
    FuzzySet* v2 = new FuzzySet(70, 80, 80, 90);
    FuzzySet* v1 = new FuzzySet(80, 90, 90, 100);
    FuzzySet* v0 = new FuzzySet(90, 100, 100, 100);

    // FuzzyInput
    FuzzyInput* temperatura = new FuzzyInput(1);
    temperatura->addFuzzySet(t1);
    temperatura->addFuzzySet(t2);
    temperatura->addFuzzySet(t3);
    temperatura->addFuzzySet(t4);
    temperatura->addFuzzySet(t5);
    temperatura->addFuzzySet(t6);
    fuzzy->addFuzzyInput(temperatura);

    // FuzzyInput
    FuzzyInput* luminosidad = new FuzzyInput(2);
    luminosidad->addFuzzySet(mbaja);
    luminosidad->addFuzzySet(baja);
    luminosidad->addFuzzySet(media);
    luminosidad->addFuzzySet(alta);
    luminosidad->addFuzzySet(malta);
    fuzzy->addFuzzyInput(luminosidad);

    // FuzzyOutput
    FuzzyOutput* voltaje = new FuzzyOutput(1);
    voltaje->addFuzzySet(v10);  
    voltaje->addFuzzySet(v9);  
    voltaje->addFuzzySet(v8);  
    voltaje->addFuzzySet(v7); 
    voltaje->addFuzzySet(v6);  
    voltaje->addFuzzySet(v5);  
    voltaje->addFuzzySet(v4);  
    voltaje->addFuzzySet(v3); 
    voltaje->addFuzzySet(v2);  
    voltaje->addFuzzySet(v1);  
    voltaje->addFuzzySet(v0);
    fuzzy->addFuzzyOutput(voltaje);

    // Building FuzzyRule1
    FuzzyRuleAntecedent* iftemperaturat1Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat1Andluminosidadmbaja->joinWithAND(t1, mbaja);
    FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule1 = new FuzzyRule(1, iftemperaturat1Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule2
    FuzzyRuleAntecedent* iftemperaturat1Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat1Andluminosidadbaja->joinWithAND(t1, baja);
    // FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule2 = new FuzzyRule(2, iftemperaturat1Andluminosidadbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule3
    FuzzyRuleAntecedent* iftemperaturat1Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat1Andluminosidadmedia->joinWithAND(t1, media);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule3 = new FuzzyRule(3, iftemperaturat1Andluminosidadmedia, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule4
    FuzzyRuleAntecedent* iftemperaturat1Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat1Andluminosidadalta->joinWithAND(t1, alta);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule4 = new FuzzyRule(4, iftemperaturat1Andluminosidadalta, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // Building FuzzyRule5
    FuzzyRuleAntecedent* iftemperaturat1Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat1Andluminosidadmalta->joinWithAND(t1, malta);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule5 = new FuzzyRule(5, iftemperaturat1Andluminosidadmalta, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // Building FuzzyRule6
    FuzzyRuleAntecedent* iftemperaturat2Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat2Andluminosidadmbaja->joinWithAND(t2, mbaja);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule6 = new FuzzyRule(6, iftemperaturat2Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // Building FuzzyRule7
    FuzzyRuleAntecedent* iftemperaturat2Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat2Andluminosidadbaja->joinWithAND(t2, baja);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule7 = new FuzzyRule(7, iftemperaturat2Andluminosidadbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // Building FuzzyRule8
    FuzzyRuleAntecedent* iftemperaturat2Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat2Andluminosidadmedia->joinWithAND(t2, media);
    FuzzyRuleConsequent* thenvoltajev1 = new FuzzyRuleConsequent();
    thenvoltajev1->addOutput(v1);
    FuzzyRule* fuzzyRule8 = new FuzzyRule(8, iftemperaturat2Andluminosidadmedia, thenvoltajev1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // Building FuzzyRule9
    FuzzyRuleAntecedent* iftemperaturat2Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat2Andluminosidadalta->joinWithAND(t2, alta);
    FuzzyRuleConsequent* thenvoltajev2 = new FuzzyRuleConsequent();
    thenvoltajev2->addOutput(v2);
    FuzzyRule* fuzzyRule9 = new FuzzyRule(9, iftemperaturat2Andluminosidadalta, thenvoltajev2);
    fuzzy->addFuzzyRule(fuzzyRule9);

    // Building FuzzyRule10
    FuzzyRuleAntecedent* iftemperaturat2Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat2Andluminosidadmalta->joinWithAND(t2, malta);
    FuzzyRuleConsequent* thenvoltajev3 = new FuzzyRuleConsequent();
    thenvoltajev3->addOutput(v3);
    FuzzyRule* fuzzyRule10 = new FuzzyRule(10, iftemperaturat2Andluminosidadmalta, thenvoltajev3);
    fuzzy->addFuzzyRule(fuzzyRule10);

    // Building FuzzyRule11
    FuzzyRuleAntecedent* iftemperaturat3Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat3Andluminosidadmbaja->joinWithAND(t3, mbaja);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule11 = new FuzzyRule(11, iftemperaturat3Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule11);

    // Building FuzzyRule12
    FuzzyRuleAntecedent* iftemperaturat3Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat3Andluminosidadbaja->joinWithAND(t3, baja);
    //FuzzyRuleConsequent* thenvoltajev1 = new FuzzyRuleConsequent();
    //thenvoltajev1->addOutput(v1);
    FuzzyRule* fuzzyRule12 = new FuzzyRule(12, iftemperaturat3Andluminosidadbaja, thenvoltajev1);
    fuzzy->addFuzzyRule(fuzzyRule12);

    // Building FuzzyRule13
    FuzzyRuleAntecedent* iftemperaturat3Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat3Andluminosidadmedia->joinWithAND(t3, media);
    //FuzzyRuleConsequent* thenvoltajev2 = new FuzzyRuleConsequent();
    //thenvoltajev2->addOutput(v2);
    FuzzyRule* fuzzyRule13 = new FuzzyRule(13, iftemperaturat3Andluminosidadmedia, thenvoltajev2);
    fuzzy->addFuzzyRule(fuzzyRule13);

    // Building FuzzyRule14
    FuzzyRuleAntecedent* iftemperaturat3Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat3Andluminosidadalta->joinWithAND(t3, alta);
    FuzzyRuleConsequent* thenvoltajev4 = new FuzzyRuleConsequent();
    thenvoltajev4->addOutput(v4);
    FuzzyRule* fuzzyRule14 = new FuzzyRule(14, iftemperaturat3Andluminosidadalta, thenvoltajev4);
    fuzzy->addFuzzyRule(fuzzyRule14);

    // Building FuzzyRule15
    FuzzyRuleAntecedent* iftemperaturat3Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat3Andluminosidadmalta->joinWithAND(t3, malta);
    FuzzyRuleConsequent* thenvoltajev6 = new FuzzyRuleConsequent();
    thenvoltajev6->addOutput(v6);
    FuzzyRule* fuzzyRule15 = new FuzzyRule(15, iftemperaturat3Andluminosidadmalta, thenvoltajev6);
    fuzzy->addFuzzyRule(fuzzyRule15);

    // Building FuzzyRule16
    FuzzyRuleAntecedent* iftemperaturat4Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat4Andluminosidadmbaja->joinWithAND(t4, mbaja);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule16 = new FuzzyRule(16, iftemperaturat4Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule16);

    // Building FuzzyRule17
    FuzzyRuleAntecedent* iftemperaturat4Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat4Andluminosidadbaja->joinWithAND(t4, baja);
    //FuzzyRuleConsequent* thenvoltajev2 = new FuzzyRuleConsequent();
    //thenvoltajev2->addOutput(v2);
    FuzzyRule* fuzzyRule17 = new FuzzyRule(17, iftemperaturat4Andluminosidadbaja, thenvoltajev2);
    fuzzy->addFuzzyRule(fuzzyRule17);

    // Building FuzzyRule18
    FuzzyRuleAntecedent* iftemperaturat4Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat4Andluminosidadmedia->joinWithAND(t4, media);
    FuzzyRuleConsequent* thenvoltajev5 = new FuzzyRuleConsequent();
    thenvoltajev5->addOutput(v5);
    FuzzyRule* fuzzyRule18 = new FuzzyRule(18, iftemperaturat4Andluminosidadmedia, thenvoltajev5);
    fuzzy->addFuzzyRule(fuzzyRule18);

    // Building FuzzyRule19
    FuzzyRuleAntecedent* iftemperaturat4Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat4Andluminosidadalta->joinWithAND(t4, alta);
    FuzzyRuleConsequent* thenvoltajev7 = new FuzzyRuleConsequent();
    thenvoltajev7->addOutput(v7);
    FuzzyRule* fuzzyRule19 = new FuzzyRule(19, iftemperaturat4Andluminosidadalta, thenvoltajev7);
    fuzzy->addFuzzyRule(fuzzyRule19);

    // Building FuzzyRule20
    FuzzyRuleAntecedent* iftemperaturat4Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat4Andluminosidadmalta->joinWithAND(t4, malta);
    FuzzyRuleConsequent* thenvoltajev9 = new FuzzyRuleConsequent();
    thenvoltajev9->addOutput(v9);
    FuzzyRule* fuzzyRule20 = new FuzzyRule(20, iftemperaturat4Andluminosidadmalta, thenvoltajev9);
    fuzzy->addFuzzyRule(fuzzyRule20);

    // Building FuzzyRule21
    FuzzyRuleAntecedent* iftemperaturat5Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat5Andluminosidadmbaja->joinWithAND(t5, mbaja);
    //FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    //thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule21 = new FuzzyRule(21, iftemperaturat5Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule21);

    // Building FuzzyRule22
    FuzzyRuleAntecedent* iftemperaturat5Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat5Andluminosidadbaja->joinWithAND(t5, baja);
    // FuzzyRuleConsequent* thenvoltajev3 = new FuzzyRuleConsequent();
    //thenvoltajev3->addOutput(v3);
    FuzzyRule* fuzzyRule22 = new FuzzyRule(22, iftemperaturat5Andluminosidadbaja, thenvoltajev3);
    fuzzy->addFuzzyRule(fuzzyRule22);

    // Building FuzzyRule23
    FuzzyRuleAntecedent* iftemperaturat5Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat5Andluminosidadmedia->joinWithAND(t5, media);
    // FuzzyRuleConsequent* thenvoltajev6 = new FuzzyRuleConsequent();
    // thenvoltajev6->addOutput(v6);
    FuzzyRule* fuzzyRule23 = new FuzzyRule(23, iftemperaturat5Andluminosidadmedia, thenvoltajev6);
    fuzzy->addFuzzyRule(fuzzyRule23);

    // Building FuzzyRule24
    FuzzyRuleAntecedent* iftemperaturat5Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat5Andluminosidadalta->joinWithAND(t5, alta);
    FuzzyRuleConsequent* thenvoltajev8 = new FuzzyRuleConsequent();
    thenvoltajev8->addOutput(v8);
    FuzzyRule* fuzzyRule24 = new FuzzyRule(24, iftemperaturat5Andluminosidadalta, thenvoltajev8);
    fuzzy->addFuzzyRule(fuzzyRule24);

    // Building FuzzyRule25
    FuzzyRuleAntecedent* iftemperaturat5Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat5Andluminosidadmalta->joinWithAND(t5, malta);
    FuzzyRuleConsequent* thenvoltajev10 = new FuzzyRuleConsequent();
    thenvoltajev10->addOutput(v10);
    FuzzyRule* fuzzyRule25 = new FuzzyRule(25, iftemperaturat5Andluminosidadmalta, thenvoltajev10);
    fuzzy->addFuzzyRule(fuzzyRule25);

    // Building FuzzyRule26
    FuzzyRuleAntecedent* iftemperaturat6Andluminosidadmbaja = new FuzzyRuleAntecedent();
    iftemperaturat6Andluminosidadmbaja->joinWithAND(t6, mbaja);
    // FuzzyRuleConsequent* thenvoltajev0 = new FuzzyRuleConsequent();
    // thenvoltajev0->addOutput(v0);
    FuzzyRule* fuzzyRule26 = new FuzzyRule(26, iftemperaturat6Andluminosidadmbaja, thenvoltajev0);
    fuzzy->addFuzzyRule(fuzzyRule26);

    // Building FuzzyRule27
    FuzzyRuleAntecedent* iftemperaturat6Andluminosidadbaja = new FuzzyRuleAntecedent();
    iftemperaturat6Andluminosidadbaja->joinWithAND(t6, baja);
    //FuzzyRuleConsequent* thenvoltajev4 = new FuzzyRuleConsequent();
    // thenvoltajev4->addOutput(v4);
    FuzzyRule* fuzzyRule27 = new FuzzyRule(27, iftemperaturat6Andluminosidadbaja, thenvoltajev4);
    fuzzy->addFuzzyRule(fuzzyRule27);

    // Building FuzzyRule28
    FuzzyRuleAntecedent* iftemperaturat6Andluminosidadmedia = new FuzzyRuleAntecedent();
    iftemperaturat6Andluminosidadmedia->joinWithAND(t6, media);
    //FuzzyRuleConsequent* thenvoltajev7 = new FuzzyRuleConsequent();
    //thenvoltajev7->addOutput(v7);
    FuzzyRule* fuzzyRule28 = new FuzzyRule(28, iftemperaturat6Andluminosidadmbaja, thenvoltajev7);
    fuzzy->addFuzzyRule(fuzzyRule28);

    // Building FuzzyRule29
    FuzzyRuleAntecedent* iftemperaturat6Andluminosidadalta = new FuzzyRuleAntecedent();
    iftemperaturat6Andluminosidadalta->joinWithAND(t6, alta);
    //FuzzyRuleConsequent* thenvoltajev9 = new FuzzyRuleConsequent();
    //thenvoltajev9->addOutput(v9);
    FuzzyRule* fuzzyRule29 = new FuzzyRule(29, iftemperaturat6Andluminosidadalta, thenvoltajev9);
    fuzzy->addFuzzyRule(fuzzyRule29);

    // Building FuzzyRule30
    FuzzyRuleAntecedent* iftemperaturat6Andluminosidadmalta = new FuzzyRuleAntecedent();
    iftemperaturat6Andluminosidadmalta->joinWithAND(t6, malta);
    //FuzzyRuleConsequent* thenvoltajev10 = new FuzzyRuleConsequent();
    //thenvoltajev10->addOutput(v10);
    FuzzyRule* fuzzyRule30 = new FuzzyRule(30, iftemperaturat6Andluminosidadmalta, thenvoltajev10);
    fuzzy->addFuzzyRule(fuzzyRule30);

    int lm35Values[10] = {200, 25, 60, 17, 9, 10, 37, 34, 40, 74};
    int ldrValues[10] = {1000, 100, 376, 34, 198, 276, 200, 250, 600, 177};

    for(int i=0; i < 1; i++){
        std::cout << "\nIteracion " << i << std::endl;

        int celsius = lm35Values[i];
        int grados = (5.0 * celsius * 100) / 1024.0;

        fuzzy->setInput(1, grados);
        fuzzy->setInput(2, ldrValues[i]);

        fuzzy->fuzzify();
        float output = fuzzy->defuzzify(1);

        std::cout << "temperatura: " << t1->getPertinence() << ", " << t2->getPertinence() << ", " << t3->getPertinence() << ", " << t4->getPertinence() << ", " << t5->getPertinence() << ", " << t6->getPertinence() << std::endl;

        std::cout << "luminosidad: " << mbaja->getPertinence() << ", " << baja->getPertinence() << ", " << media->getPertinence() << ", " << alta->getPertinence() << ", " << malta->getPertinence() << std::endl;

        std::cout << "voltaje V10-V0: " << v10->getPertinence() << ", " << v9->getPertinence() << ", " << v8->getPertinence() << ", " << v7->getPertinence() << ", " << v6->getPertinence() << ", " << v5->getPertinence() << ", " << v4->getPertinence() << ", " << v3->getPertinence() << ", " << v4->getPertinence() << ", " << v1->getPertinence() << ", " << v0->getPertinence() << std::endl;

        std::cout << "Output: " << output << std::endl;

        std::cout << "reglas 1-15 :  " << fuzzy->isFiredRule(1) << ", " << fuzzy->isFiredRule(2) << ", " << fuzzy->isFiredRule(3) << ", " << fuzzy->isFiredRule(4) << ", " << fuzzy->isFiredRule(5) << ", " << fuzzy->isFiredRule(6) << ", " << fuzzy->isFiredRule(7) << ", " << fuzzy->isFiredRule(8) << ", " << fuzzy->isFiredRule(9) << ", " << fuzzy->isFiredRule(10) << ", " << fuzzy->isFiredRule(11) << ", " << fuzzy->isFiredRule(12) << ", " << fuzzy->isFiredRule(13) << ", " << fuzzy->isFiredRule(14) << ", " << fuzzy->isFiredRule(15) << std::endl;

        std::cout << "reglas 16-30 :  " << fuzzy->isFiredRule(16) << ", " << fuzzy->isFiredRule(17) << ", " << fuzzy->isFiredRule(18) << ", " << fuzzy->isFiredRule(19) << ", " << fuzzy->isFiredRule(20) << ", " << fuzzy->isFiredRule(21) << ", " << fuzzy->isFiredRule(22) << ", " << fuzzy->isFiredRule(23) << ", " << fuzzy->isFiredRule(24) << ", " << fuzzy->isFiredRule(25) << ", " << fuzzy->isFiredRule(26) << ", " << fuzzy->isFiredRule(27) << ", " << fuzzy->isFiredRule(28) << ", " << fuzzy->isFiredRule(29) << ", " << fuzzy->isFiredRule(30) << std::endl;
    }

	return 0;
}