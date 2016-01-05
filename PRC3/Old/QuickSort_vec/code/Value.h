#pragma once

#include <string>

class Value
{
    public:
        Value(std::string word);
        // post: Value is properly initialised with word as value
        virtual ~Value();
        // empty virtual destructor

        std::string getText() const;
        // post: current value is returned

        void setText(std::string value);
        // post: value is updated with new value

        Value* getNext();
        // post: pointer to next value is returned

        void setNext(Value* value);
        // post: pointer to next value is set

        size_t getSize() const;
        // post: size of current value is returned

        void print() const;
        // post: current value is printed to stdout

    private:
        std::string word;
        Value* next;

        // private copy constructor and assignment operator to prevent making copies
        Value(const Value& other) { /* do nothing */ };
        Value& operator= (const Value& other) { return *this; };
};
