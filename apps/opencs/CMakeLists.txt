set(OPENCS
    main.cpp
)

set(OPENCS_HEADER

)

# Headers that must be pre-processed
set(OPENCS_HEADER_MOC

)

source_group(opencs FILES ${OPENCS} ${OPENCS_HEADER} ${OPENCS_HEADER_MOC})

find_package(Qt4 REQUIRED)
set(QT_USE_QTGUI 1)

# Set some platform specific settings
if(WIN32)
    set(GUI_TYPE WIN32)
    set(QT_USE_QTMAIN TRUE)
endif(WIN32)

#QT4_ADD_RESOURCES(RCC_SRCS resources.qrc)
QT4_WRAP_CPP(MOC_SRCS ${OPENCS_HEADER_MOC})

include(${QT_USE_FILE})

# Main executable

add_executable(opencs
    ${GUI_TYPE}
    ${OPENCS}
    ${RCC_SRCS}
    ${MOC_SRCS}
)

target_link_libraries(opencs
    ${Boost_LIBRARIES}
    ${QT_LIBRARIES}
    components
)

if(DPKG_PROGRAM)
    INSTALL(TARGETS opencs RUNTIME DESTINATION games COMPONENT opencs)
endif()
