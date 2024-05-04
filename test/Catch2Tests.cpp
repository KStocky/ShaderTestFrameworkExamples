
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
    ShaderTestFixture::Desc desc;
    desc.Mappings.emplace_back(GetTestVirtualDirectoryMapping());
    desc.Source = fs::path("/MyTests/ShaderTest.hlsl"); 

    ShaderTestFixture fixture(std::move(desc));

    DYNAMIC_SECTION(testName)
    {
        if (shouldSucceed)
        {
            REQUIRE(fixture.RunTest(testName, 1, 1, 1));
        }
        else
        {
            const auto result = fixture.RunTest(testName, 1, 1, 1);
            REQUIRE_FALSE(result);
        }
        
    }
}