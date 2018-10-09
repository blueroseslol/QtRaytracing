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
    Light/ambientoccluder.cpp \
    Tracer/arealighting.cpp \
    Material/emissive.cpp \
    Light/arealight.cpp \
    Geometry/rectangular.cpp \
    Light/environmentlight.cpp \
    Geometry/box.cpp \
    Geometry/Triangles/Triangle.cpp \
    Geometry/Instance.cpp \
    Geometry/compound.cpp \
    Geometry/grid.cpp \
    Tracer/whitted.cpp \
    Material/reflective.cpp \
    BRDF/perfectSpecular.cpp \
    Material/GlossyReflector.cpp \
    Tracer/pathtrace.cpp \
    Tracer/globeltracer.cpp \
    BRDF/BTDF.cpp \
    BRDF/PerfectTransmitter.cpp \
    Material/Transparent.cpp \
    Material/Dielectric.cpp \
    BRDF/FresnelReflector.cpp \
    BRDF/FresnelTransmitter.cpp \
    Texture/Checker3D.cpp \
    Texture/CubicNoise.cpp \
    Texture/Image.cpp \
    Texture/ImageTexture.cpp \
    Texture/LatticeNoise.cpp \
    Texture/PlaneChecker.cpp \
    Texture/RampFBmTexture.cpp \
    Texture/Texture.cpp \
    Texture/TurbulenceTexture.cpp \
    Texture/WrappedFBmTexture.cpp \
    Material/SV_Matte.cpp \
    Texture/constantcolor.cpp \
    BRDF/SV_Lambertian.cpp \
    Texture/Mapping.cpp \
    Texture/sphericalmap.cpp \
    Texture/TInstance.cpp \
    Texture/FBmTexture.cpp

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
    Light/ambientoccluder.h \
    Tracer/arealighting.h \
    Material/emissive.h \
    Light/arealight.h \
    Geometry/rectangular.h \
    Light/environmentlight.h \
    Geometry/box.h \
    Geometry/Triangles/Triangle.h \
    Geometry/Instance.h \
    Geometry/compound.h \
    Geometry/grid.h \
    Tracer/whitted.h \
    Material/reflective.h \
    BRDF/perfectSpecular.h \
    Material/GlossyReflector.h \
    Tracer/pathtrace.h \
    Tracer/globeltracer.h \
    BRDF/BTDF.h \
    BRDF/PerfectTransmitter.h \
    Material/Transparent.h \
    Material/Dielectric.h \
    BRDF/FresnelReflector.h \
    BRDF/FresnelTransmitter.h \
    Texture/Checker3D.h \
    Texture/CubicNoise.h \
    Texture/Image.h \
    Texture/ImageTexture.h \
    Texture/LatticeNoise.h \
    Texture/PlaneChecker.h \
    Texture/RampFBmTexture.h \
    Texture/Texture.h \
    Texture/TurbulenceTexture.h \
    Texture/WrappedFBmTexture.h \
    Material/SV_Matte.h \
    Texture/constantcolor.h \
    BRDF/SV_Lambertian.h \
    Texture/Mapping.h \
    Texture/sphericalmap.h \
    Texture/TInstance.h \
    Texture/FBmTexture.h

FORMS += \
        mainwindow.ui \
    rendersetting.ui


INCLUDEPATH += $$PWD/tbb/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tbb/lib/intel64/vc14/ -ltbb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tbb/lib/intel64/vc14/ -ltbb_debug

INCLUDEPATH += $$PWD/tbb/lib/intel64/vc14
DEPENDPATH += $$PWD/tbb/lib/intel64/vc14
