#include <assert.h>
#include <C:\ApplicationPrograms\PhysicsEngine\include\interpret\particle.h>
using namespace interpret;

void Particle::integrate(cartesian timeInterval) {
    if (inverseMass <= 0.0f) {
        return;
    }
    assert(timeInterval > 0.0f);

    position.addScaledVec(timeInterval, velocity);
    Vector3d resultingAccel = acceleration;
    resultingAccel.addScaledVec(inverseMass, accumForce);

    velocity.addScaledVec(timeInterval, resultingAccel);

    velocity *= cartesian_pow(dragValue, timeInterval);

    clearAccumulator();
}
void Particle::clearAccumulator() {
    accumForce.clear();
}
void Particle::addForce(const Vector3d &newForce) {
    accumForce += newForce;
}
