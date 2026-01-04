FetchContent_Declare(
    dx8
    GIT_REPOSITORY https://github.com/JohnsterID/min-dx8-sdk.git
    GIT_TAG        4b0f353d9e177f211facc1b46945497c542bd2a9 # fix-dxfile-ctrl-z-corruption branch
)

FetchContent_MakeAvailable(dx8)
