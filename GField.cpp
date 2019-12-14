#include <cmath>
#include <cassert>
#include "GField.h"
#include "GFNumber.h"

/**
 * Defines the default char.
 */
const long DEFAULT_CHAR = 2;

/**
 * Defins the default degree.
 */
const long DEFAULT_DEG = 1;

/**
 * Defines the smallest prime number.
 */
const int SMALLEST_PRIME = 2;

/**
 * Constructor that gets two arguments.
 * @param p The char argument.
 * @param l The degree argument.
 */
GField::GField(const long& p, const long& l)
{
    assert(l > 0);
    assert(isPrime(p));
    _char = std::abs(p);
    _deg = l;
}

/**
 * Constructor that gets only the char, and create a default l (1).
 * @param p The char argument.
 */
GField::GField(const long& p) : GField(p, DEFAULT_DEG) {}

/**
 * Default constructor.
 * Will create a default p (2) and a default l (1);
 */
GField::GField() : GField(DEFAULT_CHAR, DEFAULT_DEG) {}

/**
 * Copy constructor.
 * @param obj The object to copy from.
 */
GField::GField(const GField& obj) : GField(obj._char, obj._deg) {}

/**
 * @return The char of the object.
 */
const long& GField::getChar() const
{
    return _char;
}

/**
 * @return The degree of the object.
 */
const long& GField::getDegree() const
{
    return _deg;
}

/**
 * The order of the object - a power of the char with the degree.
 * @return
 */
long GField::getOrder() const
{
    return std::pow(_char, _deg);
}

/**
 * Checks if the given long is a prime number.
 * @param p A long to check if it's prime.
 * @return true if p is prime, false otherwise.
 */
bool GField::isPrime(long p)
{
    p = std::abs(p);
    if (p < SMALLEST_PRIME)
    {
        return false;
    }
    for (int i = SMALLEST_PRIME; i <= std::sqrt(p); i++)
    {
        if (p % i == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * Finds the greatest common divisor of the two given GFNumbers.
 * @param a The first GFNumber.
 * @param b The second GFNumber.
 * @return The greatest common divisor.
 */
GFNumber GField::gcd(const GFNumber& a, const GFNumber& b) const
{
    assert(a.getField() == *this);
    assert(b.getField() == *this);
    assert(a.getNumber() != 0 || b.getNumber() != 0);
    if (a.getNumber() == 0)
    {
        return b;
    }
    if (b.getNumber() == 0)
    {
        return a;
    }
    for (long i = std::min(a.getNumber(), b.getNumber()); i > 1; i--)
    {
        if (a.getNumber() % i == 0 && b.getNumber() % i == 0)
        {
            return createNumber(i);
        }
    }
    return createNumber(1);
}

/**
 * Creates a new GFNumber from this GField with the given k.
 * @param k The number to create.
 * @return The new GFNumber.
 */
GFNumber GField::createNumber(const long& k) const
{
    return GFNumber(k, *this);
}

/**
 * @param other Reference to another GField object.
 * @return true if this object's order and other's order are equal, false otherwise.
 */
bool GField::operator==(const GField& other) const
{
    return (getOrder() == other.getOrder());
}

/**
 * @param other Reference to another GField object.
 * @return true if this object's order and other's order are different, false otherwise.
 */
bool GField::operator!=(const GField& other) const
{
    return (getOrder() != other.getOrder());
}

/**
 * Prints the object to the given stream.
 * @param s Out stream to print to.
 * @param obj Object to print.
 * @return The given out stream.
 */
std::ostream& operator<<(std::ostream& s, const GField& obj)
{
    s << "GF(" << obj._char << "**" << obj._deg << ")";
    return s;
}

/**
 * Get GField object as an input and put it into the given obj.
 * @param s In stream to read the input from.
 * @param obj GField object to put the input object in.
 * @returnThe given in stream.
 */
std::istream& operator>>(std::istream& s, GField& obj)
{
    long p, l;
    if (!(s >> p >> l))
    {
        return s;
    }
    obj = GField(p, l);
    return s;
}
