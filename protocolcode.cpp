#include "protocolcode.h"
#include "protocolparser.h"

/*!
 * Construct a blank protocol field
 * \param protocolName is the name of the protocol
 * \param prtoocolPrefix is the naming prefix
 * \param supported indicates what the protocol can support
 */
ProtocolCode::ProtocolCode(const QString& protocolName, const QString& protocolPrefix, ProtocolSupport supported):
    Encodable(protocolName, protocolPrefix, supported)
{
}


/*!
 * Construct a protocol field by parsing the DOM
 * \param protocolName is the name of the protocol
 * \param prtoocolPrefix is the naming prefix
 * \param supported indicates what the protocol can support
 * \param field is the DOM element
 */
ProtocolCode::ProtocolCode(const QString& protocolName, const QString& protocolPrefix, ProtocolSupport supported, const QDomElement& field):
    Encodable(protocolName, protocolPrefix, supported)
{
    parse(field);
}



//! Reset all data to defaults
void ProtocolCode::clear(void)
{
    Encodable::clear();

    encode.clear();
    decode.clear();
}


/*!
 * Parse the DOM to determine the details of this ProtocolCode
 * \param field is the DOM element
 */
void ProtocolCode::parse(const QDomElement& field)
{
    clear();

    // Pull all the attribute data
    name = field.attribute("name").trimmed();
    comment = ProtocolParser::getComment(field);
    encode = field.attribute("encode").trimmed();
    decode = field.attribute("decode").trimmed();
}


/*!
 * Get the next lines(s) of source coded needed to add this code to the encode function
 * \param isBigEndian should be true for big endian encoding, ignored.
 * \param bitcount points to the running count of bits in a bitfields and
 *        should persist between calls, ignored.
 * \param isStructureMember should be true if the left hand side is a
 *        member of a user structure, else the left hand side is a pointer
 *        to the inMemoryType, ignored.
 * \return The string to add to the source file for this code.
 */
QString ProtocolCode::getEncodeString(bool isBigEndian, int* bitcount, bool isStructureMember) const
{
    QString output;

    if(encode.isEmpty())
        return output;

    if(!comment.isEmpty())
        output += "    // " + comment + "\n";

    output += "    " + encode + "\n";

    return output;
}


/*!
 * Get the next lines(s) of source coded needed to add this code to the decode function.
 * \param isBigEndian should be true for big endian encoding, ignored.
 * \param bitcount points to the running count of bits in a bitfields and
 *        should persist between calls, ignored.
 * \param isStructureMember should be true if the left hand side is a
 *        member of a user structure, else the left hand side is a pointer
 *        to the inMemoryType, ignored.
 * \param defaultEnabled should be true to handle defaults, ignored.
 * \return The string to add to the source file for this code.
 */
QString ProtocolCode::getDecodeString(bool isBigEndian, int* bitcount, bool isStructureMember, bool defaultEnabled) const
{
    QString output;

    if(decode.isEmpty())
        return output;

    if(!comment.isEmpty())
        output += "    // " + comment + "\n";

    output += "    " + decode + "\n";

    return output;
}
