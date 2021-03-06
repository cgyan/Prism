if(WIN32)
        set(SRC_EXT cpp)
elseif(APPLE)
        set(SRC_EXT mm)
endif()

set(MAIN_SOURCE ${MAIN_SOURCE}
    src/main.cpp
)

set(CORE_SOURCES ${CORE_SOURCES}
    src/core/Bitvector.cpp
    src/core/Char.cpp
    src/core/Circle.cpp
    src/core/ElapsedTimeMonitorFactory.cpp
    src/core/FileInfo.cpp
    src/core/FileSystem.${SRC_EXT}
    src/core/Fraction.cpp
    src/core/InvalidConversionException.cpp
    src/core/Mathf.cpp
    src/core/Matrix4.cpp
    src/core/Object.cpp
    src/core/Point.cpp
    src/core/Pointf.cpp
    src/core/Quaternion.cpp
    src/core/Rect.cpp
    src/core/SharedData.cpp
    src/core/Size.cpp
    src/core/String.cpp
    src/core/StringBuilder.cpp
    src/core/Time.cpp
    src/core/Vector2.cpp
    src/core/Vector3.cpp
    src/core/Vector4.cpp
    src/core/Version.cpp
    src/core/json/JsonArray.cpp
    src/core/json/JsonDoc.cpp
    src/core/json/JsonLexer.cpp
    src/core/json/JsonObject.cpp
    src/core/json/JsonStringBuilder.cpp
    src/core/json/JsonToken.cpp
    src/core/json/JsonValue.cpp
    src/core/json/JsonParserException.cpp
)

set(SOURCES
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
)
