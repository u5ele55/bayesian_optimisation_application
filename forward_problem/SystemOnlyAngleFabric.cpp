//
// Created by ormequ on 24.05.23.
//

#include "SystemOnlyAngleFabric.h"

System SystemOnlyAngleFabric::produce(const Vector &params) {
    return {omega, dissipation, params[0], angularSpeed};
}

SystemOnlyAngleFabric::SystemOnlyAngleFabric(double dissipation, double omega, double angularSpeed)
        : dissipation(dissipation),
          omega(omega),
          angularSpeed(angularSpeed) {}
