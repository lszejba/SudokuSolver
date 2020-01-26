#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "field.hpp"
#include <vector>

class Group {
    public:
        void addField(Field *field);
        bool processGroup();

    private:
        std::vector<Field *> m_fields;
};

#endif
