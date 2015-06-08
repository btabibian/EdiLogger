#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <vector>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "tcp_connection_serialized.h"
#ifndef _TCPLISTENER_
#define _TCPLISTENER_
namespace tcplib =boost::asio;
/**
 * This class provides functionalities for communicationg with a sigle client.
 */
class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
     /**
      * shared pointer type for connection.
      */
    typedef boost::shared_ptr<tcp_connection> tcp_connection_pointer;
     /**
      * Creates and instance of connection using supplied io_service
      */
    static tcp_connection_pointer create(boost::asio::io_service& io_service);
    /**
     * writes string to the underlying socket.
     */
    bool write(std::string& str);


private:
    tcp_connection(boost::asio::io_service& io_service);
    void handle_write(const boost::system::error_code& ,size_t );
    tcplib::ip::tcp::socket socket_;
    std::string message_;
    tcplib::ip::tcp::socket& socket();
};
 /**
  * This class provides functionalities for sending data to subscribed clients. It also listens to a port number and
  * accepts connection.
  */
class tcp_server
{
private :
    boost::asio::io_service service;
    void handle_accept(tcp_connection_serialized::connection_serialized_ptr new_connection,
                       const boost::system::error_code& error);
    tcplib::ip::tcp::acceptor acceptor_;
    void start_accept();
    int port;
    boost::mutex listLock;
    std::vector<tcp_connection_serialized::connection_serialized_ptr> activeConnections;
    void asyncStart();
    void handle_write(const boost::system::error_code& e, tcp_connection_serialized::connection_serialized_ptr conn);
public:
     /**
      * Creates an instance of tcp_server.
      */
    tcp_server(int port);
    /**
     * Creates an instance of tcp_server using specified port number and boost io_service.
     */
    tcp_server(int port,boost::asio::io_service& service);
     /**
      * Starts listeing to the port provided. this method is blocking.
      */
    void start();
     /**
      * This method starts listening to the port provided in a separate thread.
      */
    void startasync();
    /**
     * Sends a single message to all subscribed parties.
     */
    template <typename T>
    void sendData(const T& data);
};


#endif
