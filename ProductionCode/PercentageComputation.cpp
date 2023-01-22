#include "PercentageComputation.hpp"
using namespace std;

double PercentageComputation::success_chance(int caster_level, int enchantment_levels)
{
    const int intelligence = 18;
    const int meditation = caster_level/5+((caster_level==36)? 1 : 0);
    int result =(intelligence+meditation+compute_helpers(caster_level)+caster_level)*2-enchantment_levels*3;
    return capped_percentage_at_100(static_cast<double>(result)/100);
}

int PercentageComputation::compute_helpers(int caster_level)
{
    int num_helpers = 0;
    if(caster_level>=9 && caster_level<12) num_helpers=1;
    else if(caster_level>=12 && caster_level<15) num_helpers=2;
    else if(caster_level>=15 && caster_level<20) num_helpers=3;
    else if(caster_level>=20 && caster_level<25) num_helpers=4;
    else num_helpers=5;
    return num_helpers;
}

double PercentageComputation::capped_percentage_at_100(double percentage)
{
    return min(1.0,percentage);
}