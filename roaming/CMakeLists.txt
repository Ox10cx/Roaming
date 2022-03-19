# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

##设置生成的so动态库最后输出的路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI})


#设置头文件搜索路径（和此txt同个路径的头文件无需设置），可选
include_directories(/Users/gongxi/tools/osgle2_android-3.2.1_NEW/include
        src/main/cpp
        )

#C 的编译选项是 CMAKE_C_FLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fno-short-enums ")
# 指定编译参数，可选
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DOSG_LIBRARY_STATIC -frtti -fexceptions ")

set(CMAKE_SHARED_LINKER_FLAGS "-Wall -v -Wl, --warn-shared-textrel=no")

add_library( # Sets the name of the library.
        roaming

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/RoamingNativeLib.cpp
        src/main/cpp/OsgMainApp.cpp
        )

add_library(ft21 SHARED IMPORTED)
set_target_properties(ft21 PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI}/libft2.so)

add_library(ftstatic STATIC IMPORTED)
set_target_properties(ftstatic PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libdispmap_static.a)

add_library(osgdb_dds STATIC IMPORTED)
set_target_properties(osgdb_dds PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_dds.a)

add_library(osgdb_openflight STATIC IMPORTED)
set_target_properties(osgdb_openflight PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_openflight.a)

add_library(osgdb_tga STATIC IMPORTED)
set_target_properties(osgdb_tga PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_tga.a)

add_library(osgdb_obj STATIC IMPORTED)
set_target_properties(osgdb_obj PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_obj.a)

add_library(osgdb_jpeg STATIC IMPORTED)
set_target_properties(osgdb_jpeg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_jpeg.a)

add_library(osgdb_bmp STATIC IMPORTED)
set_target_properties(osgdb_bmp PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_bmp.a)

add_library(osgdb_rgb STATIC IMPORTED)
set_target_properties(osgdb_rgb PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_rgb.a)

#add_library(osgdb_png STATIC IMPORTED)
#set_target_properties(osgdb_png PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_png.a)

add_library(osgdb_osgterrain STATIC IMPORTED)
set_target_properties(osgdb_osgterrain PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_osgterrain.a)

add_library(osgdb_osg STATIC IMPORTED)
set_target_properties(osgdb_osg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_osg.a)

add_library(osgdb_ive STATIC IMPORTED)
set_target_properties(osgdb_ive PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_ive.a)

add_library(osgdb_freetype STATIC IMPORTED)
set_target_properties(osgdb_freetype PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_freetype.a)

add_library(ft2 STATIC IMPORTED)
set_target_properties(ft2 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libft2.a)


add_library(osgdb_deprecated_osgviewer STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgviewer PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgviewer.a)

add_library(osgdb_deprecated_osgvolume STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgvolume PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgvolume.a)

add_library(osgdb_deprecated_osgtext STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgtext PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgtext.a)

add_library(osgdb_deprecated_osgterrain STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgterrain PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgterrain.a)

add_library(osgdb_deprecated_osgsim STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgsim PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgsim.a)

add_library(osgdb_deprecated_osgshadow STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgshadow PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgshadow.a)

add_library(osgdb_deprecated_osgparticle STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgparticle PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgparticle.a)

add_library(osgdb_deprecated_osgfx STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osgfx PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osgfx.a)

add_library(osgdb_deprecated_osganimation STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osganimation PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osganimation.a)

add_library(osgdb_deprecated_osg STATIC IMPORTED)
set_target_properties(osgdb_deprecated_osg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_deprecated_osg.a)

add_library(osgdb_serializers_osgvolume STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgvolume PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgvolume.a)

add_library(osgdb_serializers_osgtext STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgtext PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgtext.a)

add_library(osgdb_serializers_osgterrain STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgterrain PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgterrain.a)

add_library(osgdb_serializers_osgsim STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgsim PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgsim.a)

add_library(osgdb_serializers_osgshadow STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgshadow PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgshadow.a)

add_library(osgdb_serializers_osgparticle STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgparticle PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgparticle.a)

add_library(osgdb_serializers_osgmanipulator STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgmanipulator PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgmanipulator.a)

