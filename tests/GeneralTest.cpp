#include <iostream>
#include <fstream>
#include "../Fuzzy.h"

using namespace std;

int main(int argc, char *argv[])
{
    Fuzzy *fuzzy = new Fuzzy();

    // FuzzyInput
    FuzzyInput *temperature = new FuzzyInput(1);

    FuzzySet *veryLow = new FuzzySet(-5, -5, 0, 15);
    temperature->addFuzzySet(veryLow);
    FuzzySet *low = new FuzzySet(10, 20, 20, 30);
    temperature->addFuzzySet(low);
    FuzzySet *high = new FuzzySet(25, 30, 30, 35);
    temperature->addFuzzySet(high);
    FuzzySet *veryHigh = new FuzzySet(30, 45, 50, 50);
    temperature->addFuzzySet(veryHigh);

    fuzzy->addFuzzyInput(temperature);

    // FuzzyInput
    FuzzyInput *humidity = new FuzzyInput(2);

    FuzzySet *dry = new FuzzySet(-5, -5, 0, 30);
    humidity->addFuzzySet(dry);
    FuzzySet *comfortable = new FuzzySet(20, 35, 35, 50);
    humidity->addFuzzySet(comfortable);
    FuzzySet *humid = new FuzzySet(40, 55, 55, 70);
    humidity->addFuzzySet(humid);
    FuzzySet *sticky = new FuzzySet(60, 100, 105, 105);
    humidity->addFuzzySet(sticky);

    fuzzy->addFuzzyInput(humidity);

    // FuzzyOutput
    FuzzyOutput *speed = new FuzzyOutput(1);

    FuzzySet *off = new FuzzySet(0, 0, 0, 0);
    speed->addFuzzySet(off);
    FuzzySet *lowHumidity = new FuzzySet(30, 45, 45, 60);
    speed->addFuzzySet(lowHumidity);
    FuzzySet *medium = new FuzzySet(50, 65, 65, 80);
    speed->addFuzzySet(medium);
    FuzzySet *fast = new FuzzySet(70, 90, 95, 95);
    speed->addFuzzySet(fast);

    fuzzy->addFuzzyOutput(speed);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndDry = new FuzzyRuleAntecedent();
    ifVeryLowAndDry->joinWithAND(veryLow, dry);
    FuzzyRuleConsequent *thenOff1 = new FuzzyRuleConsequent();
    thenOff1->addOutput(off);
    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifVeryLowAndDry, thenOff1);
    fuzzy->addFuzzyRule(fuzzyRule1);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndComfortable = new FuzzyRuleAntecedent();
    ifVeryLowAndComfortable->joinWithAND(veryLow, comfortable);
    FuzzyRuleConsequent *thenOff2 = new FuzzyRuleConsequent();
    thenOff2->addOutput(off);
    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifVeryLowAndComfortable, thenOff2);
    fuzzy->addFuzzyRule(fuzzyRule2);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndHumid = new FuzzyRuleAntecedent();
    ifVeryLowAndHumid->joinWithAND(veryLow, humid);
    FuzzyRuleConsequent *thenOff3 = new FuzzyRuleConsequent();
    thenOff3->addOutput(off);
    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifVeryLowAndHumid, thenOff3);
    fuzzy->addFuzzyRule(fuzzyRule3);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryLowAndSticky = new FuzzyRuleAntecedent();
    ifVeryLowAndSticky->joinWithAND(veryLow, sticky);
    FuzzyRuleConsequent *thenLow1 = new FuzzyRuleConsequent();
    thenLow1->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifVeryLowAndSticky, thenLow1);
    fuzzy->addFuzzyRule(fuzzyRule4);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndDry = new FuzzyRuleAntecedent();
    ifLowAndDry->joinWithAND(low, dry);
    FuzzyRuleConsequent *thenOff4 = new FuzzyRuleConsequent();
    thenOff4->addOutput(off);
    FuzzyRule *fuzzyRule5 = new FuzzyRule(5, ifLowAndDry, thenOff4);
    fuzzy->addFuzzyRule(fuzzyRule5);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndComfortable = new FuzzyRuleAntecedent();
    ifLowAndComfortable->joinWithAND(low, comfortable);
    FuzzyRuleConsequent *thenOff5 = new FuzzyRuleConsequent();
    thenOff5->addOutput(off);
    FuzzyRule *fuzzyRule6 = new FuzzyRule(6, ifLowAndComfortable, thenOff5);
    fuzzy->addFuzzyRule(fuzzyRule6);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndHumid = new FuzzyRuleAntecedent();
    ifLowAndHumid->joinWithAND(low, humid);
    FuzzyRuleConsequent *thenLow2 = new FuzzyRuleConsequent();
    thenLow2->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule7 = new FuzzyRule(7, ifLowAndHumid, thenLow2);
    fuzzy->addFuzzyRule(fuzzyRule7);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifLowAndSticky = new FuzzyRuleAntecedent();
    ifLowAndSticky->joinWithAND(low, sticky);
    FuzzyRuleConsequent *thenMedium1 = new FuzzyRuleConsequent();
    thenMedium1->addOutput(medium);
    FuzzyRule *fuzzyRule8 = new FuzzyRule(8, ifLowAndSticky, thenMedium1);
    fuzzy->addFuzzyRule(fuzzyRule8);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndDry = new FuzzyRuleAntecedent();
    ifHighAndDry->joinWithAND(high, dry);
    FuzzyRuleConsequent *thenLow3 = new FuzzyRuleConsequent();
    thenLow3->addOutput(lowHumidity);
    FuzzyRule *fuzzyRule9 = new FuzzyRule(9, ifHighAndDry, thenLow3);
    fuzzy->addFuzzyRule(fuzzyRule9);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndComfortable = new FuzzyRuleAntecedent();
    ifHighAndComfortable->joinWithAND(high, comfortable);
    FuzzyRuleConsequent *thenMedium2 = new FuzzyRuleConsequent();
    thenMedium2->addOutput(medium);
    FuzzyRule *fuzzyRule10 = new FuzzyRule(10, ifHighAndComfortable, thenMedium2);
    fuzzy->addFuzzyRule(fuzzyRule10);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndHumid = new FuzzyRuleAntecedent();
    ifHighAndHumid->joinWithAND(high, humid);
    FuzzyRuleConsequent *thenFast1 = new FuzzyRuleConsequent();
    thenFast1->addOutput(fast);
    FuzzyRule *fuzzyRule11 = new FuzzyRule(11, ifHighAndHumid, thenFast1);
    fuzzy->addFuzzyRule(fuzzyRule11);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifHighAndSticky = new FuzzyRuleAntecedent();
    ifHighAndSticky->joinWithAND(high, sticky);
    FuzzyRuleConsequent *thenFast2 = new FuzzyRuleConsequent();
    thenFast2->addOutput(fast);
    FuzzyRule *fuzzyRule12 = new FuzzyRule(12, ifHighAndSticky, thenFast2);
    fuzzy->addFuzzyRule(fuzzyRule12);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndDry = new FuzzyRuleAntecedent();
    ifVeryHighAndDry->joinWithAND(veryHigh, dry);
    FuzzyRuleConsequent *thenMedium3 = new FuzzyRuleConsequent();
    thenMedium3->addOutput(medium);
    FuzzyRule *fuzzyRule13 = new FuzzyRule(13, ifVeryHighAndDry, thenMedium3);
    fuzzy->addFuzzyRule(fuzzyRule13);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndComfortable = new FuzzyRuleAntecedent();
    ifVeryHighAndComfortable->joinWithAND(veryHigh, comfortable);
    FuzzyRuleConsequent *thenFast3 = new FuzzyRuleConsequent();
    thenFast3->addOutput(fast);
    FuzzyRule *fuzzyRule14 = new FuzzyRule(14, ifVeryHighAndComfortable, thenFast3);
    fuzzy->addFuzzyRule(fuzzyRule14);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndHumid = new FuzzyRuleAntecedent();
    ifVeryHighAndHumid->joinWithAND(veryHigh, humid);
    FuzzyRuleConsequent *thenFast4 = new FuzzyRuleConsequent();
    thenFast4->addOutput(fast);
    FuzzyRule *fuzzyRule15 = new FuzzyRule(15, ifVeryHighAndHumid, thenFast4);
    fuzzy->addFuzzyRule(fuzzyRule15);

    // Building FuzzyRule
    FuzzyRuleAntecedent *ifVeryHighAndSticky = new FuzzyRuleAntecedent();
    ifVeryHighAndSticky->joinWithAND(veryHigh, sticky);
    FuzzyRuleConsequent *thenFast5 = new FuzzyRuleConsequent();
    thenFast5->addOutput(fast);
    FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ifVeryHighAndSticky, thenFast5);
    fuzzy->addFuzzyRule(fuzzyRule16);

    // run it
    ofstream outputFile;
    outputFile.open("tests/output.txt");

    for (int t = 0; t <= 45; t++)
    {
        for (int h = 0; h <= 100; h++)
        {
            fuzzy->setInput(1, t);
            fuzzy->setInput(2, h);

            fuzzy->fuzzify();

            float o = fuzzy->defuzzify(1);

            std::cout
                << "Running with: Temperature->" << t << ", Humidity->" << h << ". Result: " << o << std::endl;

            outputFile << o << ",";
        }
        outputFile << "\n";
    }
    outputFile.close();
    return 0;
}