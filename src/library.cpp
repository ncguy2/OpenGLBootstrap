#include "../include/library.h"

#include <iostream>
#include <sstream>

int bootstrap::BootstrapVersionMajor() {
    return MAJOR_VERSION;
}

int bootstrap::BootstrapVersionMinor() {
    return MINOR_VERSION;
}

int bootstrap::BootstrapVersionBuild() {
    return BUILD_VERSION;
}

std::string bootstrap::BootstrapVersionString() {
    std::stringstream ss;
    ss << BootstrapVersionMajor() << ".";
    ss << BootstrapVersionMinor() << ".";
    ss << BootstrapVersionBuild();
    return ss.str();
}
