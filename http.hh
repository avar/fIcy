/*
 * HTTP/1.0 for streams sockets
 * Copyright(c) 2003-2005 of wave++ (Yuri D'Elia)
 * Distributed under GNU LGPL without ANY warranty.
 */

#ifndef http_hh
#define http_hh

// local headers
#include "socket.hh"

// system headers
#include <vector>
#include <string>


// protocol constants
namespace Http
{
  namespace Proto
  {
    // parameters
    const extern char* proto;
    const extern char* protoTy;
    const extern char* version;
    const size_t hdrLen = 1024;
    const extern char* endl;
    const size_t endlSz = 2;

    // requests
    const extern char* get;

    // answers
    const int ok = 200;
    const int found = 302;
    const int other = 303;

    // headers we parse
    const extern char* location;
  }


  // some useful typedefs
  typedef std::vector<std::string> Header;

  // HTTP transport reply
  struct Reply
  {
    Reply(Header* headers = NULL)
    : headers(headers)
    {}

    // necessary data
    std::string proto;
    int code;
    std::string description;

    // optional headers
    Header* headers;
  };


  // interface
  class Http
  {
    char* host;
    in_addr_t addr;
    int port;

    // http functions
    int
    getSrvPort();

    void
    readReply(Socket& s, Reply& reply);


  protected:
    // generic operations
    Socket*
    gen(const char* act, const char* path, Reply& reply,
	const Header* headers = NULL);


  public:
    // de/constructors
    Http(const char* host, const int port = 0);
    ~Http();

    // basic functionality
    Socket*
    get(const char* file, Reply& reply, const Header* headers = NULL);
  };
}

#endif
