#include "GFNumber.h"
#include <cassert>
#include <random>

/**
 * Define the default n value.
 */
const long DEFAULT_N = 0;

/**
 * Defines the smallest odd prime number.
 */
const int SMALLEST_ODD_PRIME = 3;


/**
 * Two arguments constructor.
 * @param n The number.
 * @param f The GField of this GFNumber.
 */
GFNumber::GFNumber(const long& n, const GField& f) : _f(f), _n(_modulo(n)) {}

/**
 * Constructor that gets only the n, and create a default GField (2, 1).
 * @param n The number.
 */
GFNumber::GFNumber(const long& n) : _n(_modulo(n)){}

/**
 * Default constructor - create a default n (0) and a default field (2, 1).
 */
GFNumber::GFNumber() : _n(DEFAULT_N) {}

/**
 * Copy constructor.
 * @param other The object to copy from.
 */
GFNumber::GFNumber(const GFNumber& other) : _f(other.getField()), _n(other.getNumber()) {}

/**
 * Calculates the correct n that needs to be saved in the GFNumber, by getting the original n.
 */
long GFNumber::_modulo(const long& n) const
{
    long order = _f.getOrder();
    if (n >= 0)
    {
        return n % order;
    }
    return order + n % order;
}

/**
 * @return The n of this GFNumber.
 */
const long& GFNumber::getNumber() const
{
    return _n;
}

/**
 * @return The GField of this GFNumber.
 */
const GField& GFNumber::getField() const
{
    return _f;
}

/**
 * The function that Pollard Rho algorithm use - x^2 +1.
 * @return The result of this function on this GFNumber.
 */
GFNumber GFNumber::_pollardRhoFunction(const long& modulo) const
{
    long res = _n * _n + 1;
    return _f.createNumber(res % modulo);
}

/**
 * Finds a prime factor of this GFNumber by Pollard Rho algorithm, and put it to the given res
 * reference.
 * @param res A reference to the result GFNumber.
 * @return true if it fount a prime factor, and false otherwise.
 */
bool GFNumber::_pollardRho(GFNumber& res) const
{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<> random(1, _n - 1);
    GFNumber x = _f.createNumber(random(gen));
    GFNumber y = x;
    GFNumber p = _f.createNumber(1);
    GFNumber temp;
    while (p.getNumber() == 1)
    {
        x = x._pollardRhoFunction(_n);
        y = y._pollardRhoFunction(_n)._pollardRhoFunction(_n);
        temp = (x > y) ? (x - y) : (y - x);
        p = _f.gcd(temp, *this);
    }
    if (p == *this)
    {
        return false;
    }
    res = p;
    return true;
}

/**
 * Resize the given array, copy all the GFNumbers in the old array to a new array with
 * (new size = 2 * old size), delete the old array and put the new one in the given array
 * reference.
 * @param arr Reference to an array of GFNumber, the array to resize.
 * @param curSize The current size of the array.
 */
void GFNumber::_resizeArr(GFNumber*& arr, const int& curSize)
{
    GFNumber *temp = arr;
    int newSize = (curSize == 0) ? 1 : curSize * 2;
    arr = new GFNumber[newSize];
    for (int i = 0; i < curSize; i++)
    {
        arr[i] = temp[i];
    }
    delete[] temp;
}

/**
 * Adds this GFNumber to the given array, resize the array if needed.
 * @param arr Reference to an array of GFNumber.
 * @param counter The current number of GFNumber objects in the array.
 * @param arrLength The current array capacity.
 */
void GFNumber::_addToArr(GFNumber*& arr, int& counter, int* arrLength)
{
    if (counter + 1 > *arrLength)
    {
        _resizeArr(arr, *arrLength);
        *arrLength = (*arrLength == 0) ? 1 : *arrLength * 2;
    }
    arr[counter++] = *this;
}

/**
 * Finds all the prime factors of this GFNumber by trial division, and add them to the given
 * result array.
 * @param result The array that will contain all the prime factors.
 * @param counter The current number of GFNumber objects in the array.
 * @param arrLength The current array capacity.
 */
void GFNumber::_trialDivision(GFNumber*& result, int& counter, int *arrLength)
{
    GFNumber zeroGFN = _f.createNumber(0);
    long i = SMALLEST_ODD_PRIME;
    while (i * i <= _n)
    {
        if (*this % i == zeroGFN)
        {
            GFNumber tempGFN = _f.createNumber(i);
            tempGFN._addToArr(result, counter, arrLength);
            *this =  _f.createNumber(_n / i);
        }
        else
        {
            i += 2;
        }
    }
}

