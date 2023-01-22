#include <iostream>
#include "TestBase.hpp"
#include "../ProductionCode/Calculator.cpp"
#include "../ProductionCode/ObjectCreator.cpp"
#include "../ProductionCode/WeaponCalculator.cpp"
#include "../ProductionCode/ArmorCalculator.cpp"
#include "../ProductionCode/PercentageComputation.cpp"
using namespace std;

class Test_Integration : public Test_Base {
public:
    Test_Integration() {}

    void run() override {
        cout<<"\nIntegration test run"<<endl;
        test_create_sword_3_2_2_mage_9_level();
        test_create_mace_3_2_mage_9_level();
        test_create_plate_armor_4_mage_20_level();
        test_create_potion_3_doses_level_4_mage_20_level();
        test_create_accumulator_ring_5_spells_2_3_4_4_5_mage_25_level();
        test_create_ring_prot_4_mage_15_level();
    }

private:
    void test_create_sword_3_2_2_mage_9_level()
    {
        cout<<"test_create_sword_3_2_2_mage_9_level"<<endl;
        ObjectCreationSummary expected_result = {166,52783.5,12441.8,65225.3,{0.49,0.52,0.52}};
        Sword sword = {WeaponType::Spada,3,2,2};
        ItemSummary item = calculator.calculate_cost_sword(sword);
        ObjectRecipe recipe = {item.total_cost,9,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }
    void test_create_mace_3_2_mage_9_level()
    {
        cout<<"test_create_mace_3_2_mage_9_level"<<endl;
        ObjectCreationSummary expected_result = {39,7535.32,4036.78,11572.1,{0.49,0.52}};
        Weapon mace = {WeaponType::Mazza,3,2};
        ItemSummary item = calculator.calculate_cost_weapon(mace);
        ObjectRecipe recipe = {item.total_cost,9,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }
    void test_create_plate_armor_4_mage_20_level()
    {
        cout<<"test_create_plate_armor_4_mage_20_level"<<endl;
        ObjectCreationSummary expected_result = {58,50000,20982.1,70982.1,{0.8}};
        Armor armor = {ArmorType::Piastre,4};
        ItemSummary item = calculator.calculate_cost_armor(armor);
        ObjectRecipe recipe = {item.total_cost,20,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }
    void test_create_potion_3_doses_level_4_mage_20_level()
    {
        cout<<"test_create_potion_3_doses_level_4_mage_20_level"<<endl;
        ObjectCreationSummary expected_result = {15,5200,5357.14,10557.1,{0.8}};
        ItemWithCharges potion = {RechargeType::Non_recheargeable,{4},3};
        ItemSummary item = calculator.calculate_cost_item_with_charges(potion);
        ObjectRecipe recipe = {item.total_cost,20,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }
    void test_create_accumulator_ring_5_spells_2_3_4_4_5_mage_25_level()
    {
        cout<<"test_create_accumulator_ring_5_spells_2_3_4_4_5_mage_25_level"<<endl;
        ObjectCreationSummary expected_result = {34,22613,13766,36379.1,{1,0.97,0.94,0.94,0.91}};
        ItemWithCharges ring = {RechargeType::Recheargeable,{2,3,4,4,5},1};
        ItemSummary item = calculator.calculate_cost_item_with_charges(ring);
        ObjectRecipe recipe = {item.total_cost,25,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }
    void test_create_ring_prot_4_mage_15_level()
    {
        cout<<"test_create_ring_prot_4_mage_15_level"<<endl;
        ObjectCreationSummary expected_result = {46,36363.6,12581.2,48944.8,{0.66}};
        PermanentItem ring = {4};
        ItemSummary item = calculator.calculate_cost_permanent_item(ring);
        ObjectRecipe recipe = {item.total_cost,15,item.enchantment_levels,item.enchantment_cost_by_level};

        ObjectCreationSummary result = objectCreator.calculate_cost_magic_object(recipe);
        verify_equal(result,expected_result);
    }

    Calculator calculator;
    ObjectCreator objectCreator;
};
