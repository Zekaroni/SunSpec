#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>

#include <libcamera/libcamera.h>

using namespace libcamera;
using namespace std::chrono_literals;

int main()
{
    static std::shared_ptr<Camera> camera;
    std::unique_ptr<CameraManager> cm = std::make_unique<CameraManager>();
    cm->start();
    for (auto const &camera : cm->cameras())
        std::cout << camera->id() << std::endl;
    return 0;
}
