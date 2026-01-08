FetchContent_Declare(
    dx9
    GIT_REPOSITORY https://github.com/madebr/min-dx9-sdk.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(dx9)

# Alias dx9 to d3d8lib for compatibility with existing code.
add_library(d3d8lib ALIAS dx9)
