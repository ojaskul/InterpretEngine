#include <C:\ApplicationPrograms\PhysicsEngine\include\interpret\forceGen.h>
using namespace interpret;

void ParticleForceRegistry::updateForces(cartesian timeInterval) {
    Registry::iterator i = registrations.begin();
    for (i; i < registrations.end(); i++) {
        i->pfg->updateForce(i->particle, timeInterval);
    }
}
