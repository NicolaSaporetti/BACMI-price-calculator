#ifndef ObjectCreationSummary_HPP
#define ObjectCreationSummary_HPP
#include <vector>
using namespace std;

typedef struct ObjectCreationSummary {
    int days_to_create;
    double material_cost;
    double labor_cost;
    double total_cost;
    vector<double> rolls_required;
} ObjectCreationSummary;
#endif