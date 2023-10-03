#include "earth.h"
#include "parseNMEA.h"
#include "string"
#include <iostream>

using namespace std;
namespace NMEA
{

  bool isWellFormedSentence(std::string sentence)
  {
      // Stub definition, needs implementing

      //$GP

      bool failed;
      if (sentence.find("$GP") != std::string::npos) {
//        cout << "Here" << endl;
        failed = false;
      } else {
          failed = true;
      }

      // Three letters

      char char1 = sentence[3];
      char char2 = sentence[4];
      char char3 = sentence[5];


      if (isalpha(char1) and isalpha(char2) and isalpha(char3)){
//          cout << "Three letters" << endl;
          failed = false;
      } else {
          failed = true;
      }

      // *
      string starBruh = "*";
      char star = sentence[sentence.size() -3];
      char starTwo = starBruh[0];

      cout << star << endl;
      if (star == starTwo){
          failed = false;
      } else {
          failed = true;
      }

      if (failed == true){
          return false;
      } else {
          return true;
      }
  }

  bool hasValidChecksum(std::string)
  {
      // Stub definition, needs implementing
      return false;
  }

  SentenceData extractSentenceData(std::string)
  {
      // Stub definition, needs implementing
      return {"",{}};
  }

  GPS::Position positionFromSentenceData(SentenceData)
  {
      // Stub definition, needs implementing
      return GPS::Earth::NorthPole;
  }

  Route routeFromLog(std::istream &)
  {
      // Stub definition, needs implementing
      return {};
  }

}
