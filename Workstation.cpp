#include "Workstation.h"

namespace sdds
{
    std::vector<CustomerOrder> g_pending;
    std::vector<CustomerOrder> g_completed;
    std::vector<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &str) : Station(str){};

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    };

    bool Workstation::attemptToMoveOrder()
    {
        if (m_orders.empty())
            return false;

        std::string item_name = this->getItemName();

        // there is stock
        if (getQuantity() == 0)
        {
            moveOrderToNextStation();
            return true;
        }

        // order can be processed

        if (!m_orders.begin()->itemExists(item_name))
        {
            moveOrderToNextStation();
            return true;
        }

        if (m_orders.begin()->isItemFilled(item_name))
        {
            moveOrderToNextStation();
            return true;
        }

        return false;
    };

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    };

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    };

    void Workstation::display(std::ostream &os) const
    {
        std::string item_name = this->getItemName();
        if (m_pNextStation)
        {
            std::string next_item_name = m_pNextStation->getItemName();
            os << item_name << " --> " << next_item_name << std::endl;
        }
        else
        {
            os << item_name << " --> End of Line\n";
        }
    };

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    };

    void Workstation::moveOrderToNextStation()
    {
        if (!m_orders.empty())
        {

            if (m_pNextStation == nullptr)
            {

                if (m_orders.front().isOrderFilled())
                {
                    g_completed.insert(g_completed.begin(), std::move(m_orders.front()));
                    m_orders.erase(m_orders.begin());
                }
                else
                {

                    g_incomplete.push_back(std::move(m_orders.front()));
                    m_orders.erase(m_orders.begin());
                }
            }
            else if (m_orders.front().isOrderFilled())
            {
                g_completed.push_back(std::move(m_orders.front()));
                m_orders.erase(m_orders.begin());
            }
            else
            {
                *m_pNextStation += std::move(m_orders.front());
                m_orders.erase(m_orders.begin());
            }
        }
    };

    bool Workstation::checkIfAllOrdersAreCompleted() const
    {
        if (m_orders.empty())
            return true;

        for (const auto &order : m_orders)
        {
            if (!order.isOrderFilled())
            {
                return false;
            }
        }
        return true;
    }

}