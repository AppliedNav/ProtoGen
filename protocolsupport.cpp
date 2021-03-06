#include "protocolsupport.h"
#include "protocolparser.h"

#include <QStringList>

ProtocolSupport::ProtocolSupport() :
    maxdatasize(0),
    int64(true),
    float64(true),
    specialFloat(true),
    bitfield(true),
    longbitfield(false),
    bitfieldtest(false),
    disableunrecognized(false),
    bigendian(true),
    supportbool(false),
    limitonencode(false),
    packetStructureSuffix("PacketStructure"),
    packetParameterSuffix("Packet")
{
}


//! Return the list of attributes understood by ProtocolSupport
QStringList ProtocolSupport::getAttriblist(void) const
{
    QStringList attribs;

    attribs << "maxSize"
            << "supportInt64"
            << "supportFloat64"
            << "supportSpecialFloat"
            << "supportBitfield"
            << "supportLongBitfield"
            << "bitfieldTest"
            << "file"
            << "verifyfile"
            << "comparefile"
            << "printfile"
            << "mapfile"
            << "prefix"
            << "packetStructureSuffix"
            << "packetParameterSuffix"
            << "endian"
            << "pointer"
            << "supportBool"
            << "limitOnEncode";

    return attribs;
}


/*!
 * Parse the attributes for this support object from the DOM map
 * \param map is the DOM map
 */
void ProtocolSupport::parse(const QDomNamedNodeMap& map)
{
    // Maximum bytes of data in a packet.
    maxdatasize = ProtocolParser::getAttribute("maxSize", map, "0").toInt();

    // 64-bit support can be turned off
    if(ProtocolParser::isFieldClear(ProtocolParser::getAttribute("supportInt64", map)))
        int64 = false;

    // double support can be turned off
    if(ProtocolParser::isFieldClear(ProtocolParser::getAttribute("supportFloat64", map)))
        float64 = false;

    // special float support can be turned off
    if(ProtocolParser::isFieldClear(ProtocolParser::getAttribute("supportSpecialFloat", map)))
        specialFloat = false;

    // bitfield support can be turned off
    if(ProtocolParser::isFieldClear(ProtocolParser::getAttribute("supportBitfield", map)))
        bitfield = false;

    // long bitfield support can be turned on
    if(int64 && ProtocolParser::isFieldSet("supportLongBitfield", map))
        longbitfield = true;

    // bitfield test support can be turned on
    if(ProtocolParser::isFieldSet("bitfieldTest", map))
        bitfieldtest = true;

    // bool support can be turned on
    if(ProtocolParser::isFieldSet("supportBool", map))
        supportbool = true;

    // Limit on encode can be turned on
    if(ProtocolParser::isFieldSet("limitOnEncode", map))
        limitonencode = true;

    // The global file names
    parseFileNames(map);

    // Prefix is not required
    prefix = ProtocolParser::getAttribute("prefix", map);

    // Packet pointer type (default is 'void')
    pointerType = ProtocolParser::getAttribute("pointer", map, "void*");

    // Must be a pointer type
    if(!pointerType.endsWith("*"))
        pointerType += "*";

    // Packet name post fixes
    packetStructureSuffix = ProtocolParser::getAttribute("packetStructureSuffix", map, packetStructureSuffix);
    packetParameterSuffix = ProtocolParser::getAttribute("packetParameterSuffix", map, packetParameterSuffix);

    if(ProtocolParser::getAttribute("endian", map).contains("little", Qt::CaseInsensitive))
        bigendian = false;

}// ProtocolSupport::parse


/*!
 * Parse the global file names used for this support object from the DOM map
 * \param map is the DOM map
 */
void ProtocolSupport::parseFileNames(const QDomNamedNodeMap& map)
{
    // Global file names can be specified, but cannot have a "." in it
    globalFileName = ProtocolParser::getAttribute("file", map);
    globalFileName = globalFileName.left(globalFileName.indexOf("."));
    globalVerifyName = ProtocolParser::getAttribute("verifyfile", map);
    globalVerifyName = globalVerifyName.left(globalVerifyName.indexOf("."));
    globalCompareName = ProtocolParser::getAttribute("comparefile", map);
    globalCompareName = globalCompareName.left(globalCompareName.indexOf("."));
    globalPrintName = ProtocolParser::getAttribute("printfile", map);
    globalPrintName = globalPrintName.left(globalPrintName.indexOf("."));
    globalMapName = ProtocolParser::getAttribute("mapfile", map);
    globalMapName = globalMapName.left(globalMapName.indexOf("."));

}// ProtocolSupport::parseFileNames
