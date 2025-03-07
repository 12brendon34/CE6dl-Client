#pragma once

class IEngineImpl {
public:

};

class CGameEditor {
public:
};

//some arg is passed with no way for me to figure out what the class is
//besides
//pcVar3 = (char *)(**(code **)(*param_2 + 8))(param_2);
class DummyClass {
public:
    virtual void dummyFunction1() {}
    virtual void dummyFunction2() {}
    virtual char* targetFunction() {
        return (char*)"UNKNOWN";
    }
};