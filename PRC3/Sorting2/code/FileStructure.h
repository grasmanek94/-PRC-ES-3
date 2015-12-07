#pragma once

#include <string>

#include "Key.h"

class FileStructure
{
    public:
        FileStructure();
        // post: FileStructure object is properly initialised
        virtual ~FileStructure();
        // empty virtual destructor
        
        void loadFile(const std::string& filename, Key& head) const;
        // post: if file with filename exists, its data is read, decoded and stored in a
        //       proper key/value tree.

        void saveFile(Key& head, const std::string& filename) const;
        // post: if a file with filename can be created, head is recursively written it
    
    private:
        std::string getNextWord(const char* start, char** current, size_t size) const;
        void crypt(char* start, size_t size) const;
        void decrypt(char* start, size_t size) const;

        // private copy constructor and assignment operator to prevent making copies
        FileStructure(const FileStructure& other) { /* do nothing */ };
        FileStructure& operator= (const FileStructure& other) { return *this; };
};
