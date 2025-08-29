#include "crow/app.h"
#include "crow/http_parser_merged.h"
#include "crow/http_request.h"
#include "crow/http_response.h"
#include <crow.h>
#include <cstdlib>
int main() {
  crow::SimpleApp app;
  crow::mustache::set_base("./templates/");
  // variable to store a data  //
  // To Optimize load essentioal tings to memory

  CROW_ROUTE(app, "/assets/<path>")
  ([](const crow::request &req, crow::response &res, std::string path) {
    res.set_static_file_info_unsafe("assets/" + path);
    res.end();
  });

  CROW_ROUTE(app, "/js/<path>")
  ([](const crow::request &req, crow::response &res, std::string path) {
    res.set_static_file_info_unsafe("js/" + path);
    res.add_header("Content-Type", "application/javascript");
    res.end();
  });

  CROW_ROUTE(app, "/wasm/<path>")
  ([](const crow::request &req, crow::response &res, std::string path) {
    res.set_static_file_info_unsafe("wasm" + path);
    res.add_header("Content-Type", "application/wasm");
    res.add_header("Cross-Origin-Embedder-Policy", "require-corp");

    res.add_header("Cross-Origin-Embedder-Policy", "same-origin");
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

  CROW_ROUTE(app, "/pong")
  ([]() {
    auto pongpage = crow::mustache::load("pong.html");
    return pongpage.render();
  });
  // will need this later
  //  CROW_ROUTE(app, url)([]() {
  //      auto studiopage = crow::mustache::load("");
  //  return poongpage.render();
  //   })

  const char *port_env = std::getenv("PORT");
  int port = port_env ? std::atoi(port_env) : 18000;
  app.port(port).multithreaded().run();
}
