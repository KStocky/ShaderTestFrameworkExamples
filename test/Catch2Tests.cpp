
#include <Framework/ShaderTestFixture.h>

static stf::VirtualShaderDirectoryMapping GetTestVirtualDirectoryMapping()
{
    return stf::VirtualShaderDirectoryMapping{ "/MyTests", std::filesystem::current_path() / "shader" };
}

#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

SCENARIO("BasicShaderTests")
{
    auto [testName, shouldSucceed] = GENERATE
    (
        table<std::string, bool>
        (
            {
                std::tuple{"ThisTestDoesNotExist", false},
                std::tuple{"ThisTestShouldPass", true},
                std::tuple{"ThisTestShouldFail", false},
            }
        )
    );

    stf::ShaderTestFixture fixture(
        stf::ShaderTestFixture::FixtureDesc
        {
            .Mappings{ GetTestVirtualDirectoryMapping() }
        }
    );

    DYNAMIC_SECTION(testName)
    {
        const auto result = fixture.RunTest(
            stf::ShaderTestFixture::RuntimeTestDesc
            {
                .CompilationEnv
                {
                    .Source = std::filesystem::path("/MyTests/ShaderTest.hlsl")
                },
                .TestName = testName,
                .ThreadGroupCount{1,1,1}
            }
        );

        if (shouldSucceed)
        {
            REQUIRE(result);
        }
        else
        {
            
            REQUIRE_FALSE(result);
        }
        
    }
}