#include <iostream>
#include <assert.h>
#include "TestBase.hpp"
#include "../ProductionCode/PercentageComputation.cpp"
using namespace std;

class Test_PercentageComputation : public Test_Base {
public:
    Test_PercentageComputation() {}

    void run() override {
        cout<<"\nTest PercentageComputation run"<<endl;
        test_calculate_percentage_level_9();
        test_calculate_percentage_level_10();
        test_calculate_percentage_level_12();
        test_calculate_percentage_level_15();
        test_calculate_percentage_level_20();
        test_calculate_percentage_level_25();
        test_calculate_percentage_level_30();
        test_calculate_percentage_level_35();
        test_calculate_percentage_level_36();
    }

private:
    void test_calculate_percentage_level_9()
    {
        cout<<"test_calculate_percentage_level_9 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(9,1),0.55);
    }
    void test_calculate_percentage_level_10()
    {
        cout<<"test_calculate_percentage_level_10 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(10,1),0.59);
    }
    void test_calculate_percentage_level_12()
    {
        cout<<"test_calculate_percentage_level_12 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(12,1),0.65);
    }
    void test_calculate_percentage_level_15()
    {
        cout<<"test_calculate_percentage_level_15 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(15,1),0.75);
    }
    void test_calculate_percentage_level_20()
    {
        cout<<"test_calculate_percentage_level_20 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(20,1),0.89);
    }
    void test_calculate_percentage_level_25()
    {
        cout<<"test_calculate_percentage_level_25 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(25,1),1.0);
    }
    void test_calculate_percentage_level_30()
    {
        cout<<"test_calculate_percentage_level_30 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(30,9),0.91);
    }
    void test_calculate_percentage_level_35()
    {
        cout<<"test_calculate_percentage_level_35 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(35,12),0.94);
    }
    void test_calculate_percentage_level_36()
    {
        cout<<"test_calculate_percentage_level_36 run"<<endl;
        PercentageComputation computator;
        verify_equal(computator.success_chance(36,15),0.89);
    }
};
