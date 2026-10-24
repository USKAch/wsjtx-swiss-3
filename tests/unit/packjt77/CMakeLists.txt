add_executable (test_packjt77_hash_vectors
  test_packjt77_hash_vectors.f90)
target_include_directories (test_packjt77_hash_vectors PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries (test_packjt77_hash_vectors wsjt_fort wsjt_cxx)

add_test (NAME test_packjt77_hash_vectors COMMAND test_packjt77_hash_vectors)

add_executable (test_packjt77_swiss_cantons
  test_packjt77_swiss_cantons.f90)
target_include_directories (test_packjt77_swiss_cantons PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries (test_packjt77_swiss_cantons wsjt_fort wsjt_cxx)

add_test (NAME test_packjt77_swiss_cantons COMMAND test_packjt77_swiss_cantons)
