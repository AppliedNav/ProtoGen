#ifndef ENUMCREATOR_H
#define ENUMCREATOR_H

#include <QString>
#include <QStringList>
#include <QDomElement>
#include "protocolsupport.h"
#include "protocoldocumentation.h"

class EnumCreator : public ProtocolDocumentation
{
public:
    //! Create an empty enumeration list
    EnumCreator(ProtocolParser* parse, QString Parent, ProtocolSupport supported) :
        ProtocolDocumentation(parse, Parent),
        minbitwidth(0),
        hidden(false),
        isglobal(false),
        support(supported)
    {}

    ~EnumCreator(void);

    //! Empty the enumeration list
    void clear(void);

    //! Parse the DOM to fill out the enumeration list
    virtual void parse(void);

    //! Parse the DOM to fill out the enumeration list for a global enum
    void parseGlobal(QString filename);

    //! Check names against the list of C keywords
    virtual void checkAgainstKeywords(void);

    //! Get the markdown documentation for this enumeration
    virtual QString getTopLevelMarkdown(bool global = false, const QStringList& ids = QStringList()) const;

    //! Return the enumeration name
    QString getName(void) const {return name;}

    //! Return the enumeration comment
    QString getComment(void) const {return comment;}

    //! Return the header file output string
    QString getOutput(void) const {return output;}

    //! Replace any text that matches an enumeration name with the value of that enumeration
    QString& replaceEnumerationNameWithValue(QString& text) const;

    //! Determine if text is an enumeration name
    bool isEnumerationValue(const QString& text) const;

    //! Return the minimum number of bits needed to encode the enumeration
    int getMinBitWidth(void) const {return minbitwidth;}

    //! Return true if this enumeration is hidden from the documentation
    virtual bool isHidden(void) const {return hidden;}

    //! The hierarchical name of this object
    virtual QString getHierarchicalName(void) const {return parent + ":" + name;}

    //! Return the header file name (if any) of the file holding this enumeration
    QString getHeaderFileName(void) const {return file;}

protected:

    //! Parse the enumeration values to build the number list
    void computeNumberList(void);

    //! Split string around math operators
    QStringList splitAroundMathOperators(QString text) const;

    //! Determine if a character is a math operator
    bool isMathOperator(QChar op) const;

    //! Output file for global enumerations
    QString file;

    //! List of enumeration names
    QStringList nameList;

    //! List of enumeration comments
    QStringList commentList;

    //! List of enumeration values (as strings)
    QStringList valueList;

    //! List of enumeration values (as numbers)
    QStringList numberList;

    //! List of enumeration value hidden flags
    QList<bool> hiddenList;

    //! A longer description is possible for enums (will be displayed in the documentation)
    QString description;

    //! The header file output string of the enumeration
    QString output;

    //! Minimum number of bits needed to encode the enumeration
    int minbitwidth;

    //! Determines if this enum will be hidden from the documentation
    bool hidden;

    //! Flag set true if parseGlobal() is called
    bool isglobal;

    //! Protocol options details
    ProtocolSupport support;

    //! List of document objects
    QList<ProtocolDocumentation*> documentList;
};

//! Output a string with specific spacing
QString spacedString(QString text, int spacing);

#endif // ENUMCREATOR_H
