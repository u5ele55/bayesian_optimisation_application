//
// Created by ormequ on 24.05.23.
//

#include "SystemAngleAndSpeedFabric.h"

System SystemAngleAndSpeedFabric::produce(const Vector &params) {
    return System(omega, dissipation, params[0], params[1]);
}

SystemAngleAndSpeedFabric::SystemAngleAndSpeedFabric(double dissipation, double omega)
        : dissipation(dissipation),
          omega(omega) {}
