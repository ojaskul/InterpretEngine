#include "precision.h"
namespace interpret {
    class Vector3d {
        public:
            cartesian x;
            cartesian y;
            cartesian z;
        private:
            cartesian pad;
        public:
            Vector3d(): x(0), y(0), z(0) {}
            Vector3d(const cartesian x, const cartesian y, const cartesian z) : x(x), y(y), z(z) {}
            void invert() {
                x = -x;
                y = -y;
                z = -z;
            }
    };
};