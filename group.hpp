#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "field.hpp"
#include <vector>

class Group {
    public:
        Group(int index) : m_index(index) {}
        void addField(Field *field);
        bool processGroup();
        Field * getField(int index);

    protected:
        virtual std::string dbgName() = 0;
        std::string dbgIndex() { return std::to_string(m_index); }

    private:
        std::vector<Field *> m_fields;
        int m_index;
};

class Row : public Group {
    public:
        Row(int index) : Group(index) {}
    protected:
        std::string dbgName() { return "Row"; }

};

class Column : public Group {
    public:
        Column(int index) : Group(index) {}
    protected:
        std::string dbgName() { return "Column"; }
};

class Square : public Group {
    public:
        Square(int index) : Group(index) {}
    protected:
        std::string dbgName() { return "Square"; }
};

#endif
