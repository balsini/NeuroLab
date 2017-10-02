#-------------------------------------------------
#
# Project created by QtCreator 2017-03-15T12:26:16
#
#-------------------------------------------------

QT       += core charts widgets gui

TARGET = NeuroLab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += \
    MODEL_PATH=\\\"$$_PRO_FILE_PWD_/memory_allocation/WATERS/model/ChallengeModel2017modified.amxmi\\\" \
    USE_LET_MODEL=false

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    kohonen.cpp \
    hopfield.cpp \
    matfun.cpp \
    gaerrorplot.cpp \
    memory_allocation/memory_allocation.cpp \
    memory_allocation/memoryallocationdisplay.cpp \
    memory_allocation/WATERS/src/tinyxml/tinyxml2.cpp \
    memory_allocation/WATERS/src/analyse_data.cpp \
    memory_allocation/WATERS/src/copy_in_newstruct.cpp \
    memory_allocation/WATERS/src/EventChains2.cpp \
    memory_allocation/WATERS/src/EventChains2_elem.cpp \
    memory_allocation/WATERS/src/genetic.cpp \
    memory_allocation/WATERS/src/Label2.cpp \
    memory_allocation/WATERS/src/main_waters.cpp \
    memory_allocation/WATERS/src/milpData.cpp \
    memory_allocation/WATERS/src/optimization.cpp \
    memory_allocation/WATERS/src/RT.cpp \
    memory_allocation/WATERS/src/Runnable2.cpp \
    memory_allocation/WATERS/src/strtools.cpp \
    memory_allocation/WATERS/src/Task2.cpp \
    memory_allocation/buttonlegend.cpp \
    tsp/tsp.cpp \
    tsp/tspdisplay.cpp \
    function_fitting/advanced_0/function.cpp \
    function_fitting/functionfitting.cpp \
    function_fitting/functionfittingdisplay.cpp \

HEADERS  += \
    mainwindow.h \
    kohonen.h \
    hopfield.h \
    matfun.h \
    geneticalgorithm.h \
    gaerrorplot.h \
    optimizationproblem.h \
    memory_allocation/memory_allocation.h \
    memory_allocation/memoryallocationdisplay.h \
    memory_allocation/WATERS/src/tinyxml/tinyxml2.h \
    memory_allocation/WATERS/src/analyse_data.h \
    memory_allocation/WATERS/src/copy_in_newstruct.h \
    memory_allocation/WATERS/src/EventChains2.h \
    memory_allocation/WATERS/src/EventChains2_elem.h \
    memory_allocation/WATERS/src/genetic.h \
    memory_allocation/WATERS/src/Label2.h \
    memory_allocation/WATERS/src/main_waters.h \
    memory_allocation/WATERS/src/milpData.h \
    memory_allocation/WATERS/src/optimization.h \
    memory_allocation/WATERS/src/RT.h \
    memory_allocation/WATERS/src/Runnable2.h \
    memory_allocation/WATERS/src/shared.h \
    memory_allocation/WATERS/src/strtools.h \
    memory_allocation/WATERS/src/Task2.h \
    memory_allocation/buttonlegend.h \
    tsp/tsp.h \
    tsp/tspdisplay.h \
    function_fitting/advanced_0/function.h \
    function_fitting/error_function.h \
    function_fitting/functionfitting.h \
    function_fitting/functionfittingdisplay.h

FORMS    += mainwindow.ui
