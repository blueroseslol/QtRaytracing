#-------------------------------------------------
#
# Project created by QtCreator 2018-07-10T16:45:27
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRaytracing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \ 
    main.cpp \
    mainwindow.cpp \
    Utilities/BBox.cpp \
    Utilities/Maths.cpp \
    Utilities/Matrix.cpp \
    Utilities/Mesh.cpp \
    Utilities/Normal.cpp \
    Utilities/Point2D.cpp \
    Utilities/Point3D.cpp \
    Utilities/Ray.cpp \
    Utilities/RGBColor.cpp \
    Utilities/ShadeRec.cpp \
    Utilities/Vector3D.cpp \
    Geometry/geometry.cpp \
    Geometry/plane.cpp \
    Geometry/sphere.cpp \
    World.cpp \
    Cameras/Camera.cpp \
    ViewPlane.cpp \
    Core/Render.cpp \
    Tracer/tracer.cpp \
    rendersetting.cpp \
    Tracer/mutipleobjects.cpp \
    Sampler/sampler.cpp \
    Sampler/jittered.cpp \
    Sampler/regular.cpp \
    Sampler/multijittered.cpp \
    Utilities/Constants.cpp \
    Sampler/hammersley.cpp \
    Cameras/pinhole.cpp \
    Cameras/fisheye.cpp \
    BRDF/brdf.cpp \
    BRDF/lambertian.cpp \
    Light/light.cpp \
    Light/ambient.cpp \
    Material/material.cpp \
    Tracer/raycast.cpp \
    Material/Matte.cpp \
    Material/normalmaterial.cpp \
    Light/directional.cpp \
    Light/pointlight.cpp \
    BRDF/glossyspecular.cpp \
    Material/phong.cpp \
    Light/ambientoccluder.cpp

HEADERS += \
    mainwindow.h \
    Utilities/BBox.h \
    Utilities/Constants.h \
    Utilities/Maths.h \
    Utilities/Matrix.h \
    Utilities/Mesh.h \
    Utilities/Normal.h \
    Utilities/Point2D.h \
    Utilities/Point3D.h \
    Utilities/Ray.h \
    Utilities/RGBColor.h \
    Utilities/ShadeRec.h \
    Utilities/Vector3D.h \
    Geometry/geometry.h \
    Geometry/plane.h \
    Geometry/sphere.h \
    World.h \
    Cameras/Camera.h \
    ViewPlane.h \
    Core/Render.h \
    Tracer/tracer.h \
    rendersetting.h \
    Tracer/mutipleobjects.h \
    Sampler/sampler.h \
    Sampler/jittered.h \
    Sampler/regular.h \
    Sampler/multijittered.h \
    Sampler/hammersley.h \
    Cameras/pinhole.h \
    Cameras/fisheye.h \
    BRDF/brdf.h \
    BRDF/lambertian.h \
    Light/light.h \
    Light/ambient.h \
    Material/material.h \
    Tracer/raycast.h \
    Material/Matte.h \
    Material/normalmaterial.h \
    Light/directional.h \
    Light/pointlight.h \
    BRDF/glossyspecular.h \
    Material/phong.h \
    Light/ambientoccluder.h

FORMS += \
        mainwindow.ui \
    rendersetting.ui


INCLUDEPATH += $$PWD/tbb/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tbb/lib/intel64/vc14/ -ltbb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tbb/lib/intel64/vc14/ -ltbb_debug

INCLUDEPATH += $$PWD/tbb/lib/intel64/vc14
DEPENDPATH += $$PWD/tbb/lib/intel64/vc14
