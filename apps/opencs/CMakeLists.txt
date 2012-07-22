#add_subdirectory(qtpropertybrowser)

set(OPENCS_SRC
    main.cpp
    opencs.cpp
    esmdataitem.cpp
    esmdatamodel.cpp
    model/activator.cpp
    model/potion.cpp
    model/magiceffect.cpp
    views/idlist.cpp
)

set(OPENCS_HDR
    opencs.hpp
    esmdataitem.hpp
    esmdatamodel.hpp
    model/activator.hpp
    model/potion.hpp
    model/magiceffect.hpp
    views/idlist.hpp
)

set(OPENCS_UI
    opencs.ui
    views/idlist.ui
)

set(OPENCS_RES
    ../launcher/resources.qrc
)

source_group(opencs FILES ${OPENCS_SRC} ${OPENCS_HDR})

if(WIN32)
    set(QT_USE_QTMAIN TRUE)
endif(WIN32)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

qt4_wrap_ui(OPENCS_UI_HDR ${OPENCS_UI})
qt4_wrap_cpp(OPENCS_MOC_SRC ${OPENCS_HDR})
qt4_add_resources(OPENCS_RES_SRC ${OPENCS_RES})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(opencs
    ${OPENCS_SRC}
    ${OPENCS_UI_HDR}
    ${OPENCS_MOC_SRC}
    ${OPENCS_RES_SRC}
)

target_link_libraries(opencs
    ${Boost_LIBRARIES}
    ${QT_LIBRARIES}
    components
    #PropertyBrowser
)

if(DPKG_PROGRAM)
    INSTALL(TARGETS opencs RUNTIME DESTINATION games COMPONENT opencs)
endif()
