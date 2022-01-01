#include <C:\ApplicationPrograms\PhysicsEngine\include\interpret\forceGen.h>
using namespace interpret;

void ParticleForceRegistry::updateForces(cartesian timeInterval) {
    Registry::iterator i = registrations.begin();
    for (i; i < registrations.end(); i++) {
        i->pfg->updateForce(i->particle, timeInterval);
    }
}
void ParticleGravity::updateForce(Particle *particle, cartesian timeInterval) {
    if (!particle->hasFiniteMass()) {
        return;
    }
    particle->addForce(gravity * particle->getMass());
}
void ParticleDrag::updateForce(Particle *particle, cartesian timeInterval) {
    Vector3d force;
    particle->getVelocity(&force);

    cartesian totalDrag = force.magitude();
    totalDrag = dc1 * totalDrag + dc2 * totalDrag * totalDrag;

    force.normalize();
    force *= -totalDrag;
    particle->addForce(force);
}
