#if !defined(__START_MODULE_SERVICE_HPP__)
#define __START_MODULE_SERVICE_HPP__

#include "hal.hpp"

namespace raiju {

class StartModuleService {
public:
    StartModuleService();

    bool is_start();

    void reset();

private:
    hal::GPIO enable;
    hal::GPIO reading;
};

} // namespace raiju

#endif // __START_MODULE_SERVICE_HPP__
