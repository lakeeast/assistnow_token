#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
using namespace std;
using namespace web; // JSON
using namespace web::http::client;
int main() 
{
    http_client client("http://online-live1.services.u-blox.com");
    pplx::task<web::http::http_response> resp = client.request(
		web::http::methods::GET, U("/GetOnlineData.ashx?token=WthGYmMETUOJEt1tQmnNZg;gnss=gps,glo;datatype=eph"));
    
    // attached a handler to be invoked when resp.is_done() is true
	pplx::task<json::value> jv = resp.then([=]
	(pplx::task<web::http::http_response> task) {
		web::http::http_response response = task.get();

		// Check the status code.
		if (response.status_code() != 200) {
			throw std::runtime_error("Returned " + 
				std::to_string(response.status_code()));
		}
		std::cout << "Returned " + 
			std::to_string(response.status_code())<<endl;

		// Convert the response body to JSON object.
		pplx::task<json::value> jsonObject = response.extract_json();
		return jsonObject;
	});

    // handler to be invoked when json has been extracted
	jv.then([=](json::value jo){
		std:: cout<< "Val:" << jo.serialize() << endl;
	});

	// Wait until json value is ready
	try {
		jv.wait();
	}
	catch (const std::exception & e) {
		printf("Error exception:%s\n", e.what());
	}  
     
    return 0;
}