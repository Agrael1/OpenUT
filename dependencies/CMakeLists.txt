# plugins
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
include(FetchContent)

message("Loading Wisdom...")
FetchContent_Declare(
	wisdom
	GIT_REPOSITORY https://github.com/Agrael1/Wisdom.git
	GIT_TAG origin/master
)

set(WISDOM_BUILD_TYPE "modules")
FetchContent_MakeAvailable(wisdom)