#add_subdirectory(qtpropertybrowser)

set(OPENCS_SRC
    main.cpp
    opencs.cpp
    esmdataitem.cpp
    esmdatamodel.cpp
    model/activator.cpp
    model/potion.cpp
    model/magiceffect.cpp
    model/script.cpp
    model/filter/filter.cpp
    model/filter/defaultfilter.cpp
    model/filter/matchfilter.cpp
    model/filter/unionfilter.cpp
    model/filter/intersectionfilter.cpp
    views/idlist.cpp
    views/idlistitemdelegate.cpp
    views/idlistfilter.cpp
    views/filter/filtertree.cpp
    views/filter/filtereditor.cpp
)

set(OPENCS_HDR
    opencs.hpp
    esmdataitem.hpp
    esmdatamodel.hpp
    model/activator.hpp
    model/potion.hpp
    model/magiceffect.hpp
    model/script.hpp
    model/filter/filter.hpp
    model/filter/defaultfilter.hpp
    model/filter/matchfilter.hpp
    model/filter/unionfilter.hpp
    model/filter/intersectionfilter.hpp
    views/idlist.hpp
    views/idlistitemdelegate.hpp
    views/idlistfilter.hpp
    views/filter/filtertree.hpp
    views/filter/filtereditor.hpp
)

set(OPENCS_UI
    opencs.ui
    views/idlist.ui
    views/filter/filtertree.ui
    views/filter/filtereditor.ui
)

set(OPENCS_RES
    resources.qrc
)

source_group(opencs FILES ${OPENCS_SRC} ${OPENCS_HDR})

if(WIN32)
    set(QT_USE_QTMAIN TRUE)
endif(WIN32)

find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtXmlPatterns REQUIRED)
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
