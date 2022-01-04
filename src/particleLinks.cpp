#include <particleLinks.h>
using namespace interpret;

cartesian ParticleLink::linkCurrentLength() const {
    Vector3d relativePos = particle[0]->getPosition() - particle[1]->getPosition();
    return relativePos.magitude();
}

unsigned ParticleCable::addContact(ParticleContact *contact, unsigned limit) const {
    cartesian length = linkCurrentLength();
    if (length < maxLength) {
        return 0;
    }
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3d normalVec = particle[1]->getPosition() - particle[0]->getPosition();
    normalVec.normalize();

    contact->contactNormal = normalVec;
    contact->interpenetration = length - maxLength;
    contact->restitutionCoeff = restitutionCoeff;

    return 1;
}
unsigned ParticleRod::addContact(ParticleContact *contact, unsigned limit) const {
    cartesian currentLength = linkCurrentLength();
    if (currentLength == length) {
        return 0;
    }
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3d normalVec = particle[1]->getPosition() - particle[0]->getPosition();
    normalVec.normalize();

    if (currentLength > length) {
        contact->contactNormal = normalVec;
        contact->interpenetration = currentLength - length;
    } else {
        contact->contactNormal = normalVec * -1;
        contact->interpenetration = length - currentLength;
    }

    contact->restitutionCoeff = 0;

    return 1;
}