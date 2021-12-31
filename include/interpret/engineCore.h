#include "precision.h"
#include "math.h"

namespace interpret {
    class Vector3d {
        public:
            cartesian x;
            cartesian y;
            cartesian z;
        private:
            cartesian pad;
        public:
            /**
             * Default constructor that sets the values of each instance variable to 0. 
             * */
            Vector3d(): x(0), y(0), z(0) {}
            /**
             * Constructor to be able to set different values of each instance variable.
             * */
            Vector3d(const cartesian x, const cartesian y, const cartesian z) : x(x), y(y), z(z) {}
            /**
             * Inverts the array as in opposes the direction.
             * */
            void invert() {
                x = -x;
                y = -y;
                z = -z;
            }
            /**
             * Calculate the actual magnitude of the vector. 
             * */
            cartesian magitude() const {
                return sqrt(x*x+y*y+z*z);
            }
            /**
             * Faster process for comparing approximate magnitudes instead of actually calculating sqrt.
             * */
            cartesian magSqaured() const {
                return x*x+y*y+z*z;
            }
            /**
             * Normalizes the vector to find the scalar coefficient to the unit vector.
             * */
            void normalize() {
                cartesian length = magitude();
                if (length > 0) {
                    (*this) *= ((cartesian)1)/length;
                }
            }
            /**
             * Adds a scaled vector to the current vector and updates this.
             * */
            void addScaledVec(cartesian scale, const Vector3d& otherVec) {
                x += scale * otherVec.x;
                y += scale * otherVec.y;
                z += scale * otherVec.z;
            }
            /**
             * Performs a component product with this vector and another, and returns a copy of this vector.
             * */
            Vector3d componentProduct(const Vector3d &otherVec) {
                return Vector3d(x * otherVec.x, y * otherVec.y, z * otherVec.z);
            }
            /**
             * Performs a componet product and updates the value of this vector's variables. 
             * */
            void updateComponentProduct(const Vector3d &otherVec) {
                x *= otherVec.x;
                y *= otherVec.y;
                z *= otherVec.z;
            }
            cartesian dotProduct(const Vector3d &otherVec) {
                return x*otherVec.x + y*otherVec.y + z*otherVec.z;
            }
            Vector3d crossProduct(const Vector3d &otherVec) {
                return Vector3d(y*otherVec.z - z*otherVec.y, z*otherVec.x - x*otherVec.z, x*otherVec.y - y*otherVec.x);
            }
            void makeOrthonormalVector(Vector3d *a, Vector3d *b, Vector3d *c) {
                a->normalize();
                (*c) = (*a) % (*b);
                if (c->magSqaured() == 0.0) {
                    return;
                }
                c->normalize();
                (*b) = (*c) % (*a);
            }
            /**
             * Overloaded operation to multiply each component of this vector by a scalar val.
             * */
            void operator *= (const cartesian val) {
                x *= val;
                y *= val;
                z *= val;
            }
            /**
             * Overloaded multiplication operator to return a copy of this vector scaled by val. 
             * */
            Vector3d operator * (const cartesian val) {
                return Vector3d(x*val, y*val, z*val);
            }
            cartesian operator * (const Vector3d &otherVec) {
                return x*otherVec.x + y*otherVec.y + z*otherVec.z;
            }
            /**
             * Overloaded operation to add each component of this vector to another vector.
             * */
            void operator += (const Vector3d& otherVec) {
                x += otherVec.x;
                y += otherVec.y;
                z += otherVec.z;
            }
            /**
             * Overloaded operation to add a given vector to this vector and return a copy of it.
             * */
            Vector3d operator + (const Vector3d& otherVec) {
                return Vector3d(x + otherVec.x, y + otherVec.y, z + otherVec.z);
            }
            /**
             * Overloaded operation to subtract each component of a given vector from this vector.
             * */
            void operator -= (const Vector3d& otherVec) {
                x -= otherVec.x;
                y -= otherVec.y;
                z -= otherVec.z;
            }
            /**
             * Overloaded operation to subtract a given vector from this vector and return a copy of it.
             * */
            Vector3d operator - (const Vector3d& otherVec) {
                return Vector3d(x - otherVec.x, y - otherVec.y, z - otherVec.z);
            }
            void operator %= (const Vector3d &otherVec) {
                (*this) = crossProduct(otherVec);
            }
            Vector3d operator % (const Vector3d &otherVec) {
                return Vector3d(y*otherVec.z - z*otherVec.y, z*otherVec.x - x*otherVec.z, x*otherVec.y - y*otherVec.x);
            }
    };
};