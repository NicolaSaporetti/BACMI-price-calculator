#ifndef ObjectCreator_HPP
#define ObjectCreator_HPP

#include "ObjectCreationSummary.hpp"
#include "ObjectRecipe.hpp"
using namespace std;

class ObjectCreator {
public:
    ObjectCreationSummary calculate_cost_magic_object(const ObjectRecipe& object_recipe);
private:
    vector<double> compute_roll_required(const vector<int>& enchantment_levels, int caster_level);
    int compute_days_to_create(int base_cost);
    double compute_days_to_bill(int material_cost, int base_cost);
    double compute_percentage(int caster_level, int enchantment_levels);
    int compute_helpers(int caster_level);
    int compute_labor_cost(int caster_level, double days_to_create);
    int adjust_price_based_on_difficulty(double base_cost, const vector<double>& rolls);
    int compute_material_cost(const vector<int>& enchantment_cost_by_level, const vector<double>& rolls);
    void removePriceRest(vector<int>& price_by_roll, const vector<double>& percentage_by_cumulative_roll, int index);
};
#endif