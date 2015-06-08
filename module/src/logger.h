/**
 * @author Behzad Tabibian
 */
 
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H
#include <alcore/alptr.h>
#include <boost/archive/text_iarchive.hpp>
#include <alcommon/almodule.h>
#include "../../common/TcpListener.h"
#include <alproxies/almotionproxy.h>
#include <alproxies/alsonarproxy.h>
#include <boost/thread.hpp>
//#include "../../common/message.h"
#define DEBUG_CONFIG
struct Element
{
  std::string element_add;
  std::string element_tag;
};

namespace AL
{
  class ALBroker;
}

/**
 * Logger Module main class continuesly checking variuos memory variables and sends them to subscribed parties.
 */


class Logger : public AL::ALModule
{

  public:

    /**
     * Default Constructor.
     */
     Logger(AL::ALPtr<AL::ALBroker> pBroker, const std::string& pName );

    /**
     * Destructor.
     */
    virtual ~Logger();
     /**
      * Initializing Logger.
      */
     void init();
    
  private:
    std::string name;
    tcp_server* _connection;
    void motionLogger();
    void sonarLogger();
    void Observer();    
    bool Loadconfig();
    void customLogger();
    template <typename T>
    void sendLog(T& data);
    AL::ALPtr<AL::ALMemoryProxy> memoryProPtr;
    std::vector<Element> customModules;

#ifdef DEBUG_CONFIG
    AL::ALPtr<AL::ALProxy> mLocalisation;
#endif

    AL::ALPtr<AL::ALMotionProxy> motionProPtr;
    bool motion;
    std::string motionType;
    boost::thread* WorkerThread;
    
    
};

#endif  // LOGGER_LOGGER_H

