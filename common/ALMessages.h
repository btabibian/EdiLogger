#ifndef  ALMESSAGES_H_
#define ALMESSAGES_H_
#include "LocationMessage.h"
#include "movementMessage.h"
#include "GeneralALMessage.h"
#include <alproxies/almemoryproxy.h>
#include <alcore/alptr.h>
class ALMessages
{
public: 
    //! \brief reads ALLocation from ALMemory
    /*!
     \param ALLocation ALValue representing ALLocation
     \param type type of the message
     \returns returns locationmessage containing the location
    */
    static locationMessage readLocationfromMemory(AL::ALValue ALLocation,std::string type="");
    //! \brief reads Movement from memory
    /*!
     \param ALLocation ALValue representing movement
     \returns returns locationmessage containing the movement
    */
    static movementMessage readMovementfromMemory(AL::ALValue ALLocation);
    //! \brief Writes Location to memory
    /*!
     \param msg location message
     \returns ALValue containing the location.
    */
    static AL::ALValue writeLocationtoMemory(locationMessage msg);
    //! \brief Writes Movement to memory
    /*!
     \param msg movement message to write.
     \returns ALValue containing the movement
    */
    static AL::ALValue writeMovementtoMemory(movementMessage msg);
    //! \brief Writes Generic message to memory
    /*!
     \param msg generic message to write.
     \returns ALValue containing the message.
    */
    static AL::ALValue writeGeneraltoMemory(generalAlMessage msg);
    //! \brief Reads Generic message from memory
    /*!
     \param msg generic message to read.
     \param type type of the message.
     \returns generic message.
    */
    static generalAlMessage readgeneralfromMemory(AL::ALValue ALGMessage,std::string type="");
};
#endif
