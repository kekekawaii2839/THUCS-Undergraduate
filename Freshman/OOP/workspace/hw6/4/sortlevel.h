#pragma once
enum order_type { ASCEND, DESCEND }; 
struct sort_level {
    int column;
    order_type order;
};