#include <particle.h>
namespace interpret {
    class ParticleContact {
        friend class ParticleContactResolver;
        public:
            Particle* particle[2];
            cartesian restitutionCoeff; // Velocity before and after contact.
            Vector3d contactNormal; // Direction of the contact resolution.
            cartesian interpenetration;
        protected:
            void resolve(cartesian timeInterval);
            cartesian calculateSeperatingVelocity() const;
        private:
            void resolveVelocity(cartesian timeInterval);
            void resolveInterpenetration();
    };
    class ParticleContactResolver {
        protected:
            unsigned iterations;
            unsigned iterationsUsed;
        public:
            ParticleContactResolver(unsigned iterations);
            void setIterations(unsigned iterations);
            void resolveContacts(ParticleContact *contacts, unsigned numContacts, cartesian timeInterval);
    };
    class ParticleContactGenerator {
        public:
            virtual unsigned addContact(ParticleContact *contact, unsigned limit) const = 0;
    };
};