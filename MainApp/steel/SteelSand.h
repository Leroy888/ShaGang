#ifndef STEELSAND_H
#define STEELSAND_H

#include "SteelSand_global.h"

#include <QWidget>
#include "SteelForm.h"

class STEELSAND_EXPORT SteelSand
{
public:
    SteelSand();

    QWidget* createSteelForm();
};

#endif // STEELSAND_H
