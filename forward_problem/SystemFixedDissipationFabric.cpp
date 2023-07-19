//
// Created by ormequ on 23.05.23.
//

#include "SystemFixedDissipationFabric.h"

SystemFixedDissipationFabric::SystemFixedDissipationFabric(double dissipation)
        : dissipation(dissipation) {}

System SystemFixedDissipationFabric::produce(const Vector& params) {
    return {params[0], dissipation, params[1], params[2]};
}


