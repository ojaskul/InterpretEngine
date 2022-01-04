#include <particleLinks.h>
#include <forceGen.h>

namespace interpret {
    class ParticleWorld {
        public:
            typedef std::vector<Particle*> Particles;
            typedef std::vector<ParticleContactGenerator*> ContactGenerators;
        protected:
            Particles particles;
            ParticleForceRegistry registry;
            ParticleContactResolver resolver;
            ContactGenerators contactGenerators;
            bool calculateIterations;
            ParticleContact *contacts;
            unsigned maxContacts;
        public:
            ParticleWorld(unsigned maxContacts, unsigned iterations = 0);
            void startFrame();
            unsigned generateContacts();
            void integrate(cartesian timeInterval);
            void runPhysics(cartesian timeInterval);
    };
};