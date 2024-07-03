# Assembly Line Management

This project is a simulation of an assembly line that fills customer orders for an assortment of items.

![Assembly Line](utils/assemblyline.jpg)

> The assembly line in your solution consists of a set of workstations each of which holds a set of stock items, which are specific to the station. A line manager moves customer orders along the line filling the orders at each station, as requested. Each customer order consists of a list of items that need to be filled. Each station processes a queue of orders by filling the next order in the queue if that order requests the station's item and that item is in stock. The line manager keeps moving the customer orders from station to station until all orders have been processed. Any station that has used all the items in stock cannot fill any more orders. At the end of the line orders are either completed or incomplete due to a lack of inventory at one or more stations. The simulator lists the completed orders and those that are incomplete once the line manager has finished processing all orders.

## Project Overview

The project is divided into several parts, each focusing on a specific aspect of the assembly line simulation.

### Modules

1. **Workstation Module:** This module represents a station on the assembly line. Each workstation holds a set of stock items that are specific to that station. It processes a queue of orders, filling the next order in the queue if that order requests the station's item and the item is in stock. If a workstation runs out of stock, it can no longer fill any more orders.

2. **Customer Order Module:** This module represents a customer order. Each customer order consists of a list of items that need to be filled. The order moves along the assembly line, with each workstation filling the items requested by the order if those items are in stock at the workstation.

3. **Line Manager Module:** This module manages the movement of customer orders along the assembly line. It keeps moving the customer orders from one workstation to the next until all orders have been processed. At the end of the line, orders are either completed or incomplete due to a lack of inventory at one or more workstations. Once all orders have been processed, the line manager lists the completed orders and those that are incomplete.

4. **Inventory Module:** This module manages the stock of items at each workstation. When a workstation fills an order, it uses up one unit of stock for each item filled. If a workstation runs out of stock for an item, it can no longer fill orders that request that item.

5. **Simulator Module:** This module runs the assembly line simulation. It uses the other modules to set up the assembly line, process customer orders, and report the results. It lists the completed orders and those that are incomplete once the line manager has finished processing all orders.

Through this project, I've gained a deeper understanding of C++ programming, particularly in areas like file parsing, object-oriented design, and memory management. I've also learned how to effectively manage and organize a larger codebase, and how to debug and test my code to ensure it's working as expected.

It's a completed project that I've learned a lot from, and I'm always open to feedback and suggestions for future improvements.

## How to run

### Compiling the Program

Before running the program, you need to compile it. If you're using the g++ compiler, you can use the following command to compile the program:

```bash
g++ -std=c++11 -o assemblyline *.cpp
```

### Running the Program

To run the program, you need to provide four text files as command line arguments. These files contain the information needed to set up the assembly line and the customer orders.

Here's the command to run the program:

```bash
assemblyline Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
```
