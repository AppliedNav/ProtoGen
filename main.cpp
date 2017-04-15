#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDomDocument>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <iostream>

#include "protocolparser.h"
#include "xmllinelocator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName( "Protogen" );
    QCoreApplication::setApplicationVersion(ProtocolParser::genVersion);

    QCommandLineParser argParser;

    argParser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    argParser.setApplicationDescription("Protocol generation tool");
    argParser.addHelpOption();
    argParser.addVersionOption();

    argParser.addPositionalArgument("input", "Protocol defintion file, .xml");
    argParser.addPositionalArgument("outputpath", "Path for generated protocol files (default = current working directory)");

    argParser.addOption({{"d", "docs"}, "Path for generated documentation files (default = outputpath)", "docpath"});
    argParser.addOption({"show-hidden-items", "Show all items in documentation even if they are marked as 'hidden'"});
    argParser.addOption({"latex", "Enable extra documentation output required for LaTeX integration"});
    argParser.addOption({{"l", "latex-header-level"}, "LaTeX header level", "latexlevel"});
    argParser.addOption({"no-doxygen", "Skip generation of developer-level documentation"});
    argParser.addOption({"no-markdown", "Skip generation of user-level documentation"});
    argParser.addOption({"no-helper-files", "Skip creation of helper files not directly specifed by protocol .xml file"});
    argParser.addOption({{"s", "style"}, "Specify a css file to override the default style for HTML documentation", "cssfile"});
    argParser.addOption({"no-unrecognized-warnings", "Suppress warnings for unrecognized xml tags"});

    argParser.process(a);

    ProtocolParser parser;

    // Process the positional arguments
    QStringList args = argParser.positionalArguments();

    QString filename, path;

    if (args.count() > 0 )
        filename = args.at(0);

    if (args.count() > 1)
        path = args.at(1);

    if (filename.isEmpty() || !filename.endsWith(".xml", Qt::CaseInsensitive))
    {
        std::cerr << "error: must provide a protocol (*.xml) file." << std::endl;
        return 2;   // no input file
    }

    // Documentation directory
    QString docs = argParser.value("docs");

    if (!docs.isEmpty() && !argParser.isSet("no-markdown"))
    {
        docs =  ProtocolFile::sanitizePath(docs);

        if (QDir(docs).exists() || QDir::current().mkdir(docs))
        {
            parser.setDocsPath(docs);
        }
    }

    // Process the optional arguments
    parser.disableDoxygen(argParser.isSet("no-doxygen"));
    parser.disableMarkdown(argParser.isSet("no-markdown"));
    parser.disableHelperFiles(argParser.isSet("no-helper-files"));
    parser.showHiddenItems(argParser.isSet("show-hidden-items"));
    parser.disableUnrecognizedWarnings(argParser.isSet("no-unrecognized-warnings"));
    parser.setLaTeXSupport(argParser.isSet("latex"));

    QString latexLevel = argParser.value("latex-header-level");

    if (!latexLevel.isEmpty())
    {
        bool ok = false;
        int lvl = latexLevel.toInt(&ok);

        if (ok)
        {
            parser.setLaTeXLevel(lvl);
        }
        else
        {
            std::cerr << "warning: -latex-header-level argument '" << latexLevel.toStdString() << "' is invalid.";
        }
    }

    QString css = argParser.value("style");

    if (!css.isEmpty() && css.endsWith(".css", Qt::CaseInsensitive))
    {
        // First attempt to open the file
        QFile file(css);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            parser.setInlineCSS(file.readAll());
            file.close();
        }
        else
        {
            std::cerr << "warning: Failed to open " << QDir::toNativeSeparators(css).toStdString() << ", using default css" << std::endl;
        }
    }

    if (parser.parse(filename, path))
    {
        // Normal exit
        return 0;
    }
    else
    {
        // Input file in error
        return 1;
    }

}
