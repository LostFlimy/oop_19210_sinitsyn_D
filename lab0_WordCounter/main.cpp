#include<fstream>
#include <sstream>
#include <gtest/gtest.h>
#include "lineReader.h"
#include "tokenService.h"
#include "wordStateService.h"
#include "reportService.h"

using namespace std;

TEST(WordCounterTests, TokenServiceTest){
    TokenService service1;
    service1.fillLine("Hello,. : World., asd!!!");
    vector<string> curvector;
    curvector.push_back("Hello");
    curvector.push_back("World");
    curvector.push_back("asd");
    ASSERT_TRUE(service1.getParts() == curvector);

    TokenService service2;
    service2.fillLine("");
    ASSERT_TRUE(service2.getParts().size() == 0);
}

TEST(WordCounterTests, WordStateService){
    {
        WordStateService service1;
        string curstring = "You just want attention, you don't want my heart\n"
                           "Maybe you just hate the thought of me with someone new\n"
                           "Yeah, you just want attention, I knew from the start\n"
                           "You're just making sure I'm never gettin' over you, oh";
        TokenService tokens;
        tokens.fillLine(curstring);
        service1.createState(tokens.getParts());
        vector<pair<pair<int, double>, string>> result = service1.getState();
        ASSERT_TRUE(result[0].second == "you" || result[0].second == "just");
        ASSERT_TRUE(result[0].first.second == 0.1);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

