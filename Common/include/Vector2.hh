#pragma once

#include <string>
#include <array>
#include <type_traits>

namespace Vector
{
  template<typename T>
  class	Vector2
  {
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");

  private:
    std::array<T, 2> _values;

  public:

    Vector2<T>() : _values({ 0, 0 }) {}
    Vector2<T>(const T &x, const T &y) : _values({ x, y }) {}

    ~Vector2<T>() {}

    Vector2<T>(const Vector2<T> &v)
    {
      this->_values[0] = v.x();
      this->_values[1] = v.y();
    }

    Vector2<T>& operator=(const Vector2<T>& v)
    {
      this->_values[0] = v.x();
      this->_values[1] = v.y();
      return *this;
    }

    T const x() const
    {
      return _values[0];
    }

    T const y() const
    {
      return _values[1];
    }

    void x(const T &val)
    {
      _values[0] = val;
    }

    void y(const T &val)
    {
      _values[1] = val;
    }

    Vector2<T> &normalize()
    {
      //static_assert(std::is_integral<T>::value, "Unable to normalise an Integer-Type Vector2");

      T norm = sqrt(_values[0] * _values[0] + _values[1] * _values[1]);
      if (norm != T(0.0)) {
        _values[0] /= norm;
        _values[1] /= norm;
      }

      return *this;
    }

    Vector2<T> &operator+=(const Vector2<T> &other)
    {
      _values[0] += other.x();
      _values[1] += other.y();
      return *this;
    }

    Vector2<T> &operator-=(const Vector2<T> &other)
    {
      _values[0] -= other.x();
      _values[1] -= other.y();
      return *this;
    }

    Vector2<T> &operator*=(const T& val)
    {
      _values[0] *= val;
      _values[1] *= val;
      return *this;
    }

    Vector2<T> &operator/=(const T& val)
    {
      _values[0] /= val;
      _values[1] /= val;
      return *this;
    }

    std::string toString() const
    {
      std::string type = typeid(T).name();

      return "type : " + type + " // x : " + std::to_string(_values[0]) + " y : " + std::to_string(_values[1]);
    }

    static const Vector2<T> Right;
    static const Vector2<T> Up;
    static const Vector2<T> Zero;
    static const Vector2<T> One;
  };

  static const float epsilon = 00000.1f;

  template<typename T>
  Vector2<T> const operator+(const Vector2<T>& v1, const Vector2<T>& v2)
  {
    return Vector2<T>(v1.x() + v2.x(), v1.y() + v2.y());
  }

  template<typename T>
  Vector2<T> const operator-(const Vector2<T>& v1, const Vector2<T>& v2)
  {
    return Vector2<T>(v1.x() - v2.x(), v1.y() - v2.y());
  }

  template<typename T>
  Vector2<T> operator-(const Vector2<T>& v)
  {
    return Vector2<T>(-v.x(), -v.y());
  }

  template<typename T>
  Vector2<T> operator*(const Vector2<T>& v1, float f)
  {
    return Vector2<T>(v1.x() * f, v1.y() * f);
  }

  template<typename T>
  Vector2<T> operator*(float f, const Vector2<T>& v1)
  {
    return (v1 * f);
  }

  template<typename T>
  Vector2<T> operator/(const Vector2<T>& v1, float f)
  {
    return Vector2<T>(v1.x() / f, v1.y() / f);
  }

  template<typename T>
  Vector2<T> operator/(float f, const Vector2<T>& v1)
  {
    return (v1 / f);
  }

  template<typename T, typename U>
  Vector2<U> normalized(const Vector2<T>& v)
  {
    static_assert(std::is_floating_point<U>::value, "Return type must be a floating point type");

    U norm = std::sqrt(v.x() * v.x() + v.y() * v.y());
    if (norm == 0)
      return Vector::Vector2<U>::Zero;
    return Vector2<U>(static_cast<U>(v.x() / norm), static_cast<U>(v.y() / norm));
  }

  template<typename T, typename U>
  U magnitude(const Vector2<T>& v)
  {
    static_assert(std::is_floating_point<U>::value, "Return type must be a floating point type");

    return static_cast<U>(std::sqrt(v.x() * v.x() + v.y() * v.y()));
  }


  template<typename T>
  Vector2<T> const sign(const Vector2<T>& v)
  {
    return Vector2<T>(v.x() == 0 ? 0 : v.x() / std::abs(v.x()), v.y() == 0 ? 0 : v.y() / std::abs(v.y()));
  }

  template<typename T>
  const Vector2<T> operator*(const Vector2<T>& v1, const Vector2<T>& v2)
  {
    return Vector2<T>(v1.x() * v2.x(), v1.y() * v2.y());
  }

  template<typename T>
  bool operator==(const Vector2<T>& v1, const Vector2<T>& v2)
  {
    return (v1.x() == v2.x() && v1.y() == v2.y());
  }

  template<typename T>
  bool operator!=(const Vector2<T>& v1, const Vector2<T>& v2)
  {
    return (!(v1 == v2));
  }

  template<typename T>
  const Vector::Vector2<T> Vector::Vector2<T>::Right(1, 0);

  template<typename T>
  const Vector::Vector2<T> Vector::Vector2<T>::Up(0, 1);

  template<typename T>
  const Vector::Vector2<T> Vector::Vector2<T>::Zero(0, 0);

  template<typename T>
  const Vector::Vector2<T> Vector::Vector2<T>::One(1, 1);
}