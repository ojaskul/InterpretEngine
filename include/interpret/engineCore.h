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
            void clear() {
                x = y = z = 0;
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
    class Matrix3 {
        public:
            cartesian data[9];
        public:
            Matrix3()
            {
                data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
                data[6] = data[7] = data[8] = 0;
            }
            Matrix3 (cartesian c0, cartesian c1, cartesian c2, cartesian c3, cartesian c4, cartesian c5, cartesian c6, cartesian c7, cartesian c8) {
                data[0] = c0;
                data[1] = c1;
                data[2] = c2;
                data[3] = c3;
                data[4] = c4;
                data[5] = c5;
                data[6] = c6;
                data[7] = c7;
                data[8] = c8;
            }
            Vector3d operator * (const Vector3d &vec) const {
                return Vector3d(vec.x * data[0] + vec.y * data[1] + vec.z * data[2], vec.x * data[3] + vec.y * data[4] + vec.z * data[5], vec.x * data[6] + vec.y * data[7] + vec.z * data[8]);
            }
            Vector3d transform (const Vector3d &vec) const {
                return (*this) * vec;
            }
            Matrix3 operator * (const Matrix3 &m) const {
                return Matrix3(
                    m.data[0]*data[0] + m.data[3]*data[1] + m.data[6]*data[2],
                    m.data[1]*data[0] + m.data[4]*data[1] + m.data[7]*data[2],
                    m.data[2]*data[0] + m.data[5]*data[1] + m.data[8]*data[2],

                    m.data[0]*data[3] + m.data[3]*data[4] + m.data[6]*data[5],
                    m.data[1]*data[3] + m.data[4]*data[4] + m.data[7]*data[5],
                    m.data[2]*data[3] + m.data[5]*data[4] + m.data[8]*data[5],

                    m.data[0]*data[6] + m.data[3]*data[7] + m.data[6]*data[8],
                    m.data[1]*data[6] + m.data[4]*data[7] + m.data[7]*data[8],
                    m.data[2]*data[6] + m.data[5]*data[7] + m.data[8]*data[8]
                );
            }
            void operator *= (const Matrix3 &m) {
                cartesian nd1;
                cartesian nd2;
                cartesian nd3;

                nd1 = m.data[0]*data[0] + m.data[3]*data[1] + m.data[6]*data[2];
                nd2 = m.data[1]*data[0] + m.data[4]*data[1] + m.data[7]*data[2];
                nd3 = m.data[2]*data[0] + m.data[5]*data[1] + m.data[8]*data[2];

                data[0] = nd1;
                data[1] = nd2;
                data[2] = nd3; 

                nd1 = m.data[0]*data[3] + m.data[3]*data[4] + m.data[6]*data[5];
                nd2 = m.data[1]*data[3] + m.data[4]*data[4] + m.data[7]*data[5];
                nd3 = m.data[2]*data[3] + m.data[5]*data[4] + m.data[8]*data[5];

                data[3] = nd1;
                data[4] = nd2;
                data[5] = nd3; 

                nd1 = m.data[0]*data[6] + m.data[3]*data[7] + m.data[6]*data[8];
                nd2 = m.data[1]*data[6] + m.data[4]*data[7] + m.data[7]*data[8];
                nd3 = m.data[2]*data[6] + m.data[5]*data[7] + m.data[8]*data[8];

                data[6] = nd1;
                data[7] = nd2;
                data[8] = nd3; 
            }
            void setInverse (const Matrix3 &m) {
                cartesian nd1 = m.data[0]*m.data[4];
                cartesian nd2 = m.data[0]*m.data[5];
                cartesian nd3 = m.data[1]*m.data[3];
                cartesian nd4 = m.data[2]*m.data[3];
                cartesian nd5 = m.data[1]*m.data[6];
                cartesian nd6 = m.data[2]*m.data[6];

                cartesian detrm = (nd1*m.data[8] - nd2*m.data[7] - nd3*m.data[8]+
                nd4*m.data[7] + nd5*m.data[5] - nd6*m.data[4]);

                // Make sure the determinant is non-zero.

                if (detrm == (cartesian)0.0f) return;
                cartesian invd = (cartesian)1.0f/detrm;
                data[0] = (m.data[4]*m.data[8]-m.data[5]*m.data[7])*invd;
                data[1] = -(m.data[1]*m.data[8]-m.data[2]*m.data[7])*invd;
                data[2] = (m.data[1]*m.data[5]-m.data[2]*m.data[4])*invd;
                data[3] = -(m.data[3]*m.data[8]-m.data[5]*m.data[6])*invd;
                data[4] = (m.data[0]*m.data[8]-nd6)*invd;
                data[5] = -(nd2-nd4)*invd;
                data[6] = (m.data[3]*m.data[7]-m.data[4]*m.data[6])*invd;
                data[7] = -(m.data[0]*m.data[7]-nd5)*invd;
                data[8] = (nd1-nd3)*invd;

            }
            Matrix3 inverse() const {
                Matrix3 result;
                result.setInverse(*this);
                return result;
            }
            void invert() {
                setInverse(*this);
            }
            void setTranspose(const Matrix3 &m) {
                data[0] = m.data[0];
                data[1] = m.data[3];
                data[2] = m.data[6];
                data[3] = m.data[1];
                data[4] = m.data[4];
                data[5] = m.data[7];
                data[6] = m.data[2];
                data[7] = m.data[5];
                data[8] = m.data[8];
            }
            Matrix3 transpose() const {
                Matrix3 result;
                result.setTranspose(*this);
                return result;
            }
            void setOrientation(const Quaternion &q) {
                data[0] = 1 - (2*q.j*q.j + 2*q.k*q.k);
                data[1] = 2*q.i*q.j + 2*q.k*q.r;
                data[2] = 2*q.i*q.k - 2*q.j*q.r;
                data[3] = 2*q.i*q.j - 2*q.k*q.r;
                data[4] = 1 - (2*q.i*q.i + 2*q.k*q.k);
                data[5] = 2*q.j*q.k + 2*q.i*q.r;
                data[6] = 2*q.i*q.k + 2*q.j*q.r;
                data[7] = 2*q.j*q.k - 2*q.i*q.r;
                data[8] = 1 - (2*q.i*q.i + 2*q.j*q.j);
            }
    };
    class Matrix4 {
        public:
            cartesian data[12];
        public:
            Matrix4()
                {
                    data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
                    data[6] = data[7] = data[8] = data[9] = data[10] = data[11] = 0;
                }
            Vector3d operator * (const Vector3d &vec) const {
                return Vector3d(
                    vec.x * data[0] + vec.y * data[1] + vec.z * data[2] + data[3], 
                    vec.x * data[4] + vec.y * data[5] + vec.z * data[6] + data[7], 
                    vec.x * data[8] + vec.y * data[9] + vec.z * data[10] + data[11]
                );
            }
            Vector3d transform (const Vector3d &vec) const {
                return (*this) * vec;
            }
            Matrix4 operator * (const Matrix4 &m) const {
                Matrix4 matrix;
                matrix.data[0] = m.data[0] * data[0] + m.data[4] * data[1] + m.data[8] * data[2];
                matrix.data[4] = m.data[0] * data[4] + m.data[4] * data[5] + m.data[8] * data[6];
                matrix.data[8] = m.data[0] * data[8] + m.data[4] * data[9] + m.data[8] * data[10];

                matrix.data[1] = m.data[1] * data[0] + m.data[5] * data[1] + m.data[9] * data[2];
                matrix.data[5] = m.data[1] * data[4] + m.data[5] * data[5] + m.data[9] * data[6];
                matrix.data[9] = m.data[1] * data[8] + m.data[5] * data[9] + m.data[9] * data[10];

                matrix.data[2] = m.data[2] * data[0] + m.data[6] * data[1] + m.data[10] * data[2];
                matrix.data[6] = m.data[2] * data[4] + m.data[6] * data[5] + m.data[10] * data[6];
                matrix.data[10] = m.data[2] * data[8] + m.data[6] * data[9] + m.data[10] * data[10];

                matrix.data[3] = m.data[3] * data[0] + m.data[7] * data[1] + m.data[11] * data[2] + data[3];
                matrix.data[7] = m.data[3] * data[4] + m.data[7] * data[5] + m.data[11] * data[6] + data[7];
                matrix.data[11] = m.data[3] * data[8] + m.data[7] * data[9] + m.data[11] * data[10] + data[11];

                return matrix;
            }

            cartesian getDet() const;
            
            void setInverse(const Matrix4 &m);

            Matrix4 inverse() const {
                Matrix4 result;
                result.setInverse(*this);
                return result;
            }

            void invert() {
                setInverse(*this);
            }

            void setOrientationAndPosition(const Quaternion &q, const Vector3d &pos) {
                data[0] = 1 - (2*q.j*q.j + 2*q.k*q.k);
                data[1] = 2*q.i*q.j + 2*q.k*q.r;
                data[2] = 2*q.i*q.k - 2*q.j*q.r;
                data[3] = pos.x;

                data[4] = 2*q.i*q.j - 2*q.k*q.r;
                data[5] = 1 - (2*q.i*q.i + 2*q.k*q.k);
                data[6] = 2*q.j*q.k + 2*q.i*q.r;
                data[7] = pos.y;

                data[8] = 2*q.i*q.k + 2*q.j*q.r;
                data[9] = 2*q.j*q.k - 2*q.i*q.r;
                data[10] = 1 - (2*q.i*q.i + 2*q.j*q.j);
                data[11] = pos.z;
            }
            Vector3d transformInverse(const Vector3d &vec) const {
                Vector3d intermed = vec;
                    intermed.x -= data[3];
                    intermed.y -= data[7];
                    intermed.z -= data[11];
                    
                return Vector3d(
                    intermed.x * data[0] +
                    intermed.y * data[4] +
                    intermed.z * data[8],

                    intermed.x * data[1] +
                    intermed.y * data[5] +
                    intermed.z * data[9],
                    
                    intermed.x * data[2] +
                    intermed.y * data[6] +
                    intermed.z * data[10]
                    );
            }
    };

    class Quaternion {
        public:
            cartesian r;
            cartesian i;
            cartesian j;
            cartesian k;
        public:
            Quaternion(const cartesian r, const cartesian i, const cartesian j, const cartesian k) : r(r), i(i),j(j), k(k) {}
    };
};