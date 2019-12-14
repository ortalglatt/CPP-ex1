#ifndef EX1_GFNUMBER_H
#define EX1_GFNUMBER_H

#include "GField.h"


/**
 * GFNumber class, that has a GField - f, and a number - n.
 */
class GFNumber
{
private:
    GField _f;
    long _n;

    /**
     * Calculates the correct n that needs to be saved in the GFNumber, by getting the original n.
     */
    long _modulo(const long& n) const;

    /**
     * Finds a prime factor of this GFNumber by Pollard Rho algorithm, and put it to the given res
     * reference.
     * @param res A reference to the result GFNumber.
     * @return true if it fount a prime factor, and false otherwise.
     */
    bool _pollardRho(GFNumber& res) const;

    /**
     * The function that Pollard Rho algorithm use - x^2 +1.
     * @return The result of this function on this GFNumber.
     */
    GFNumber _pollardRhoFunction(const long& modulo) const;

    /**
     * Resize the given array, copy all the GFNumbers in the old array to a new array with
     * (new size = 2 * old size), delete the old array and put the new one in the given array
     * reference.
     * @param arr Reference to an array of GFNumber, the array to resize.
     * @param curSize The current size of the array.
     */
    static void _resizeArr(GFNumber*& arr, const int& curSize);

    /**
     * Adds this GFNumber to the given array, resize the array if needed.
     * @param arr Reference to an array of GFNumber.
     * @param counter The current number of GFNumber objects in the array.
     * @param arrLength The current array capacity.
     */
    void _addToArr(GFNumber*& arr, int& counter, int *arrLength);

    /**
     * Finds all the prime factors of this GFNumber by trial division, and add them to the given
     * result array.
     * @param result The array that will contain all the prime factors.
     * @param counter The current number of GFNumber objects in the array.
     * @param arrLength The current array capacity.
     */
    void _trialDivision(GFNumber*& result, int& counter, int *arrLength);

public:
    /**
     * Two arguments constructor.
     * @param n The number.
     * @param f The GField of this GFNumber.
     */
    GFNumber(const long& n, const GField& f);

    /**
     * Constructor that gets only the n, and create a default GField (2, 1).
     * @param n The number.
     */
    GFNumber(const long& n);

    /**
     * Default constructor - create a default n (0) and a default field (2, 1).
     */
    GFNumber();

    /**
     * Copy constructor.
     * @param other The object to copy from.
     */
    GFNumber(const GFNumber& other);

    /**
     * Destructor for the GFNumber object.
     */
    ~GFNumber() = default;

    /**
     * @return The n of this GFNumber.
     */
    const long& getNumber() const;

    /**
     * @return The GField of this GFNumber.
     */
    const GField& getField() const;

    /**
     * Finds all the prime factors of this GFNumber and save them in a dynamic allocated array, it
     * will save the factors amount in the given arrLength pointer.
     * @param arrLength The array length pointer.
     * @return The array of the prime factors, if n is prime - the array will be empty.
     */
    GFNumber *getPrimeFactors(int *arrLength) const;

    /**
     * Print all the prime factors of this GFNumber.
     */
    void printFactors() const;

    /**
     * Check f n is prime.
     * @return true if n is prime, false otherwise.
     */
    bool getIsPrime() const;

    /**
     * @param other Reference to another GFNumber object.
     * @return This object after putting in its data members the other's data members.
     */
    GFNumber& operator=(const GFNumber& other) = default;

    /**
     * @param other The object to add to this GFNumber.
     * @return The addition GFNumber of this and given GFNumber object.
     */
    GFNumber operator+(const GFNumber& other) const;

    /**
     * @param i long to add to this GFNumber.
     * @return The addition GFNumber of this and given long.
     */
    GFNumber operator+(const long& i) const;

    /**
     * Adds to this GFNumber the given GFNumber object.
     * @param other The object to add to this GFNumber.
     * @return This after the addition.
     */
    GFNumber& operator+=(const GFNumber& other);