add_library(osgdb_serializers_osgfx STATIC IMPORTED)
set_target_properties(osgdb_serializers_osgfx PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osgfx.a)

add_library(osgdb_serializers_osganimation STATIC IMPORTED)
set_target_properties(osgdb_serializers_osganimation PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osganimation.a)

add_library(osgdb_serializers_osg STATIC IMPORTED)
set_target_properties(osgdb_serializers_osg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgdb_serializers_osg.a)

add_library(osgViewer STATIC IMPORTED)
set_target_properties(osgViewer PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgViewer.a)

add_library(osgVolume STATIC IMPORTED)
set_target_properties(osgVolume PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgVolume.a)

add_library(osgTerrain STATIC IMPORTED)
set_target_properties(osgTerrain PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgTerrain.a)

add_library(osgText STATIC IMPORTED)
set_target_properties(osgText PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgText.a)

add_library(osgShadow STATIC IMPORTED)
set_target_properties(osgShadow PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgShadow.a)

add_library(osgSim STATIC IMPORTED)
set_target_properties(osgSim PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgSim.a)

add_library(osgParticle STATIC IMPORTED)
set_target_properties(osgParticle PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgParticle.a)

add_library(osgManipulator STATIC IMPORTED)
set_target_properties(osgManipulator PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgManipulator.a)

add_library(osgGA STATIC IMPORTED)
set_target_properties(osgGA PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgGA.a)

add_library(osgFX STATIC IMPORTED)
set_target_properties(osgFX PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgFX.a)

add_library(osgDB STATIC IMPORTED)
set_target_properties(osgDB PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgDB.a)

add_library(osgAnimation STATIC IMPORTED)
set_target_properties(osgAnimation PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgAnimation.a)

add_library(osgUtil STATIC IMPORTED)
set_target_properties(osgUtil PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosgUtil.a)

add_library(osg STATIC IMPORTED)
set_target_properties(osg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libosg.a)


add_library(jpeg STATIC IMPORTED)
set_target_properties(jpeg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libjpeg.a)

add_library(tiff STATIC IMPORTED)
set_target_properties(tiff PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libtiff.a)

#add_library(png STATIC IMPORTED)
#set_target_properties(png PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libpng.a)

add_library(zlib STATIC IMPORTED)
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libzlib.a)

add_library(OpenThreads STATIC IMPORTED)
set_target_properties(OpenThreads PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libOpenThreads.a)

#add_library(gnustl_static STATIC IMPORTED)
#set_target_properties(gnustl_static PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libgnustl_static.a)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        roaming
        ftstatic
        osgdb_dds
        osgdb_openflight
        osgdb_tga
        osgdb_obj
        osgdb_jpeg
        osgdb_bmp
        osgdb_rgb
        #                        osgdb_png
        osgdb_osgterrain
        osgdb_osg
        osgdb_ive
        osgdb_freetype
        ft2
        osgdb_deprecated_osgviewer
        osgdb_deprecated_osgvolume
        osgdb_deprecated_osgtext
        osgdb_deprecated_osgterrain
        osgdb_deprecated_osgsim
        osgdb_deprecated_osgshadow
        osgdb_deprecated_osgparticle
        osgdb_deprecated_osgfx
        osgdb_deprecated_osganimation
        osgdb_deprecated_osg
        osgdb_serializers_osgvolume
        osgdb_serializers_osgtext
        osgdb_serializers_osgterrain
        osgdb_serializers_osgsim
        osgdb_serializers_osgshadow
        osgdb_serializers_osgparticle
        osgdb_serializers_osgmanipulator
        osgdb_serializers_osgfx
        osgdb_serializers_osganimation
        osgdb_serializers_osg
        osgViewer
        osgVolume
        osgTerrain
        osgText
        osgShadow
        osgSim
        osgParticle
        osgManipulator
        osgGA
        osgFX
        osgDB
        osgAnimation
        osgUtil
        osg
        jpeg
        tiff
        #                        png
        zlib
        OpenThreads
#        gnustl_static


        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        -llog
        -lGLESv2
        -lz
        -ljnigraphics
        )


#