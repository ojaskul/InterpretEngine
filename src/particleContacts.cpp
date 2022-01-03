#include <particleContacts.h>
using namespace interpret;

void ParticleContact::resolve(cartesian timeInterval) {
    resolveVelocity(timeInterval);
    // resolveInterpenetration(timeInterval);
}
cartesian ParticleContact::calculateSeperatingVelocity() const {
    Vector3d relativeVelocity = particle[0]->getVelocity();
    if (particle[1] != NULL){
        relativeVelocity -= particle[1]->getVelocity();
    }
    return relativeVelocity * contactNormal;
}
void ParticleContact::resolveVelocity(cartesian timeInterval) {
    cartesian sepVel = calculateSeperatingVelocity();
    if (sepVel > 0) {
        return;
    }
    cartesian newSepVel = -1 * sepVel * restitutionCoeff;
    cartesian changeInVel = newSepVel - sepVel;
    cartesian totalInverseMass = particle[0]->getInverseMass();
    if (particle[1] != NULL) {
        totalInverseMass += particle[1]->getInverseMass();
    }
    if (totalInverseMass <= 0) return;
    cartesian impulseCalc = changeInVel / totalInverseMass;
    Vector3d impulsePerInverseMass = contactNormal * impulseCalc;

    /**
     * particle[0].newVelocity = particle[0].oldVelocity + newVelocityByImpulse
     * There will always be at least one particle in the collision stored at array[0].
     * */
    particle[0]->setVelocity(particle[0]->getVelocity() + (impulsePerInverseMass * particle[0]->getInverseMass()));

    /**
     * Check for null pointer, and if 2 particles are present then calculate velocity in opposite direction.
     * */
    if (particle[1] != NULL) {
        particle[1]->setVelocity(particle[1]->getVelocity() + (impulsePerInverseMass * -particle[1]->getInverseMass()));
    }
} 