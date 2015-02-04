#include "encodable.h"
#include "protocolfield.h"
#include "protocolstructure.h"

/*!
 * Constructor for encodable
 */
Encodable::Encodable(const QString& protocolName, const QString& protocolPrefix, ProtocolSupport supported) :
    support(supported),
    protoName(protocolName),
    prefix(protocolPrefix),
    null(false),
    reserved(false)
{
}

/*!
 * Reset all data to defaults
 */
void Encodable::clear(void)
{
    typeName.clear();
    name.clear();
    comment.clear();
    array.clear();
    encodedLength.clear();
    null = false;
    reserved = false;
}


/*!
 * Get the source needed to close out a string of bitfields.
 * \param bitcount points to the running count of bits in this string of
 *        bitfields, and will be updated by this function.
 * \param encLength is appended for length information of this field.
 * \return The string to add to the source file that closes the bitfield.
 */
QString Encodable::getCloseBitfieldString(int* bitcount, EncodedLength* encLength)
{
    QString output;
    QString spacing;

    if(*bitcount != 0)
    {
        // The number of bytes that the previous sequence of bit fields used up
        int length = *bitcount / 8;

        // Get the spacing right
        spacing += "    ";

        // If bitcount is not modulo 8, then the last byte was still in
        // progress, so increment past that
        if((*bitcount) % 8)
        {
            output += spacing + "bitcount = 0; byteindex++; // close bit field, go to next byte\n";
            length++;
        }
        else
        {
           output += spacing + "bitcount = 0; // close bit field, byte index already advanced\n";
        }

        output += "\n";

        // Add the length data if we have a place for it
        if(encLength != NULL)
            encLength->addToLength(QString().setNum(length));

        // Reset bit counter
        *bitcount = 0;
    }

    return output;

}// Encodable::getCloseBitfieldString


/*!
 * Return the signature of this field in an encode function signature. The
 * string will start with ", " assuming this field is not the first part of
 * the function signature.
 * \return the string that provides this fields encode function signature
 */
QString Encodable::getEncodeSignature(void) const
{
    if(null || reserved)
        return "";
    else if(isArray())
        return ", const " + typeName + " " + name + "[" + array + "]";
    else if(isPrimitive())
        return ", " + typeName + " " + name;
    else
        return ", const " + typeName + "* " + name;
}


/*!
 * Return the signature of this field in an decode function signature. The
 * string will start with ", " assuming this field is not the first part of
 * the function signature.
 * \return the string that provides this fields decode function signature
 */
QString Encodable::getDecodeSignature(void) const
{
    if(null || reserved)
        return "";
    else if(isArray())
        return ", " + typeName + " " + name + "[" + array + "]";
    else
        return ", " + typeName + "* " + name;
}


/*!
 * Return the string that documents this field as a encode function parameter.
 * The string starts with " * " and ends with a linefeed
 * \return the string that povides the parameter documentation
 */
QString Encodable::getEncodeParameterComment(void) const
{
    if(null || reserved)
        return "";
    else
        return " * \\param " + name + " is " + comment + "\n";
}


/*!
 * Return the string that documents this field as a decode function parameter.
 * The string starts with " * " and ends with a linefeed
 * \return the string that povides the parameter documentation
 */
QString Encodable::getDecodeParameterComment(void) const
{
    if(null || reserved)
        return "";
    else
        return " * \\param " + name + " receives " + comment + "\n";
}


/*!
 * Construct a protocol field by parsing a DOM element. The type of Encodable
 * created will be either a ProtocolStructure or a ProtocolField
 * \param protocolName is the name of the protocol
 * \param protocolPrefix is a prefix to use for typenames
 * \param supported describes what the protocol can support
 * \param field is the DOM element to parse (including its children)
 * \return a pointer to a newly allocated encodable. The caller is
 *         responsible for deleting this object.
 */
Encodable* Encodable::generateEncodable(const QString& protocolName, const QString& protocolPrefix, ProtocolSupport supported, const QDomElement& field)
{
    if(field.tagName().contains("Structure", Qt::CaseInsensitive))
        return new ProtocolStructure(protocolName, protocolPrefix, supported, field);
    else if(field.tagName().contains("Data", Qt::CaseInsensitive))
        return new ProtocolField(protocolName, protocolPrefix, supported, field);

    return NULL;
}
