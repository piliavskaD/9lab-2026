include(FetchContent)

if (BUILD_APPROVAL_TESTS_WITH_GTEST OR BUILD_UNIT_TESTS_WITH_GTEST)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(googletest)
endif()

if (BUILD_APPROVAL_TESTS_WITH_CATCH2 OR BUILD_UNIT_TESTS_WITH_CATCH2)
  FetchContent_Declare(
    catch2 
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.0
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(catch2)
endif()

if (BUILD_APPROVAL_TESTS_WITH_GTEST OR BUILD_UNIT_TESTS_WITH_GTEST)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
endif()

add_subdirectory(cpp_googletest_unittest)
