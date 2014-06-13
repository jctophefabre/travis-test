
ADD_DEFINITIONS(-DOPENFLUID_VERSION=${FULL_VERSION})
ADD_DEFINITIONS(-DBUILDINGDLL)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}/src")


OPNFLD_ADD_OBSERVER(tests.empty tests.empty ${TEST_OUTPUT_PATH})
OPNFLD_ADD_OBSERVER(tests.primitives.time tests.primitives.time ${TEST_OUTPUT_PATH})

###########################################################################


OPNFLD_ADD_OBSERVER(tests.hopla tests.hopla ${TEST_OUTPUT_PATH})
OPENFLUID_ADD_TEST(NAME observers-Hopla 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                                 "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.PrimitivesHopla"
                                 "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.PrimitivesHopla" 
                                 "-p${TEST_OUTPUT_PATH}"
                                 "-n${TEST_OUTPUT_PATH}"
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.PrimitivesHopla"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.PrimitivesHopla/tests.hopla_ofware-obs.log"
                   )


###########################################################################


OPNFLD_ADD_OBSERVER(tests.exceptions tests.exceptions ${TEST_OUTPUT_PATH})
OPENFLUID_ADD_TEST(NAME observers-Exceptions 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                           "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.ObsExceptions"
                           "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.ObsExceptions" 
                           "-p${TEST_OUTPUT_PATH}"
                           "-n${TEST_OUTPUT_PATH}"
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.ObsExceptions"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.ObsExceptions/openfluid-messages.log"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.ObsExceptions/tests.exceptions_ofware-sim.log"
                   )
SET_TESTS_PROPERTIES(observers-Exceptions PROPERTIES WILL_FAIL TRUE)


###########################################################################

                                 
OPENFLUID_ADD_TEST(NAME observers-CSVFiles 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                        "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.CSVObserver"
                        "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver" 
                        "-p${TEST_OUTPUT_PATH}"
                        "-n${TEST_OUTPUT_PATH}"
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver/fullfull_TestUnits1_tests.double.csv"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver/fullfull_TestUnits5_tests.double.csv"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver/some_TestUnits11_tests.string.csv"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver/someunits_TestUnits9_tests.matrix.dt.csv"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.CSVObserver/somevars_TestUnits7_tests.vector.csv"
                   )


###########################################################################

                        
OPENFLUID_ADD_TEST(NAME observers-DotFiles 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                        "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.DotObserver"
                        "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.DotObserver" 
                        "-p${TEST_OUTPUT_PATH}"
                        "-n${TEST_OUTPUT_PATH}"
                    PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.DotObserver"
                    POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.DotObserver/spatial-graph_t0.dot"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.DotObserver/spatial-graph_init.dot"
                              CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.DotObserver/spatial-graph_final.dot"
                   )


###########################################################################

                        
OPENFLUID_ADD_TEST(NAME observers-KmlFiles 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                        "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.KmlObservers"
                        "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.KmlObservers" 
                        "-p${TEST_OUTPUT_PATH}"
                        "-n${TEST_OUTPUT_PATH}"
                   PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.KmlObservers"
                   POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.KmlObservers/kmlplot.kmz"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.KmlObservers/SU.kmz"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.KmlObservers/RS.kmz"
                  )


###########################################################################

                        
OPENFLUID_ADD_TEST(NAME observers-VtkFiles 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                        "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.VtkObserver"
                        "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver" 
                        "-p${TEST_OUTPUT_PATH}"
                        "-n${TEST_OUTPUT_PATH}"
                   PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver"
                   POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver/VTKseries/RS_tests.random/RS_tests.random_t0.vtu"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver/VTKseries/RS_tests.random/RS_tests.random_t345600.vtu"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver/VTKseries/SU_tests.fixed/SU_tests.fixed_t57600.vtu"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.VtkObserver/VTKseries/SU_tests.random/SU_tests.random_t57600.vtu"                                                          
                  ) 


###########################################################################

                        
OPENFLUID_ADD_TEST(NAME observers-GNUplot 
                   COMMAND "${BIN_OUTPUT_PATH}/${OPENFLUID_CMD_APP}" 
                        "-i${TESTS_DATASETS_PATH}/OPENFLUID.IN.GNUplotObserver"
                        "-o${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver" 
                        "-p${TEST_OUTPUT_PATH}"
                        "-n${TEST_OUTPUT_PATH}"
                   PRE_TEST REMOVE_DIRECTORY "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver"
                   POST_TEST CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver/script.gnuplot"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver/s1_data.gnuplot"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver/s2_data.gnuplot"
                             CHECK_FILE_EXIST "${TESTS_OUTPUTDATA_PATH}/OPENFLUID.OUT.GNUplotObserver/s4_data.gnuplot"
                  )
                                                