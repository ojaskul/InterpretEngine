#include "engineCore.h"
#include "precision.h"

namespace interpret {
    class Particle {
        protected:
            Vector3d position;
            Vector3d velocity;
            Vector3d acceleration;
            Vector3d accumForce;
            cartesian dragValue;
            cartesian inverseMass;
        public:
            void integrate(cartesian timeInterval);
            void clearAccumulator();
            void addForce(const Vector3d &newForce);
    };
};