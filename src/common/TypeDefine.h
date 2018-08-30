//
// Created by Lewis on 2017/2/17.
//

#ifndef ELFBOX_TYPEDEFINE_H
#define ELFBOX_TYPEDEFINE_H

#include <string>
#include <math.h>

namespace elfbox
{

#ifdef ELFBOX_UINT32_IS_ULONG
typedef long int32_;
typedef unsigned long uint32_;
#else
typedef int int32_;
typedef unsigned int uint32_;
#endif

typedef unsigned char uint8_;
typedef unsigned short uint16_;
typedef unsigned short ushort_;
typedef unsigned long ulong_;

#if defined(__STDC__) || defined(__cplusplus)
typedef signed char int8_;
#else
typedef char int8_;
#endif

typedef short int16_;
typedef short short_;
typedef long long_;

typedef char char_;
typedef wchar_t wchar_;

typedef float float_;
typedef double double_;

typedef unsigned char byte_;
typedef unsigned short word_;
typedef uint32_ dword_;

typedef bool bool_;

#ifdef _SZ_NO_INT_64

/* define _SZ_NO_INT_64, if your compiler doesn't support 64-bit integers.
       NOTES: Some code will work incorrectly in that case! */

    typedef long_ int64_;
    typedef unsigned long_ uint64_;

#else

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef __int64 int64_;
    typedef unsigned __int64 uint64_;
#define UINT64_CONST(n) n
#else
//typedef long_ long_ int32_ int64_;
//typedef unsigned long_ long_ int32_ uint64_;
#define UINT64_CONST(n) n ## ULL
#endif

#endif

#ifdef _LWDP_NO_SYSTEM_SIZE_T
typedef L_UINT32    size_t_;
#else
typedef size_t size_t_;
#endif

#ifdef _UNICODE
typedef std::wstring tstring;
typedef wchar_ tchar_;
#else
typedef std::string tstring;
typedef char_ tchar_;
#endif

template <class T>
struct Point2D
{
    T x;
    T y;

    Point2D<T> operator-(Point2D<T> other)
    {
        return Point2D<T>(x - other.x, y - other.y);
    }
    Point2D<T> operator+(Point2D<T> other)
    {
        return Point2D<T>(x + other.x, y + other.y);
    }
    Point2D<T> operator*(Point2D<T> other)
    {
        return Point2D<T>(x * other.x, y * other.y);
    }
    Point2D<T> operator*(T other)
    {
        return Point2D<T>(x * other, y * other);
    }
    T distance(Point2D<T> other)
    {
        return (T)abs(sqrt((other.x - x)*(other.x - x) + (other.y - y)*(other.y - y)));
    }

    Point2D<T>(): x(0), y(0) {}
    Point2D<T>(T rx, T ry): x(rx), y(ry) {}
    Point2D<T>(const Point2D<T>& other)
    {
        x = other.x;
        y = other.y;
    }
};

typedef Point2D<int> Point2DInt;
typedef Point2D<float> Point2DFloat;

template <class T>
struct Vector2D : public Point2D<T>
{
    T length()
    {
        return static_cast<T>(sqrt(x*x + y*y));
        //return static_cast<T>(0);
    }

    Vector2D(T rx, T ry): Point2D<T>(rx, ry) {}
    Vector2D(const Point2D<T> other)
    {
        x = other.x;
        y = other.y;
    }
    void normalize()
    {
        float length = sqrt(x*x + y*y);

        x = x / length;
        y = y / length;
    }
};

typedef Vector2D<float> Vector2DFloat;

template <class T>
struct Rect
{
    T x, y;
    T w, h;

    void setPosition(const Point2D<T>& position)
    {
        x = position.x;
        y = position.y;
    }

    Point2D<T> getPosition()
    {
        return Point2D<T>(x, y);
    }

    Point2D<T> getCenter()
    {
        return Point2D<T>(x + w / 2.0f, y + h / 2.0f);
    }

    Point2D<T> getUpperLeft()
    {
        return getPosition();
    }

    Point2D<T> getBottomLeft()
    {
        Point2D<T> point = getPosition();
        return Point2D<T>(point.x, point.y + h);
    }
    Point2D<T> getBottomRight()
    {
        Point2D<T> point = getPosition();
        return Point2D<T>(point.x + w, point.y + h);
    }
    Point2D<T> getUpperRight()
    {
        Point2D<T> point = getPosition();
        return Point2D<T>(point.x + w, point.y);
    }

    bool isInRect(const Point2D<T>& point)
    {
        if (point.x < x || point.y < y)
            return false;

        if (point.x > (x + w) || point.y > (y + h))
            return false;

        return true;
    }

    bool isIntersectionRect(Rect<T> rect)
    {
        Point2DFloat upperLeft = rect.getUpperLeft();
        if (isInRect(upperLeft))
            return true;
        Point2DFloat bottomLeft = rect.getBottomLeft();
        if (isInRect(bottomLeft))
            return true;
        Point2DFloat bottomRight = rect.getBottomRight();
        if (isInRect(bottomRight))
            return true;
        Point2DFloat upperRight = rect.getUpperRight();
        if (isInRect(upperRight))
            return true;

        //other
        Point2DFloat upperLeftSelf = getUpperLeft();
        if (rect.isInRect(upperLeftSelf))
            return true;
        Point2DFloat bottomLeftSelf = getBottomLeft();
        if (rect.isInRect(bottomLeftSelf))
            return true;
        Point2DFloat bottomRightSelf = getBottomRight();
        if (rect.isInRect(bottomRightSelf))
            return true;
        Point2DFloat upperRightSelf = getUpperRight();
        if (rect.isInRect(upperRightSelf))
            return true;

        //return false;

        Point2DFloat selfCenter(x + w/2.0f, y + h/2.0f);
        Point2DFloat otherCenter(rect.x + rect.w/2.0f, rect.y + rect.h/2.0f);

        float verticalDistance = abs(int(selfCenter.x - otherCenter.x));
        float horizontalDistance = abs(int(selfCenter.y - otherCenter.y));

        return (verticalDistance < (h / 2.0f + rect.h / 2.0f)) &&
                   (horizontalDistance < (w / 2.0f + rect.w / 2.0f))
               ? true : false;
    }

    bool isIncludeRect(Rect<T> rect)
    {
        Point2DFloat upperLeft = rect.getUpperLeft();
        if (!isInRect(upperLeft))
            return false;
        Point2DFloat bottomLeft = rect.getBottomLeft();
        if (!isInRect(bottomLeft))
            return false;
        Point2DFloat bottomRight = rect.getBottomRight();
        if (!isInRect(bottomRight))
            return false;
        Point2DFloat upperRight = rect.getUpperRight();
        if (!isInRect(upperRight))
            return false;

        return true;
    }

    Rect(): x(0), y(0),
        w(0), h(0) {}

    Rect(T rx, T ry, T rw, T rh):x(rx), y(ry),
           w(rw), h(rh) {}
    Rect(const Rect& other)
    {
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
    }
};
typedef Rect<int> RectInt;
typedef Rect<float> RectFloat;
}
#endif //ELFBOX_TYPEDEFINE_H
