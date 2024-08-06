#pragma once

#define _USE_MATH_DEFINES
#define SMALL_float 0.0000000001
#include "math.h"

namespace Unity
{
    struct Vector2
    {
        union
        {
            struct
            {
                float x;
                float y;
            };
            float data[2];
        };


        /**
         * Constructors.
         */
        inline Vector2();
        inline Vector2(float data[]);
        inline Vector2(float value);
        inline Vector2(float x, float y);


        /**
         * Constants for common vectors.
         */
        static inline Vector2 Zero();
        static inline Vector2 One();
        static inline Vector2 Right();
        static inline Vector2 Left();
        static inline Vector2 Up();
        static inline Vector2 Down();


        /**
         * Returns the angle between two vectors in radians.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A scalar value.
         */
        static inline float Angle(Vector2 a, Vector2 b);

        /**
         * Returns a vector with its magnitude clamped to maxLength.
         * @param vector: The target vector.
         * @param maxLength: The maximum length of the return vector.
         * @return: A new vector.
         */
        static inline Vector2 ClampMagnitude(Vector2 vector, float maxLength);

        /**
         * Returns the component of a in the direction of b (scalar projection).
         * @param a: The target vector.
         * @param b: The vector being compared against.
         * @return: A scalar value.
         */
        static inline float Component(Vector2 a, Vector2 b);

        /**
         * Returns the distance between a and b.
         * @param a: The first point.
         * @param b: The second point.
         * @return: A scalar value.
         */
        static inline float Distance(Vector2 a, Vector2 b);

        /**
         * Returns the dot product of two vectors.
         * @param lhs: The left side of the multiplication.
         * @param rhs: The right side of the multiplication.
         * @return: A scalar value.
         */
        static inline float Dot(Vector2 lhs, Vector2 rhs);

        /**
         * Converts a polar representation of a vector into cartesian
         * coordinates.
         * @param rad: The magnitude of the vector.
         * @param theta: The angle from the x axis.
         * @return: A new vector.
         */
        static inline Vector2 FromPolar(float rad, float theta);

        /**
         * Returns a vector linearly interpolated between a and b, moving along
         * a straight line. The vector is clamped to never go beyond the end points.
         * @param a: The starting point.
         * @param b: The ending point.
         * @param t: The interpolation value [0-1].
         * @return: A new vector.
         */
        static inline Vector2 Lerp(Vector2 a, Vector2 b, float t);

        /**
         * Returns a vector linearly interpolated between a and b, moving along
         * a straight line.
         * @param a: The starting point.
         * @param b: The ending point.
         * @param t: The interpolation value [0-1] (no actual bounds).
         * @return: A new vector.
         */
        static inline Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);

        /**
         * Returns the magnitude of a vector.
         * @param v: The vector in question.
         * @return: A scalar value.
         */
        static inline float Magnitude(Vector2 v);

        /**
         * Returns a vector made from the largest components of two other vectors.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A new vector.
         */
        static inline Vector2 Max(Vector2 a, Vector2 b);

        /**
         * Returns a vector made from the smallest components of two other vectors.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A new vector.
         */
        static inline Vector2 Min(Vector2 a, Vector2 b);

        /**
         * Returns a vector "maxDistanceDelta" units closer to the target. This
         * interpolation is in a straight line, and will not overshoot.
         * @param current: The current position.
         * @param target: The destination position.
         * @param maxDistanceDelta: The maximum distance to move.
         * @return: A new vector.
         */
        static inline Vector2 MoveTowards(Vector2 current, Vector2 target,
                                          float maxDistanceDelta);

        /**
         * Returns a new vector with magnitude of one.
         * @param v: The vector in question.
         * @return: A new vector.
         */
        static inline Vector2 Normalized(Vector2 v);

        /**
         * Creates a new coordinate system out of the two vectors.
         * Normalizes "normal" and normalizes "tangent" and makes it orthogonal to
         * "normal"..
         * @param normal: A reference to the first axis vector.
         * @param tangent: A reference to the second axis vector.
         */
        static inline void OrthoNormalize(Vector2 &normal, Vector2 &tangent);

        /**
         * Returns the vector projection of a onto b.
         * @param a: The target vector.
         * @param b: The vector being projected onto.
         * @return: A new vector.
         */
        static inline Vector2 Project(Vector2 a, Vector2 b);

        /**
         * Returns a vector reflected about the provided line.
         * This behaves as if there is a plane with the line as its normal, and the
         * vector comes in and bounces off this plane.
         * @param vector: The vector traveling inward at the imaginary plane.
         * @param line: The line about which to reflect.
         * @return: A new vector pointing outward from the imaginary plane.
         */
        static inline Vector2 Reflect(Vector2 vector, Vector2 line);

        /**
         * Returns the vector rejection of a on b.
         * @param a: The target vector.
         * @param b: The vector being projected onto.
         * @return: A new vector.
         */
        static inline Vector2 Reject(Vector2 a, Vector2 b);

        /**
         * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
         * This treats the vectors as directions and will linearly interpolate
         * between their magnitudes by "maxMagnitudeDelta". This function does not
         * overshoot. If a negative delta is supplied, it will rotate away from
         * "target" until it is pointing the opposite direction, but will not
         * overshoot that either.
         * @param current: The starting direction.
         * @param target: The destination direction.
         * @param maxRadiansDelta: The maximum number of radians to rotate.
         * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
         * @return: A new vector.
         */
        static inline Vector2 RotateTowards(Vector2 current, Vector2 target,
                                            float maxRadiansDelta,
                                            float maxMagnitudeDelta);

        /**
         * Multiplies two vectors component-wise.
         * @param a: The lhs of the multiplication.
         * @param b: The rhs of the multiplication.
         * @return: A new vector.
         */
        static inline Vector2 Scale(Vector2 a, Vector2 b);

        /**
         * Returns a vector rotated towards b from a by the percent t.
         * Since interpolation is done spherically, the vector moves at a constant
         * angular velocity. This rotation is clamped to 0 <= t <= 1.
         * @param a: The starting direction.
         * @param b: The ending direction.
         * @param t: The interpolation value [0-1].
         */
        static inline Vector2 Slerp(Vector2 a, Vector2 b, float t);

        inline std::string ToString() {
            std::string vector=std::to_string(x)+", "+std::to_string(y);
            return vector;
        }
        /**
         * Returns a vector rotated towards b from a by the percent t.
         * Since interpolation is done spherically, the vector moves at a constant
         * angular velocity. This rotation is unclamped.
         * @param a: The starting direction.
         * @param b: The ending direction.
         * @param t: The interpolation value [0-1].
         */
        static inline Vector2 SlerpUnclamped(Vector2 a, Vector2 b, float t);

        /**
         * Returns the squared magnitude of a vector.
         * This is useful when comparing relative lengths, where the exact length
         * is not important, and much time can be saved by not calculating the
         * square root.
         * @param v: The vector in question.
         * @return: A scalar value.
         */
        static inline float SqrMagnitude(Vector2 v);

        /**
         * Calculates the polar coordinate space representation of a vector.
         * @param vector: The vector to convert.
         * @param rad: The magnitude of the vector.
         * @param theta: The angle from the x axis.
         */
        static inline void ToPolar(Vector2 vector, float &rad, float &theta);


