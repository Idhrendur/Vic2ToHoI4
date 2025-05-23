#ifndef OUT_HOI4_STATES_H
#define OUT_HOI4_STATES_H



#include "src/HOI4World/States/HoI4States.h"



namespace HoI4
{

void outputStates(const States& theStates, const std::filesystem::path& outputName, bool debugEnabled);

}



#endif // OUT_HOI4_STATES_H