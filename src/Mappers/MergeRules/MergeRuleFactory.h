#ifndef MERGE_RULE_FACTORY_H
#define MERGE_RULE_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/MergeRules/MergeRule.h"
#include <memory>



namespace Mappers
{

class MergeRule::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<MergeRule> importMergeRule(std::istream& theStream);

  private:
	std::unique_ptr<MergeRule> mergeRule;
};

} // namespace Mappers



#endif // MERGE_RULE_FACTORY_H