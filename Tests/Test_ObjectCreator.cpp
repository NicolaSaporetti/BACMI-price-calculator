#include <iostream>
#include "TestBase.hpp"
#include "../ProductionCode/ObjectCreator.cpp"
using namespace std;

class Test_ObjectCreator : public Test_Base {
public:
    Test_ObjectCreator() {}

    void run() override {
        cout<<"\nTest ObjectCreator run"<<endl;
        test_create_plate_armor_1_mage_9_level();
        test_create_plate_armor_1_mage_36_level_roll_is_max_100();
        test_create_object_with_cost_not_multiple_of_1000();
        test_create_object_two_enchantments();
        test_create_object_with_multiple_enchantments();
    }

private:
    void test_create_plate_armor_1_mage_9_level()
    {
        cout<<"test_create_plate_armor_1_mage_9_level"<<endl;
        ObjectRecipe object_recipe = {10000,9,{1},{10000}};
        ObjectCreator object_creator;
        ObjectCreationSummary expected_result = {30,18181,4800,22981,{0.55}};
        
        ObjectCreationSummary result = object_creator.calculate_cost_magic_object(object_recipe);
        verify_equal(result,expected_result);
    }
    void test_create_plate_armor_1_mage_36_level_roll_is_max_100()
    {
        cout<<"test_create_plate_armor_1_mage_36_level"<<endl;
        ObjectRecipe object_recipe = {10000,36,{1},{10000}};
        ObjectCreator object_creator;
        ObjectCreationSummary expected_result = {17,10000,10914,20914,{1.0}};
        
        ObjectCreationSummary result = object_creator.calculate_cost_magic_object(object_recipe);
        verify_equal(result,expected_result);
    }
    void test_create_object_with_cost_not_multiple_of_1000()
    {
        cout<<"test_create_object_with_cost_not_multiple_of_1000"<<endl;
        ObjectRecipe object_recipe = {1,9,{1},{1}};
        ObjectCreator object_creator;
        ObjectCreationSummary expected_result = {14,1,1280,1281,{0.55}};
        
        ObjectCreationSummary result = object_creator.calculate_cost_magic_object(object_recipe);
        verify_equal(result,expected_result);
    }
    void test_create_object_two_enchantments()
    {
        cout<<"test_create_object_two_enchantments"<<endl;
        ObjectRecipe object_recipe = {2000,10,{4,4},{1000,1000}};
        ObjectCreator object_creator;
        ObjectCreationSummary expected_result = {36,6000,4806,10806,{0.5,0.5}};
        
        ObjectCreationSummary result = object_creator.calculate_cost_magic_object(object_recipe);
        verify_equal(result,expected_result);
    }
    void test_create_object_with_multiple_enchantments()
    {
        cout<<"test_create_object_with_multiple_enchantments"<<endl;
        ObjectRecipe object_recipe = {100005,9,{5,4,5},{35000,30005,35000}};
        ObjectCreator object_creator;
        ObjectCreationSummary expected_result = {1269,644592,111379,755971,{0.43,0.46,0.43}};
        
        ObjectCreationSummary result = object_creator.calculate_cost_magic_object(object_recipe);
        verify_equal(result,expected_result);
    }
};
