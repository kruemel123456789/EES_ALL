#include "utils.h"

Utils::Utils()
{

}

// Outputs order state in human friendly format
QString Utils::printOrderState(uint8_t state) {
    switch(state) {
        case 0: return "open";
        case 1: return "processing";
        case 2: return "done";
    }

}
