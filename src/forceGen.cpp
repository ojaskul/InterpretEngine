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
void ParticleSpring::updateForce(Particle *particle, cartesian timeInterval) {
    Vector3d force;
    particle->getPosition(&force);
    force -= otherEnd->getPosition();

    cartesian magnitude = force.magitude();
    magnitude = cartesian_abs(magnitude - restLength);
    magnitude *= springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}
void ParticleAnchoredSpring::updateForce(Particle *particle, cartesian timeInterval) {
    Vector3d force;
    particle->getPosition(&force);
    force -= *anchorLocation;

    cartesian magnitude = force.magitude();
    magnitude = (restLength - magnitude) * springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}
void ParticleBungee::updateForce(Particle *particle, cartesian timeInterval) {
    Vector3d force;
    particle->getPosition(&force);
    force -= otherParticle->getPosition();

    cartesian magnitude = force.magitude();

    if (magnitude <= restLength) return;

    magnitude = (restLength - magnitude) * springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}
void ParticleBuoyancy::updateForce(Particle *particle, cartesian timeInterval) {
    cartesian depth = particle->getPosition().y;
    if (depth >= maxDepth + waterHeight) {
        return;
    }
    Vector3d force(0,0,0);

    if (depth < waterHeight - maxDepth) {
        force.y = density * volume;
        particle->addForce(force);
        return;
    }
    force.y = density * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
    particle->addForce(force);
}