#ifndef READER_HH
#define READER_HH

#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Configuration.hh"
#include "xmlinterp.hh"

#define LINE_SIZE 500

class Reader
{
private:
    std::string cmdFileName;

public:
    Reader(){};
    bool init(std::string cmdFile);
    
    bool execPreprocesor(std::istringstream &IStrm4Cmds);

    bool ReadFile(const char *sFileName, Configuration &rConfig);

    void setupParserFeaturesAndHandlers(xercesc::SAX2XMLReader* pParser, xercesc::DefaultHandler* pHandler);
    bool loadGrammarAndParse(xercesc::SAX2XMLReader* pParser, const char* sFileName);
    void handleXMLException(const xercesc::XMLException& Exception);
    void handleSAXParseException(const xercesc::SAXParseException& Exception);
    void cleanupParserAndHandler(xercesc::SAX2XMLReader* pParser, xercesc::DefaultHandler* pHandler);

};

#endif