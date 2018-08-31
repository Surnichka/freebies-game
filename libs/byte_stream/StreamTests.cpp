#include "StreamTests.h"
#include "OutByteStream.h"
#include "InByteStream.h"

/*TODO:
 * Cast from type to type
 * Every type of array
 */

namespace byte_stream
{
namespace tests
{
namespace utility
{
static bool isTestValid = false;

struct compare
{
    template<typename T1, typename T2>
    static inline std::enable_if_t
    <
        libs::type_tools::TypeInfo<T1>::IsFundamental == true &&
        libs::type_tools::TypeInfo<T1>::IsArray       == false,
    void
    >
    isValid(const T1& val1, const T2& val2, bool expected)
    {
       isTestValid = (val1 == static_cast<T1>(val2)) == expected;
    }

    template<typename T1, typename T2>
    static inline std::enable_if_t
    <
        libs::type_tools::TypeInfo<T1>::IsArray == true,
    void
    >
    isValid(const T1& val1, const T2& val2, bool expected)
    {
        uint32_t size1 = libs::type_tools::ArrayInfo<T1>::GetSize(val1);
        uint32_t size2 = libs::type_tools::ArrayInfo<T2>::GetSize(val2);

        isTestValid = size1 == size2;
        if(isTestValid != expected) { return; }

        for(uint32_t i = 0; i < size1; ++i)
        {
            isTestValid = (val1[i] == val2[i]);

            if(isTestValid != expected) { return; }
        }
    }

    template<typename T1, typename T2>
    static inline std::enable_if_t
    <
        libs::type_tools::TypeInfo<T1>::IsArray       == false &&
        libs::type_tools::TypeInfo<T1>::IsFundamental == false,
    void
    >
    isValid(const T1& val1, const T2& val2, bool expected)
    {
        uint32_t size1 = static_cast<uint32_t>(val1.size());
        uint32_t size2 = static_cast<uint32_t>(val2.size());

        isTestValid = size1 == size2;
        if(isTestValid != expected) { return; }

        isTestValid = (val1 == val2) == expected;
    }

};

}

bool FundamentalTypes()
{
    libs::oByteStream out;
    libs::iByteStream in;

	char test1 = 'a';
	int test2 = 11;
	float test3 = 12.345f;
	double test4 = 54.321;
	unsigned int test5 = 123;

	out << test1 << test2 << test3 << test4 << test5;

	in.SetBuffer(out.GetBuffer());

	char ret1 = 0;
	int ret2 = 0;
	float ret3 = 0.f;
	double ret4 = 0;
	unsigned int ret5 = 0;

	in >> ret1;
    utility::compare::isValid(test1, ret1, true);
	in >> ret2;
    utility::compare::isValid(test2, ret2, true);
	in >> ret3;
    utility::compare::isValid(test3, ret3, true);//values are exactly the same so it shouldn't fail
	in >> ret4;
    utility::compare::isValid(test4, ret4, true);//values are exactly the same so it shouldn't fail
	in >> ret5;
    utility::compare::isValid(test5, ret5, true);

    return utility::isTestValid;
}

bool ArrayTypes()
{
    libs::oByteStream out;
    libs::iByteStream in;

    std::vector<int>                        test1 = {1, 2, 4};
    std::vector<std::string>                test2 = {"one", "two", "three", "sixteen", "quad"};
    const char*                             test3 = "my string is bigger than your string";
    char                                    test4[] = "this string sucks things";
    //std::array<float, 10>                   test5 = {{1.10f, 2.9f, 3.8f, 4.7f, 5.6f, 6.5f, 7.4f, 8.3f, 9.2f, 10.1f}};
    double                                  test6[10] = {1.10, 2.9, 3.8, 4.7, 5.6, 6.5, 7.4, 8.3, 9.2, 10.1};
    std::list<std::string>                  test7 = {"list item weqr", "list item dasfadf", "list item xxbn", "list item etsherq"};
    std::map<std::string, int>              test8 = {{"key1", 1}, {"key2", 2}, {"key3", 3}, {"key4", 4}, {"key5", 5}};
    std::set<int>                           test9 = {4, 6, 2, 0, -1};
    std::unordered_map<std::string, int>    test10 = {{"bla", 2}, {"df", 3}, {"r", 1}, {"erre", 4}, {"grt", 5}};

    out << test1;
    out << test2;
    //test for -> const char*
    out << test3;
    out << test4;
    //out << test5;
    out << test6;
    out << test7;
    out << test8;
    out << test9;
    out << test10;

    in.SetBuffer(out.GetBuffer());

    std::vector<int>                        ret1;
    std::vector<std::string>                ret2;
    //from const char*
    std::string                             ret3;
    //from char[]
    std::string                             ret4;
    std::array<float, 10>                   ret5;
    double                                  ret6[10];
    std::list<std::string>                  ret7;
    std::map<std::string, int>              ret8;
    std::set<int>                           ret9;
    std::unordered_map<std::string, int>    ret10;

    in >> ret1;
    utility::compare::isValid(test1, ret1, true);
    in >> ret2;
    utility::compare::isValid(test2, ret2, true);
    in >> ret3;
    utility::compare::isValid(std::string(test3), ret3, true);
    in >> ret4;
    utility::compare::isValid(std::string(test4), ret4, true);
    //in >> ret5;
    //utility::compare::isValid(test5, ret5, true);
    in >> ret6;
    utility::compare::isValid(test6, ret6, true);
    in >> ret7;
    utility::compare::isValid(test7, ret7, true);
    in >> ret8;
    utility::compare::isValid(test8, ret8, true);
    in >> ret9;
    utility::compare::isValid(test9, ret9, true);
    in >> ret10;
    utility::compare::isValid(test10, ret10, true);

    return utility::isTestValid;
}

bool UserDefinedTypes()
{
	return false;
}

void RunTests()
{
    if(FundamentalTypes())
	{
		printf("Expected fundamental types are Serializing and Deserializing correctly.\n");
	}

    if(ArrayTypes())
	{
		printf("Expected array types are Serializing and Deserializing correctly.\n");
	}

    if(UserDefinedTypes())
	{
		printf("User defined types are not yet supported!\n");
	}
}

}//end of tests
}//end of byte_stream
