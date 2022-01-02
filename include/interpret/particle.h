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
            
            void setMass(const cartesian mass);
            cartesian getMass() const;

            void setInverseMass(const cartesian inverseMass);
            cartesian getInverseMass() const;

            bool hasFiniteMass();

            void setDamping(const cartesian damping);
            cartesian getDamping() const;

            void setPosition(const Vector3d &position);
            void setPosition(const cartesian x, const cartesian y, const cartesian z);
            void getPosition(Vector3d *position) const;
            Vector3d getPosition();

            void setVelocity(const Vector3d &velocity);
            void setVelocity(const cartesian x, const cartesian y, const cartesian z);
            void getVelocity(Vector3d *velocity) const;
            Vector3d getVelocity() const;

            void setAccel(const Vector3d &accel);
            void setAccel(const cartesian x, const cartesian y, const cartesian z);
            void getAccel(Vector3d *accel) const;
            Vector3d getAccel() const;

            void addForce(const Vector3d &newForce);
            void clearAccumulator();
    };
};