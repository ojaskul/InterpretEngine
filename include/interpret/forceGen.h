#include "particle.h"
#include <vector>
namespace interpret {
    class ParticleForceGenerator {
        public:
            virtual void updateForce(Particle *particle, cartesian timeInterval) = 0;
    };
    class ParticleForceRegistry {
        protected:
            struct ParticleForceRegistration {
                Particle *particle;
                ParticleForceGenerator *pfg;
            };
            typedef std::vector<ParticleForceRegistration> Registry;
            Registry registrations;
        public:
            void addToRegistry(Particle* particle, ParticleForceGenerator *pfg);
            void removeFromRegistry(Particle* particle, ParticleForceGenerator *pfg);
            void clearRegistry();
            void updateForces(cartesian timeInterval);
    };
};