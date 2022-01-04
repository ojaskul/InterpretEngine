#include <particleContacts.h>
using namespace interpret;

void ParticleContact::resolve(cartesian timeInterval) {
    resolveVelocity(timeInterval);
    resolveInterpenetration();
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
    Vector3d velocityCausedByAccel = particle[0]->getAccel();
    if (particle[1] != NULL) {
        velocityCausedByAccel -= particle[1]->getAccel();
    }
    cartesian sepVelCausedByAccel = velocityCausedByAccel * contactNormal * timeInterval;

    if (sepVelCausedByAccel < 0) {
        newSepVel += restitutionCoeff * sepVelCausedByAccel;
        if (newSepVel < 0) {
            newSepVel = 0;
        }
    }

    cartesian changeInVel = newSepVel - sepVel;

    cartesian totalInverseMass = particle[0]->getInverseMass();
    if (particle[1] != NULL) {
        totalInverseMass += particle[1]->getInverseMass();
    }
    if (totalInverseMass <= 0) return;

    Vector3d impulsePerInverseMass = contactNormal * (changeInVel / totalInverseMass);

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

void ParticleContact::resolveInterpenetration() {
    if (interpenetration <= 0) {
        return;
    }
    cartesian totalInverseMass = particle[0]->getInverseMass();
    if (particle[1] != NULL) {
        totalInverseMass += particle[1]->getInverseMass();
    }
    if (totalInverseMass <= 0) return;

    Vector3d movePerInverseMass = contactNormal * (interpenetration / totalInverseMass);

    particle[0]->setPosition(particle[0]->getPosition() + (movePerInverseMass * particle[0]->getInverseMass()));

    if (particle[1] != NULL) {
        particle[1]->setPosition(particle[1]->getPosition() + (movePerInverseMass * -particle[1]->getInverseMass()));
    }
}

void ParticleContactResolver::resolveContacts(ParticleContact *contacts, unsigned numContacts, cartesian timeInterval) {
    unsigned i;
    iterationsUsed = 0;
    while(iterationsUsed < iterations) {
        cartesian maximum = CART_MAX;
        unsigned maxIndex = numContacts;
        for (i = 0; i < numContacts; i++) {
            cartesian sepVel = contacts[i].calculateSeperatingVelocity();
            if (sepVel < maximum && (sepVel < 0 || contacts[i].interpenetration > 0)) {
                maximum = sepVel;
                maxIndex = i;
            }
        }
        if (maxIndex == numContacts) break;

        contacts[maxIndex].resolve(timeInterval);
        iterationsUsed++;
    }
}