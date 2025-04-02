#pragma once
#include "GenericInputController.h"

class BGInputController : public GenericInputController {
public:
    BGInputController(std::string name);
    ~BGInputController();
    void perform() override;
    bool isMove(); 

private:
    bool move = false;
};

