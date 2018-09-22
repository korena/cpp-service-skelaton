#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ServiceConfig.h"

#ifdef USE_MYMATH
#include "mathFunctions.h"
#endif

#include "Cms.hpp"

int main(int argc, char *argv[]) {

    helloWorld();

    std::cout << "Service version (" << SERVICE_VERSION_MAJOR << "." << SERVICE_VERSION_MINOR << ")" << std::endl;
    if (argc < 2) {
        fprintf(stdout, "Usage: %s number\n", argv[0]);
        return 1;
    }

    double inputValue = atof(argv[1]);

#ifdef USE_MYMATH
    double outputValue = mySqrt(inputValue);
#else
    double outputValue = sqrt(inputValue);
#endif

    fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);
    return 0;
}
