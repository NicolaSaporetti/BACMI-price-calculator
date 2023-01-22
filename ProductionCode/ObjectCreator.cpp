#include "ObjectCreator.hpp"
#include "ObjectCreationSummary.hpp"
#include "ObjectRecipe.hpp"
#include "PercentageComputation.hpp"
using namespace std;

ObjectCreationSummary ObjectCreator::calculate_cost_magic_object(const ObjectRecipe& object_recipe)
{
    ObjectCreationSummary object_summary = {};
    object_summary.rolls_required = compute_roll_required(object_recipe.enchantment_levels,object_recipe.caster_level);
    object_summary.days_to_create = adjust_price_based_on_difficulty(compute_days_to_create(object_recipe.total_cost), object_summary.rolls_required);
    object_summary.material_cost = compute_material_cost(object_recipe.enchantment_cost_by_level, object_summary.rolls_required);
    object_summary.labor_cost = compute_labor_cost(object_recipe.caster_level, (object_summary.material_cost/object_recipe.total_cost)*compute_days_to_create(object_recipe.total_cost));
    object_summary.total_cost = object_summary.material_cost+object_summary.labor_cost;
    return object_summary;
}

vector<double> ObjectCreator::compute_roll_required(const vector<int>& enchantment_levels, int caster_level)
{
    vector<double> rolls;
    PercentageComputation percentage_computation;
    for(size_t idx=0; idx<enchantment_levels.size(); idx++) rolls.push_back(percentage_computation.success_chance(caster_level,enchantment_levels[idx]));
    return rolls;
}

double ObjectCreator::adjust_price_based_on_difficulty(double base_cost, const vector<double>& rolls)
{
    for(const auto& roll : rolls) base_cost/=roll;
    return base_cost;
}

int ObjectCreator::compute_days_to_create(int base_cost)
{
    const int base_days = 7;
    int days_to_create = base_cost/1000+((base_cost%1000!=0)? 1 : 0);
    return base_days + days_to_create;
}

double ObjectCreator::compute_material_cost(const vector<int>& enchantment_cost_by_level, const vector<double>& rolls)
{
    vector<double> price_by_roll(rolls.size()+1,0);
    vector<double> percentage_by_cumulative_roll(rolls.size()+1,0);
    vector<double> cumulative_enchantment_cost;
    for(int i=0;i<rolls.size();i++) cumulative_enchantment_cost.push_back(static_cast<double>(enchantment_cost_by_level[i]));
    for(int i=1;i<rolls.size();i++) cumulative_enchantment_cost[i]+=cumulative_enchantment_cost[i-1];
    double percentage = 1.0;
    double percentageLeft = 1.0;
    for(int i=0;i<rolls.size();i++)
    {
        percentage*=static_cast<double>(1.0-rolls[i]);
        percentage_by_cumulative_roll[i]=percentage;
        percentageLeft-=percentage;
        percentage_by_cumulative_roll[i+1]=percentageLeft;
        price_by_roll[i+1]=adjust_price_based_on_difficulty(cumulative_enchantment_cost[i],{percentage_by_cumulative_roll[i+1]});
        removePriceRest(price_by_roll,percentage_by_cumulative_roll,i);
        percentage = percentageLeft;
    }
    return price_by_roll[rolls.size()];
}

void ObjectCreator::removePriceRest(vector<double>& price_by_roll, const vector<double>& percentage_by_cumulative_roll, int index)
{
    for(int i=0;i<index;i++)
    {
        double numberCreated = percentage_by_cumulative_roll[i+1]/percentage_by_cumulative_roll[index+1];
        price_by_roll[index+1]-=price_by_roll[i+1]*numberCreated;
    }
}

double ObjectCreator::compute_labor_cost(int caster_level, double days_to_create)
{
    const int day_in_a_month = 28;
    const double cost_by_level = 500.0;
    double daily_cost = (cost_by_level*caster_level)/day_in_a_month;
    return days_to_create*daily_cost;
}