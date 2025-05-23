#include "src/OutHoi4/OutLocalisation.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"
#include <fstream>



void outputLocalisations(const std::filesystem::path& localisationPath,
	 const std::string& filenameStart,
	 const HoI4::languageToLocalisationsMap& localisations)
{
	for (const auto& languageToLocalisations: localisations)
	{
		if (languageToLocalisations.first == "")
		{
			continue;
		}
		std::filesystem::path folder = localisationPath / languageToLocalisations.first;
		std::filesystem::path file = folder / filenameStart;
		file += languageToLocalisations.first + ".yml";
		std::filesystem::create_directories(folder);
		std::ofstream localisationFile(file, std::ios_base::app);
		if (!localisationFile.is_open())
		{
			throw std::runtime_error("Could not update localisation text file");
		}
		localisationFile << "\xEF\xBB\xBF"; // output a BOM to make HoI4 happy
		localisationFile << "l_" << languageToLocalisations.first << ":\n";

		for (const auto& mapping: languageToLocalisations.second)
		{
			localisationFile << " " << mapping.first << ":0 \"" << mapping.second << "\"" << std::endl;
		}
	}
}


void outputStateLocalisations(const std::filesystem::path& localisationPath,
	 const std::map<HoI4::language, std::map<HoI4::stateNumber, std::string>>& stateLocalisations)
{
	for (const auto& languageToLocalisations: stateLocalisations)
	{
		if (languageToLocalisations.first == "")
		{
			continue;
		}
		std::filesystem::path folder = localisationPath / languageToLocalisations.first;
		std::filesystem::path file = folder / "state_names_l_";
		file += languageToLocalisations.first + ".yml";
		std::filesystem::create_directories(folder);
		std::ofstream localisationFile(file, std::ios_base::app);
		if (!localisationFile.is_open())
		{
			throw std::runtime_error("Could not update state localisation text file");
		}
		localisationFile << "\xEF\xBB\xBF"; // output a BOM to make HoI4 happy
		localisationFile << "l_" << languageToLocalisations.first << ":\n";

		for (const auto& mapping: languageToLocalisations.second)
		{
			localisationFile << " STATE_" << mapping.first << ":0 \"" << mapping.second << "\"" << std::endl;
		}
	}
}


void HoI4::outputLocalisation(const Localisation& localisation, const std::filesystem::path& outputName)
{
	Log(LogLevel::Debug) << "Writing localisations";
	const auto localisationPath = "output" / outputName / "localisation";
	if (!commonItems::DoesFolderExist(localisationPath) && !std::filesystem::create_directories(localisationPath))
	{
		throw std::runtime_error("Could not create localisation folder");
	}

	outputLocalisations(localisationPath, "countries_l_", localisation.getCountryLocalisations());
	outputLocalisations(localisationPath, "focus_mod_l_", localisation.getNewFocuses());
	outputStateLocalisations(localisationPath, localisation.getStateLocalisations());
	outputLocalisations(localisationPath, "victory_points_l_", localisation.getVPLocalisations());
	outputLocalisations(localisationPath, "converted_ideas_l_", localisation.getIdeaLocalisations());
	outputLocalisations(localisationPath, "converted_events_l_", localisation.getNewEventLocalisations());
	outputLocalisations(localisationPath, "parties3_l_", localisation.getPoliticalPartyLocalisations());
	outputLocalisations(localisationPath, "decisions3_l_", localisation.getDecisionLocalisations());
	outputLocalisations(localisationPath, "custom_localization_converter_l_", localisation.getCustomLocalisations());
	outputLocalisations(localisationPath,
		 "converted_character_localisation_l_",
		 localisation.getCharacterLocalisations());
}