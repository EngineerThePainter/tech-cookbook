#include <iostream>
#include <utility>

#include <Poco/ActiveMethod.h>
#include <Poco/ActiveResult.h>
#include <Poco/BasicEvent.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Delegate.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/ThreadPool.h>
#include <Poco/Timestamp.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

class Source
{
public:
  Poco::BasicEvent<int> event_;

  void callEvent(int n) { event_(this, n); }
};

class Target
{
public:
  void onEvent(const void* sender, int& arg) { std::cout << "onEvent: " << arg << std::endl; }
};

class ActiveAdder
{
public:
  ActiveAdder() : add(this, &ActiveAdder::addImpl) {}

  Poco::ActiveMethod<int, std::pair<int, int>, ActiveAdder> add;

private:
  int addImpl(const std::pair<int, int>& args) { return args.first + args.second; }
};

class TimeRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
  TimeRequestHandler(const std::string& format) : _format(format) {}

  void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override
  {
    Poco::Util::Application& app = Poco::Util::Application::instance();
    app.logger().information("Request from %s", request.clientAddress().toString());

    Poco::Timestamp now;
    std::string dt(Poco::DateTimeFormatter::format(now, _format));
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& ostr = response.send();
    ostr << "<html><head><title>HTTPTimeServer powered by POCO C++ Libraries</title>";
    ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
    ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
    ostr << dt;
    ostr << "</p></body></html>";
  }

private:
  std::string _format;
};

class TimeRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
  TimeRequestHandlerFactory(const std::string& format) : _format(format) {}

  Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
  {
    if (request.getURI() == "/")
      return new TimeRequestHandler(_format);
    else
      return 0;
  }

private:
  std::string _format;
};

class HTTPTimeServer : public Poco::Util::ServerApplication
{
protected:
  void initialize(Application& self)
  {
    loadConfiguration();
    ServerApplication::initialize(self);
  }

  void defineOptions(Poco::Util::OptionSet& options)
  {
    ServerApplication::defineOptions(options);

    options.addOption(Poco::Util::Option("help", "h", "display argument help information")
                          .required(false)
                          .repeatable(false)
                          .callback(Poco::Util::OptionCallback<HTTPTimeServer>(this, &HTTPTimeServer::handleHelp)));
  }

  void handleHelp(const std::string& name, const std::string& value)
  {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A web server that serves the current date and time.");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    _helpRequested = true;
  }

  int main(const std::vector<std::string>& args)
  {
    if (!_helpRequested) {
      unsigned short port = static_cast<unsigned short>(config().getInt("HTTPTimeServer.port", 9980));
      std::string format(config().getString("HTTPTimeServer.format", Poco::DateTimeFormat::SORTABLE_FORMAT));

      Poco::Net::ServerSocket svs(port);
      Poco::Net::HTTPServer srv(new TimeRequestHandlerFactory(format), svs, new Poco::Net::HTTPServerParams);
      srv.start();
      waitForTerminationRequest();
      srv.stop();
    }
    return Application::EXIT_OK;
  }

private:
  bool _helpRequested = false;
};

int main(int argc, char** argv)
{
  // Delegation events example
  Source source;
  Target target;

  source.event_ += Poco::delegate(&target, &Target::onEvent);
  source.callEvent(42);
  source.event_ -= Poco::delegate(&target, &Target::onEvent);

  // Active method example
  ActiveAdder adder;
  Poco::ActiveResult<int> result = adder.add(std::make_pair(3, 4));
  result.wait();
  std::cout << "Active result: " << result.data() << std::endl;

  // Simple HTTP server example
  HTTPTimeServer app;

  return app.run(argc, argv);
}