    /**
     * Adds to this GFNumber the given long.
     * @param i long to add to this GFNumber.
     * @return This after the addition.
     */
    GFNumber& operator+=(const long& i);

    /**
     * @param other The object to subtract from this GFNumber.
     * @return The subtraction GFNumber of this and given GFNumber object.
     */
    GFNumber operator-(const GFNumber& other) const;

    /**
     * @param i long to subtract from this GFNumber.
     * @return The subtraction GFNumber of this and given long.
     */
    GFNumber operator-(const long& i) const;

    /**
     * Subtracts the given GFNumber object from this GFNumber.
     * @param other The object to subtract from this GFNumber.
     * @return This after the subtraction.
     */
    GFNumber& operator-=(const GFNumber& other);

    /**
     * Subtracts the given long from this GFNumber.
     * @param i long to subtract from this GFNumber.
     * @return This after the subtraction.
     */
    GFNumber& operator-=(const long& i);

    /**
     * @param other The object to multiply this GFNumber by.
     * @return The multiplication GFNumber of this and given GFNumber object.
     */
    GFNumber operator*(const GFNumber& other) const;

    /**
     * @param i long to to multiply this GFNumber by.
     * @return The multiplication GFNumber of this and given long.
     */
    GFNumber operator*(const long& i) const;

    /**
     * Multiply this GFNumber by the given GFNumber object.
     * @param other The object to multiply this GFNumber by.
     * @return This after the multiplication.
     */
    GFNumber& operator*=(const GFNumber& other);

    /**
     * Multiply this GFNumber by the given long.
     * @param i long to multiply this GFNumber by.
     * @return This after the multiplication.
     */
    GFNumber& operator*=(const long& i);

    /**
     * @param other The object to modulo this GFNumber by.
     * @return The modulo GFNumber of this by the given GFNumber object.
     */
    GFNumber operator%(const GFNumber& other) const;

    /**
     * @param i long to to modulo this GFNumber by.
     * @return The modulo GFNumber of this by the given long.
     */
    GFNumber operator%(const long& i) const;

    /**
     * Modulo this GFNumber by the given GFNumber object.
     * @param other The object to modulo this GFNumber by.
     * @return This after the modulo operation.
     */
    GFNumber& operator%=(const GFNumber& other);

    /**
     * Modulo this GFNumber by the given long.
     * @param i long to modulo this GFNumber by.
     * @return This after the modulo operation.
     */
    GFNumber& operator%=(const long& i);

    /**
     * @param other Reference to another GFNumber object.
     * @return true if the n's are equal and the fields are equal, false otherwise.
     */
    bool operator==(const GFNumber& other) const;

    /**
     * @param other Reference to another GFNumber object.
     * @return true if the n's are different or the fields are different, false otherwise.
     */
    bool operator!=(const GFNumber& other) const;

    /**
     * @param other Reference to another GFNumber object.
     * @return true if this n is smaller than other's n, false otherwise.
     */
    bool operator<(const GFNumber& other) const;

    /**
     * @param other Reference to another GFNumber object.
     * @return true if this n is smaller or equal to other's n, false otherwise.
     */
    bool operator<=(const GFNumber& other) const;

    /**
     * @param other Reference to another GFNumber object.
     * @return true if this n is bigger than other's n, false otherwise.
     */
    bool operator>(const GFNumber& other) const;

    /**
     * @param other Reference to another GFNumber object.
     * @return true if this n is bigger or equal to other's n, false otherwise.
     */
    bool operator>=(const GFNumber& other) const;

    /**
     * Prints the object to the given stream.
     * @param s Out stream to print to.
     * @param obj Object to print.
     * @return The given out stream.
     */
    friend std::ostream& operator<<(std::ostream& s, const GFNumber& obj);

    /**
     * Get GFNumber object as an input and put init to the given obj.
     * @param s In stream to read the input from.
     * @param obj GFNumber object to put the input object in.
     * @returnThe given in stream.
     */
    friend std::istream& operator>>(std::istream& s, GFNumber& obj);

};

#endif //EX1_GFNUMBER_H
