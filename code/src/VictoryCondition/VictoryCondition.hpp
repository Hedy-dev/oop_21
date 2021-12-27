#pragma once

#include "ExitCellReachRequirement.hpp"
#include "EnemiesKilledRequirement.hpp"
#include "CollectedItemRequirement.hpp"

template <class... Types>
class VictoryCondition {
public:
    VictoryCondition(Types&... parameters){
        //найдем правило 1
        auto rule1 = reinterpret_cast<ExitCellReachRequirement*>(findRule<ExitCellReachRequirement>(parameters...));
        processRule(rule1);

        //найдем правило 2
        auto rule2 = (EnemiesKilledRequirement*)findRule<EnemiesKilledRequirement>(parameters...);
        processRule(rule2);

        //найдем правило 3
        auto rule3 = (CollectedItemRequirement*)findRule<CollectedItemRequirement>(parameters...);
        processRule(rule3);
    }

    bool rule1 = false;
    short rule2 = 0;
    short rule3 = 0;

    bool getRule1() {
      return rule1;
    }

    short getRule2() {
      return rule2;
    }

    short getRule3() {
      return rule3;
    }

    void processRule(ExitCellReachRequirement* rule) {
        rule1 = rule->descriptionExitCellReachRequirement();
    }

    void processRule(EnemiesKilledRequirement* rule) {
        rule2 = rule->descriptionEnemiesKilledRequirement();
    }

    void processRule(CollectedItemRequirement* rule) {
        rule3 = rule->descriptionCollectedItemRequirement();
    }

    template <class FindRule>
    void* findRule() {
        return nullptr;
    }

    template <class FindRule, class FirstRule, class... OtherRules>
    void* findRule(FirstRule& first_rule, OtherRules&... other_rules)
    {
        if (typeid(first_rule) == typeid(FindRule)) {
            return &first_rule;
        } else {
            return findRule<FindRule>(other_rules...);
        }
    }

    void serialize(std::ofstream& ofs)
    {
        ofs << rule1 << std::endl;
        ofs << rule2 << std::endl;
        ofs << rule3 << std::endl;
    }

    void deserialize(std::ifstream& ifs)
    {
        ifs >> rule1;
        ifs >> rule2;
        ifs >> rule3;
    }
};


