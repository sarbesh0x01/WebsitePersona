#include "crow/app.h"
#include "crow/http_response.h"
#include "crow/mustache.h"
#include <crow.h>
int main() {

  crow::SimpleApp app;
      crow::mustache::set_base("./templates/");
  // variable to store a data  //
  // To Optimize load essentioal tings to memory
  CROW_ROUTE(app, "/<string>")
  ([](std::string name) {
    auto page = crow::mustache::load(
        "index.html");
    // res.set_static_file_info(
    //     "/home/sarbesh/Projects/WebsiteDevelopment/index.html");
    //  res.set_header("content-type", "text/html");
    // res.end();
    // return (200, "text/html", "data");
    crow::mustache::context ctx({{"person", name}});
    return page.render(ctx);
  });

  app.port(18000).run();
}


