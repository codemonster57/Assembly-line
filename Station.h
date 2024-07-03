#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iomanip>
#include <iostream>
#include "Utilities.h"

namespace sdds
{
    class Station
    {
        int m_id;
        std::string m_name;
        std::string m_description;
        unsigned m_serial_num;
        unsigned m_stock;

        static unsigned m_widthField;
        static unsigned id_generator;

    public:
        Station();
        Station(const std::string &);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
        std::string generateStringBluePrint() const;
    };
}
#endif