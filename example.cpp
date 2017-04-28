#include <iostream>

#include <cpr/cpr.h>
#include <json.hpp>

using namespace std;

int main(int argc, char** argv) {
    cpr::File newFile = cpr::File{"/home/debian/Desktop/PlaneRecognizer/test/plane.jpg"};
    auto response = cpr::Post(cpr::Url{"http://gateway-a.watsonplatform.net/visual-recognition/api/v3/classify?api_key={}&version=2016-05-20"},cpr::Multipart{{"images_file", newFile}});
    //    auto response = cpr::Post(cpr::Url{"http://httpbin.org/post"},cpr::Multipart{{"images_file", newFile}});
    //auto response = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    auto json = nlohmann::json::parse(response.text);
    std::cout << json.dump(4) << std::endl;
}
