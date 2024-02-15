#include <gtest/gtest.h>

#include "search.h"
#include "tests/build_index.h"
#include "tests/clean_token.h"
#include "tests/find_query_matches.h"
#include "tests/gather_tokens.h"

TEST(CleanToken, PunctBothEnds) {
    map<string, set<string>> tests;
    tests["color"].insert("!?color?!");
    tests["lock"].insert("..LOCK,,");
    tests["play"].insert(".:play''");
    testCleanToken(tests);
}

TEST(CleanToken, PunctMidOnly) {
    map<string, set<string>> tests;
    tests["co.lor"].insert("CO.LOR");
    tests["co..lor"].insert("co..lOr");
    tests["sing!er"].insert("SINg!er");
    testCleanToken(tests);
}

TEST(CleanToken, PunctMidAndStart) {
    map<string, set<string>> tests;
    tests["ra!inbow"].insert("..Ra!inbow");
    tests["conne???ct"].insert("??!conne???ct");
    tests["mor...ning"].insert("???MOR...ning");
    testCleanToken(tests);
}

TEST(CleanToken, PunctMidAndEnd) {
    map<string, set<string>> tests;
    tests["co,lor"].insert("co,lor??");
    tests["ben?ch"].insert("ben?ch!!");
    tests["mult?i"].insert("MULt?i");
    testCleanToken(tests);
}

TEST(CleanToken, NumInFront) {
    map<string, set<string>> tests;
    tests["123hi"].insert("123hi??");
    testCleanToken(tests);
}

TEST(CleanToken, OneLet) {
    map<string, set<string>> tests;
    tests["x"].insert("x!");
    testCleanToken(tests);
}

TEST(CleanToken, PunctandSpace) {
    map<string, set<string>> tests;
    tests["a"].insert(". . .a");
    testCleanToken(tests);
}

TEST(CleanToken, NotPunct) {
    map<string, set<string>> tests;
    tests["“hi“"].insert("“hi“!");
    testCleanToken(tests);
}

TEST(GatherTokens, LeadSpace){
    string text = "   How are you?";
    set<string> expected = {"how","are","you"};
    set<string> studentResult = gatherTokens(text);
    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(GatherTokens, TrailSpace){
    string text = "I'm doing good!   ";
    set<string> expected = {"i'm","doing","good"};
    set<string> studentResult = gatherTokens(text);
    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(GatherTokens, MultiSpace){
    string text = "Me   as    well.";
    set<string> expected = {"me","as","well"};
    set<string> studentResult = gatherTokens(text);
    string testFeedback = "gatherTokens(\"" + text + "\") incorrect\n";

    EXPECT_EQ(expected, studentResult) << testFeedback;
}

TEST(BuildIndex, TinyText){
    string filename = "tiny.txt";
    map<string, set<string>> expected = {
        {"eggs",{"www.shoppinglist.com"}},
        {"milk",{"www.shoppinglist.com"}},
        {"fish",{"www.shoppinglist.com", "www.dr.seuss.net"}},
        {"bread",{"www.shoppinglist.com"}},
        {"cheese",{"www.shoppinglist.com"}},
        {"red",{"www.rainbow.org", "www.dr.seuss.net"}},
        {"green",{"www.rainbow.org"}},
        {"orange",{"www.rainbow.org"}},
        {"yellow",{"www.rainbow.org"}},
        {"blue",{"www.rainbow.org", "www.dr.seuss.net"}},
        {"indigo",{"www.rainbow.org"}},
        {"violet",{"www.rainbow.org"}},
        {"one",{"www.dr.seuss.net"}},
        {"two",{"www.dr.seuss.net"}},
        {"i'm",{"www.bigbadwolf.com"}},
        {"not",{"www.bigbadwolf.com"}},
        {"trying",{"www.bigbadwolf.com"}},
        {"to",{"www.bigbadwolf.com"}},
        {"eat",{"www.bigbadwolf.com"}},
        {"you",{"www.bigbadwolf.com"}}
    };
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(4, studentNumProcesed) << retTestFeedback;
}

TEST(BuildIndex, InvalidFile){
    string filename = "invalid.txt";
    map<string, set<string>> expected = {};
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);

    string indexTestFeedback = "buildIndex(\"" + filename + "\", ...) index incorrect\n";
    EXPECT_EQ(expected, studentIndex) << indexTestFeedback;

    string retTestFeedback = "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
    EXPECT_EQ(0, studentNumProcesed) << retTestFeedback;
}

TEST(FindQueryMatches, NotInIndex) {
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
    };

    set<string> expected;
    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "invalid"));
}

TEST(FindQueryMatches, LaterPlus){
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
    };

    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "not +here"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "neither +here +or"));
}

TEST(FindQueryMatches, LaterMinus){
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
    };

    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "not -here"));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "neither -here -or"));
}

TEST(FindQueryMatches, LaterSpace) {
    map<string, set<string>> INDEX = {
    {"hello", {"example.com", "uic.edu"}},
    {"there", {"example.com"}},
    {"according", {"uic.edu"}},
    {"to", {"uic.edu"}},
    {"all", {"example.com", "uic.edu", "random.org"}},
    {"known", {"uic.edu"}},
    {"laws", {"random.org"}},
    {"of", {"random.org"}},
    {"aviation", {"random.org"}},
    {"a", {"uic.edu", "random.org"}},
    };
    
    set<string> expected;

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "unknown "));

    expected = {};
    EXPECT_EQ(expected, findQueryMatches(INDEX, "unknown token"));
}

