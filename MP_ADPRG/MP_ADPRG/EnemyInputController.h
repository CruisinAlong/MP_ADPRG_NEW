#pragma once

#include "GenericInputController.h"

class EnemyInputController : public GenericInputController {
public:
    EnemyInputController(std::string name);
    ~EnemyInputController();
    void perform() override;
    bool isMove();

private:
    bool move;
};



