#ifndef __LOGICALLANE_H__
#define __LOGICALLANE_H__

#include <string>
#include <vector>
#include "group.hpp"

class LogicalLane {
    public:
        LogicalLane(int index) : m_index(index) {}
        void addGroup(Group *group);
        void processLane();

    protected:
        virtual std::string dbgName() = 0;
        std::string dbgIndex() { return std::to_string(m_index); }

    private:
        void removePossibleFromOtherSquares(int num, int groupIdx, int ownerIdx);
        void checkSquare(int idx, int number);
        std::vector<Group *> m_groups;
        int m_index;
};

class LogicalRow : public LogicalLane {
    public:
        LogicalRow(int index) : LogicalLane(index) {}

    protected:
        std::string dbgName() { return "LogicalRow"; }
};

class LogicalColumn : public LogicalLane {
    public:
        LogicalColumn(int index) : LogicalLane(index) {}

    protected:
        std::string dbgName() { return "LogicalColumn"; }
};  

#endif