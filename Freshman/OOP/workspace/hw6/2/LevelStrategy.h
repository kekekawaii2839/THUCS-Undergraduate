#pragma once

class LevelStrategy
{
public:
    virtual int get_base() = 0;
};

class P1LStrategy: public LevelStrategy{
public:
    int get_base() {
        return 2000;
    }
};

class P2LStrategy: public LevelStrategy{
public:
    int get_base() {
        return 5000;
    }
};

class P3LStrategy: public LevelStrategy{
public:
    int get_base() {
        return 10000;
    }
};