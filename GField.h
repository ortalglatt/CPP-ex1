#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H

#include <iostream>

class GFNumber;

/**
 * GField class, that has a char - p, and a degree - l.
 */
class GField
{
private:
    long _char, _deg;

public:
    /**
     * Constructor that gets two arguments.
     * @param p The char argument.
     * @param l The degree argument.
     */
    GField(const long& p, const long& l);

    /**
     * Constructor that gets only the char, and create a default l (1).
     * @param p The char argument.
     */
    GField(const long& p);

    /**
     * Default constructor.
     * Will create a default p (2) and a default l (1);
     */
    GField();

    /**
     * Copy constructor.
     * @param obj The object to copy from.
     */
    GField(const GField& obj);

    /**
     * Destructor for the GField object.
     */
    ~GField() = default;

    /**
     * @return The char of the object.
     */
    const long& getChar() const ;

    /**
     * @return The degree of the object.
     */
    const long& getDegree() const;

    /**
     * The order of the object - a power of the char with the degree.
     * @return
     */
    long getOrder() const;

    /**
     * Checks if the given long is a prime number.
     * @param p A long to check if it's prime.
     * @return true if p is prime, false otherwise.
     */
    static bool isPrime(long p);

    /**
     * Finds the greatest common divisor of the two given GFNumbers.
     * @param a The first GFNumber.
     * @param b The second GFNumber.
     * @return The greatest common divisor.
     */
    GFNumber gcd(const GFNumber& a, const GFNumber& b) const;

    /**
     * Creates a new GFNumber from this GField with the given k.
     * @param k The number to create.
     * @return The new GFNumber.
     */
    GFNumber createNumber(const long& k) const;

    /**
     * @param other Reference to another GField object.
     * @return This object after putting in its data members the other's data members.
     */
    GField& operator=(const GField& other) = default;

    /**
     * @param other Reference to another GField object.
     * @return true if this object's order and other's order are equal, false otherwise.
     */
    bool operator==(const GField& other) const;

    /**
     * @param other Reference to another GField object.
     * @return true if this object's order and other's order are different, false otherwise.
     */
    bool operator!=(const GField& other) const;

    /**
     * Prints the object to the given stream.
     * @param s Out stream to print to.
     * @param obj Object to print.
     * @return The given out stream.
     */
    friend std::ostream& operator<<(std::ostream& s, const GField& obj);

    /**
     * Get GField object as an input and put it into the given obj.
     * @param s In stream to read the input from.
     * @param obj GField object to put the input object in.
     * @returnThe given in stream.
     */
    friend std::istream& operator>>(std::istream& s, GField& obj);
};

#endif //EX1_GFIELD_H
