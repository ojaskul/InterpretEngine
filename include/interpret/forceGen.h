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
    class ParticleGravity : public ParticleForceGenerator {
        Vector3d gravity;
        public:
            ParticleGravity(const Vector3d &gravity);
            virtual void updateForce(Particle *particle, cartesian timeInterval);
    };
    class ParticleDrag : public ParticleForceGenerator {
        cartesian dc1;
        cartesian dc2;
        public:
            ParticleDrag(cartesian dc1, cartesian dc2);
            virtual void updateForce(Particle *particle, cartesian timeInterval);
    };
    class ParticleSpring : public ParticleForceGenerator {
        Particle *otherEnd;
        cartesian springConstant;
        cartesian restLength;
        public:
            ParticleSpring(Particle *particle, cartesian springConstant, cartesian restLength);
            virtual void updateForce(Particle *particle, cartesian timeInterval);
    };
};