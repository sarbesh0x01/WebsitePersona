#include "crow/app.h"
#include "crow/http_response.h"
#include "crow/mustache.h"
#include <crow.h>
int main() {

  crow::SimpleApp app;
      crow::mustache::set_base("./templates/");
  // variable to store a data  //
  // To Optimize load essentioal tings to memory
  CROW_ROUTE(app, "/")
  ([]() {
    auto page = crow::mustache::load(
        "index.html");
    return page.render();
  });
  app.port(18000).run();
}


