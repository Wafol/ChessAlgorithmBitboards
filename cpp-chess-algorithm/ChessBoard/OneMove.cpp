
#include "OneMove.h"

OneMove::OneMove() {

}

std::string OneMove::toString() const {
    return std::to_string(i1) + std::to_string(j1) + std::to_string(i2) + std::to_string(j2);
}
