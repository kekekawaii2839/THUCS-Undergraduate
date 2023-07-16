#pragma once
#include "operation.h"

class substract : public OperationNodeTwo {
public:
    substract(string name, Node *x1, Node *x2) : OperationNodeTwo(name, x1, x2) {}

    void UpdateValue() override {
        value_ = input1->value() - input2->value();
    }

    ~substract() override = default;
};