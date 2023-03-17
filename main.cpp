#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <string>
#include <iostream>
#include <memory>
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int main() 
{
    auto fileStream = std::make_shared<ostream>();
    // Open stream to output file.
	auto requestTask = fstream::open_ostream("token.ubx")
    .then([=](ostream outFile) {
        *fileStream = outFile;
        http_client client("http://online-live1.services.u-blox.com");
            pplx::task<web::http::http_response> resp = client.request(
		web::http::methods::GET, U("/GetOnlineData.ashx?token=WthGYmMETUOJEt1tQmnNZg;gnss=gps,glo;datatype=eph"));
        // attached a handler to be invoked when resp.is_done() is true
        pplx::task<void> jv = resp.then([=]
        (pplx::task<web::http::http_response> task) {
            web::http::http_response response = task.get();

            // Check the status code.
            if (response.status_code() != 200) {
                throw std::runtime_error("Returned " + 
                    std::to_string(response.status_code()));
            }
            std::cout << "Returned " + 
                std::to_string(response.status_code()) << std::endl;

            response.body().read_to_end(fileStream->streambuf()).wait();
 
            // Close the file.
            fileStream->close();
        });
        jv.then([=](){
                std::cout << "Done reading file!" << std::endl;
            });

        // Wait until json value is ready
        try {
            jv.wait();
        }
        catch (const std::exception & e) {
            printf("Error exception:%s\n", e.what());
        }
    });

    // Wait until json value is ready
	try {
		requestTask.wait();
	}
	catch (const std::exception & e) {
		printf("Error exception:%s\n", e.what());
	}

    return 0;
}