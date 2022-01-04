#include <particleContacts.h>
namespace interpret {
    class ParticleLink : public ParticleContactGenerator {
        public:
            Particle* particle[2];
        protected:
            cartesian linkCurrentLength() const;
        public:
            virtual unsigned addContact(ParticleContact *contact, unsigned limit) const = 0;
    };
    class ParticleCable : public ParticleLink {
        public:
            cartesian maxLength;
            cartesian restitutionCoeff;
        public:
            virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
    };
    class ParticleRod : public ParticleLink {
        public:
            cartesian length;
        public:
            virtual unsigned addContact(ParticleContact *contact, unsigned limit) const;
    };
};