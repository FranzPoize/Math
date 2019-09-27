project(math)

set(${PROJECT_NAME}_HEADERS
    Barycentric.h
    commons.h
    Matrix.h
    MatrixBase.h
    MatrixBase-impl.h
    MatrixTraits.h
    Range.h
    Rectangle.h
    Utilities.h
    Vector.h
    Vector-impl.h
)

add_library(${PROJECT_NAME} INTERFACE)

# Custom target to have the files show up in the IDE
add_custom_target(${PROJECT_NAME}_IDE
    SOURCES
        ${${PROJECT_NAME}_HEADERS}
)

target_include_directories(${PROJECT_NAME} 
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
        $<INSTALL_INTERFACE:include/>
)


##
## Install
##
include(cmc-install)

# Install the header files
cmc_install_with_folders(DESTINATION include/${PROJECT_NAME}
                         FILES ${${PROJECT_NAME}_HEADERS})

cmc_install_packageconfig(${PROJECT_NAME} NAMESPACE ad)