        /**
         * Operator overloading.
         */
        inline struct Vector2& operator+=(const float rhs);
        inline struct Vector2& operator-=(const float rhs);
        inline struct Vector2& operator*=(const float rhs);
        inline struct Vector2& operator/=(const float rhs);
        inline struct Vector2& operator+=(const Vector2 rhs);
        inline struct Vector2& operator-=(const Vector2 rhs);
    };

    inline Vector2 operator-(Vector2 rhs);
    inline Vector2 operator+(Vector2 lhs, const float rhs);
    inline Vector2 operator-(Vector2 lhs, const float rhs);
    inline Vector2 operator*(Vector2 lhs, const float rhs);
    inline Vector2 operator/(Vector2 lhs, const float rhs);
    inline Vector2 operator+(const float lhs, Vector2 rhs);
    inline Vector2 operator-(const float lhs, Vector2 rhs);
    inline Vector2 operator*(const float lhs, Vector2 rhs);
    inline Vector2 operator/(const float lhs, Vector2 rhs);
    inline Vector2 operator+(Vector2 lhs, const Vector2 rhs);
    inline Vector2 operator-(Vector2 lhs, const Vector2 rhs);
    inline bool operator==(const Vector2 lhs, const Vector2 rhs);
    inline bool operator!=(const Vector2 lhs, const Vector2 rhs);



