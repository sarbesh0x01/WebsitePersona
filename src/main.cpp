#include "crow/app.h"
#include "crow/http_request.h"
#include "crow/http_response.h"
#include "crow/mustache.h"
#include <crow.h>
#include <cstdlib>
int main() {
  crow::SimpleApp app;
  crow::mustache::set_base("./templates/");
  // variable to store a data  //
  // To Optimize load essentioal tings to memory

  CROW_ROUTE(app, "/static/<path>")
  ([](const crow::request &req, crow::response &res, std::string path) {
    res.set_static_file_info_unsafe("static/" + path);
    res.end();
  });

  CROW_ROUTE(app, "/")
  ([]() {
    auto page = crow::mustache::load("index.html");
    return page.render();
  });
  CROW_ROUTE(app, "/projects")
  ([]() {
    auto projectpage = crow::mustache::load("project.html");
    return projectpage.render();
  });
  const char *port_env = std::getenv("PORT");
  int port = port_env ? std::atoi(port_env) :18000;
  app.port(18000).run();
}
