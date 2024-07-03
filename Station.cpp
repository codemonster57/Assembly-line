#include "Station.h"

namespace sdds
{
    unsigned Station::m_widthField = 0;
    unsigned Station::id_generator = 0;

    Station::Station(const std::string &record)
    {
        Utilities util;
        bool more = true; // if there are more tokens in the input string
        size_t pos = 0u;  // position of the next token in the input string
        int counter = 0;
        while (more)
        {
            counter++;
            try
            {
                auto token = util.extractToken(record, pos, more);
                if (counter == 1)
                {
                    m_id = ++id_generator;
                    if (util.getFieldWidth() > m_widthField)
                        m_widthField = util.getFieldWidth();
                    m_name = token;
                }
                else if (counter == 2)
                    m_serial_num = std::stoi(token);
                else if (counter == 3)
                    m_stock = std::stoi(token);
                else
                    m_description = token;
            }
            catch (...)
            {
                std::cout << "   ERROR: No token.\n";
            }
        }
    };

    const std::string &Station::getItemName() const
    {
        return m_name;
    };
    size_t Station::getNextSerialNumber()
    {
        return m_serial_num++;
    };
    size_t Station::getQuantity() const
    {
        return m_stock;
    };
    void Station::updateQuantity()
    {
        m_stock > 0 && --m_stock;
    };

    std::string Station::generateStringBluePrint() const
    {
        // Armchair,    654321,  10,  Upholstered Wing Chair
        std::string bluePrint = m_name + "| " + std::to_string(m_serial_num) + "| " + std::to_string(m_stock) + "| " + m_description;
        return bluePrint;
    }

    void Station::display(std::ostream &os, bool full) const
    {
        if (full)
        {
            os << std::setfill('0') << std::setw(3) << std::right << m_id << " | "
               << std::setfill(' ') << std::setw(m_widthField - 1) << std::left << m_name << " | "
               << std::setfill('0') << std::setw(6) << std::right << m_serial_num << " | "
               << std::setfill(' ') << std::setw(4) << std::right << m_stock << " | "
               << m_description << std::endl;
        }
        else
        {
            os << std::setfill('0') << std::setw(3) << std::right << m_id << " | ";
            os << std::setfill(' ') << std::setw(m_widthField - 1) << std::left << m_name << " | ";
            os << std::setfill('0') << std::setw(6) << std::right << m_serial_num << " | " << std::endl;
        }
    };

}