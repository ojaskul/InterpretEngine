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
void Particle::setMass(const cartesian mass) {
    assert(mass != 0);
    Particle::inverseMass = ((cartesian)1)/mass;
}
cartesian Particle::getMass() const {
    if (inverseMass == 0) {
        return (cartesian)0.0;
    } else {
        return ((cartesian)1.0)/inverseMass;
    }
}
void Particle::setInverseMass(const cartesian inverseMass) {
    Particle::inverseMass == inverseMass;
}
cartesian Particle::getInverseMass() const {
    return inverseMass;
}
bool Particle::hasFiniteMass() const{
    return inverseMass >= 0.0f;
}
void Particle::setDamping(const cartesian damping) {
    Particle::dragValue == damping;
}
cartesian Particle::getDamping() const {
    return dragValue;
}
void Particle::setPosition(const Vector3d &position) {
    Particle::position = position;
}
void Particle::setPosition(const cartesian x, const cartesian y, const cartesian z) {
    position.x = x;
    position.y = y;
    position.z = z;
}
void Particle::getPosition(Vector3d *position) const {
    *position = Particle::position;
}
Vector3d Particle::getPosition() const {
    return position;
}
void Particle::setVelocity(const Vector3d &velocity) {
    Particle::velocity = velocity;
}
void Particle::setVelocity(const cartesian x, const cartesian y, const cartesian z) {
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}
void Particle::getVelocity(Vector3d *velocity) const {
    *velocity = Particle::velocity;
}
Vector3d Particle::getVelocity() const {
    return velocity;
}
void Particle::setAccel(const Vector3d &accel) {
    Particle::acceleration = accel;
}
void Particle::setAccel(const cartesian x, const cartesian y, const cartesian z) {
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}
void Particle::getAccel(Vector3d *accel) const {
    *accel = Particle::acceleration;
}
Vector3d Particle::getAccel() const {
    return acceleration;
}