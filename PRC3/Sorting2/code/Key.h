#pragma once

#include "Value.h"

class Key
{
    public:
        Key();
        // post: Key is properly initialised, however the key value
        //       is illegal (empty)

        virtual ~Key();
        // post: recursively deletes all keys and values
        
        
        std::string getText() const;
        // post: current key value is returned
        
        bool setText(std::string key);
        // post: if key length equals 2 the key value is set and true is returned,
        //       else key is ignored and false is returned

        void addValue(std::string word);
        // post: a new word is added to the correct key:
        //       - if the word fits in this key, a new value is added to the valuelist
        //       - if the word doesn't fit in this key, addValue is called on the next key
        //       - if no fitting key is found, a new key is made with this value in it
        
        Value* getValuePtr();
        // post: pointer to this key's first value is returned
        
        void setValuePtr(Value* value);
        // post: pointer to this key's first value is set
        
        void setNext(Key* next);
        // post: pointer to the next key is set
        
        Key* getNext();
        // post: pointer to the next key is returned

        size_t getSize(size_t separatorSize) const;
        // post: size in bytes of all data is returned, separatorSize is added to each value
        void print() const;
        // post: all keys and values are recursively printed
        
    private:
        std::string key;
        Value* valueHead;
        Key* nextKey;
        
        // private copy constructor and assignment operator to prevent making copies
        Key(const Key& other) { /* do nothing */ };
        Key& operator= (const Key& other) { return *this; };
};
