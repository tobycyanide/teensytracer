add_executable(raytracer_test
        TupleTest.cpp
        ColorTest.cpp
        CanvasTest.cpp
        MatrixTest.cpp
        TransformTest.cpp
        RaysTest.cpp
        SpheresTest.cpp
        IntersectionTest.cpp
        LightsTest.cpp
        MaterialsTest.cpp
        WorldTest.cpp
        CameraTest.cpp
        ShapesTest.cpp
        PlanesTest.cpp)


target_link_libraries(raytracer_test raytracer_lib)