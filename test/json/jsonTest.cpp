#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "gtest/gtest.h"


namespace {

    using namespace rapidjson;

    TEST(jsonTest, BASIC) {
        // 1. Parse a JSON string into DOM.
        const char *json = R"({"project":"rapidjson","stars":10})";
        Document d;
        d.Parse(json);

        // 2. Modify it by DOM.
        Value &s = d["stars"];
        s.SetInt(s.GetInt() + 1);

        // 3. Stringify the DOM
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        d.Accept(writer);

        EXPECT_STREQ(R"({"project":"rapidjson","stars":11})", buffer.GetString());
    }

}  // namespace