/*******************************************************************************
 * Implementation
 */

    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float data[]) : x(data[0]), y(data[1]) {}
    Vector2::Vector2(float value) : x(value), y(value) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}


    Vector2 Vector2::Zero() { return Vector2(0, 0); }
    Vector2 Vector2::One() { return Vector2(1, 1); }
    Vector2 Vector2::Right() { return Vector2(1, 0); }
    Vector2 Vector2::Left() { return Vector2(-1, 0); }
    Vector2 Vector2::Up() { return Vector2(0, 1); }
    Vector2 Vector2::Down() { return Vector2(0, -1); }


    float Vector2::Angle(Vector2 a, Vector2 b)
    {
        float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
        v = fmax(v, -1.0);
        v = fmin(v, 1.0);
        return acos(v);
    }

    Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength)
    {
        float length = Magnitude(vector);
        if (length > maxLength)
            vector *= maxLength / length;
        return vector;
    }

    float Vector2::Component(Vector2 a, Vector2 b)
    {
        return Dot(a, b) / Magnitude(b);
    }

    float Vector2::Distance(Vector2 a, Vector2 b)
    {
        return Vector2::Magnitude(a - b);
    }

    float Vector2::Dot(Vector2 lhs, Vector2 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    Vector2 Vector2::FromPolar(float rad, float theta)
    {
        Vector2 v;
        v.x = rad * cos(theta);
        v.y = rad * sin(theta);
        return v;
    }

    Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return LerpUnclamped(a, b, t);
    }

    Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t)
    {
        return (b - a) * t + a;
    }

    float Vector2::Magnitude(Vector2 v)
    {
        return sqrt(SqrMagnitude(v));
    }

    Vector2 Vector2::Max(Vector2 a, Vector2 b)
    {
        float x = a.x > b.x ? a.x : b.x;
        float y = a.y > b.y ? a.y : b.y;
        return Vector2(x, y);
    }

    Vector2 Vector2::Min(Vector2 a, Vector2 b)
    {
        float x = a.x > b.x ? b.x : a.x;
        float y = a.y > b.y ? b.y : a.y;
        return Vector2(x, y);
    }

    Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target,
                                 float maxDistanceDelta)
    {
        Vector2 d = target - current;
        float m = Magnitude(d);
        if (m < maxDistanceDelta || m == 0)
            return target;
        return current + (d * maxDistanceDelta / m);
    }

    Vector2 Vector2::Normalized(Vector2 v)
    {
        float mag = Magnitude(v);
        if (mag == 0)
            return Vector2::Zero();
        return v / mag;
    }

    void Vector2::OrthoNormalize(Vector2 &normal, Vector2 &tangent)
    {
        normal = Normalized(normal);
        tangent = Reject(tangent, normal);
        tangent = Normalized(tangent);
    }

    Vector2 Vector2::Project(Vector2 a, Vector2 b)
    {
        float m = Magnitude(b);
        return Dot(a, b) / (m * m) * b;
    }

    Vector2 Vector2::Reflect(Vector2 vector, Vector2 planeNormal)
    {
        return vector - 2 * Project(vector, planeNormal);
    }

    Vector2 Vector2::Reject(Vector2 a, Vector2 b)
    {
        return a - Project(a, b);
    }

    Vector2 Vector2::RotateTowards(Vector2 current, Vector2 target,
                                   float maxRadiansDelta,
                                   float maxMagnitudeDelta)
    {
        float magCur = Magnitude(current);
        float magTar = Magnitude(target);
        float newMag = magCur + maxMagnitudeDelta *
                                ((magTar > magCur) - (magCur > magTar));
        newMag = fmin(newMag, fmax(magCur, magTar));
        newMag = fmax(newMag, fmin(magCur, magTar));

        float totalAngle = Angle(current, target) - maxRadiansDelta;
        if (totalAngle <= 0)
            return Normalized(target) * newMag;
        else if (totalAngle >= M_PI)
            return Normalized(-target) * newMag;

        float axis = current.x * target.y - current.y * target.x;
        axis = axis / fabs(axis);
        if (!(1 - fabs(axis) < 0.00001))
            axis = 1;
        current = Normalized(current);
        Vector2 newVector = current * cos(maxRadiansDelta) +
                            Vector2(-current.y, current.x) * sin(maxRadiansDelta) * axis;
        return newVector * newMag;
    }

    Vector2 Vector2::Scale(Vector2 a, Vector2 b)
    {
        return Vector2(a.x * b.x, a.y * b.y);
    }

    Vector2 Vector2::Slerp(Vector2 a, Vector2 b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return SlerpUnclamped(a, b, t);
    }

    Vector2 Vector2::SlerpUnclamped(Vector2 a, Vector2 b, float t)
    {
        float magA = Magnitude(a);
        float magB = Magnitude(b);
        a /= magA;
        b /= magB;
        float dot = Dot(a, b);
        dot = fmax(dot, -1.0);
        dot = fmin(dot, 1.0);
        float theta = acos(dot) * t;
        Vector2 relativeVec = Normalized(b - a * dot);
        Vector2 newVec = a * cos(theta) + relativeVec * sin(theta);
        return newVec * (magA + (magB - magA) * t);
    }

    float Vector2::SqrMagnitude(Vector2 v)
    {
        return v.x * v.x + v.y * v.y;
    }

    void Vector2::ToPolar(Vector2 vector, float &rad, float &theta)
    {
        rad = Magnitude(vector);
        theta = atan2(vector.y, vector.x);
    }


    struct Vector2& Vector2::operator+=(const float rhs)
    {
        x += rhs;
        y += rhs;
        return *this;
    }

    struct Vector2& Vector2::operator-=(const float rhs)
    {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    struct Vector2& Vector2::operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    struct Vector2& Vector2::operator/=(const float rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    struct Vector2& Vector2::operator+=(const Vector2 rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    struct Vector2& Vector2::operator-=(const Vector2 rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2 operator-(Vector2 rhs) { return rhs * -1; }
    Vector2 operator+(Vector2 lhs, const float rhs) { return lhs += rhs; }
    Vector2 operator-(Vector2 lhs, const float rhs) { return lhs -= rhs; }
    Vector2 operator*(Vector2 lhs, const float rhs) { return lhs *= rhs; }
    Vector2 operator/(Vector2 lhs, const float rhs) { return lhs /= rhs; }
    Vector2 operator+(const float lhs, Vector2 rhs) { return rhs += lhs; }
    Vector2 operator-(const float lhs, Vector2 rhs) { return rhs -= lhs; }
    Vector2 operator*(const float lhs, Vector2 rhs) { return rhs *= lhs; }
    Vector2 operator/(const float lhs, Vector2 rhs) { return rhs /= lhs; }
    Vector2 operator+(Vector2 lhs, const Vector2 rhs) { return lhs += rhs; }
    Vector2 operator-(Vector2 lhs, const Vector2 rhs) { return lhs -= rhs; }

    bool operator==(const Vector2 lhs, const Vector2 rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    bool operator!=(const Vector2 lhs, const Vector2 rhs)
    {
        return !(lhs == rhs);
    }

//    struct Vector3
//    {
//        float x, y, z;
//
//        Vector3() { x = y = z = 0.f; }
//        Vector3(float f1, float f2, float f3) { x = f1; y = f2; z = f3; }
//
//        float Length()
//        {
//            return x * x + y * y + z * z;
//        }
//
//        float Dot(Vector3 b)
//        {
//            return x * b.x + y * b.y + z * b.z;
//        }
//
//        Vector3 Normalize()
//        {
//            float len = Length();
//            if (len > 0)
//                return Vector3(x / len, y / len, z / len);
//            else
//                return Vector3(x, y, z);
//        }
//        void ToVectors(Vector3* m_pForward, Vector3* m_pRight, Vector3* m_pUp)
//        {
//            float m_fDeg2Rad = static_cast<float>(M_PI) / 180.f;
//
//            float m_fSinX = sinf(x * m_fDeg2Rad);
//            float m_fCosX = cosf(x * m_fDeg2Rad);
//
//            float m_fSinY = sinf(y * m_fDeg2Rad);
//            float m_fCosY = cosf(y * m_fDeg2Rad);
//
//            float m_fSinZ = sinf(z * m_fDeg2Rad);
//            float m_fCosZ = cosf(z * m_fDeg2Rad);
//
//            if (m_pForward)
//            {
//                m_pForward->x = m_fCosX * m_fCosY;
//                m_pForward->y = -m_fSinX;
//                m_pForward->z = m_fCosX * m_fSinY;
//            }
//
//            if (m_pRight)
//            {
//                m_pRight->x = -1.f * m_fSinZ * m_fSinX * m_fCosY + -1.f * m_fCosZ * -m_fSinY;
//                m_pRight->y = -1.f * m_fSinZ * m_fCosX;
//                m_pRight->z = -1.f * m_fSinZ * m_fSinX * m_fSinY + -1.f * m_fCosZ * m_fCosY;
//            }
//
//            if (m_pUp)
//            {
//                m_pUp->x = m_fCosZ * m_fSinX * m_fCosY + -m_fSinZ * -m_fSinY;
//                m_pUp->y = m_fCosZ * m_fCosX;
//                m_pUp->z = m_fCosZ * m_fSinX * m_fSinY + -m_fSinZ * m_fCosY;
//            }
//        }
//    };


    struct Vector3
    {

        union {
            struct {
                float x,y,z;
            };
            float data[3];
        };


        /**
         * Constructors.
         */

        inline Vector3() : x(0), y(0), z(0) {}
        inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        static inline Vector3 Zero() { return Vector3(0, 0, 0); }
        static inline Vector3 One() { return Vector3(1, 1, 1); }
        static inline Vector3 Right() { return Vector3(1, 0, 0); }
        static inline Vector3 Left() { return Vector3(-1, 0, 0); }
        static inline Vector3 Up() { return Vector3(0, 1, 0); }
        static inline Vector3 Down() { return Vector3(0, -1, 0); }
        static inline Vector3 Forward() { return Vector3(0, 0, 1); }
        static inline Vector3 Backward() { return Vector3(0, 0, -1); }


        /**
         * Returns the angle between two vectors in radians.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A scalar value.
         */
        static inline float Angle(Vector3 a, Vector3 b);

        /**
         * Returns a vector with its magnitude clamped to maxLength.
         * @param vector: The target vector.
         * @param maxLength: The maximum length of the return vector.
         * @return: A new vector.
         */
        static inline Vector3 ClampMagnitude(Vector3 vector, float maxLength);

        /**
         * Returns the component of a in the direction of b (scalar projection).
         * @param a: The target vector.
         * @param b: The vector being compared against.
         * @return: A scalar value.
         */
        static inline float Component(Vector3 a, Vector3 b);

        /**
         * Returns the cross product of two vectors.
         * @param lhs: The left side of the multiplication.
         * @param rhs: The right side of the multiplication.
         * @return: A new vector.
         */
        static inline Vector3 Cross(Vector3 lhs, Vector3 rhs);

        /**
         * Returns the distance between a and b.
         * @param a: The first point.
         * @param b: The second point.
         * @return: A scalar value.
         */
        static inline float Distance(Vector3 a, Vector3 b);

        inline std::string ToString() {
            std::string vector=std::to_string(x)+", "+std::to_string(y)+", "+std::to_string(z);
            return vector;
        }

        /**
         * Returns the dot product of two vectors.
         * @param lhs: The left side of the multiplication.
         * @param rhs: The right side of the multiplication.
         * @return: A scalar value.
         */
        static inline float Dot(Vector3 lhs, Vector3 rhs);

        /**
         * Converts a spherical representation of a vector into cartesian
         * coordinates.
         * This uses the ISO convention (radius r, inclination theta, azimuth phi).
         * @param rad: The magnitude of the vector.
         * @param theta: The angle in the XY plane from the x axis.
         * @param phi: The angle from the positive z axis to the vector.
         * @return: A new vector.
         */
        static inline Vector3 FromSpherical(float rad, float theta, float phi);

        /**
         * Returns a vector linearly interpolated between a and b, moving along
         * a straight line. The vector is clamped to never go beyond the end points.
         * @param a: The starting point.
         * @param b: The ending point.
         * @param t: The interpolation value [0-1].
         * @return: A new vector.
         */
        static inline Vector3 Lerp(Vector3 a, Vector3 b, float t);

        /**
         * Returns a vector linearly interpolated between a and b, moving along
         * a straight line.
         * @param a: The starting point.
         * @param b: The ending point.
         * @param t: The interpolation value [0-1] (no actual bounds).
         * @return: A new vector.
         */
        static inline Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

        /**
         * Returns the magnitude of a vector.
         * @param v: The vector in question.
         * @return: A scalar value.
         */
        static inline float Magnitude(Vector3 v);

        /**
         * Returns a vector made from the largest components of two other vectors.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A new vector.
         */
        static inline Vector3 Max(Vector3 a, Vector3 b);

        /**
         * Returns a vector made from the smallest components of two other vectors.
         * @param a: The first vector.
         * @param b: The second vector.
         * @return: A new vector.
         */
        static inline Vector3 Min(Vector3 a, Vector3 b);

        /**
         * Returns a vector "maxDistanceDelta" units closer to the target. This
         * interpolation is in a straight line, and will not overshoot.
         * @param current: The current position.
         * @param target: The destination position.
         * @param maxDistanceDelta: The maximum distance to move.
         * @return: A new vector.
         */
        static inline Vector3 MoveTowards(Vector3 current, Vector3 target,
                                          float maxDistanceDelta);

        /**
         * Returns a new vector with magnitude of one.
         * @param v: The vector in question.
         * @return: A new vector.
         */
        static inline Vector3 Normalized(Vector3 v);

        /**
         * Returns an arbitrary vector orthogonal to the input.
         * This vector is not normalized.
         * @param v: The input vector.
         * @return: A new vector.
         */
        static inline Vector3 Orthogonal(Vector3 v);

        /**
         * Creates a new coordinate system out of the three vectors.
         * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
         * "normal" and normalizes "binormal" and makes it orthogonal to both
         * "normal" and "tangent".
         * @param normal: A reference to the first axis vector.
         * @param tangent: A reference to the second axis vector.
         * @param binormal: A reference to the third axis vector.
         */
        static inline void OrthoNormalize(Vector3 &normal, Vector3 &tangent,
                                          Vector3 &binormal);

        /**
         * Returns the vector projection of a onto b.
         * @param a: The target vector.
         * @param b: The vector being projected onto.
         * @return: A new vector.
         */
        static inline Vector3 Project(Vector3 a, Vector3 b);

        /**
         * Returns a vector projected onto a plane orthogonal to "planeNormal".
         * This can be visualized as the shadow of the vector onto the plane, if
         * the light source were in the direction of the plane normal.
         * @param vector: The vector to project.
         * @param planeNormal: The normal of the plane onto which to project.
         * @param: A new vector.
         */
        static inline Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);

        /**
         * Returns a vector reflected off the plane orthogonal to the normal.
         * The input vector is pointed inward, at the plane, and the return vector
         * is pointed outward from the plane, like a beam of light hitting and then
         * reflecting off a mirror.
         * @param vector: The vector traveling inward at the plane.
         * @param planeNormal: The normal of the plane off of which to reflect.
         * @return: A new vector pointing outward from the plane.
         */
        static inline Vector3 Reflect(Vector3 vector, Vector3 planeNormal);

        /**
         * Returns the vector rejection of a on b.
         * @param a: The target vector.
         * @param b: The vector being projected onto.
         * @return: A new vector.
         */
        static inline Vector3 Reject(Vector3 a, Vector3 b);

        /**
         * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
         * This treats the vectors as directions and will linearly interpolate
         * between their magnitudes by "maxMagnitudeDelta". This function does not
         * overshoot. If a negative delta is supplied, it will rotate away from
         * "target" until it is pointing the opposite direction, but will not
         * overshoot that either.
         * @param current: The starting direction.
         * @param target: The destination direction.
         * @param maxRadiansDelta: The maximum number of radians to rotate.
         * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
         * @return: A new vector.
         */
        static inline Vector3 RotateTowards(Vector3 current, Vector3 target,
                                            float maxRadiansDelta,
                                            float maxMagnitudeDelta);

        /**
         * Multiplies two vectors element-wise.
         * @param a: The lhs of the multiplication.
         * @param b: The rhs of the multiplication.
         * @return: A new vector.
         */
        static inline Vector3 Scale(Vector3 a, Vector3 b);

        /**
         * Returns a vector rotated towards b from a by the percent t.
         * Since interpolation is done spherically, the vector moves at a constant
         * angular velocity. This rotation is clamped to 0 <= t <= 1.
         * @param a: The starting direction.
         * @param b: The ending direction.
         * @param t: The interpolation value [0-1].
         */
        static inline Vector3 Slerp(Vector3 a, Vector3 b, float t);

        /**
         * Returns a vector rotated towards b from a by the percent t.
         * Since interpolation is done spherically, the vector moves at a constant
         * angular velocity. This rotation is unclamped.
         * @param a: The starting direction.
         * @param b: The ending direction.
         * @param t: The interpolation value [0-1].
         */
        static inline Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);

        /**
         * Returns the squared magnitude of a vector.
         * This is useful when comparing relative lengths, where the exact length
         * is not important, and much time can be saved by not calculating the
         * square root.
         * @param v: The vector in question.
         * @return: A scalar value.
         */
        static inline float SqrMagnitude(Vector3 v);

        /**
         * Calculates the spherical coordinate space representation of a vector.
         * This uses the ISO convention (radius r, inclination theta, azimuth phi).
         * @param vector: The vector to convert.
         * @param rad: The magnitude of the vector.
         * @param theta: The angle in the XY plane from the x axis.
         * @param phi: The angle from the positive z axis to the vector.
         */
        static inline void ToSpherical(Vector3 vector, float &rad, float &theta,
                                       float &phi);


        /**
         * Operator overloading.
         */
        struct Vector3& operator+=(const float rhs);
        struct Vector3& operator-=(const float rhs);
        struct Vector3& operator*=(const float rhs);
        struct Vector3& operator/=(const float rhs);
        struct Vector3& operator+=(const Vector3 rhs);
        struct Vector3& operator-=(const Vector3 rhs);
    };

    Vector3 operator-(Vector3 rhs);
    Vector3 operator+(Vector3 lhs, const float rhs);
    Vector3 operator-(Vector3 lhs, const float rhs);
    Vector3 operator*(Vector3 lhs, const float rhs);
    Vector3 operator/(Vector3 lhs, const float rhs);
    Vector3 operator+(const float lhs, Vector3 rhs);
    Vector3 operator-(const float lhs, Vector3 rhs);
    Vector3 operator*(const float lhs, Vector3 rhs);
    Vector3 operator/(const float lhs, Vector3 rhs);
    Vector3 operator+(Vector3 lhs, const Vector3 rhs);
    Vector3 operator-(Vector3 lhs, const Vector3 rhs);
    bool operator==(const Vector3 lhs, const Vector3 rhs);
    bool operator!=(const Vector3 lhs, const Vector3 rhs);



/*******************************************************************************
 * Implementation
 */




    float Vector3::Angle(Vector3 a, Vector3 b)
    {
        float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
        v = fmax(v, -1.0);
        v = fmin(v, 1.0);
        return acos(v);
    }

    Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
    {
        float length = Magnitude(vector);
        if (length > maxLength)
            vector *= maxLength / length;
        return vector;
    }

    float Vector3::Component(Vector3 a, Vector3 b)
    {
        return Dot(a, b) / Magnitude(b);
    }

    Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
    {
        float x = lhs.y * rhs.z - lhs.z * rhs.y;
        float y = lhs.z * rhs.x - lhs.x * rhs.z;
        float z = lhs.x * rhs.y - lhs.y * rhs.x;
        return Vector3(x, y, z);
    }

    float Vector3::Distance(Vector3 a, Vector3 b)
    {
        return Vector3::Magnitude(a - b);
    }

    float Vector3::Dot(Vector3 lhs, Vector3 rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    Vector3 Vector3::FromSpherical(float rad, float theta, float phi)
    {
        Vector3 v;
        v.x = rad * sin(theta) * cos(phi);
        v.y = rad * sin(theta) * sin(phi);
        v.z = rad * cos(theta);
        return v;
    }

    Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return LerpUnclamped(a, b, t);
    }

    Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
    {
        return (b - a) * t + a;
    }

    float Vector3::Magnitude(Vector3 v)
    {
        return sqrt(SqrMagnitude(v));
    }

    Vector3 Vector3::Max(Vector3 a, Vector3 b)
    {
        float x = a.x > b.x ? a.x : b.x;
        float y = a.y > b.y ? a.y : b.y;
        float z = a.z > b.z ? a.z : b.z;
        return Vector3(x, y, z);
    }

    Vector3 Vector3::Min(Vector3 a, Vector3 b)
    {
        float x = a.x > b.x ? b.x : a.x;
        float y = a.y > b.y ? b.y : a.y;
        float z = a.z > b.z ? b.z : a.z;
        return Vector3(x, y, z);
    }

    Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target,
                                 float maxDistanceDelta)
    {
        Vector3 d = target - current;
        float m = Magnitude(d);
        if (m < maxDistanceDelta || m == 0)
            return target;
        return current + (d * maxDistanceDelta / m);
    }

    Vector3 Vector3::Normalized(Vector3 v)
    {
        float mag = Magnitude(v);
        if (mag == 0)
            return Vector3::Zero();
        return v / mag;
    }

    Vector3 Vector3::Orthogonal(Vector3 v)
    {
        return v.z < v.x ? Vector3(v.y, -v.x, 0) : Vector3(0, -v.z, v.y);
    }

    void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent,
                                 Vector3 &binormal)
    {
        normal = Normalized(normal);
        tangent = ProjectOnPlane(tangent, normal);
        tangent = Normalized(tangent);
        binormal = ProjectOnPlane(binormal, tangent);
        binormal = ProjectOnPlane(binormal, normal);
        binormal = Normalized(binormal);
    }

    Vector3 Vector3::Project(Vector3 a, Vector3 b)
    {
        float m = Magnitude(b);
        return Dot(a, b) / (m * m) * b;
    }

    Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
    {
        return Reject(vector, planeNormal);
    }

    Vector3 Vector3::Reflect(Vector3 vector, Vector3 planeNormal)
    {
        return vector - 2 * Project(vector, planeNormal);
    }

    Vector3 Vector3::Reject(Vector3 a, Vector3 b)
    {
        return a - Project(a, b);
    }

    Vector3 Vector3::RotateTowards(Vector3 current, Vector3 target,
                                   float maxRadiansDelta,
                                   float maxMagnitudeDelta)
    {
        float magCur = Magnitude(current);
        float magTar = Magnitude(target);
        float newMag = magCur + maxMagnitudeDelta *
                                ((magTar > magCur) - (magCur > magTar));
        newMag = fmin(newMag, fmax(magCur, magTar));
        newMag = fmax(newMag, fmin(magCur, magTar));

        float totalAngle = Angle(current, target) - maxRadiansDelta;
        if (totalAngle <= 0)
            return Normalized(target) * newMag;
        else if (totalAngle >= M_PI)
            return Normalized(-target) * newMag;

        Vector3 axis = Cross(current, target);
        float magAxis = Magnitude(axis);
        if (magAxis == 0)
            axis = Normalized(Cross(current, current + Vector3(3.95, 5.32, -4.24)));
        else
            axis /= magAxis;
        current = Normalized(current);
        Vector3 newVector = current * cos(maxRadiansDelta) +
                            Cross(axis, current) * sin(maxRadiansDelta);
        return newVector * newMag;
    }

    Vector3 Vector3::Scale(Vector3 a, Vector3 b)
    {
        return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
    }

    Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t)
    {
        if (t < 0) return a;
        else if (t > 1) return b;
        return SlerpUnclamped(a, b, t);
    }

    Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t)
    {
        float magA = Magnitude(a);
        float magB = Magnitude(b);
        a /= magA;
        b /= magB;
        float dot = Dot(a, b);
        dot = fmax(dot, -1.0);
        dot = fmin(dot, 1.0);
        float theta = acos(dot) * t;
        Vector3 relativeVec = Normalized(b - a * dot);
        Vector3 newVec = a * cos(theta) + relativeVec * sin(theta);
        return newVec * (magA + (magB - magA) * t);
    }

    float Vector3::SqrMagnitude(Vector3 v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    void Vector3::ToSpherical(Vector3 vector, float &rad, float &theta,
                              float &phi)
    {
        rad = Magnitude(vector);
        float v = vector.z / rad;
        v = fmax(v, -1.0);
        v = fmin(v, 1.0);
        theta = acos(v);
        phi = atan2(vector.y, vector.x);
    }


    struct Vector3& Vector3::operator+=(const float rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        return *this;
    }

    struct Vector3& Vector3::operator-=(const float rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        return *this;
    }

    struct Vector3& Vector3::operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    struct Vector3& Vector3::operator/=(const float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    struct Vector3& Vector3::operator+=(const Vector3 rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    struct Vector3& Vector3::operator-=(const Vector3 rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }



    Vector3 operator-(Vector3 rhs) { return rhs * -1; }
    Vector3 operator+(Vector3 lhs, const float rhs) { return lhs += rhs; }
    Vector3 operator-(Vector3 lhs, const float rhs) { return lhs -= rhs; }
    Vector3 operator*(Vector3 lhs, const float rhs) { return lhs *= rhs; }
    Vector3 operator/(Vector3 lhs, const float rhs) { return lhs /= rhs; }
    Vector3 operator+(const float lhs, Vector3 rhs) { return rhs += lhs; }
    Vector3 operator-(const float lhs, Vector3 rhs) { return rhs -= lhs; }
    Vector3 operator*(const float lhs, Vector3 rhs) { return rhs *= lhs; }
    Vector3 operator/(const float lhs, Vector3 rhs) { return rhs /= lhs; }
    Vector3 operator+(Vector3 lhs, const Vector3 rhs) { return lhs += rhs; }
    Vector3 operator-(Vector3 lhs, const Vector3 rhs) { return lhs -= rhs; }

    bool operator==(const Vector3 lhs, const Vector3 rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    bool operator!=(const Vector3 lhs, const Vector3 rhs)
    {
        return !(lhs == rhs);
    }

    struct Vector4
    {
        float x, y, z, w;

        Vector4() { x = y = z = w = 0.f; }
        Vector4(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }
    };

//    struct Quaternion
//    {
//        float x, y, z, w;
//
//        Quaternion() { x = y = z = w = 0.f; }
//        Quaternion(float f1, float f2, float f3, float f4) { x = f1; y = f2; z = f3; w = f4; }
//
//        Quaternion Euler(float m_fX, float m_fY, float m_fZ)
//        {
//            float m_fDeg2Rad = static_cast<float>(M_PI) / 180.f;
//
//            m_fX = m_fX * m_fDeg2Rad * 0.5f;
//            m_fY = m_fY * m_fDeg2Rad * 0.5f;
//            m_fZ = m_fZ * m_fDeg2Rad * 0.5f;
//
//            float m_fSinX = sinf(m_fX);
//            float m_fCosX = cosf(m_fX);
//
//            float m_fSinY = sinf(m_fY);
//            float m_fCosY = cosf(m_fY);
//
//            float m_fSinZ = sinf(m_fZ);
//            float m_fCosZ = cosf(m_fZ);
//
//            x = m_fCosY * m_fSinX * m_fCosZ + m_fSinY * m_fCosX * m_fSinZ;
//            y = m_fSinY * m_fCosX * m_fCosZ - m_fCosY * m_fSinX * m_fSinZ;
//            z = m_fCosY * m_fCosX * m_fSinZ - m_fSinY * m_fSinX * m_fCosZ;
//            w = m_fCosY * m_fCosX * m_fCosZ + m_fSinY * m_fSinX * m_fSinZ;
//
//            return *this;
//        }
//
//        Quaternion Euler(Vector3 m_vRot)
//        {
//            return Euler(m_vRot.x, m_vRot.y, m_vRot.z);
//        }
//
//        Vector3 ToEuler()
//        {
//            Vector3 m_vEuler;
//
//            float m_fDist = (x * x) + (y * y) + (z * z) + (w * w);
//
//            float m_fTest = x * w - y * z;
//            if (m_fTest > 0.4995f * m_fDist)
//            {
//                m_vEuler.x = static_cast<float>(M_PI) * 0.5f;
//                m_vEuler.y = 2.f * atan2f(y, x);
//                m_vEuler.z = 0.f;
//            }
//            else if (m_fTest < -0.4995f * m_fDist)
//            {
//                m_vEuler.x = static_cast<float>(M_PI) * -0.5f;
//                m_vEuler.y = -2.f * atan2f(y, x);
//                m_vEuler.z = 0.f;
//            }
//            else
//            {
//                m_vEuler.x = asinf(2.f * (w * x - y * z));
//                m_vEuler.y = atan2f(2.f * w * y + 2.f * z * x, 1.f - 2.f * (x * x + y * y));
//                m_vEuler.z = atan2f(2.f * w * z + 2.f * x * y, 1.f - 2.f * (z * z + x * x));
//            }
//
//            float m_fRad2Deg = 180.f / static_cast<float>(M_PI);
//            m_vEuler.x *= m_fRad2Deg;
//            m_vEuler.y *= m_fRad2Deg;
//            m_vEuler.z *= m_fRad2Deg;
//
//            return m_vEuler;
//        }
//    };

    struct Quaternion
    {
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            float data[4];
        };


        /**
         * Constructors.
         */
        inline Quaternion();
        inline Quaternion(float data[]);
        inline Quaternion(Vector3 vector, float scalar);
        inline Quaternion(float x, float y, float z, float w);


        /**
         * Constants for common quaternions.
         */
        static inline Quaternion Identity();


        /**
         * Returns the angle between two quaternions.
         * The quaternions must be normalized.
         * @param a: The first quaternion.
         * @param b: The second quaternion.
         * @return: A scalar value.
         */
        static inline float Angle(Quaternion a, Quaternion b);

        /**
         * Returns the conjugate of a quaternion.
         * @param rotation: The quaternion in question.
         * @return: A new quaternion.
         */
        static inline Quaternion Conjugate(Quaternion rotation);

        /**
         * Returns the dot product of two quaternions.
         * @param lhs: The left side of the multiplication.
         * @param rhs: The right side of the multiplication.
         * @return: A scalar value.
         */
        static inline float Dot(Quaternion lhs, Quaternion rhs);

        /**
         * Creates a new quaternion from the angle-axis representation of
         * a rotation.
         * @param angle: The rotation angle in radians.
         * @param axis: The vector about which the rotation occurs.
         * @return: A new quaternion.
         */
        static inline Quaternion FromAngleAxis(float angle, Vector3 axis);

        /**
         * Create a new quaternion from the euler angle representation of
         * a rotation. The z, x and y values represent rotations about those
         * axis in that respective order.
         * @param rotation: The x, y and z rotations.
         * @return: A new quaternion.
         */
        static inline Quaternion FromEuler(Vector3 rotation);

        /**
         * Create a new quaternion from the euler angle representation of
         * a rotation. The z, x and y values represent rotations about those
         * axis in that respective order.
         * @param x: The rotation about the x-axis in radians.
         * @param y: The rotation about the y-axis in radians.
         * @param z: The rotation about the z-axis in radians.
         * @return: A new quaternion.
         */
        static inline Quaternion FromEuler(float x, float y, float z);

        /**
         * Create a quaternion rotation which rotates "fromVector" to "toVector".
         * @param fromVector: The vector from which to start the rotation.
         * @param toVector: The vector at which to end the rotation.
         * @return: A new quaternion.
         */
        static inline Quaternion FromToRotation(Vector3 fromVector,
                                                Vector3 toVector);

        /**
         * Returns the inverse of a rotation.
         * @param rotation: The quaternion in question.
         * @return: A new quaternion.
         */
        static inline Quaternion Inverse(Quaternion rotation);

        /**
         * Interpolates between a and b by t, which is clamped to the range [0-1].
         * The result is normalized before being returned.
         * @param a: The starting rotation.
         * @param b: The ending rotation.
         * @return: A new quaternion.
         */
        static inline Quaternion Lerp(Quaternion a, Quaternion b, float t);

        /**
         * Interpolates between a and b by t. This normalizes the result when
         * complete.
         * @param a: The starting rotation.
         * @param b: The ending rotation.
         * @param t: The interpolation value.
         * @return: A new quaternion.
         */
        static inline Quaternion LerpUnclamped(Quaternion a, Quaternion b,
                                               float t);

        /**
         * Creates a rotation with the specified forward direction. This is the
         * same as calling LookRotation with (0, 1, 0) as the upwards vector.
         * The output is undefined for parallel vectors.
         * @param forward: The forward direction to look toward.
         * @return: A new quaternion.
         */
        static inline Quaternion LookRotation(Vector3 forward);

        /**
         * Creates a rotation with the specified forward and upwards directions.
         * The output is undefined for parallel vectors.
         * @param forward: The forward direction to look toward.
         * @param upwards: The direction to treat as up.
         * @return: A new quaternion.
         */
        static inline Quaternion LookRotation(Vector3 forward, Vector3 upwards);

        /**
         * Returns the norm of a quaternion.
         * @param rotation: The quaternion in question.
         * @return: A scalar value.
         */
        static inline float Norm(Quaternion rotation);

        /**
         * Returns a quaternion with identical rotation and a norm of one.
         * @param rotation: The quaternion in question.
         * @return: A new quaternion.
         */
        static inline Quaternion Normalized(Quaternion rotation);

        /**
         * Returns a new Quaternion created by rotating "from" towards "to" by
         * "maxRadiansDelta". This will not overshoot, and if a negative delta is
         * applied, it will rotate till completely opposite "to" and then stop.
         * @param from: The rotation at which to start.
         * @param to: The rotation at which to end.
         # @param maxRadiansDelta: The maximum number of radians to rotate.
         * @return: A new Quaternion.
         */
        static inline Quaternion RotateTowards(Quaternion from, Quaternion to,
                                               float maxRadiansDelta);

        /**
         * Returns a new quaternion interpolated between a and b, using spherical
         * linear interpolation. The variable t is clamped to the range [0-1]. The
         * resulting quaternion will be normalized.
         * @param a: The starting rotation.
         * @param b: The ending rotation.
         * @param t: The interpolation value.
         * @return: A new quaternion.
         */
        static inline Quaternion Slerp(Quaternion a, Quaternion b, float t);

        /**
         * Returns a new quaternion interpolated between a and b, using spherical
         * linear interpolation. The resulting quaternion will be normalized.
         * @param a: The starting rotation.
         * @param b: The ending rotation.
         * @param t: The interpolation value.
         * @return: A new quaternion.
         */
        static inline Quaternion SlerpUnclamped(Quaternion a, Quaternion b,
                                                float t);

        /**
         * Outputs the angle axis representation of the provided quaternion.
         * @param rotation: The input quaternion.
         * @param angle: The output angle.
         * @param axis: The output axis.
         */
        static inline void ToAngleAxis(Quaternion rotation, float &angle,
                                       Vector3 &axis);

        /**
         * Returns the Euler angle representation of a rotation. The resulting
         * vector contains the rotations about the z, x and y axis, in that order.
         * @param rotation: The quaternion to convert.
         * @return: A new vector.
         */
        static inline Vector3 ToEuler(Quaternion rotation);

        /**
         * Operator overloading.
         */
        inline struct Quaternion& operator+=(const float rhs);
        inline struct Quaternion& operator-=(const float rhs);
        inline struct Quaternion& operator*=(const float rhs);
        inline struct Quaternion& operator/=(const float rhs);
        inline struct Quaternion& operator+=(const Quaternion rhs);
        inline struct Quaternion& operator-=(const Quaternion rhs);
        inline struct Quaternion& operator*=(const Quaternion rhs);
    };

    inline Quaternion operator-(Quaternion rhs);
    inline Quaternion operator+(Quaternion lhs, const float rhs);
    inline Quaternion operator-(Quaternion lhs, const float rhs);
    inline Quaternion operator*(Quaternion lhs, const float rhs);
    inline Quaternion operator/(Quaternion lhs, const float rhs);
    inline Quaternion operator+(const float lhs, Quaternion rhs);
    inline Quaternion operator-(const float lhs, Quaternion rhs);
    inline Quaternion operator*(const float lhs, Quaternion rhs);
    inline Quaternion operator/(const float lhs, Quaternion rhs);
    inline Quaternion operator+(Quaternion lhs, const Quaternion rhs);
    inline Quaternion operator-(Quaternion lhs, const Quaternion rhs);
    inline Quaternion operator*(Quaternion lhs, const Quaternion rhs);
    inline Vector3 operator*(Quaternion lhs, const Vector3 rhs);
    inline bool operator==(const Quaternion lhs, const Quaternion rhs);
    inline bool operator!=(const Quaternion lhs, const Quaternion rhs);



/*******************************************************************************
 * Implementation
 */

    Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
    Quaternion::Quaternion(float data[]) : x(data[0]), y(data[1]), z(data[2]),
                                           w(data[3]) {}
    Quaternion::Quaternion(Vector3 vector, float scalar) : x(vector.x),
                                                           y(vector.y), z(vector.z), w(scalar) {}
    Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y),
                                                                 z(z), w(w) {}


    Quaternion Quaternion::Identity() { return Quaternion(0, 0, 0, 1); }


    float Quaternion::Angle(Quaternion a, Quaternion b)
    {
        float dot = Dot(a, b);
        return acos(fmin(fabs(dot), 1)) * 2;
    }

    Quaternion Quaternion::Conjugate(Quaternion rotation)
    {
        return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
    }

    float Quaternion::Dot(Quaternion lhs, Quaternion rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    Quaternion Quaternion::FromAngleAxis(float angle, Vector3 axis)
    {
        Quaternion q;
        float m = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
        float s = sin(angle / 2) / m;
        q.x = axis.x * s;
        q.y = axis.y * s;
        q.z = axis.z * s;
        q.w = cos(angle / 2);
        return q;
    }

    Quaternion Quaternion::FromEuler(Vector3 rotation)
    {
        return FromEuler(rotation.x, rotation.y, rotation.z);
    }

    Quaternion Quaternion::FromEuler(float x, float y, float z)
    {
        float cx = cos(x * 0.5);
        float cy = cos(y * 0.5);
        float cz = cos(z * 0.5);
        float sx = sin(x * 0.5);
        float sy = sin(y * 0.5);
        float sz = sin(z * 0.5);
        Quaternion q;
        q.x = cx * sy * sz + cy * cz * sx;
        q.y = cx * cz * sy - cy * sx * sz;
        q.z = cx * cy * sz - cz * sx * sy;
        q.w = sx * sy * sz + cx * cy * cz;
        return q;
    }

    Quaternion Quaternion::FromToRotation(Vector3 fromVector, Vector3 toVector)
    {
        float dot = Vector3::Dot(fromVector, toVector);
        float k = sqrt(Vector3::SqrMagnitude(fromVector) *
                       Vector3::SqrMagnitude(toVector));
        if (fabs(dot / k + 1) < 0.00001)
        {
            Vector3 ortho = Vector3::Orthogonal(fromVector);
            return Quaternion(Vector3::Normalized(ortho), 0);
        }
        Vector3 cross = Vector3::Cross(fromVector, toVector);
        return Normalized(Quaternion(cross, dot + k));
    }

    Quaternion Quaternion::Inverse(Quaternion rotation)
    {
        float n = Norm(rotation);
        return Conjugate(rotation) / (n * n);
    }

    Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
    {
        if (t < 0) return Normalized(a);
        else if (t > 1) return Normalized(b);
        return LerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        Quaternion quaternion;
        if (Dot(a, b) >= 0)
            quaternion = a * (1 - t) + b * t;
        else
            quaternion = a * (1 - t) - b * t;
        return Normalized(quaternion);
    }

    Quaternion Quaternion::LookRotation(Vector3 forward)
    {
        return LookRotation(forward, Vector3(0, 1, 0));
    }

    Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
    {
        // Normalize inputs
        forward = Vector3::Normalized(forward);
        upwards = Vector3::Normalized(upwards);
        // Don't allow zero vectors
        if (Vector3::SqrMagnitude(forward) < SMALL_float || Vector3::SqrMagnitude(upwards) < SMALL_float)
            return Quaternion::Identity();
        // Handle alignment with up direction
        if (1 - fabs(Vector3::Dot(forward, upwards)) < SMALL_float)
            return FromToRotation(Vector3::Forward(), forward);
        // Get orthogonal vectors
        Vector3 right = Vector3::Normalized(Vector3::Cross(upwards, forward));
        upwards = Vector3::Cross(forward, right);
        // Calculate rotation
        Quaternion quaternion;
        float radicand = right.x + upwards.y + forward.z;
        if (radicand > 0)
        {
            quaternion.w = sqrt(1.0 + radicand) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.w);
            quaternion.x = (upwards.z - forward.y) * recip;
            quaternion.y = (forward.x - right.z) * recip;
            quaternion.z = (right.y - upwards.x) * recip;
        }
        else if (right.x >= upwards.y && right.x >= forward.z)
        {
            quaternion.x = sqrt(1.0 + right.x - upwards.y - forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.x);
            quaternion.w = (upwards.z - forward.y) * recip;
            quaternion.z = (forward.x + right.z) * recip;
            quaternion.y = (right.y + upwards.x) * recip;
        }
        else if (upwards.y > forward.z)
        {
            quaternion.y = sqrt(1.0 - right.x + upwards.y - forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.y);
            quaternion.z = (upwards.z + forward.y) * recip;
            quaternion.w = (forward.x - right.z) * recip;
            quaternion.x = (right.y + upwards.x) * recip;
        }
        else
        {
            quaternion.z = sqrt(1.0 - right.x - upwards.y + forward.z) * 0.5;
            float recip = 1.0 / (4.0 * quaternion.z);
            quaternion.y = (upwards.z + forward.y) * recip;
            quaternion.x = (forward.x + right.z) * recip;
            quaternion.w = (right.y - upwards.x) * recip;
        }
        return quaternion;
    }

    float Quaternion::Norm(Quaternion rotation)
    {
        return sqrt(rotation.x * rotation.x +
                    rotation.y * rotation.y +
                    rotation.z * rotation.z +
                    rotation.w * rotation.w);
    }

    Quaternion Quaternion::Normalized(Quaternion rotation)
    {
        return rotation / Norm(rotation);
    }

    Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to,
                                         float maxRadiansDelta)
    {
        float angle = Quaternion::Angle(from, to);
        if (angle == 0)
            return to;
        maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
        float t = fmin(1, maxRadiansDelta / angle);
        return Quaternion::SlerpUnclamped(from, to, t);
    }

    Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
    {
        if (t < 0) return Normalized(a);
        else if (t > 1) return Normalized(b);
        return SlerpUnclamped(a, b, t);
    }

    Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t)
    {
        float n1;
        float n2;
        float n3 = Dot(a, b);
        bool flag = false;
        if (n3 < 0)
        {
            flag = true;
            n3 = -n3;
        }
        if (n3 > 0.999999)
        {
            n2 = 1 - t;
            n1 = flag ? -t : t;
        }
        else
        {
            float n4 = acos(n3);
            float n5 = 1 / sin(n4);
            n2 = sin((1 - t) * n4) * n5;
            n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
        }
        Quaternion quaternion;
        quaternion.x = (n2 * a.x) + (n1 * b.x);
        quaternion.y = (n2 * a.y) + (n1 * b.y);
        quaternion.z = (n2 * a.z) + (n1 * b.z);
        quaternion.w = (n2 * a.w) + (n1 * b.w);
        return Normalized(quaternion);
    }

    void Quaternion::ToAngleAxis(Quaternion rotation, float &angle, Vector3 &axis)
    {
        if (rotation.w > 1)
            rotation = Normalized(rotation);
        angle = 2 * acos(rotation.w);
        float s = sqrt(1 - rotation.w * rotation.w);
        if (s < 0.00001) {
            axis.x = 1;
            axis.y = 0;
            axis.z = 0;
        } else {
            axis.x = rotation.x / s;
            axis.y = rotation.y / s;
            axis.z = rotation.z / s;
        }
    }

    Vector3 Quaternion::ToEuler(Quaternion rotation)
    {
        float sqw = rotation.w * rotation.w;
        float sqx = rotation.x * rotation.x;
        float sqy = rotation.y * rotation.y;
        float sqz = rotation.z * rotation.z;
        // If normalized is one, otherwise is correction factor
        float unit = sqx + sqy + sqz + sqw;
        float test = rotation.x * rotation.w - rotation.y * rotation.z;
        Vector3 v;
        // Singularity at north pole
        if (test > 0.4995f * unit)
        {
            v.y = 2 * atan2(rotation.y, rotation.x);
            v.x = M_PI_2;
            v.z = 0;
            return v;
        }
        // Singularity at south pole
        if (test < -0.4995f * unit)
        {
            v.y = -2 * atan2(rotation.y, rotation.x);
            v.x = -M_PI_2;
            v.z = 0;
            return v;
        }
        // Yaw
        v.y = atan2(2 * rotation.w * rotation.y + 2 * rotation.z * rotation.x,
                    1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
        // Pitch
        v.x = asin(2 * (rotation.w * rotation.x - rotation.y * rotation.z));
        // Roll
        v.z = atan2(2 * rotation.w * rotation.z + 2 * rotation.x * rotation.y,
                    1 - 2 * (rotation.z * rotation.z + rotation.x * rotation.x));
        return v;
    }

    struct Quaternion& Quaternion::operator+=(const float rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        w += rhs;
        return *this;
    }

    struct Quaternion& Quaternion::operator-=(const float rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        w -= rhs;
        return *this;
    }

    struct Quaternion& Quaternion::operator*=(const float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    struct Quaternion& Quaternion::operator/=(const float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    struct Quaternion& Quaternion::operator+=(const Quaternion rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    struct Quaternion& Quaternion::operator-=(const Quaternion rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    struct Quaternion& Quaternion::operator*=(const Quaternion rhs)
    {
        Quaternion q;
        q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
        q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
        q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
        q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
        *this = q;
        return *this;
    }

    Quaternion operator-(Quaternion rhs) { return rhs * -1; }
    Quaternion operator+(Quaternion lhs, const float rhs) { return lhs += rhs; }
    Quaternion operator-(Quaternion lhs, const float rhs) { return lhs -= rhs; }
    Quaternion operator*(Quaternion lhs, const float rhs) { return lhs *= rhs; }
    Quaternion operator/(Quaternion lhs, const float rhs) { return lhs /= rhs; }
    Quaternion operator+(const float lhs, Quaternion rhs) { return rhs += lhs; }
    Quaternion operator-(const float lhs, Quaternion rhs) { return rhs -= lhs; }
    Quaternion operator*(const float lhs, Quaternion rhs) { return rhs *= lhs; }
    Quaternion operator/(const float lhs, Quaternion rhs) { return rhs /= lhs; }
    Quaternion operator+(Quaternion lhs, const Quaternion rhs)
    {
        return lhs += rhs;
    }
    Quaternion operator-(Quaternion lhs, const Quaternion rhs)
    {
        return lhs -= rhs;
    }
    Quaternion operator*(Quaternion lhs, const Quaternion rhs)
    {
        return lhs *= rhs;
    }

    Vector3 operator*(Quaternion lhs, const Vector3 rhs)
    {
        Vector3 u = Vector3(lhs.x, lhs.y, lhs.z);
        float s = lhs.w;
        return u * (Vector3::Dot(u, rhs) * 2)
               + rhs * (s * s - Vector3::Dot(u, u))
               + Vector3::Cross(u, rhs) * (2.0 * s);
    }

    bool operator==(const Quaternion lhs, const Quaternion rhs)
    {
        return lhs.x == rhs.x &&
               lhs.y == rhs.y &&
               lhs.z == rhs.z &&
               lhs.w == rhs.w;
    }

    bool operator!=(const Quaternion lhs, const Quaternion rhs)
    {
        return !(lhs == rhs);
    }

    struct Bounds
    {
        Vector3 m_vCenter;
        Vector3 m_vExtents;
    };

    struct Plane
    {
        Vector3 m_vNormal;
        float fDistance;
    };

    struct Ray
    {
        Vector3 m_vOrigin;
        Vector3 m_vDirection;
    };

    struct Rect
    {
        float fX, fY;
        float fWidth, fHeight;

        Rect() { fX = fY = fWidth = fHeight = 0.f; }
        Rect(float f1, float f2, float f3, float f4) { fX = f1; fY = f2; fWidth = f3; fHeight = f4; }
    };

    struct Color {
        float r, b, g, a;

        Color() {
            SetColor( 0 , 0 , 0 , 255 );
        }

        Color( float r , float g , float b ) {
            SetColor( r , g , b , 255 );
        }

        Color( float r, float g, float b, float a) {
            SetColor( r , g , b , a );
        }

        void SetColor( float r1 , float g1 , float b1 , float a1 = 255 ) {
            r = r1;
            g = g1;
            b = b1;
            a = a1;
        }

        static inline  Color Black(float a = 255){ return Color(0, 0, 0, a); }
        static inline  Color White(float a = 255){ return Color(255 , 255 , 255, a); }
        static inline  Color Red(float a = 255){ return Color(255 , 0 , 0, a); }
        static inline  Color Green(float a = 255){ return Color(0 , 255 , 0, a); }
        static inline  Color Blue(float a = 255){ return Color(0 , 0 , 255, a); }
        static inline  Color Yellow(float a = 255){ return Color(255 , 255 , 0, a); }
        static inline  Color Cyan(float a = 255){ return Color(0 , 255 , 255, a); }
        static inline  Color Magenta(float a = 255){ return Color(255 , 0 , 255, a); }
        static inline  Color FromHSB(float hue, float saturation, float brightness)
        {
            Color white = Color::White();

            float h = hue == 1.0f ? 0 : hue * 6.0f;
            float f = h - (int)h;
            float p = brightness * (1.0f - saturation);
            float q = brightness * (1.0f - saturation * f);
            float t = brightness * (1.0f - (saturation * (1.0f - f)));

            if (h < 1)
            {
                white.r = (brightness * 255.0f);
                white.g = (t * 255.0f);
                white.b = (p * 255.0f);
            }
            else if (h < 2)
            {
                white.r = (q * 255.0f);
                white.g = (brightness * 255.0f);
                white.b = (p * 255.0f);
            }
            else if (h < 3)
            {
                white.r = (p * 255.0f);
                white.g = (brightness * 255.0f);
                white.b = (t * 255.0f);
            }
            else if (h < 4)
            {
                white.r = (p * 255.0f);
                white.g = (q * 255.0f);
                white.b = (brightness * 255.0f);
            }
            else if (h < 5)
            {

                white.r = (t * 255.0f);
                white.g = (p * 255.0f);
                white.b = (brightness * 255.0f);
            }
            else
            {

                white.r = (brightness * 255.0f);
                white.g = (p * 255.0f);
                white.b = (q * 255.0f);
            }
            return white;
        }
    };

    struct Matrix4x4 {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;

        inline struct Matrix4x4& operator*=(const Matrix4x4 rhs);
    };

    inline Matrix4x4 operator*(Matrix4x4 lhs, const Matrix4x4 rhs);

    struct Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 m2)
    {
        Matrix4x4 m {
                _11 * m2._11 + _12 * m2._21 + _13 * m2._31 + _14 * m2._41,
                _11 * m2._12 + _12 * m2._22 + _13 * m2._32 + _14 * m2._42,
                _11 * m2._13 + _12 * m2._23 + _13 * m2._33 + _14 * m2._43,
                _11 * m2._14 + _12 * m2._24 + _13 * m2._34 + _14 * m2._44,

                _21 * m2._11 + _22 * m2._21 + _23 * m2._31 + _24 * m2._41,
                _21 * m2._12 + _22 * m2._22 + _23 * m2._32 + _24 * m2._42,
                _21 * m2._13 + _22 * m2._23 + _23 * m2._33 + _24 * m2._43,
                _21 * m2._14 + _22 * m2._24 + _23 * m2._34 + _24 * m2._44,

                _31 * m2._11 + _32 * m2._21 + _33 * m2._31 + _34 * m2._41,
                _31 * m2._12 + _32 * m2._22 + _33 * m2._32 + _34 * m2._42,
                _31 * m2._13 + _32 * m2._23 + _33 * m2._33 + _34 * m2._43,
                _31 * m2._14 + _32 * m2._24 + _33 * m2._34 + _34 * m2._44,

                _41 * m2._11 + _42 * m2._21 + _43 * m2._31 + _44 * m2._41,
                _41 * m2._12 + _42 * m2._22 + _43 * m2._32 + _44 * m2._42,
                _41 * m2._13 + _42 * m2._23 + _43 * m2._33 + _44 * m2._43,
                _41 * m2._14 + _42 * m2._24 + _43 * m2._34 + _44 * m2._44
        };

        *this = m;
        return *this;
    }

    Matrix4x4 operator*(Matrix4x4 lhs, const Matrix4x4 rhs)
    {
        return lhs *= rhs;
    }
}
