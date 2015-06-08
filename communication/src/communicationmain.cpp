/**
 * \mainpage
 * \section Author
 * @author Behzad Tabibian
 *
 * \section Copyright
 *  This file is part of Implementation of EdiLogger program.
 *
 *  Implementation of EdiLogger is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Implementation of EdiLogger is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Implementation of EdiLogger.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  University of Edinburgh, hereby disclaims all copyright interest in the program
 *  "EdiLogger".
 */

#include <signal.h>
#include <alcore/alptr.h>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

#include "comclient.h"



#ifdef COMMUNICATION_IS_REMOTE_OFF

#ifdef _WIN32
    #define ALCALL __declspec(dllexport)
#else
    #define ALCALL
#endif
#else
    #define ALCALL
#endif

#ifdef __cplusplus
extern "C"
{
#endif


ALCALL int _createModule( AL::ALPtr<AL::ALBroker> pBroker )
{      
  // init broker with the main broker inctance 
  // from the parent executable
  AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
  AL::ALBrokerManager::getInstance()->addBroker(pBroker);

    
  AL::ALModule::createModule<comClient>( pBroker, "comClient" );


  return 0;
}

ALCALL int _closeModule(  )
{
  return 0;
}

# ifdef __cplusplus
}
# endif

#ifdef COMMUNICATION_IS_REMOTE_ON

int main( int argc, char *argv[] )
{
  // pointer to createModule
  TMainType sig;
  sig = &_createModule;

  // call main
  ALTools::mainFunction("communication",argc, argv,sig);
}
#endif

