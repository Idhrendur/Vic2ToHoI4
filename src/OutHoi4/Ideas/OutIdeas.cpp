#include "src/OutHoi4/Ideas/OutIdeas.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"
#include "src/HOI4World/Ideas/Ideas.h"
#include <fstream>



void outputIdeologicalIdeas(const std::map<std::string, std::vector<HoI4::IdeaGroup>>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName);
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const std::filesystem::path& outputName);
void outputMonarchIdeas(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const std::filesystem::path& outputName);
void HoI4::outIdeas(const Ideas& ideas,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const std::filesystem::path& outputName)
{
	outputIdeologicalIdeas(ideas.getIdeologicalIdeas(), majorIdeologies, outputName);
	outputGeneralIdeas(ideas.getGeneralIdeas(), outputName);
	outputMonarchIdeas(countries, outputName);
}


void outputIdeologicalIdeas(const std::map<std::string, std::vector<HoI4::IdeaGroup>>& ideologicalIdeas,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName)
{
	std::ofstream ideasFile("output" / outputName / "common/ideas/convertedIdeas.txt");
	ideasFile << "ideas = {\n";
	for (const auto& [ideaCategory, ideaGroups]: ideologicalIdeas)
	{
		ideasFile << "\n";
		ideasFile << "\t" << ideaCategory << " = {\n";
		for (const auto& ideaGroup: ideaGroups)
		{
			for (const auto& idea: ideaGroup.getIdeas())
			{
				ideasFile << "\n";
				ideasFile << idea;
			}
		}
		ideasFile << "\t}\n";
	}
	ideasFile << "}";
	ideasFile.close();
}


std::ofstream openIdeaFile(const std::filesystem::path& fileName);
void closeIdeaFile(std::ofstream& fileStream);
void outputGeneralIdeas(const std::vector<HoI4::IdeaGroup>& generalIdeas, const std::filesystem::path& outputName)
{
	auto manpowerFile = openIdeaFile("output" / outputName / "common/ideas/_manpower.txt");
	auto economicFile = openIdeaFile("output" / outputName / "common/ideas/_economic.txt");
	auto genericFile = openIdeaFile("output" / outputName / "common/ideas/zzz_generic.txt");

	for (const auto& theGroup: generalIdeas)
	{
		if (theGroup.getName() == "mobilization_laws")
		{
			manpowerFile << theGroup;
		}
		else if ((theGroup.getName() == "economy") || (theGroup.getName() == "trade_laws"))
		{
			economicFile << theGroup;
		}
		else
		{
			genericFile << theGroup;
		}
	}

	closeIdeaFile(manpowerFile);
	closeIdeaFile(economicFile);
	closeIdeaFile(genericFile);
}


std::ofstream openIdeaFile(const std::filesystem::path& fileName)
{
	std::ofstream theFile(fileName);
	theFile << "ideas = {\n";
	return theFile;
}


void closeIdeaFile(std::ofstream& fileStream)
{
	fileStream << "}";
	fileStream.close();
}


void outputMonarchIdeas(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const std::filesystem::path& outputName)
{
	std::ofstream monarchFile("output" / outputName / "common/ideas/_monarchs.txt");

	monarchFile << "ideas = {\n";
	monarchFile << "\tcountry = {\n";

	for (const auto& [tag, country]: countries)
	{
		if (!country->hasMonarchIdea())
		{
			continue;
		}

		monarchFile << "\t\t" << tag << "_monarch = {\n";
		monarchFile << "\t\t\tallowed = {\n";
		monarchFile << "\t\t\t\toriginal_tag = " << tag << "\n";
		monarchFile << "\t\t\t}\n";
		monarchFile << "\n";
		monarchFile << "\t\t\tallowed_civil_war = {\n";
		monarchFile << "\t\t\t\toriginal_tag = " << tag << "\n";
		monarchFile << "\t\t\t\thas_government = " << country->getGovernmentIdeology() << "\n";
		monarchFile << "\t\t\t}\n";
		monarchFile << "\n";
		monarchFile << "\t\t\tremoval_cost = -1\n";
		monarchFile << "\n";
		monarchFile << "\t\t\ttraits = { popular_figurehead }\n";
		monarchFile << "\t\t}\n";
	}

	monarchFile << "\t}\n";
	monarchFile << "}";

	monarchFile.close();
}
