// SPDX-License-Identifier: Apache-2.0
// Copyright 2020 - 2023 Pionix GmbH and Contributors to EVerest
#include <catch2/catch_all.hpp>

#include <framework/everest.hpp>

// FIXME: convert the configs, interfaces, etc. used in these tests to yaml

SCENARIO("Check config parser", "[!throws]") {
    GIVEN("An empty config") {
        Everest::Config config = Everest::Config("../../schemas", "valid/config.yaml", "test_modules",
                                                 "test_interfaces", "dummy_types", "", "");
        THEN("It should not contain some module") {
            CHECK(!config.contains("some_module"));
        }
    }

    // FIXME (aw): all the exception checks can't distinguish, what the
    //             real reason was, this needs to be improved (probably
    //             by proper ExceptionTypes)
    GIVEN("An invalid main dir") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "wrong_maindir", "test_modules", "test_interfaces",
                                            "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    GIVEN("A non existing config file") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "missing_config", "test_modules", "test_interfaces",
                                            "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    GIVEN("A broken config file") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "broken_config/config.yaml", "test_modules",
                                            "test_interfaces", "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    GIVEN("A config file referencing a non existent module") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "missing_module_config/config.yaml", "test_modules",
                                            "test_interfaces", "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    // FIXME
    GIVEN("A config file using a module with broken manifest") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "broken_manifest/config.yaml", "broken_manifest/modules",
                                            "test_interfaces", "dummy_types", "", ""),
                            Everest::EverestConfigError);
            // FIXME: an empty manifest breaks the test?
            CHECK_THROWS_AS(Everest::Config("../../schemas", "broken_manifest2/config.yaml", "broken_manifest2/modules",
                                            "test_interfaces", "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    GIVEN("A config file using a module with a valid manifest referencing an invalid interface") {
        THEN("It should throw Everest::EverestConfigError") {
            CHECK_THROWS_AS(Everest::Config("../../schemas", "valid_manifest_missing_interface/config.yaml",
                                            "valid_manifest_missing_interface/modules", "test_interfaces",
                                            "dummy_types", "", ""),
                            Everest::EverestConfigError);
        }
    }

    GIVEN("A valid config") {
        THEN("It should not throw at all") {
            CHECK_NOTHROW(Everest::Config("../../schemas", "valid_manifest_valid_interface/config.yaml",
                                          "valid_manifest_valid_interface/modules",
                                          "valid_manifest_valid_interface/interfaces", "dummy_types", "", ""));
        }
    }
}
