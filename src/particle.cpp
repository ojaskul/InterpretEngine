#include <assert.h>
#include <./include/interpret/particle.h>
using namespace interpret;

void Particle::integrate(cartesian timeInterval) {
    if (inverseMass <= 0.0f) {
        return;
    }
    assert(timeInterval > 0.0f);
    position.addScaledVec(timeInterval, velocity);
    Vector3d resultingAccel = acceleration;
    velocity.addScaledVec(timeInterval, resultingAccel);
    velocity *= cartesian_pow(dragValue, timeInterval);
}