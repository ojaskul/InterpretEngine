#include <particle.h>
namespace interpret {
    class ParticleContact {
        public:
            Particle* particle[2];
            cartesian restitutionCoeff; // Velocity before and after contact.
            Vector3d contactNormal; // Direction of the contact resolution.
        protected:
            void resolve(cartesian timeInterval);
            cartesian calculateSeperatingVelocity() const;
        private:
            void resolveVelocity(cartesian timeInterval);
    };
};