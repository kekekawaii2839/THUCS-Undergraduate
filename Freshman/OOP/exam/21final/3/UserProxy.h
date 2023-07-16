#pragma once
#include <iostream>
#include "User.h"
#include "EncryptStrategy.h"
#include "VerificationStrategy.h"

using namespace std;

class UserProxy{
private:
    RealUser* user;
    EncryptStrategy* encStr;
    VerificationStrategy* verStr;
public:
    UserProxy(RealUser* u, EncryptStrategy* es, VerificationStrategy* vs): user(u), encStr(es), verStr(vs){}
    void sendMessage(std::string mes){
        user->sendMessage(encStr->encode(mes));
        cout << verStr->verify(mes) << endl;
    }
};