FetchContent_Declare(
    dx9
    GIT_REPOSITORY https://github.com/madebr/min-dx9-sdk.git
    GIT_TAG        5597304
)

FetchContent_MakeAvailable(dx9)

# Create d3d8lib alias for DirectX 9 to maintain compatibility with existing code
add_library(d3d8lib INTERFACE)
target_link_libraries(d3d8lib INTERFACE d3d9lib)