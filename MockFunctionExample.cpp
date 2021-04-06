#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace windows {
enum class Severity { LOW, MEDIUM, CRITICAL };
bool troubleshooting_tool(Severity severity)
{
    std::cout << "Looking for solution... \n";
    std::this_thread::sleep_for(std::chrono::seconds(2000));
    throw std::runtime_error {"System Windows cannot find the solution."};
}
} // namespace windows

struct AdvancedTroubleshootingTool {
    void FixMonitorDriver()
    {
            try {
                predicate(windows::Severity::CRITICAL);
            } catch (const std::exception& ex)
            {
                std::cout << "Success: " << ex.what() << "\n";
                throw;
            }
    }

    std::function<bool(windows::Severity)> predicate = &windows::troubleshooting_tool;
};

TEST(AdvancedTroubleshootingToolTest, DoesNotFixMonitorDriver)
{
    ::testing::MockFunction<bool(windows::Severity)> windowsTrouleshootingMock{};
    EXPECT_CALL(windowsTrouleshootingMock, Call(windows::Severity::CRITICAL))
        .WillOnce(::testing::Throw(std::runtime_error{"Exception thrown from mock."}));
        
    AdvancedTroubleshootingTool unit_under_test{ windowsTrouleshootingMock.AsStdFunction() };

    EXPECT_THROW(unit_under_test.FixMonitorDriver(), std::exception);
}

int main (int argc, char * argv[]) 
{
    ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}
