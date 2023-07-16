#pragma once
#include "LevelStrategy.h"
#include "PerformStrategy.h"

class Calculator
{
private:
    LevelStrategy* m_levelStrategy;
    PerformStrategy* m_performStrategy;
public:
    Calculator(LevelStrategy* levelStrategy, PerformStrategy* performStrategy): m_levelStrategy(levelStrategy), m_performStrategy(performStrategy) {}
    int get_base() {
        return m_levelStrategy->get_base();
    }
    int get_total(int base) {
        return m_performStrategy->get_bonus(base) + base;
    }
};