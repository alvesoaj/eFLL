/*
 * Robotic Research Group (RRG)
 * State University of Piaui (UESPI), Brazil - Piauí - Teresina
 *
 * FuzzyRuleAntecedent.cpp
 *
 *      Author: AJ Alves <aj.alves@zerokol.com>
 *          Co authors: Msc. Marvin Lemos <marvinlemos@gmail.com>
 *                      Douglas S. Kridi <douglaskridi@gmail.com>
 *                      Kannya Leal <kannyal@hotmail.com>
 */
#include "FuzzyRuleAntecedent.h"

// CONSTRUTORES
FuzzyRuleAntecedent::FuzzyRuleAntecedent(){
    this->op = 0;
    this->mode = 0;
    this->fuzzySet1 = NULL;
    this->fuzzySet2 = NULL;
    this->fuzzyRuleAntecedent1 = NULL;
    this->fuzzyRuleAntecedent2 = NULL;
}

// MÉTODOS PÚBLICOS
bool FuzzyRuleAntecedent::joinSingle(FuzzySet* fuzzySet){
    if(fuzzySet){
        this->mode = MODE_FS;
        this->fuzzySet1 = fuzzySet;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2){
    if(fuzzySet1 != NULL && fuzzySet2 != NULL){
        this->op = OP_AND;
        this->mode = MODE_FS_FS;
        this->fuzzySet1 = fuzzySet1;
        this->fuzzySet2 = fuzzySet2;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzySet* fuzzySet1, FuzzySet* fuzzySet2){
    if(fuzzySet1 != NULL && fuzzySet2 != NULL){
        this->op = OP_OR;
        this->mode = MODE_FS_FS;
        this->fuzzySet1 = fuzzySet1;
        this->fuzzySet2 = fuzzySet2;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent){
    if(fuzzySet != NULL && fuzzyRuleAntecedent != NULL){
        this->op = OP_AND;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet){
    if(fuzzySet != NULL && fuzzyRuleAntecedent != NULL){
        this->op = OP_AND;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzySet* fuzzySet, FuzzyRuleAntecedent* fuzzyRuleAntecedent){
    if(fuzzySet != NULL && fuzzyRuleAntecedent != NULL){
        this->op = OP_OR;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent, FuzzySet* fuzzySet){
    if(fuzzySet != NULL && fuzzyRuleAntecedent != NULL){
        this->op = OP_OR;
        this->mode = MODE_FS_FRA;
        this->fuzzySet1 = fuzzySet;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithAND(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2){
    if(fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL){
        this->op = OP_AND;
        this->mode = MODE_FRA_FRA;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
        this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
        return true;
    }
    return false;
}

bool FuzzyRuleAntecedent::joinWithOR(FuzzyRuleAntecedent* fuzzyRuleAntecedent1, FuzzyRuleAntecedent* fuzzyRuleAntecedent2){
    if(fuzzyRuleAntecedent1 != NULL && fuzzyRuleAntecedent2 != NULL){
        this->op = OP_OR;
        this->mode = MODE_FRA_FRA;
        this->fuzzyRuleAntecedent1 = fuzzyRuleAntecedent1;
        this->fuzzyRuleAntecedent2 = fuzzyRuleAntecedent2;
        return true;
    }
    return false;
}

float FuzzyRuleAntecedent::evaluate(){
    switch(this->mode){
        case MODE_FS:
            return this->fuzzySet1->getPertinence();
            break;
        case MODE_FS_FS:
            switch(this->op){
                case OP_AND:
                    if(this->fuzzySet1->getPertinence() > 0.0 && this->fuzzySet2->getPertinence() > 0.0){
                        if(this->fuzzySet1->getPertinence() < this->fuzzySet2->getPertinence()){
                            return this->fuzzySet1->getPertinence();
                        }else{
                            return this->fuzzySet2->getPertinence();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                case OP_OR:
                    if(this->fuzzySet1->getPertinence() > 0.0 || this->fuzzySet2->getPertinence() > 0.0){
                        if(this->fuzzySet1->getPertinence() > this->fuzzySet2->getPertinence()){
                            return this->fuzzySet1->getPertinence();
                        }else{
                            return this->fuzzySet2->getPertinence();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                default:
                    return 0.0;
            }
            break;
        case MODE_FS_FRA:
            switch(this->op){
                case OP_AND:
                    if(this->fuzzySet1->getPertinence() > 0.0 && fuzzyRuleAntecedent1->evaluate() > 0.0){
                        if(this->fuzzySet1->getPertinence() < fuzzyRuleAntecedent1->evaluate()){
                            return this->fuzzySet1->getPertinence();
                        }else{
                            return fuzzyRuleAntecedent1->evaluate();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                case OP_OR:
                    if(this->fuzzySet1->getPertinence() > 0.0 || fuzzyRuleAntecedent1->evaluate() > 0.0){
                        if(this->fuzzySet1->getPertinence() > fuzzyRuleAntecedent1->evaluate()){
                            return this->fuzzySet1->getPertinence();
                        }else{
                            return fuzzyRuleAntecedent1->evaluate();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                default:
                    return 0.0;
            }
            break;
        case MODE_FRA_FRA:
            switch(this->op){
                case OP_AND:
                    if(fuzzyRuleAntecedent1->evaluate() > 0.0 && fuzzyRuleAntecedent2->evaluate() > 0.0){
                        if(fuzzyRuleAntecedent1->evaluate() < fuzzyRuleAntecedent2->evaluate()){
                            return fuzzyRuleAntecedent1->evaluate();
                        }else{
                            return fuzzyRuleAntecedent2->evaluate();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                case OP_OR:
                    if(fuzzyRuleAntecedent1->evaluate() > 0.0 || fuzzyRuleAntecedent2->evaluate() > 0.0){
                        if(fuzzyRuleAntecedent1->evaluate() > fuzzyRuleAntecedent2->evaluate()){
                            return fuzzyRuleAntecedent1->evaluate();
                        }else{
                            return fuzzyRuleAntecedent2->evaluate();
                        }
                    }else{
                        return 0.0;
                    }
                    break;
                default:
                    return 0.0;
            }
            break;
        default:
            return 0.0;
    }
    return 0.0;
}