/**
 * Finds all the prime factors of this GFNumber and save them in a dynamic allocated array, it
 * will save the factors amount in the given arrLength pointer.
 * @param arrLength The array length pointer.
 * @return The array of the prime factors, if n is prime - the array will be empty.
 */
GFNumber *GFNumber::getPrimeFactors(int* arrLength) const
{
    *arrLength = 0;
    int counter = 0;
    GFNumber *result = new GFNumber[*arrLength];
    if (_n == 0 || _n == 1 || getIsPrime())
    {
        return result;
    }
    GFNumber num = *this;
    const GFNumber zeroGFN = _f.createNumber(0);
    GFNumber twoGFN = _f.createNumber(2);
    while (num % 2 == zeroGFN && num != twoGFN)
    {
        twoGFN._addToArr(result, counter, arrLength);
        num._n = num._n / 2;
    }
    while (!num.getIsPrime())
    {
        GFNumber tempGFN;
        if (!num._pollardRho(tempGFN))
        {
            break;
        }
        if (tempGFN.getIsPrime())
        {
            tempGFN._addToArr(result, counter, arrLength);
        }
        else
        {
            tempGFN._trialDivision(result, counter, arrLength);
        }
        num._n = num._n / tempGFN._n;
    }
    if (!num.getIsPrime())
    {
        num._trialDivision(result, counter, arrLength);
    }
    if (num._n > 1)
    {
        num._addToArr(result, counter, arrLength);
    }
    *arrLength = counter;
    return result;
}

/**
 * Print all the prime factors of this GFNumber.
 */
void GFNumber::printFactors() const
{
    int arrLength = 0;
    GFNumber* primeFactors = getPrimeFactors(&arrLength);
    std::cout << _n << "=";
    if (arrLength == 0)
    {
        std::cout << _n << "*1" << std::endl;
    }
    else
    {
        for (int i = 0; i < arrLength - 1; i++)
        {
            std::cout << primeFactors[i]._n << "*";
        }
        std::cout << primeFactors[arrLength - 1]._n << std::endl;
    }
    delete[] primeFactors;
}

/**
 * Check f n is prime.
 * @return true if n is prime, false otherwise.
 */
bool GFNumber::getIsPrime() const
{
    return (GField::isPrime(_n));
}

/**
 * @param other The object to add to this GFNumber.
 * @return The addition GFNumber of this and given GFNumber object.
 */
GFNumber GFNumber::operator+(const GFNumber& other) const
{
    assert(_f == other.getField());
    return _f.createNumber(_n + other.getNumber());
}

/**
 * @param i long to add to this GFNumber.
 * @return The addition GFNumber of this and given long.
 */
GFNumber GFNumber::operator+(const long& i) const
{
    return _f.createNumber(_n + i);
}

/**
 * Adds to this GFNumber the given GFNumber object.
 * @param other The object to add to this GFNumber.
 * @return This after the addition.
 */
GFNumber& GFNumber::operator+=(const GFNumber& other)
{
    assert(_f == other.getField());
    _n = (_n + other.getNumber()) % _f.getOrder();
    return *this;
}

/**
 * Adds to this GFNumber the given long.
 * @param i long to add to this GFNumber.
 * @return This after the addition.
 */
GFNumber& GFNumber::operator+=(const long& i)
{
    _n = _modulo(_n + i);
    return *this;
}

/**
 * @param other The object to subtract from this GFNumber.
 * @return The subtraction GFNumber of this and given GFNumber object.
 */
GFNumber GFNumber::operator-(const GFNumber& other) const
{
    assert(_f == other.getField());
    return _f.createNumber(_n - other.getNumber());
}

/**
 * @param i long to subtract from this GFNumber.
 * @return The subtraction GFNumber of this and given long.
 */
GFNumber GFNumber::operator-(const long& i) const
{
    return _f.createNumber(_n - i);
}

/**
 * Subtracts the given GFNumber object from this GFNumber.
 * @param other The object to subtract from this GFNumber.
 * @return This after the subtraction.
 */
GFNumber& GFNumber::operator-=(const GFNumber& other)
{
    assert(_f == other.getField());
    _n = _modulo(_n - other.getNumber());
    return *this;
}

