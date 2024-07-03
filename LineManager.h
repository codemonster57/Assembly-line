#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H

#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "Workstation.h"

namespace sdds
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation *m_firstStation;

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
        Workstation *getFirstStation() const;
    };
}

#endif