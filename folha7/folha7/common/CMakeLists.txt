

file(GLOB LIB_FILES
        "*.hpp"
        "*.cpp"
        "*.h"
        )

add_library(common ${LIB_FILES})