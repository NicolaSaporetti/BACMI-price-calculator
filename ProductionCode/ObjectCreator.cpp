#include "ObjectCreator.hpp"
#include "ObjectCreationSummary.hpp"
#include "ObjectRecipe.hpp"
using namespace std;

ObjectCreationSummary ObjectCreator::calculate_cost_magic_object(const ObjectRecipe& object_recipe)
{
    ObjectCreationSummary object_summary = {};
    object_summary.rolls_required = compute_roll_required(object_recipe.enchantment_levels,object_recipe.caster_level);
    object_summary.days_to_create = adjust_price_based_on_difficulty(compute_days_to_create(object_recipe.total_cost), object_summary.rolls_required);
    object_summary.material_cost = compute_material_cost(object_recipe.enchantment_cost_by_level, object_summary.rolls_required);
    object_summary.labor_cost = compute_labor_cost(object_recipe.caster_level, (static_cast<double>(object_summary.material_cost)/object_recipe.total_cost)*compute_days_to_create(object_recipe.total_cost));
    object_summary.total_cost = object_summary.material_cost+object_summary.labor_cost;
    return object_summary;
}

vector<double> ObjectCreator::compute_roll_required(const vector<int>& enchantment_levels, int caster_level)
{
    vector<double> rolls;
    for(size_t idx=0; idx<enchantment_levels.size(); idx++) rolls.push_back(min(compute_percentage(caster_level,enchantment_levels[idx]),1.0));
    return rolls;
}

double ObjectCreator::compute_percentage(int caster_level, int enchantment_levels)
{
    const int intelligence = 18;
    const int meditation = caster_level/5+((caster_level==36)? 1 : 0);
    int result =(intelligence+meditation+compute_helpers(caster_level)+caster_level)*2-enchantment_levels*3;
    return static_cast<double>(result)/100;
}

int ObjectCreator::compute_helpers(int caster_level)
{
    int num_helpers = 0;
    if(caster_level>=9 && caster_level<12) num_helpers=1;
    else if(caster_level>=12 && caster_level<15) num_helpers=2;
    else if(caster_level>=15 && caster_level<20) num_helpers=3;
    else if(caster_level>=20 && caster_level<25) num_helpers=4;
    else num_helpers=5;
    return num_helpers;
}

int ObjectCreator::adjust_price_based_on_difficulty(double base_cost, const vector<double>& rolls)
{
    for(const auto& roll : rolls) base_cost/=roll;
    return static_cast<int>(base_cost);
}

int ObjectCreator::compute_days_to_create(int base_cost)
{
    const int base_days = 7;
    int days_to_create = base_cost/1000+((base_cost%1000!=0)? 1 : 0);
    return base_days + days_to_create;
}

int ObjectCreator::compute_material_cost(const vector<int>& enchantment_cost_by_level, const vector<double>& rolls)
{
    vector<int> price_by_roll(rolls.size()+1,0);
    vector<double> percentage_by_cumulative_roll(rolls.size()+1,0);
    vector<double> object_cost(rolls.size()+1,0);
    vector<int> cumulative_enchantment_cost = enchantment_cost_by_level;
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

void ObjectCreator::removePriceRest(vector<int>& price_by_roll, const vector<double>& percentage_by_cumulative_roll, int index)
{
    for(int i=0;i<index;i++)
    {
        double numberCreated = percentage_by_cumulative_roll[i+1]/percentage_by_cumulative_roll[index+1];
        price_by_roll[index+1]-=price_by_roll[i+1]*numberCreated;
    }
}

int ObjectCreator::compute_labor_cost(int caster_level, double days_to_create)
{
    const int day_in_a_month = 28;
    const int cost_by_level = 500;
    double daily_cost = (500*caster_level)/day_in_a_month;
    return days_to_create*daily_cost;
}