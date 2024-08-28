
#include <Framework/ShaderTestFixture.h>

static VirtualShaderDirectoryMapping GetTestVirtualDirectoryMapping()
{
    return VirtualShaderDirectoryMapping{ "/MyTests", fs::current_path() / "shader" };
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

    ShaderTestFixture fixture(
        ShaderTestFixture::FixtureDesc
        {
            .Mappings{ GetTestVirtualDirectoryMapping() }
        }
    );

    DYNAMIC_SECTION(testName)
    {
        const auto result = fixture.RunTest(
            ShaderTestFixture::RuntimeTestDesc
            {
                .CompilationEnv
                {
                    .Source = fs::path("/MyTests/ShaderTest.hlsl")
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