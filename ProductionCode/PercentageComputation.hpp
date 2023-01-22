#ifndef PercentageComputation_HPP
#define PercentageComputation_HPP

using namespace std;

class PercentageComputation {
public:
    double success_chance(int caster_level, int enchantment_levels);
private:
    int compute_helpers(int caster_level);
    double capped_percentage_at_100(double percentage);
};
#endif