/**
 * @author Behzad Tabibian
 *
 * This file was generated by Aldebaran Robotics ModuleGenerator
 */
 
#ifndef COMMUNICATION_COMCLIENT_H
#define COMMUNICATION_COMCLIENT_H

#include <alcore/alptr.h>
#include <alcommon/almodule.h>
#include <alproxies/almemoryproxy.h>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "tcp_connection_serialized.h"
#include "Message.h"
#include "LocationMessage.h"
#include <fstream>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/config.hpp>

namespace pod=boost::program_options::detail;
namespace AL
{
  class ALBroker;
}
/**
 * This class provides functionality to recieve data from a provider and saves them in ALMemory.
 */
struct CommChannel
{

    typedef boost::shared_ptr<CommChannel> CommChannel_ptr;
private:
    Message data;
    tcp_connection_serialized::connection_serialized_ptr conn;
    AL::ALPtr<AL::ALMemoryProxy> memoryProPtr;
    std::string ip;
    std::string port;
    boost::asio::io_service* srv;

    void networklayer(boost::asio::io_service& serv);
    void reconnect(int count,boost::asio::io_service* serv);
    void handle_read(const boost::system::error_code& e);

public:
    /**
     * Creates an instance of CommChannel using a boost asio io_serivce, ip address and port number
     * to connect and a pointer to device memory
     */
    CommChannel(boost::asio::io_service& service,std::string ip,std::string port,AL::ALPtr<AL::ALMemoryProxy> memoryPtr);
    ~CommChannel();
};

/**
 * communication client module class. This module creates connections to providers and saves data sent by them in device memory.
 */
class comClient : public AL::ALModule
{

  public:

    /**
     * Default Constructor.
     */
     comClient(AL::ALPtr<AL::ALBroker> pBroker, const std::string& pName );

    /**
     * Destructor.
     */
    virtual ~comClient();
    void init();


private:
    bool loadConfig();
    std::vector<CommChannel::CommChannel_ptr> channels;
    boost::asio::io_service service;
    boost::thread* WorkerThread;
    void Observer();
};

#endif  // COMMUNICATION_COMCLIENT_H

