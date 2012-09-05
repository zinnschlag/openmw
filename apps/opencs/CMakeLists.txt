#add_subdirectory(qtpropertybrowser)

set(OPENCS_SRC
    main.cpp
    opencs.cpp

    model/modelitem.cpp

    model/esm/dataitem.cpp
    model/esm/esmfile.cpp
    model/esm/esmdataitem.cpp
    model/esm/record/activator.cpp
    model/esm/record/potion.cpp
    model/esm/record/magiceffect.cpp
    model/esm/record/script.cpp
    model/esm/record/setting.cpp

    model/filter/filterfile.cpp
    model/filter/filter.cpp
    model/filter/defaultfilter.cpp
    model/filter/matchfilter.cpp
    model/filter/setoperationfilter.cpp

    persistence/filter/filterdom.cpp

    viewmodel/esmdatamodel.cpp
    viewmodel/filtereditmodel.cpp
    viewmodel/filterproxymodel.cpp

    view/idlist.cpp
    view/idlistitemdelegate.cpp
    view/filter/filtertree.cpp
    view/filter/filtereditor.cpp
)

set(OPENCS_HDR
    opencs.hpp

    model/modelitem.hpp

    model/esm/dataitem.hpp
    model/esm/esmfile.hpp
    model/esm/esmdataitem.hpp
    model/esm/record/activator.hpp
    model/esm/record/potion.hpp
    model/esm/record/magiceffect.hpp
    model/esm/record/script.hpp
    model/esm/record/setting.hpp

    model/filter/filterfile.hpp
    model/filter/filter.hpp
    model/filter/defaultfilter.hpp
    model/filter/matchfilter.hpp
    model/filter/setoperationfilter.hpp

    persistence/filter/filterdom.hpp

    viewmodel/esmdatamodel.hpp
    viewmodel/filtereditmodel.hpp
    viewmodel/filterproxymodel.hpp

    view/idlist.hpp
    view/idlistitemdelegate.hpp
    view/filter/filtertree.hpp
    view/filter/filtereditor.hpp
)

set(OPENCS_UI
    opencs.ui
    view/idlist.ui
    view/filter/filtertree.ui
    view/filter/filtereditor.ui
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
    #QtSolutions_PropertyBrowser-2.5
)

if(DPKG_PROGRAM)
    INSTALL(TARGETS opencs RUNTIME DESTINATION games COMPONENT opencs)
endif()