/**
 * Subtracts the given long from this GFNumber.
 * @param i long to subtract from this GFNumber.
 * @return This after the subtraction.
 */
GFNumber& GFNumber::operator-=(const long& i)
{
    _n = _modulo(_n - i);
    return *this;
}

/**
 * @param other The object to multiply this GFNumber by.
 * @return The multiplication GFNumber of this and given GFNumber object.
 */
GFNumber GFNumber::operator*(const GFNumber& other) const
{
    assert(_f == other.getField());
    return _f.createNumber(_n * other.getNumber());
}

/**
 * @param i long to to multiply this GFNumber by.
 * @return The multiplication GFNumber of this and given long.
 */
GFNumber GFNumber::operator*(const long& i) const
{
    return _f.createNumber(_n * i);
}

/**
 * Multiply this GFNumber by the given GFNumber object.
 * @param other The object to multiply this GFNumber by.
 * @return This after the multiplication.
 */
GFNumber& GFNumber::operator*=(const GFNumber& other)
{
    assert(_f == other.getField());
    _n = (_n * other.getNumber()) % _f.getOrder();
    return *this;
}

/**
 * Multiply this GFNumber by the given long.
 * @param i long to multiply this GFNumber by.
 * @return This after the multiplication.
 */
GFNumber& GFNumber::operator*=(const long& i)
{
    _n = _modulo(_n * i);
    return *this;
}

/**
 * @param other The object to modulo this GFNumber by.
 * @return The modulo GFNumber of this by the given GFNumber object.
 */
GFNumber GFNumber::operator%(const GFNumber& other) const
{
    assert(_f == other.getField());
    assert(other.getNumber() != 0);
    return _f.createNumber(_n % other.getNumber());
}

/**
 * @param i long to to modulo this GFNumber by.
 * @return The modulo GFNumber of this by the given long.
 */
GFNumber GFNumber::operator%(const long& i) const
{
    long correctI = _modulo(i);
    assert(correctI != 0);
    return _f.createNumber(_n % correctI);
}

/**
 * Modulo this GFNumber by the given GFNumber object.
 * @param other The object to modulo this GFNumber by.
 * @return This after the modulo operation.
 */
GFNumber& GFNumber::operator%=(const GFNumber& other)
{
    assert(_f == other.getField());
    assert(other.getNumber() != 0);
    _n %= other.getNumber();
    return *this;
}

/**
 * Modulo this GFNumber by the given long.
 * @param i long to modulo this GFNumber by.
 * @return This after the modulo operation.
 */
GFNumber& GFNumber::operator%=(const long& i)
{
    assert(i != 0);
    long correctI = _modulo(i);
    _n %= correctI;
    return *this;
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if the n's are equal and the fields are equal, false otherwise.
 */
bool GFNumber::operator==(const GFNumber& other) const
{
    return (_n == other.getNumber() && _f == other.getField());
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if the n's are different or the fields are different, false otherwise.
 */
bool GFNumber::operator!=(const GFNumber& other) const
{
    return (_n != other.getNumber() || _f != other.getField());
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if this n is smaller than other's n, false otherwise.
 */
bool GFNumber::operator<(const GFNumber& other) const
{
    return (_n < other.getNumber());
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if this n is smaller or equal to other's n, false otherwise.
 */
bool GFNumber::operator<=(const GFNumber& other) const
{
    return (_n <= other.getNumber());
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if this n is bigger than other's n, false otherwise.
 */
bool GFNumber::operator>(const GFNumber& other) const
{
    return (_n > other.getNumber());
}

/**
 * @param other Reference to another GFNumber object.
 * @return true if this n is bigger or equal to other's n, false otherwise.
 */
bool GFNumber::operator>=(const GFNumber& other) const
{
    return (_n >= other.getNumber());
}

/**
 * Prints the object to the given stream.
 * @param s Out stream to print to.
 * @param obj Object to print.
 * @return The given out stream.
 */
std::ostream& operator<<(std::ostream& s, const GFNumber& obj)
{
    s << obj.getNumber() << " " << obj.getField();
    return s;
}

/**
 * Get GFNumber object as an input and put init to the given obj.
 * @param s In stream to read the input from.
 * @param obj GFNumber object to put the input object in.
 * @returnThe given in stream.
 */
std::istream& operator>>(std::istream& s, GFNumber& obj)
{
    long n;
    GField f;
    if (!(s >> n >> f))
    {
        return s;
    }
    obj = GFNumber(n, f);
    return s;
}
