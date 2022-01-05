#include <particleWorld.h>
using namespace interpret;

unsigned ParticleWorld::generateContacts() {
    unsigned limit = maxContacts;

    ParticleContact *nextContact = contacts;

    for (ContactGenerators::iterator g = contactGenerators.begin(); g != contactGenerators.end(); g++) {
        unsigned usedContacts = (*g)->addContact(nextContact, limit);
        limit = limit - usedContacts;
        nextContact = nextContact + usedContacts;
        
        if (limit <= 0) break;
    }

    return maxContacts - limit;
}
void ParticleWorld::integrate(cartesian timeInterval) {
    for (Particles::iterator p = particles.begin(); p != particles.end(); p++) {
        (*p)->integrate(timeInterval);
    }
}
void ParticleWorld::runPhysics(cartesian timeInterval) {
    registry.updateForces(timeInterval);
    integrate(timeInterval);
    unsigned usedContacts = generateContacts();

    if (usedContacts != NULL) {
        if (calculateIterations) {
            resolver.setIterations(usedContacts * 2);
            resolver.resolveContacts(contacts, usedContacts, timeInterval);
        }
    }
}