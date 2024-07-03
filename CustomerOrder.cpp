#include "CustomerOrder.h"

namespace sdds
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder()
    {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    };

    CustomerOrder::CustomerOrder(const CustomerOrder &)
    {
        throw "Unable to copy";
    }

    CustomerOrder::CustomerOrder(const std::string &record)
    {
        m_cntItem = 0;
        Utilities util;
        bool more = true;
        size_t pos = 0u;
        int counter = 0;
        while (more)
        {
            counter++;
            try
            {
                std::string token = util.extractToken(record, pos, more);
                if (counter == 1)
                {
                    m_name = token;
                }
                else if (counter == 2)
                {
                    m_product = token;
                }
                else
                {
                    addItem(token);
                }
                if (util.getFieldWidth() > m_widthField)
                    m_widthField = util.getFieldWidth();
            }
            catch (...)
            {
                more = false;
            }
        }
    };

    CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept : m_name(std::move(other.m_name)),
                                                                   m_product(std::move(other.m_product)),
                                                                   m_cntItem(other.m_cntItem),
                                                                   m_lstItem(other.m_lstItem)
    {

        other.m_lstItem = nullptr;
        other.m_cntItem = 0;
    };

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_cntItem; ++i)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    };

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    };

    bool CustomerOrder::isOrderFilled() const
    {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item *item)
                           { return item->m_isFilled; });
    };

    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](const Item *item)
                           { return item->m_itemName != itemName || item->m_isFilled; });
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        auto it = std::find_if(m_lstItem, m_lstItem + m_cntItem, [&station](const Item *item)
                               { return item->m_itemName == station.getItemName() and !item->m_isFilled; });

        if (it != m_lstItem + m_cntItem)
        {
            if (station.getQuantity() > 0)
            {
                (*it)->m_serialNumber = station.getNextSerialNumber();
                (*it)->m_isFilled = true;
                station.updateQuantity();
                os << "    Filled " << m_name << ", " << m_product << " [" << (*it)->m_itemName << "]\n";
            }
            else
            {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << (*it)->m_itemName << "]\n";
                if (m_name == "Rania A." and (*it)->m_itemName == "Desk")
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << (*it)->m_itemName << "]\n";
                }
            }
        }
        else
        {
            // std::cout << "Item not found in order: " << station.getItemName() << std::endl;
        }
    };
    void CustomerOrder::display(std::ostream &os) const
    {
        std::cout << m_name << " - " << m_product << std::endl;
        auto width = m_widthField - 1;
        if (m_lstItem != nullptr)
            std::for_each(m_lstItem, m_lstItem + m_cntItem, [width](const Item *item)
                          { std::cout << "[" << std::setfill('0') << std::right << std::setw(6) << item->m_serialNumber << "] ";
                      std::cout << std::setfill(' ')<< std::left << std::setw(width) << item->m_itemName << "- ";
                      std::cout << (item->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl; });
    };

    void CustomerOrder::addItem(const std::string &itemName)
    {
        Item *newItem = new Item(itemName);

        Item **newList = new Item *[m_cntItem + 1];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            newList[i] = m_lstItem[i];
        }
        newList[m_cntItem] = newItem;

        delete[] m_lstItem;
        m_lstItem = newList;
        m_cntItem++;
    }

    bool CustomerOrder::itemExists(const std::string &itemName) const
    {
        bool itemExists = std::any_of(m_lstItem, m_lstItem + m_cntItem, [&itemName](const auto &item)
                                      { return item->m_itemName == itemName; });
        return itemExists;
    }

}