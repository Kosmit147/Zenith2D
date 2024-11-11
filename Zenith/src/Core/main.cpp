#include <memory>

#include "Zenith/Core/Application.hpp"

using namespace zth;

namespace zth {
extern Application* create_application();
}

int main()
{
    std::unique_ptr<Application> app(create_application());
    app->run();
}
